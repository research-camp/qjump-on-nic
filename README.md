# QJump over NIC queue

In this project we are going to use Rustlang in order to reschedule linux
network interface card processes queue. We are going to send the less important
processes like background processes, docker containers, etc to the back of the queue
so that our user process will get in front.

## steps

For creating this module, we are going to explain each of our steps in order to implement
a complete solution for this problem.

### step.1

First we need to list all of the interfaces that are waiting inside of network interface card.
After that we need to list the process ids in each interface. So the output should be something
like this.

```rust
struct Process {
    id: int,
    priority: int,
    is_background: bool,
    namespace: String,
}
```

### step.2

After we got the processes information, we need to make queue buffers in order to sort them. What
we are going to do is that we create a priority queue for non-background processes and one for
background processes. Then we sort them in each queue. After that we insert them into their
network interface.

```rust
use priority_queue::PriorityQueue;

let mut bg_pq = PriorityQueue::new();
let mut non_bg_pq = PriorityQueue::new();

// insert processes based on their type

for (item, _) in bg_pq.into_sorted_iter() {
    // insert them in interface of nic
}

for (item, _) in non_bg_pq.into_sorted_iter() {
    // insert them in interface of nic
}
```

### step.3

Now that we have a module which implements what we want, we need to use kernel modules
in order to set this module into linux kernel.


### step.4

At the final stage, we need to run this kernel module everytime a new process is being added
to nic queue.
