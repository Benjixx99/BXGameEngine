
cmake_minimum_required(VERSION 3.27)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR  "In-source builds are not allowed!")
endif()

if(NOT CREATED_FOLDERS_AND_FILES)
    include("Cmake/CreateFolders.cmake")
    include("Cmake/CreateFiles.cmake")
    set(CREATED_FOLDERS_AND_FILES true CACHE BOOL "Folders and files have been created" FORCE)
endif()

project(BXGameEnigne VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Cmake/Find")

find_package(SQLite3 REQUIRED)
find_package(SFML 2.6 COMPONENTS graphics window audio REQUIRED)
find_package(Qt6 6.6 COMPONENTS Core Gui Widgets REQUIRED)
qt_standard_project_setup()

file(GLOB_RECURSE GAME_ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Sourcefiles/*.cpp")
file(GLOB_RECURSE GAME_ENGINE_HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Headerfiles/*.hpp")
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS        "${CMAKE_SOURCE_DIR}/Game/Sourcefiles/*.cpp")
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS        "${CMAKE_SOURCE_DIR}/Game/Headerfiles/*.hpp")
file(GLOB_RECURSE FORMS CONFIGURE_DEPENDS               "${CMAKE_SOURCE_DIR}/Formfiles/*.ui")

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/Formfiles/")
include_directories("${CMAKE_SOURCE_DIR}/Headerfiles")

qt_add_executable(BXGameEnigne 
    ${GAME_ENGINE_SOURCES} 
    ${GAME_ENGINE_HEADERS}
    ${GAME_SOURCES}
    ${GAME_HEADERS}
    ${FORMS}
)

if(MSVC)
    target_compile_features(BXGameEnigne PUBLIC cxx_std_17)
    target_compile_options(BXGameEnigne PUBLIC "-Zc:__cplusplus")
endif()

target_link_libraries(BXGameEnigne PUBLIC   sfml-graphics
                                            sfml-window
                                            sfml-audio
                                            Qt6::Core
	                                        Qt6::Gui
                                            Qt6::Widgets
                                            ${SQLITE3_LIBRARIES}
)

#set_target_properties(test PROPERTIES WIN32_EXECUTABLE ON) # Disable the console!

message("Build successful!")
