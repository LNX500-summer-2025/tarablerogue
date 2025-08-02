cmake_minimum_required( VERSION 3.20 )

project( fiddle VERSION 1.0 LANGUAGES CXX )

add_subdirectory( src )

install( TARGETS fiddle
    RUNTIME DESTINATION bin
)
