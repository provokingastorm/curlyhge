project(imgui)
cmake_minimum_required(VERSION 2.8)

#------ sources ------
set( IMGUI_SRC
	imconfig.h
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_impl_dx9.cpp
	imgui_impl_dx9.h
	imgui_impl_win32.cpp
	imgui_impl_win32.h
	imgui_internal.h
	imgui_tables.cpp
	imgui_widgets.cpp
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
    )

#------ additional includes ------
include_directories(${HGE_SOURCE_DIR}/include)

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/linklib )

#------ target -----
add_library( imgui STATIC ${IMGUI_SRC} )