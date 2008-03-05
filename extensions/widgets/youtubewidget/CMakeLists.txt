
set(QT_USE_OPENGL TRUE)
# -> this will cause cmake to include and link against the OpenGL module
include(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
	   ${QT_INCLUDES}
	   ${QT_QTOPENGL_INCLUDE_DIR}
	   ${QT_QTNETWORK_INCLUDE_DIR}
	   ${QT_QTTEST_INCLUDE_DIR}
		 )


SET (plexyyoutubesrc
	youtube.cpp
	youtubewidget.cpp
	videoentity.cpp
		)

add_library (plexyyoutube SHARED ${plexyyoutubesrc})
QT4_AUTOMOC( ${plexyyoutubesrc}) 

#SET_TARGET_PROPERTIES(plexy
#
#	·       ·       PROPERTIES
	#	#	·       ·       COMPILE_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS})
#

TARGET_LINK_LIBRARIES(
	       plexyyoutube
			qtviz
		   ${QT_QTGUI_LIBRARY}
	       ${OPENGL_LIBRARIES}
	       ${QT_QTCORE_LIBRARY}
	       ${QT_QTOPENGL_LIBRARY}
       )

INSTALL(TARGETS plexyyoutube DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/plexyext/)
install(FILES youtube.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/ext/groups/)

add_subdirectory(youtube)