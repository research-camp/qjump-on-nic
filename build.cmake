cmake_minimum_required(VERSION 3.0)
project(nic_qjump)

set(KERNEL_SOURCE_PATH "/lib/modules/$(shell uname -r)/build")

add_custom_target(build_module
    COMMAND make -C ${KERNEL_SOURCE_PATH} M=${CMAKE_CURRENT_SOURCE_DIR} modules
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building kernel module"
)

add_custom_target(clean_module
    COMMAND make -C ${KERNEL_SOURCE_PATH} M=${CMAKE_CURRENT_SOURCE_DIR} clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Cleaning kernel module"
)

add_custom_target(install_module
    COMMAND sudo insmod nic_qjump.ko
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Installing kernel module"
)

add_custom_target(remove_module
    COMMAND sudo rmmod nic_qjump
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Removing kernel module"
)

add_dependencies(install_module build_module)
add_dependencies(remove_module install_module)
