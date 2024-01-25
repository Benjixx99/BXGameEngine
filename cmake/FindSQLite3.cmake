function(add_sqlite3_library library include)
    add_library(SQLITE3::SQLITE3 UNKNOWN IMPORTED)
    set_target_properties(SQLITE3::SQLITE3 PROPERTIES
        IMPORTED_LOCATION ${library}
        INTERFACE_INCLUDE_DIRECTORIES ${include}
    )
    
    set(SQLITE3_FOUND CACHE INTERNAL "SQLite3 found" FORCE)
    set(SQLITE3_LIBRARIES ${library} CACHE STRING "Path to SQLite3 library" FORCE)
    set(SQLITE3_INCLUDES ${include} CACHE STRING "Path to SQLite3 headers" FORCE)

    mark_as_advanced(FORCE SQLITE3_LIBRARIES)
    mark_as_advanced(FORCE SQLITE3_INCLUDES)

    include_directories(${SQLITE3_INCLUDES})
endfunction()

find_path(SQLITE3_INCLUDE NAMES sqlite3.h)
find_library(SQLITE3_LIBRARY NAMES sqlite3)

INCLUDE(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SQLITE3 DEFAULT_MSG SQLITE3_LIBRARY SQLITE3_INCLUDE)

if(SQLITE3_FOUND)
    add_sqlite3_library(${SQLITE3_LIBRARY} ${SQLITE3_INCLUDE})
endif()
