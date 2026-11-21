target_sources(kernel
        PRIVATE
        kernel/kernel_main.c
        kernel/uart_driver.c
        kernel/exceptionHandler.c
        #[[List of .c/.h files for libc]]       
)

add_subdirectory(arch/${ARCH_NAME})
target_include_directories(kernel PRIVATE include)