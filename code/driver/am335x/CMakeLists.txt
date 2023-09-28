# Define our target library and an alias for consumers
target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/sdrv_intc_c.c
    ${CMAKE_CURRENT_LIST_DIR}/src/sdrv_intc_s.s
    ${CMAKE_CURRENT_LIST_DIR}/src/sdrv_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/src/sdrv_timer.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
