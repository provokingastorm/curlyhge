project(CURLY_ENGINE)
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( CURLY_ENGINE_SRC
	curlycore.cpp
	curlycore.h
	curlyengine.cpp
	curlyengine.h
	debugutilities.cpp
	debugutilities.h
	enginesubsystem.cpp
	enginesubsystem.h
	gamesession.cpp
	gamesession.h
	launch.cpp
	vector2d.cpp
	vector2d.h
    )

#------ additional includes ------
include_directories(${HGE_SOURCE_DIR}/include)
include_directories(${HGE_SOURCE_DIR}/src/imgui)

#------ link directories listed ------
link_directories(${HGE_SOURCE_DIR}/linklib)
link_libraries(hge)


#------ target -----
add_library( curlyengine STATIC ${CURLY_ENGINE_SRC} )

if( MSVC )
    SET_TARGET_PROPERTIES( curlyengine PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()
