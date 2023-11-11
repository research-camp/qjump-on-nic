# QJump over NIC queue

Moving high priority packets to the front of the network interface card (aka ```queue jumping```).
The idea of this project comes from a paper called
[__Queues Don’t Matter When You Can JUMP Them!__](https://www.usenix.org/conference/nsdi15/technical-sessions/presentation/grosvenor) that
its focus is on deployable approach to controlling network interference in datacenter networks.

Our goal is to create a kernel module to perform this approach on our local system's __NIC__. In this repository
we present this module's code-base. In the next sections we are going to describe this module by presenting 4
steps that its taking.

## step one (NIC event capturing)

The first step is to capture packets that are inserted into NIC queues. We should capture both
input packets and output packets.

## step two (event management)

Next step is creating a event callback function to be called whenever we capture a packet. This callback
function gets packet data and decides where it belongs to.

## step three (queue reordering)

After callback function is called, we need to reorder our system's NIC queue.

## step four (system logging)

In the final step we log these events into a file for debugging and tracing.

## resources

- [Libpcap](https://www.opensourceforu.com/2011/02/capturing-packets-c-program-libpcap/)
- [Libpcap Linux](https://www.binarytides.com/packet-sniffer-code-c-libpcap-linux-sockets/)
- [Packet sniffer](https://www.binarytides.com/packet-sniffer-code-c-linux/)
