# Define our target library and an alias for consumers
target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/driver_intc.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
