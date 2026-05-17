cmake_minimum_required(VERSION 3.16)
project(CLionGraphicsKit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(graphics graphics.cpp)

include_directories(include)
link_directories(lib)

target_link_libraries(graphics SDL2 SDL2.dll SDL2main SDL2_ttf SDL2_ttf.dll)

add_executable(CLionGraphicsKit
    main.cpp
    CWidget.cpp
    CButton.cpp
    CBoardWidget.cpp
    CStatusWidget.cpp
    CGameMaster.cpp
        CNextPlayerWidget.hpp
        CNextPlayerWidget.cpp
    CSpinbox.cpp
    CListbox.cpp
)

target_link_libraries(CLionGraphicsKit graphics)
