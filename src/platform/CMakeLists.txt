add_subdirectory(Generic)
add_subdirectory(Wayland)
add_subdirectory(X11)

# Conditionally link the appropriate platform adapter.
# Qt6 defines QT_FEATURE_wayland and QT_FEATURE_xcb when those backends are available.
if(QT_FEATURE_wayland)
    message(STATUS "LingmoWindow: Using Wayland platform adapter")
    target_link_libraries(LingmoWindow PRIVATE LingmoWindow_Wayland)
elseif(QT_FEATURE_xcb)
    message(STATUS "LingmoWindow: Using X11 platform adapter")
    target_link_libraries(LingmoWindow PRIVATE LingmoWindow_X11)
else()
    message(STATUS "LingmoWindow: Using Generic platform adapter (fallback)")
    target_link_libraries(LingmoWindow PRIVATE LingmoWindow_Generic)
endif()
