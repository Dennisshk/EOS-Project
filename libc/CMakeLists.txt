target_sources(libk
        PRIVATE
        #[[List of .c/.h files for libk]]


        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        #[[List of public header files for libk]]

)
target_compile_definitions(libk PRIVATE __is_libk)
target_include_directories(libk PUBLIC include ../kernel/include)

# Ignore for now!
#target_sources(libc
#        PRIVATE
#        #[[List of .c files for libc]]
#
#        INTERFACE
#        FILE_SET HEADERS
#        BASE_DIRS include
#        FILES
#        #[[List of public header files for libc]]
#
#)
#target_link_libraries(libc PUBLIC libk)
#target_include_directories(libc PUBLIC include)

add_subdirectory(arch/${ARCH_NAME})
