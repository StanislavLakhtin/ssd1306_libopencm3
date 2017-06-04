cmake_minimum_required(VERSION 3.6)

#Переделать здесь, чтобы не ссылаться на относительные пути для поиска -- некрасиво
file(GLOB USER_SOURCES ./*.c
        )

add_executable(${PROJECT_NAME}.elf ${USER_SOURCES})

target_link_libraries(${PROJECT_NAME}.elf
        opencm3_stm32f1)

add_bin_from_elf(${PROJECT_NAME}.bin ${PROJECT_NAME}.elf)