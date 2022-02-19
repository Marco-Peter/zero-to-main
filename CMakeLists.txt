cmake_minimum_required(VERSION 3.20)

set(TOOLCHAIN_PREFIX "/home/marco/.local/gcc-arm-none-eabi-10.3-2021.10")
message("Using toolchain in ${TOOLCHAIN_PREFIX}")

include(cmake/arm-none-eabi.cmake)

project(minimal C)

add_executable(${PROJECT_NAME})
target_sources(minimal PRIVATE
        src/minimal.c
        src/startup_stm32g03x.c
)
target_include_directories(minimal PRIVATE
        STM32G0xx_HAL_Driver/Inc
        CMSIS/Device/ST/STM32G0xx/Include
        CMSIS/Include
)
target_compile_definitions(minimal PRIVATE
        STM32G031xx
)
target_compile_options(minimal PRIVATE
        -ffreestanding
)
target_link_options(minimal PRIVATE
        -nostdlib
        -T${CMAKE_CURRENT_LIST_DIR}/minimal.ld
)
add_custom_command(TARGET minimal
        POST_BUILD
        COMMAND ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT} ARGS minimal
        COMMENT "\nResulting size of application:\n"
)