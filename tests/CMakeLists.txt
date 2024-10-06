# Defines utility macros used thoughout tests and aggregates them 

set(this masterTestSuite)

# This macro must be called by all unit tests that want to be a part of the test suite
macro(add_unit_test target target_test)
    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${target_test} PARENT_SCOPE)
    add_test(target ${CMAKE_CURRENT_BINARY_DIR}/${target_test})
endmacro(add_unit_test)

# Define a target that gathers all tests appended though macro @ref add_unit_test
add_custom_target( ${this}
                   DEPENDS ${UNIT_TEST_TARGETS}
)

# Post build step that runs all tests 
add_custom_command(TARGET ${this} 
                   COMMENT "Running all tests"
                   POST_BUILD COMMAND ctest ARGS --output-on-failure
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Subdirectories of unit tests 
add_subdirectory(DebouncerTest)

