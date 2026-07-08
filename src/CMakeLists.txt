add_subdirectory(Core)
add_subdirectory(platform)

# Platform adapter sources — compiled directly as part of LingmoWindow
# (not as OBJECT libraries) to inherit all Qt and project dependencies.
target_sources(LingmoWindow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/WindowAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/Generic/GenericAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/Wayland/WaylandAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/X11/X11Adapter.cpp
)

target_include_directories(LingmoWindow
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}   # for <platform/WindowAdapter.h>
)
