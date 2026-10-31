target_sources(kernel
        PRIVATE
        boot.S
)

target_link_options(kernel
        PRIVATE
        -T linker.ld
)