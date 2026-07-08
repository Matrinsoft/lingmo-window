add_subdirectory(Core)
add_subdirectory(platform)

# WindowAdapter factory — compiled as part of LingmoWindow, needs access to
# concrete adapter headers from the platform subdirectories.
target_sources(LingmoWindow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/WindowAdapter.cpp
)

target_include_directories(LingmoWindow
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}   # for <platform/WindowAdapter.h>
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/Generic
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/Wayland
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/X11
)
