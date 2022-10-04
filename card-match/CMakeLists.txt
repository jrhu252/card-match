cmake_minimum_required(VERSION 3.16)
project(card-match)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakeLocal.txt OPTIONAL)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
qt_standard_project_setup()
set(CMAKE_AUTORCC on)

add_executable(card-match main.cpp mainwindow.cpp mainwindow.h mainwindow.ui
               cards.qrc card.cpp card.h cardbutton.cpp cardbutton.h)
target_link_libraries(card-match PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
