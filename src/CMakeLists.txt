set ( CMAKE_CXX_STANDARD 20 )

add_executable( ${PROJECT_NAME}
    cellular.cpp
    entity.cpp
    main.cpp
    map.cpp
    random.cpp
    screen.cpp
    tiles.cpp
    vec2d.cpp
)

target_include_directories( ${PROJECT_NAME} PUBLIC ../include )

set( CURSES_NEED_NCURSES TRUE )

find_package( Curses REQUIRED )

target_link_libraries( ${PROJECT_NAME} PRIVATE ${CURSES_LIBRARY} )
