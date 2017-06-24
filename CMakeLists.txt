cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(PROJECT_NAME scab)

project(${PROJECT_NAME} VERSION 0.0.0.1 LANGUAGES CXX)

###################################################
# Set local settings, such as SFML_ROOT in this file
include(local_settings.cmake OPTIONAL)
###################################################

option(SCAB_STATIC "Whether to link statically or not" ON)

if(${APPLE})
  message("Apple")
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++14)
elseif(${MSVC})
  message("MSVC")
  string(REGEX REPLACE "/Z[iI7]" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
  string(REGEX REPLACE "/SAFESEH:(YES|NO)" "" CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
endif()

file(GLOB HDR *.hpp)
file(GLOB SRC *.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
if(${SCAB_STATIC})
  set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2 REQUIRED graphics window system)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
