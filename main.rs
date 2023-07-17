use ethtool::{Ethtool, Interface};
use nice::nice;


fn main() {
    // Create an Ethtool instance
    let mut ethtool = Ethtool::new().expect("Failed to create Ethtool instance");

    // Get the list of network interfaces
    let interfaces = ethtool.interfaces().expect("Failed to get network interfaces");

    println!("Processes in NIC Ready Queue:");

    // Iterate over the network interfaces
    for interface in interfaces {
        let queues = ethtool.queues(&interface.name).expect("Failed to get queues");

        // Check if there are any processes in the NIC ready queue
        if let Some(nic_ready_queue) = queues.nic_ready_queue {
            // Print the interface name and the number of processes in the NIC ready queue
            println!(
                "Interface: {}, NIC Ready Queue: {}",
                interface.name, nic_ready_queue
            );

            // Set the process priority to move it to the back of the queue
            if let Err(error) = nice(interface.pid as i32, 10) {
                eprintln!("Failed to adjust process priority: {:?}", error);
            } else {
                println!("Process with PID {} moved to the back of the queue", interface.pid);
            }
        }
    }
}
