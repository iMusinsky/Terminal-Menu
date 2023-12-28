cmake_minimum_required(VERSION 3.10)

set(LIB_NAME castom_menu)

set(BUILD_EXAMPLE ON)


set(INCLUDE_PATH include/)

project(${LIB_NAME})

set(SOURCES
    src/main.c
    src/ansi_esc_code.c)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH})

if(${BUILD_EXAMPLE})
    add_subdirectory(example)
endif(${BUILD_EXAMPLE})
