cmake_minimum_required(VERSION 3.27)
set(PROJECT_TITLE "eos-project")
project(${PROJECT_TITLE} LANGUAGES C CXX ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

# Custom Settings
if (NOT DEFINED DEBUG AND DEFINED ENV{DEBUG})
    set(DEBUG "$ENV{DEBUG}" CACHE BOOL "Enable debug code paths" FORCE)
endif()
if (NOT DEFINED HARDWARE_DEBUG AND DEFINED ENV{HARDWARE_DEBUG})
    set(HARDWARE_DEBUG "$ENV{HARDWARE_DEBUG}" CACHE BOOL "Enable hardware debug code paths" FORCE)
    set(DEBUG "$ENV{HARDWARE_DEBUG}" CACHE BOOL "Enable debug code paths" FORCE)
endif()


# Sets compiler options
if (DEBUG OR HARDWARE_DEBUG)
    add_compile_options(-ffreestanding -O0 -g -Wall -Wextra)
else()
    add_compile_options(-ffreestanding -O2 -Wall -Wextra)
endif()
add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions;-fno-rtti;-fno-use-cxa-atexit>") # Only use these for C++ files

# Sets linker options
if (DEBUG OR HARDWARE_DEBUG)
    add_link_options(-ffreestanding -O0 -nostdlib)
else()
    add_link_options(-ffreestanding -O2 -nostdlib)
endif()

# Define executable and libraries and add their subdirectories
add_executable(kernel)
#add_library(libc)
add_library(libk)
add_subdirectory(kernel)
add_subdirectory(libc)

# Includes libraries in the kernel
target_link_libraries(kernel
        PRIVATE
        libk
        gcc
)
set_target_properties(kernel PROPERTIES
        OUTPUT_NAME ${PROJECT_TITLE}
        SUFFIX ".elf"
)
add_custom_command(
        TARGET kernel POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_TITLE}.elf ${PROJECT_TITLE}.img
)

# Apply Settings to Macros
if (HARDWARE_DEBUG)
    target_compile_definitions(kernel PRIVATE HARDWARE_DEBUG=1)
    target_compile_definitions(libk PRIVATE HARDWARE_DEBUG=1)
    #    target_compile_definitions(lib PRIVATE HARDWARE_DEBUG=1)
endif()
if (DEBUG)
    target_compile_definitions(kernel PRIVATE DEBUG=1)
    target_compile_definitions(libk PRIVATE DEBUG=1)
    #    target_compile_definitions(lib PRIVATE DEBUG=1)
endif()