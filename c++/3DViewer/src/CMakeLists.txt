cmake_minimum_required(VERSION 3.5)

project(Viewer3D VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(USE_STATIC "Use static library" ON)

include_directories(${PROJECT_SOURCE_DIR} ./View/include/ ./Controller/include/ ./Geometry/include/)

# set(CMAKE_BUILD_TYPE RELEASE)
find_program(QMAKE_EXECUTABLE qmake) #Если не поможет найти по qmake где лежит QT
if(QMAKE_EXECUTABLE)
    get_filename_component(Qt_DIR ${QMAKE_EXECUTABLE} PATH)
    set(CMAKE_PREFIX_PATH ${Qt_DIR}/lib/cmake)
endif()

if (APPLE)
    set(CMAKE_PREFIX_PATH "PATH/clang_64/lib/cmake") 
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
endif()


add_definitions(-DQT_NO_DEBUG_OUTPUT)

find_library(MYLIBRARY model.a ../build/)
message("--------------------------------------------")
message(lib path = ${MYLIBRARY})
message("--------------------------------------------")
# Найти Qt и нужные компоненты
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core  REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets OpenGL Core  REQUIRED)


#подключение glm
# include(FetchContent)
# FetchContent_Declare(
#     glm
#     GIT_REPOSITORY https://github.com/g-truc/glm.git
#     GIT_TAG 1.0.1 # последняя версия
# )
# FetchContent_MakeAvailable(glm)

#подключение glew
# find_package(GLEW REQUIRED)
# if (NOT GLEW_FOUND)
#     message(STATUS "GLEW не найден, загружаем через FetchContent")
# else()
#     message(STATUS "GLEW найден в системе, используя его")
# endif()

# Установить предпочтение GLVND или Legacy
# set(OpenGL_GL_PREFERENCE GLVND)  # Или можно заменить на LEGACY, если нужно

file(GLOB_RECURSE VIEW_SOURCES 
    View/src/*.cpp
    View/include/*.h
    Controller/include/*.h
    Controller/src/*.cpp
    # QtGifImage/src/gifimage/*.h
    # QtGifImage/src/gifimage/qgifimage.cpp
    # QtGifImage/src/3rdParty/giflib/*.h
)

set(PROJECT_SOURCES
    main.cpp
    ${VIEW_SOURCES}
    View/include/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION  # Указываем, что мы будем завершать финализацию вручную
        ${PROJECT_SOURCES}
        ${GL_FLAG}
    )
    qt_finalize_executable(Viewer3D)
else()
    add_executable(Viewer3D ${PROJECT_SOURCES})
endif()

add_subdirectory(QtGifImage)
set(LINK_LIBRARIES
        QtGifImage::QtGifImage
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBRARIES})
# Указать пути к include и бинарному каталогу
target_include_directories(Viewer3D PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR} ${OPEN_GL_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/QtGifImage/src/gifimage/  ${CMAKE_SOURCE_DIR}/QtGifImage/src/3rdParty/giflib/)
# SET(MYCOMPILE_FLAGS "-fsanitize=address;")
# target_compile_options(View PUBLIC ${MYCOMPILE_FLAGS})
# Линковка библиотек Qt
# target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE  ${MYLIBRARY})
find_package(OpenGL REQUIRED)

if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        Qt6::Widgets 
        Qt6::Core 
        Qt6::OpenGLWidgets 
        QtGifImage::QtGifImage 
        OpenGL::GL
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        Qt5::Widgets 
        Qt5::Core 
        Qt5::OpenGL 
        QtGifImage::QtGifImage 
        OpenGL::GL
    )
endif()
# target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
set_target_properties(${PROJECT_NAME} PROPERTIES
MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
MACOSX_BUNDLE TRUE
WIN32_EXECUTABLE TRUE
)
