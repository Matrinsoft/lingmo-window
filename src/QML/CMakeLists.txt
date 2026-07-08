file(GLOB QML_SRC
    "${CMAKE_SOURCE_DIR}/qml/Lingmo/Window/*.qml"
)
foreach(FILE ${QML_SRC})
    list(APPEND QML_FILES "${FILE}")
    get_filename_component(FNAME "${FILE}" NAME)
    set_source_files_properties("${FILE}" PROPERTIES QT_RESOURCE_ALIAS "${FNAME}")
endforeach()

set(SOURCES
    LingmoWindowPlugin.cpp
)

set(CMAKE_AUTOMOC ON)

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
        Lingmo::LingmoTheme
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

install(TARGETS LingmoWindowQml
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt6/qml/Lingmo/Window
)
