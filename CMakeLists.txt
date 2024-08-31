cmake_minimum_required(VERSION 3.28.0)

project(ButtonDebounce VERSION 1.0.0 LANGUAGES C)

add_executable(App)

target_sources( App PRIVATE
    ${PROJECT_SOURCE_DIR}/Src/Main.c
    ${PROJECT_SOURCE_DIR}/Src/Debounce.c
    ${PROJECT_SOURCE_DIR}/Src/version.c
)

target_include_directories( App PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
)



