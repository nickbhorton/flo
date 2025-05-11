cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

project(
    flo 
    LANGUAGES CXX
)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLAD_GL "")

add_subdirectory(glfw)

option(FLO_USE_GLFW_GLAD "Use GLAD from GLFW" ON)

if(FLO_USE_GLFW_GLAD)
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h")
endif()

# IMGUI
include(FetchContent)
FetchContent_Declare(imgui_external
	URL https://github.com/ocornut/imgui/archive/refs/tags/v1.90.8.tar.gz
	EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(imgui_external)

add_library(imgui
	${imgui_external_SOURCE_DIR}/imgui.cpp
	${imgui_external_SOURCE_DIR}/imgui_draw.cpp
	${imgui_external_SOURCE_DIR}/imgui_tables.cpp
	${imgui_external_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_external_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
	${imgui_external_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)
target_include_directories(imgui PUBLIC ${imgui_external_SOURCE_DIR})
target_include_directories(imgui PUBLIC ${imgui_external_SOURCE_DIR}/backends)

# FLO
add_compile_options(
    -g
    -Wall
    -Werror
    -Wextra
)

set(FLO_SOURCE_DIR src)

add_executable(
    flo
    ${FLO_SOURCE_DIR}/entry.cpp
    ${GLAD_GL}
)
target_link_libraries(
    flo
    ${OPENGL_LIBRARIES}
    glfw
    imgui
)
