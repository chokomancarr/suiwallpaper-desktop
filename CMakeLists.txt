cmake_minimum_required(VERSION 3.14)
project (suiwallpaper VERSION 1.0.0 DESCRIPTION "a")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(Threads REQUIRED)

if(MSVC)
	set(CMAKE_CXX_FLAGS "/EHsc /W3")
	string(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
endif()

if(UNIX)
	find_package(X11 REQUIRED)
endif()

set(INC_DIRS
	${PROJECT_SOURCE_DIR}/src
	${GLFW3_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
)

set(LIBS
	OpenGL::GL
	glfw
	${GLM_LIBRARY}
	GLEW::GLEW
)

if(UNIX)
	list(APPEND LIBS X11::X11)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(app WIN32 "")

target_include_directories(app PRIVATE ${INC_DIRS})

if(MSVC)
set_target_properties(app PROPERTIES LINK_FLAGS "/INCREMENTAL:NO /SUBSYSTEM:windows /ENTRY:mainCRTStartup")
endif()

add_subdirectory(src)

target_link_libraries(app ${LIBS})
