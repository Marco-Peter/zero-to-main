cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN arm-none-eabi)
set(TOOLCHAIN_PREFIX "/home/marco/.local/gcc-arm-none-eabi-10.3-2021.10")

if(WIN32)
    set(TOOLCHAIN_EXT ".exe" )
else()
    set(TOOLCHAIN_EXT "" )
endif()

message("Using toolchain in ${TOOLCHAIN_PREFIX}")
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_FLAGS   "-mcpu=cortex-m0plus -mthumb -Wall")
set(CMAKE_CXX_FLAGS "-mcpu=cortex-m0plus -mthumb -Wall")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m0plus -mthumb -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m0plus -mthumb -nostdlib -Wall -Wl,-Map=${CMAKE_PROJECT_NAME}.map")

set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_ASM_FLAGS_DEBUG "-g")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_ASM_FLAGS_RELEASE "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")

set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT})
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT})

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}/${${TOOLCHAIN}})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(LINKER_SCRIPT "minimal.ld")

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
target_link_options(minimal PRIVATE
        "-T${CMAKE_CURRENT_LIST_DIR}/minimal.ld"
)
add_custom_command(TARGET minimal
        POST_BUILD
        COMMAND ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT} ARGS minimal
        COMMENT "\nResulting size of application:\n"
)