if(WIN32)
	set(REPARENTSRC ${CMAKE_CURRENT_SOURCE_DIR}/reparent-win.cpp)
elseif(UNIX)
	set(REPARENTSRC ${CMAKE_CURRENT_SOURCE_DIR}/reparent-x11.cpp)
endif()

target_sources(app PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lodepng.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lines.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
	${REPARENTSRC}
)
