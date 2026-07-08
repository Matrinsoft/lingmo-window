# X11 platform adapter
add_library(LingmoWindow_X11 OBJECT
    X11Adapter.cpp
    X11Adapter.h
)

target_include_directories(LingmoWindow_X11
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include    # for <LingmoWindow/Types.h>
        ${CMAKE_BINARY_DIR}/include    # for generated <LingmoWindow/LingmoWindowExport.h>
        ${CMAKE_CURRENT_SOURCE_DIR}/../..   # src/ — for <platform/WindowAdapter.h>
)

target_link_libraries(LingmoWindow_X11
    PUBLIC
        Qt6::Core
)
