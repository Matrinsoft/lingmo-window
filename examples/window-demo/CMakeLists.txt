find_package(Qt6 REQUIRED COMPONENTS Quick Qml)

qt_add_executable(window-demo
    main.cpp
    main.qml
)

target_link_libraries(window-demo
    PRIVATE
        Lingmo::Window
        Lingmo::Theme
        Qt6::Quick
        Qt6::Qml
)
