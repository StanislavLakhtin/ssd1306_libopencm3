cmake_minimum_required(VERSION 3.6.0)
project(SSD1306_library)

enable_language(C CXX ASM)

IF(NOT CMAKE_CROSSCOMPILING)
    message(FATAL_ERROR "Cross compiling only. \
            Please use -DCMAKE_TOOLCHAIN_FILE=/PATH/TO/libopencm3.cmake")
ENDIF(NOT CMAKE_CROSSCOMPILING)

add_definitions(-DSTM32F1)

set(LIBOPENCM3_ROOT ${CMAKE_SOURCE_DIR}/lib/libopencm3)

#file(GLOB_RECURSE USER_SOURCES src/*.c)

include_directories(
        ${LIBOPENCM3_ROOT}/include
)

link_directories(
        ${LIBOPENCM3_ROOT}/lib
)

set(NEWLIBS "-lc -lgcc")
set(NEWLIB_SPEC "--specs=nano.specs")

set(STM32F1_ISSUE_602117 "-mfix-cortex-m3-ldrd")
set(CMAKE_ASM_FLAGS "-D__ASSEMBLY__ -D__NEWLIB__ -mcpu=cortex-m3 -mthumb ${STM32F1_ISSUE_602117}")
set(STM32F1_FLAGS "-mcpu=cortex-m3 -mthumb -msoft-float ${STM32F1_ISSUE_602117}")
set(CMAKE_C_FLAGS " \
    ${NEWLIB_SPEC} \
    -Os -g -Wall -Werror -Wredundant-decls -Wstrict-prototypes \
    -fno-common -ffunction-sections -fdata-sections \
    -MD -Wall -Wundef -Werror\
    ${STM32F1_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c++14 ${STM32F1_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS " \
    -T ${CMAKE_SOURCE_DIR}/libopencm3.ld \
     --static -nostartfiles -Wl,--start-group ${NEWLIBS} -Wl,--end-group")

add_custom_target(libopencm3 make WORKING_DIRECTORY ${LIBOPENCM3_ROOT})

function(add_bin_from_elf bin elf)
    add_custom_target(${bin}
            ALL ${CMAKE_OBJCOPY}
            -Obinary ${elf} ${bin} DEPENDS ${elf})
endfunction(add_bin_from_elf)

add_subdirectory(src)
