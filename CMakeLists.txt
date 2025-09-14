cmake_minimum_required (VERSION 3.26)

project (SFML_CHESS_ENGINE)
set (MY_AUTHORS "Ilya_Kirshtein-Guy_Danin")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME} WIN32)

if (MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/fsanitize=address>)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
endif()

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

include (cmake/Zip.cmake)

set (SFML_LOCATION "C:/SFML/SFML-2.6.0")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

find_package (SFML 2.6 COMPONENTS graphics REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-main sfml-audio)

include (cmake/SFML.cmake)

# --------------------------
# Copy resources and DLLs
# --------------------------

# Folder for the executable
set(EXE_OUTPUT_DIR $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)

# Copy resources folder
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "${EXE_OUTPUT_DIR}"
)

# Copy OpenAL DLL from SFML bin
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_LOCATION}/bin/openal32.dll"
        "${EXE_OUTPUT_DIR}"
)
