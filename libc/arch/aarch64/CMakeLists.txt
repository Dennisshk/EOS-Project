target_sources(libk
        PRIVATE
        #[[List of .c/.h files for libk]]

        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        #[[List of public header files for libk]]

)

# Ignore for now!
#target_sources(libc
#        PRIVATE
#        #[[List of .c/.h files for libc]]
#
#        INTERFACE
#        FILE_SET HEADERS
#        BASE_DIRS include
#        FILES
#        #[[List of public header files for libc]]
#
#)