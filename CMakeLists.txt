## HGE CMake script including HGEHELP and examples
##
project(HGE)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##----------------------------------------
## Edit this to match your configuration
##----------------------------------------

SET(DIRECTX_SDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")

##----------------------------------------
## End of manual configuration section
## try to minimize tampering with code below unless you know how CMake works
##----------------------------------------

add_definitions("-DHGE_UNICODE=${HGE_UNICODE}")
# disable warnings on STD non conformance and security issues
add_definitions(
        "-D_CRT_SECURE_NO_WARNINGS"
        "-D_CRT_NONSTDC_NO_WARNINGS"
        "-D_SCL_SECURE_NO_WARNINGS"
        "-D_WIN32_WINNT=0x0501" "/MP")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${HGE_SOURCE_DIR}/bin CACHE PATH "Single Directory for all executables.")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${HGE_SOURCE_DIR}/bin CACHE PATH "Single Directory for all executables.")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${HGE_SOURCE_DIR}/linklib CACHE PATH "Single Directory for all static libraries.")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)


#---------------------------------
add_subdirectory(src/zlib-1.2.5)
add_subdirectory(src/libPNG)
add_subdirectory(src/imgui)

#--- HGE core library and helpers ---
add_subdirectory(src/helpers)
add_subdirectory(src/core)

#--- curly engine library ---
add_subdirectory(src/curlyengine)

#--- Games ---
add_subdirectory(src/esm)