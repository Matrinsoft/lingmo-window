cmake_minimum_required(VERSION 3.21)
project(LingmoWindow VERSION 1.0.0 DESCRIPTION "Lingmo Desktop - Application Window Base Library"
        HOMEPAGE_URL "https://lingmo.org" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(LingmoCompilerSettings)
include(LingmoSanitizers)
include(LingmoPCH)

option(BUILD_TESTING "Build tests" ON)
option(LINGMO_ENABLE_SANITIZERS "Enable sanitizers" OFF)
option(LINGMO_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt6 COMPONENTS Qml Quick Test QUIET)
qt_policy(SET QTP0001 NEW)
find_package(LingmoTheme REQUIRED)

add_subdirectory(src)

if(Qt6Qml_FOUND AND Qt6Quick_FOUND)
    add_subdirectory(src/QML)
endif()

if(BUILD_EXAMPLES AND Qt6Quick_FOUND)
    add_subdirectory(examples)
endif()

if(BUILD_TESTING AND Qt6Test_FOUND)
    enable_testing()
    add_subdirectory(tests)
endif()
