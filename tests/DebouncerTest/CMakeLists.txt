#Tests 

set(this DebounceTest)

add_executable(${this} DebouncerTest.c)

set(app_sources 
${CMAKE_CURRENT_SOURCE_DIR}/DebouncerTest.c
${PROJECT_SOURCE_DIR}/Src/Debouncer/Debounce.c
)

set(app_includes 
${PROJECT_SOURCE_DIR}/Src/Debouncer/Debounce.h
)

target_sources(${this} PRIVATE
${app_sources}
${app_includes}
)


target_include_directories(${this} PUBLIC 
${PROJECT_SOURCE_DIR}/Src/Debouncer 
${PROJECT_SOURCE_DIR}/external/Unity/src
)


target_link_libraries(${this}
    Unity
)

add_unit_test(${this}_test ${this})


