add_library(hello greeting.cpp greeting.hpp)
target_include_directories(hello INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
  hello
  PUBLIC project_options fmt::fmt
  PRIVATE project_warnings)

if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_executable(hello_app main.cpp)
target_link_libraries(hello_app PRIVATE project_options project_warnings hello)

install(TARGETS hello_app RUNTIME_DEPENDENCY_SET deps RUNTIME DESTINATION bin)

if(NOT EMSCRIPTEN)
  install(
    RUNTIME_DEPENDENCY_SET
    deps
    PRE_EXCLUDE_REGEXES
    [[libc\.so\..*]]
    [[libgcc_s\.so\..*]]
    [[libm\.so\..*]]
    [[libstdc\+\+\.so\..*]]
    [[api-ms-win-.*]]
    [[ext-ms-.*]]
    [[kernel32\.dll]]
    POST_EXCLUDE_REGEXES
    [[.*/system32/.*\.dll]])
endif()

# For WASM builds, CMake thinks the above target is just the .html file, so we need to add the .js and .wasm files
# manually
if(EMSCRIPTEN)
  install(FILES "$<TARGET_FILE_DIR:hello_app>/hello_app.wasm" "$<TARGET_FILE_DIR:hello_app>/hello_app.js"
          DESTINATION bin)
endif()
