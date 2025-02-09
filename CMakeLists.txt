# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(modulo_PWM C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(modulo_PWM modulo_PWM.c)

pico_set_program_name(modulo_PWM "modulo_PWM")
pico_set_program_version(modulo_PWM "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(modulo_PWM 0)
pico_enable_stdio_usb(modulo_PWM 0)

# Add the standard library and hardware PWM library
target_link_libraries(modulo_PWM
    pico_stdlib
    hardware_pwm  # Biblioteca PWM
)

# Add the standard include files to the build
target_include_directories(modulo_PWM PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(modulo_PWM)

pico_add_extra_outputs(modulo_PWM)
