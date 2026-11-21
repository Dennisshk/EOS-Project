target_sources(kernel
        PRIVATE
        boot.S
        exceptionVector.S
        generalPurposeRegisters.S
        exceptionHandler.S
)

target_link_options(kernel
        PRIVATE
        "-Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
)