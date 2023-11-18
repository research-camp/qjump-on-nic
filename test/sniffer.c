#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

static struct nf_hook_ops nfho;

unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct iphdr *ip_header;
    struct tcphdr *tcp_header;
    unsigned int data_len;
    unsigned char *data;

    if (!skb) {
        return NF_ACCEPT;
    }

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
