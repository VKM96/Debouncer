cmake_minimum_required(VERSION 3.28.0)

project(ButtonDebounce VERSION 1.0.0 LANGUAGES C DESCRIPTION "A collection of Debouncing algorithms suitable for embedded environments")

add_executable(App)

target_sources( App PRIVATE
    ${PROJECT_SOURCE_DIR}/Src/Main.c
    ${PROJECT_SOURCE_DIR}/Src/Debounce.c
)

target_include_directories( App PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
)

# Generate Version from this file and save to Version.c 
# Compile the Version utility as a static Library
configure_file(${PROJECT_SOURCE_DIR}/Src/Version.c.in ${PROJECT_BINARY_DIR}/Version.c @ONLY)
add_library(VersionLib STATIC ${PROJECT_BINARY_DIR}/Version.c)
target_include_directories(VersionLib PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# Link static library to Final application 
target_link_libraries(App PRIVATE VersionLib)

# Generate Docs through doxygen
option(BUILD_WITH_DOCS "Generate Docs" OFF)
message("BUILD_WITH_DOCS: ${BUILD_WITH_DOCS}")
if(BUILD_WITH_DOCS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/docs)
endif()


