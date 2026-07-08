find_package(Qt6 REQUIRED COMPONENTS Test QuickTest)

function(add_lingmo_window_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
        PRIVATE
            Lingmo::Window
            Qt6::Test
    )
    add_test(NAME ${name} COMMAND ${name})
endfunction()

if(Qt6QuickTest_FOUND)
    add_executable(tst_qmlimport
        tst_QmlImport.cpp
    )
    target_link_libraries(tst_qmlimport
        PRIVATE
            Lingmo::Window
            Qt6::QuickTest
    )
    add_test(NAME tst_qmlimport COMMAND tst_qmlimport)
endif()

add_lingmo_window_test(tst_Window)
add_lingmo_window_test(tst_HeaderBar)
