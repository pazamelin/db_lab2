cmake_minimum_required(VERSION 3.5)

project(db_lab2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)
find_package(Qt5WebChannel REQUIRED)
find_package(Qt5Sql REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)


set(SOURCES
    main.cpp
    LoginWindow.cpp
    MainWindow.cpp

    database.cpp
)

set(HEADERS
    LoginWindow.h
    MainWindow.h

    database.h
)

set(INTERFACES
    MainWindow.ui
    LoginWindow.ui
)

set(RESOURCES
    resources.qrc
)

add_executable(db_lab2
   ${SOURCES} ${HEADERS} ${INTERFACES} ${RESOURCES}
)

target_link_libraries(db_lab2
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
            Qt5::Sql
)
