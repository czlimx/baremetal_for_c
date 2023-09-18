cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# Set up the project
project(trycode LANGUAGES C ASM CXX)

# clear not used warning
if(DEFINED _initial_CMAKE_TOOLCHAIN_FILE
   AND NOT _initial_CMAKE_TOOLCHAIN_FILE STREQUAL CMAKE_TOOLCHAIN_FILE)
  #message(WARNING "The CMAKE_TOOLCHAIN_FILE cannot be changed")
elseif(DEFINED CMAKE_TOOLCHAIN_FILE)
  set(_initial_CMAKE_TOOLCHAIN_FILE "${CMAKE_TOOLCHAIN_FILE}" CACHE INTERNAL "")
endif()

# set binary dir
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${RTOS_BOARD}/${RTOS_KERNEL})

# Define our target library and an alias for consumers
add_link_options(-T${CMAKE_CURRENT_LIST_DIR}/example/${RTOS_BOARD}/linker.lds -Wl,-Map=${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.map,--cref)

# Define our target
add_executable(${PROJECT_NAME})

# Pick up the board stuff
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/device/${RTOS_BOARD})

# Pick up the port specific variables and apply them
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/arch/${RTOS_ARCH})

# Pick up the kernel stuff
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tryrtos/${RTOS_KERNEL})

# Pick up the driver stuff
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/driver/${RTOS_CPU})

# Pick up the board stuff
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/example/${RTOS_BOARD}/${RTOS_KERNEL})

# Pick up the libc stuff
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libc)

# post build command
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${PROJECT_NAME}> > ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.dis
)
