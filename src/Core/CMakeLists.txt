set(PRIVATE_HEADERS
    private/Window_p.h
    private/HeaderBar_p.h
    private/WindowController_p.h
    private/WindowChrome_p.h
    private/WindowEffects_p.h
)

set(SOURCES
    Window.cpp
    WindowController.cpp
    WindowChrome.cpp
    WindowEffects.cpp
    HeaderBar.cpp
    WindowHelper.cpp
    WindowManager.cpp
)

add_library(LingmoWindow SHARED ${SOURCES} ${PRIVATE_HEADERS})
add_library(Lingmo::Window ALIAS LingmoWindow)

target_include_directories(LingmoWindow
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LingmoWindow
    PUBLIC
        Lingmo::LingmoTheme
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

target_compile_definitions(LingmoWindow
    PRIVATE
        LINGMOWINDOW_LIBRARY
)

set_target_properties(LingmoWindow
    PROPERTIES
        SOVERSION 1
        VERSION ${PROJECT_VERSION}
        DEFINE_SYMBOL LINGMOWINDOW_LIBRARY
        OUTPUT_NAME LingmoWindow
)

configure_file(
    "${CMAKE_SOURCE_DIR}/include/LingmoWindow/LingmoWindowExport.h.in"
    "${CMAKE_BINARY_DIR}/include/LingmoWindow/LingmoWindowExport.h"
)

configure_file(
    "${CMAKE_SOURCE_DIR}/include/LingmoWindow/LingmoWindowVersion.h.in"
    "${CMAKE_BINARY_DIR}/include/LingmoWindow/LingmoWindowVersion.h"
)

install(TARGETS LingmoWindow
    EXPORT LingmoWindowTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/LingmoWindow/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LingmoWindow
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*.h.in" EXCLUDE
)

install(FILES
    "${CMAKE_BINARY_DIR}/include/LingmoWindow/LingmoWindowExport.h"
    "${CMAKE_BINARY_DIR}/include/LingmoWindow/LingmoWindowVersion.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LingmoWindow
)

install(EXPORT LingmoWindowTargets
    FILE LingmoWindowTargets.cmake
    NAMESPACE Lingmo::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LingmoWindow
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/LingmoWindowConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/LingmoWindowConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LingmoWindow
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/LingmoWindowConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_BINARY_DIR}/LingmoWindowConfig.cmake"
    "${CMAKE_BINARY_DIR}/LingmoWindowConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LingmoWindow
)
