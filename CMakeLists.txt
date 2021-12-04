cmake_minimum_required(VERSION 3.3)
project (suiwallpaper VERSION 1.0.0 DESCRIPTION "a")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(Threads REQUIRED)
set(CMAKE_CXX_FLAGS "/EHsc /W3")
string(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})

set(INC_DIRS
	${PROJECT_SOURCE_DIR}/src
	${GLFW3_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
)

set(LIBS
	${OPENGL_gl_LIBRARY}
	glfw
	${GLM_LIBRARY}
	${GLEW_LIBRARY}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(app "")

target_include_directories(app PRIVATE ${INC_DIRS})

set_target_properties(app PROPERTIES LINK_FLAGS "/INCREMENTAL:NO /SUBSYSTEM:windows /ENTRY:mainCRTStartup")

add_subdirectory(src)

target_link_libraries(app ${LIBS})