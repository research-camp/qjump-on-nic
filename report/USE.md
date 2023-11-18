# QJUMP Project

## Overview

This project contains a Linux kernel module that intercepts outgoing TCP packets,
sorts them based on whether the associated process is in the foreground or background.

## Files

- **kernel.c**: Contains the implementation of the kernel module.
- **module.h**: Header file declaring function prototypes used in the module.

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

### usage

Inserting the Module:

```sh
sudo insmod kernel.ko
```

Removing the Module:

```sh
sudo rmmod qjump
```

## Important Notes

Ensure that the Linux kernel headers and build environment are properly set up.
Be cautious when working with kernel modules, as they can affect system stability.
Adjust paths and commands in the Makefile/CMakeLists.txt as needed for your system.

## References

- Linux Kernel Documentation
- Netfilter Documentation
