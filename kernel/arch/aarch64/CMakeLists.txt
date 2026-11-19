target_sources(kernel
        PRIVATE
        boot.S
        interrupts.S
)

target_link_options(kernel
        PRIVATE
        "-Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
)