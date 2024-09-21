# Create Docs through Doxygen
message("Generating Doxygen Documentation")

find_package(Doxygen REQUIRED doxygen)

if(DOXYGEN_FOUND)

    set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/docs/Doxyfile.out)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build 
    COMMENT "Generating Doxygen documentation" 
    VERBATIM 
    )
else()
    message("Doxygen not found")
endif()