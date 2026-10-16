target_sources(kernel
        PRIVATE
        #[[List of .c/.h files for libc]]       
)

add_subdirectory(arch/${ARCH_NAME})
target_include_directories(kernel PRIVATE include)