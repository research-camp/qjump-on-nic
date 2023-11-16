# Kernel Module Project

## Overview
This project contains a Linux kernel module that intercepts outgoing TCP packets, sorts them based on whether the associated process is in the foreground or background, and prints their information.

## Files
- **your_module.c**: Contains the implementation of the kernel module.
- **packet_functions.h**: Header file declaring function prototypes used in the module.

## Functionality
- **hook_func**: Netfilter hook function that intercepts outgoing packets.
- **insert_packet**: Inserts packets into a queue along with information about whether the associated process is in the foreground or background.
- **compare**: Compares packets based on whether the associated process is in the foreground.
- **process_queue**: Sorts and processes packets based on the foreground/background status of associated processes.

## Building the Module
To build the kernel module, use the provided Makefile:
```bash
make
```

Usage
Inserting the Module:

bash
Copy code
sudo insmod your_module_name.ko
Removing the Module:

bash
Copy code
sudo rmmod your_module_name
Important Notes
Ensure that the Linux kernel headers and build environment are properly set up.
Be cautious when working with kernel modules, as they can affect system stability.
Adjust paths and commands in the Makefile/CMakeLists.txt as needed for your system.
References
Linux Kernel Documentation
Netfilter Documentation
Author
Your Name (Your Email)

License
This project is licensed under the GNU General Public License v2.0.