cmake_minimum_required(VERSION 3.28.0)

project(ButtonDebounce VERSION 1.0.0 LANGUAGES C DESCRIPTION "A collection of Debouncing algorithms suitable for embedded environments")

option(OP_BUILD_APP "Build APP" ON)
message("App build option: ${OP_BUILD_APP}")
if(BUILD_APP)
    add_subdirectory(Src)
endif()

option(OP_BUILD_TESTS "Build Tests" OFF)
message("Test build option: ${OP_BUILD_TESTS}")
if(BUILD_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(external)
    add_subdirectory(tests)
endif()

# Generate Docs through doxygen
option(OP_BUILD_DOCS "Generate Docs" OFF)
message("Documentation generation: ${OP_BUILD_DOCS}")
if(BUILD_DOCS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/docs)
endif()


