cmake_minimum_required(VERSION 3.28.0)

project(ButtonDebounce VERSION 1.0.0 LANGUAGES C DESCRIPTION "A collection of Debouncing algorithms suitable for embedded environments")

add_subdirectory(Src)

# Generate Docs through doxygen
option(BUILD_WITH_DOCS "Generate Docs" OFF)
message("BUILD_WITH_DOCS: ${BUILD_WITH_DOCS}")
if(BUILD_WITH_DOCS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/docs)
endif()


