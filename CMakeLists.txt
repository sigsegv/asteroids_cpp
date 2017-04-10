cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(PROJECT_NAME scab)

project(${PROJECT_NAME} VERSION 0.0.0.1 LANGUAGES CXX)

##################################################################
# Options for UI
set(SFML_ROOT "NOT_FOUND" CACHE PATH "Folder containing SFML include and lib folders")
option(USE_SFML_STATIC "Whether to statically link SFML or not" ON)
##################################################################

include(local_settings.cmake OPTIONAL)

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

set(INC_FOLDERS ${SFML_ROOT}/include)

set(SFML_LIBS_BASE 
  ${SFML_ROOT}/lib/sfml-graphics
  ${SFML_ROOT}/lib/sfml-window
  #${SFML_ROOT}/lib/sfml-audio
  #${SFML_ROOT}/lib/sfml-main
  #${SFML_ROOT}/lib/sfml-network
  ${SFML_ROOT}/lib/sfml-system
)

foreach(loop_var ${SFML_LIBS_BASE})
  set(SFML_LIBS_SHARED ${SFML_LIBS_STATIC} optimized ${loop_var}.lib)
  set(SFML_LIBS_STATIC ${SFML_LIBS_STATIC} optimized ${loop_var}-s.lib)
  set(SFML_LIBS_STATIC_DEBUG ${SFML_LIBS_STATIC_DEBUG} debug ${loop_var}-s-d.lib)
  set(SFML_LIBS_SHARED_DEBUG ${SFML_LIBS_DEBUG} debug ${loop_var}-d.lib)
endforeach(loop_var)

set(SFML_LIBS_COMMON
  ${SFML_ROOT}/lib/freetype.lib
  ${SFML_ROOT}/lib/jpeg.lib
  opengl32.lib
  winmm.lib
)

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
if(USE_SFML_STATIC)
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBS_STATIC} ${SFML_LIBS_STATIC_DEBUG})
  target_compile_definitions(${PROJECT_NAME} PUBLIC SFML_STATIC)
else()
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBS_SHARED} ${SFML_LIBS_SHARED_DEBUG})
endif()
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS_COMMON})
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_FOLDERS})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
#$<TARGET_FILE_DIR:${PROJECT_NAME}>
