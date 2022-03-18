cmake_minimum_required(VERSION 3.20)

set(TOOLCHAIN_PREFIX "/home/marco/.local/gcc-arm-none-eabi-10.3-2021.10")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Using toolchain in ${TOOLCHAIN_PREFIX}")

include(cmake/arm-none-eabi.cmake)

project(minimal C)

add_library(cmsis INTERFACE)
target_include_directories(cmsis INTERFACE
        CMSIS/Include
        CMSIS/Device/ST/STM32G0xx/Include
)
target_compile_definitions(cmsis INTERFACE
        STM32G031xx
)

add_library(hal_driver)
target_sources(hal_driver PRIVATE
        STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_exti.c
        STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_gpio.c
        STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_pwr.c
        STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_rcc.c
        STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_utils.c
)
target_include_directories(hal_driver PUBLIC
        STM32G0xx_HAL_Driver/Inc
)
target_link_libraries(hal_driver PUBLIC
        cmsis
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
        src/minimal.c
        src/startup_stm32g03x.c
)
target_include_directories(${PROJECT_NAME} PRIVATE
        STM32G0xx_HAL_Driver/Inc
        CMSIS/Device/ST/STM32G0xx/Include
        CMSIS/Include
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        hal_driver
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
        STM32G031xx
)
#target_compile_options(${PROJECT_NAME} PRIVATE
#        -ffreestanding
#)
#target_link_options(${PROJECT_NAME} PRIVATE
#        -nostdlib
#        -T${CMAKE_CURRENT_LIST_DIR}/minimal.ld
#)
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT} ARGS minimal
        COMMENT "\nResulting size of application:\n"
)