cmake_minimum_required(VERSION 3.5)

project(desktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Опции для выбора игры
option(TETRIS "Build Tetris model" OFF)
option(SNAKE "Build Snake model" ON)

# Установка исходных файлов
if (TETRIS)
    message(STATUS "Building Tetris Model")
    add_definitions(-DTETRIS)
    set(PROJECT_SOURCES
        ../../brick_game/tetris/tetrisModel.cpp
        ../../brick_game/tetris/tetrisModel.h
        ../../brick_game/tetris/statesTetris.h
        ../../brick_game/tetris/statesTetris.cpp
        ../../brick_game/Common/IGames.h
        ../../_config/config_tetris.h
        main.cpp
        qtview.cpp
        qtview.h
    )
    add_executable(desktop_tetris ${PROJECT_SOURCES})
    target_link_libraries(desktop_tetris PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    set_target_properties(desktop_tetris PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(desktop_tetris)
    endif()
elseif(SNAKE)
    message(STATUS "Building Snake Model")
    add_definitions(-DSNAKE)
    set(PROJECT_SOURCES
        ../../brick_game/snake/snakeModel.cpp
        ../../brick_game/snake/snakeModel.h
        ../../brick_game/snake/statesSnake.cpp
        ../../brick_game/snake/statesSnake.h
        ../../brick_game/Common/IGames.h
        ../../_config/config_snake.h
        main.cpp
        qtview.cpp
        qtview.h
    )
    add_executable(desktop_snake ${PROJECT_SOURCES})
    target_link_libraries(desktop_snake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    set_target_properties(desktop_snake PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(desktop_snake)
    endif()
endif()
