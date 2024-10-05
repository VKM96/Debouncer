set(this App)

add_executable(${this})

set(app_sources 
${CMAKE_CURRENT_SOURCE_DIR}/Main.c
${CMAKE_CURRENT_SOURCE_DIR}/Debouncer/Debounce.c
)

set(app_includes 
${CMAKE_CURRENT_SOURCE_DIR}/UserConfig.h
${CMAKE_CURRENT_SOURCE_DIR}/Debouncer/Debounce.h
${CMAKE_CURRENT_SOURCE_DIR}/Version/Version.h
)

target_sources(${this} PRIVATE
${app_sources}
${app_includes}
)

target_include_directories(${this} PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/Debouncer 
${CMAKE_CURRENT_SOURCE_DIR}/Version  
)

# Generate Version from this file and save to Version.c 
# Compile the Version utility as a static Library
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Version/Version.c.in ${PROJECT_BINARY_DIR}/Version.c @ONLY)
add_library(VersionLib STATIC ${PROJECT_BINARY_DIR}/Version.c)
target_include_directories(VersionLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Version)

# Link static library to Final application 
target_link_libraries(${this} PRIVATE VersionLib)