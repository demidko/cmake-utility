cmake_minimum_required(VERSION 3.5)
project(conan-utility)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
add_definitions("-std=c++20")
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_configure(REQUIRES fmt/6.1.2 GENERATORS cmake_find_package)
conan_cmake_configure(REQUIRES cli11/1.9.1 GENERATORS cmake_find_package)
conan_cmake_configure(REQUIRES catch2/2.13.6 GENERATORS cmake_find_package)
conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE . BUILD missing REMOTE conan-center SETTINGS ${settings})
find_package(fmt)
find_package(cli11)
find_package(Catch2)

file(GLOB proj_sources src/*.cpp)
add_executable(proj ${proj_sources})
target_link_libraries(proj PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(proj PRIVATE CLI11::CLI11)

#[[Changing the entry point for tests]]
list(FILTER proj_sources EXCLUDE REGEX ".*Main.cpp$")
file(GLOB test_sources test/*.cpp)
add_executable(test ${proj_sources} ${test_sources})
target_link_libraries(test PRIVATE Catch2::Catch2)
target_link_libraries(test PRIVATE CLI11::CLI11)
target_link_libraries(test PRIVATE fmt::fmt fmt::fmt-header-only)



