cmake_minimum_required(VERSION 3.10)

project(example)

set(sources
    main.c)

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})
