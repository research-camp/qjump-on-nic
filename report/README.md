# Project

## section 1

This kernel module uses Netfilter hooks to intercept outgoing TCP packets and print their source and destination IP addresses, source and destination ports, and packet data.

Remember, working with kernel modules requires caution. Ensure you are testing this in an appropriate environment as kernel modules can crash the system if not implemented correctly. Also, the code might need adjustments based on the kernel version and system configuration.

## section 2

To sort the NIC queue's packets based on their PIDs, you'll need to access the process ID (PID) associated with each packet and sort them accordingly. Here's an extended version of the previous code with PID sorting.

This updated code includes:

- insert_packet function: Adds packets along with their PIDs to the packet_queue.
- compare function: Used by qsort to sort the packet queue based on PIDs.
- process_queue function: Sorts and processes the packets in the queue when it's full or at certain intervals.

This module now queues packets with their associated PIDs and sorts them based on PIDs using qsort. Then, it processes and prints the packets in PID-sorted order when the queue reaches its limit or at specific intervals (as defined in process_queue).

## section 3

To prioritize processes that are not running in the background, you'll need to modify the logic to detect whether a process is in the foreground or background. In Linux, the foreground process typically has control of the terminal. You can check this by examining the session ID (sessionid) and the foreground process group ID (tgid).

This code introduces the is_foreground variable, which is set to 1 if the associated process is in the foreground (i.e., not running in the background) based on its control of the terminal. The compare function then sorts the packets based on whether their associated process is in the foreground or background, with foreground processes prioritized.

## section 4

The code provided primarily runs in the top half of the Linux kernel.

The networking code and Netfilter hooks, which intercept packets and execute the associated callback functions (hook_func in this case), primarily operate in the context of the kernel's networking stack. These functions are executed in the context of the current task or process, which generally operates in the context of the top half of the kernel.

The term "top half" and "bottom half" often refer to the division of processing in the Linux kernel:

Top half: This includes the critical processing done in response to hardware interrupts and executes within interrupt context. This context demands a high level of efficiency and has restrictions on what can be executed to prevent delays in handling hardware interrupts.

Bottom half: This refers to deferred processing or tasks that can be delayed, scheduled, or performed asynchronously after the immediate interrupt handling in the top half. These tasks, often implemented as kernel threads, work on deferred work queues and execute when the system is less constrained, allowing for more complex and time-consuming operations.

In the case of the provided code:

The Netfilter hook (hook_func) executes in response to packet processing and happens in the context of the top half.
The packet processing, sorting, and printing of packet information occur within the context of the Netfilter hook and do not involve explicit delegation to bottom-half processing mechanisms.

Keep in mind that kernel networking and packet processing happen within the context of system-level interactions and are managed by the kernel itself. Therefore, the handling of packets and associated callbacks primarily operates within the top half of the kernel, which deals with immediate processing and handling of interrupts and events.
