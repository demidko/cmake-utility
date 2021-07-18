cmake_minimum_required(VERSION 3.18)
project(utility)
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
# 1. configure any conan dependencies here (all dependencies: https://conan.io/center)
conan_cmake_configure(REQUIRES catch2/2.13.6 spdlog/1.8.5 cpr/1.6.2 threadpool/20140926 simdjson/0.9.6 icu/69.1 GENERATORS cmake_find_package)
conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE . BUILD missing REMOTE conan-center SETTINGS ${settings})
# 2. find dependency here
find_package(Catch2)
find_package(ICU)
find_package(cpr)
find_package(spdlog)
find_package(simdjson)
find_package(ThreadPool)

file(GLOB proj_sources src/*.cpp)
add_executable(app ${proj_sources})
# 3. link dependency with executable app here
target_link_libraries(app PRIVATE ThreadPool::ThreadPool spdlog::spdlog cpr::cpr simdjson::simdjson ICU::io ICU::i18n ICU::uc ICU::data)

#[[Changing the entry point for tests]]
list(FILTER proj_sources EXCLUDE REGEX ".*Main.cpp$")
file(GLOB test_sources test/*.cpp)
add_executable(test ${proj_sources} ${test_sources})
# 4. link dependency with tests here
target_link_libraries(test PRIVATE Catch2::Catch2 ThreadPool::ThreadPool spdlog::spdlog cpr::cpr simdjson::simdjson ICU::io ICU::i18n ICU::uc ICU::data)



