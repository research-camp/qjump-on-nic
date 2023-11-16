#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/sched/signal.h>

static struct nf_hook_ops nfho;

struct packet_info {
    struct sk_buff *skb;
    int is_foreground;
};

#define MAX_QUEUE_SIZE 1000
struct packet_info packet_queue[MAX_QUEUE_SIZE];
int queue_index = 0;

static void insert_packet(struct sk_buff *skb, int is_foreground) {
    if (queue_index < MAX_QUEUE_SIZE) {
        packet_queue[queue_index].skb = skb;
        packet_queue[queue_index].is_foreground = is_foreground;
        queue_index++;
    } else {
        printk(KERN_INFO "Packet queue full, dropping packets.\n");
    }
}

static int compare(const void *a, const void *b) {
    return ((struct packet_info *)b)->is_foreground - ((struct packet_info *)a)->is_foreground;
}

static void process_queue(void) {
    if (queue_index > 0) {
        qsort(packet_queue, queue_index, sizeof(struct packet_info), compare);
        for (int i = 0; i < queue_index; i++) {
            struct sk_buff *skb = packet_queue[i].skb;
            struct iphdr *ip_header;
            struct tcphdr *tcp_header;
            unsigned int data_len;
            unsigned char *data;

            ip_header = ip_hdr(skb);

            if (ip_header->protocol == IPPROTO_TCP) {
                tcp_header = tcp_hdr(skb);
                data_len = skb->len - sizeof(struct iphdr) - tcp_header->doff * 4;
                data = (unsigned char *)(tcp_header) + tcp_header->doff * 4;

                printk(KERN_INFO "Captured Packet - Source IP: %pI4, Destination IP: %pI4, Source Port: %d, Destination Port: %d\n",
                       &ip_header->saddr, &ip_header->daddr, ntohs(tcp_header->source), ntohs(tcp_header->dest));

                if (data_len > 0) {
                    printk(KERN_INFO "Data: %.*s\n", data_len, data);
                }
            }

            kfree_skb(skb);
        }
        queue_index = 0;
    }
}

unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct iphdr *ip_header;
    struct tcphdr *tcp_header;
    struct net_device *outdev;
    int is_foreground = 0;

    if (!skb) {
        return NF_ACCEPT;
    }

    ip_header = ip_hdr(skb);
    outdev = skb->dev;

    if (outdev && outdev->type == ARPHRD_ETHER && ip_header->protocol == IPPROTO_TCP) {
        struct task_struct *task = get_current();
        struct pid *pid_struct = get_task_pid(task, PIDTYPE_PID);
        struct task_struct *leader = task->group_leader;

        if (leader->signal->tty != NULL) {
            is_foreground = 1;
        }

        insert_packet(skb, is_foreground);
    }

    process_queue();

    return NF_ACCEPT;
}

static int __init packet_sniffer_init(void) {
    nfho.hook = hook_func;
    nfho.hooknum = NF_INET_POST_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);
    printk(KERN_INFO "Packet sniffer loaded.\n");

    return 0;
}

static void __exit packet_sniffer_exit(void) {
    nf_unregister_net_hook(&init_net, &nfho);
    printk(KERN_INFO "Packet sniffer unloaded.\n");
}

module_init(packet_sniffer_init);
module_exit(packet_sniffer_exit);

MODULE_LICENSE("GPL");
