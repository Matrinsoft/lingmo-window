file(GLOB QML_FILES
    "${CMAKE_SOURCE_DIR}/qml/Lingmo/Window/*.qml"
)

set(SOURCES
    LingmoWindowPlugin.cpp
)

qt_add_qml_module(LingmoWindowQml
    URI Lingmo.Window
    VERSION 1.0
    QML_FILES ${QML_FILES}
    SOURCES ${SOURCES}
    CLASS_NAME LingmoWindowPlugin
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml/Lingmo/Window"
)

target_link_libraries(LingmoWindowQml
    PUBLIC
        Lingmo::Window
        Lingmo::Theme
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

install(TARGETS LingmoWindowQml
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt6/qml/Lingmo/Window
)
