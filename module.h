#ifndef PACKET_FUNCTIONS_H
#define PACKET_FUNCTIONS_H

#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

struct packet_info {
    struct sk_buff *skb;
    int is_foreground;
};

void insert_packet(struct sk_buff *skb, int is_foreground);
int compare(const void *a, const void *b);
void process_queue(void);
unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state);

#endif /* PACKET_FUNCTIONS_H */
