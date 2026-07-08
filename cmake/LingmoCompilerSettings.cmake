if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /utf-8)
endif()

if(LINGMO_ENABLE_UNITY_BUILD)
    set(CMAKE_UNITY_BUILD ON)
endif()
