add_library(LingmoWindow_Generic OBJECT
    GenericAdapter.cpp
    GenericAdapter.h
)

target_include_directories(LingmoWindow_Generic
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include    # for <LingmoWindow/Types.h>
        ${CMAKE_BINARY_DIR}/include    # for generated <LingmoWindow/LingmoWindowExport.h>
        ${CMAKE_CURRENT_SOURCE_DIR}/../..   # src/ — for <platform/WindowAdapter.h>
)

target_link_libraries(LingmoWindow_Generic
    PUBLIC
        Qt6::Core
)
