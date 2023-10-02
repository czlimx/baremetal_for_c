# Define our target library and an alias for consumers
target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/libc_list.c
    ${CMAKE_CURRENT_LIST_DIR}/src/libc_memory.c
    ${CMAKE_CURRENT_LIST_DIR}/src/libc_printf.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
