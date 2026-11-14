
cmake_minimum_required(VERSION 3.22)

project(OfficialCurtyyyZygisk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(
    officialcurtyyy_profiles
    SHARED
    entry.cpp
    app_profiles.cpp
)

target_include_directories(
    officialcurtyyy_profiles
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(
    officialcurtyyy_profiles
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
