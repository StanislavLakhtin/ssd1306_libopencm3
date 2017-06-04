cmake_minimum_required(VERSION 3.6.0)

include(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m3)

SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Find the cross compiler
find_program(ARM_CC arm-none-eabi-gcc
            ${TOOLCHAIN_DIR}/bin)
find_program(ARM_CXX arm-none-eabi-g++
            ${TOOLCHAIN_DIR}/bin)
find_program(ARM_OBJCOPY arm-none-eabi-objcopy
            ${TOOLCHAIN_DIR}/bin)
find_program(ARM_SIZE_TOOL arm-none-eabi-size
            ${TOOLCHAIN_DIR}/bin)
find_program(ARM_AS arm-none-eabi-as
            ${TOOLCHAIN_DIR}/bin)
find_program(ARM_AR arm-none-eabi-ar
            ${TOOLCHAIN_DIR}/bin)


#CMAKE_FORCE_C_COMPILER(${ARM_CC} GNU)
#CMAKE_FORCE_CXX_COMPILER(${ARM_CXX} GNU)

SET(CMAKE_C_COMPILER ${ARM_CC})
SET(CMAKE_CXX_COMPILER ${ARM_CXX})
SET(CMAKE_C_ARCHIVE_CREATE ${ARM_AR})

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)