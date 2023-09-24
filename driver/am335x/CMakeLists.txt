# Define our target library and an alias for consumers
target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/drv_intc_c.c
    ${CMAKE_CURRENT_LIST_DIR}/src/drv_intc_s.s
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
