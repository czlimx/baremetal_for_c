# Define our target library and an alias for consumers
target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_atomic.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_branch_predictor.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_cache.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_context.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_cpu.c
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_exception.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_fpu.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_init.c
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_irq.c
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_mmu.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_tlb.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_pmu.s
	${CMAKE_CURRENT_LIST_DIR}/src/arch_startup.s
    ${CMAKE_CURRENT_LIST_DIR}/src/arch_vectors.s
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)
