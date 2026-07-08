# Wayland platform adapter
add_library(LingmoWindow_Wayland OBJECT
    WaylandAdapter.cpp
    WaylandAdapter.h
)

target_include_directories(LingmoWindow_Wayland
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../..   # src/ — for <platform/WindowAdapter.h>
)
