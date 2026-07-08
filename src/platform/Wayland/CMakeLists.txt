# Wayland platform adapter
add_library(LingmoWindow_Wayland OBJECT
    WaylandAdapter.cpp
    WaylandAdapter.h
)

target_include_directories(LingmoWindow_Wayland
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include    # for <LingmoWindow/Types.h>
        ${CMAKE_BINARY_DIR}/include    # for generated <LingmoWindow/LingmoWindowExport.h>
        ${CMAKE_CURRENT_SOURCE_DIR}/../..   # src/ — for <platform/WindowAdapter.h>
)

target_link_libraries(LingmoWindow_Wayland
    PUBLIC
        Qt6::Core
)
