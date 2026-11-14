
cmake_minimum_required(VERSION 3.18)

project(OfficialCurtyyyZygisk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    officialcurtyyy_profiles
    SHARED
    app_profiles.cpp
    entry.cpp
)

target_compile_options(
    officialcurtyyy_profiles
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
