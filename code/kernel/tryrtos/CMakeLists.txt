# Define our target library and an alias for consumers
target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/tryrtos_tick.c
    #${CMAKE_CURRENT_LIST_DIR}/src/tryrtos_schedule.c
    ${CMAKE_CURRENT_LIST_DIR}/src/tryrtos_thread.c
    ${CMAKE_CURRENT_LIST_DIR}/src/tryrtos_kernel.c
    #${CMAKE_CURRENT_LIST_DIR}/src/tryrtos_idle.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
