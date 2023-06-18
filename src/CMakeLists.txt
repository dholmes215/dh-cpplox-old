add_library(lox_lib chunk.cpp chunk.hpp debug.cpp debug.hpp memory.cpp memory.hpp value.hpp value.cpp vm.cpp vm.hpp)
target_include_directories(lox_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
  lox_lib
  PUBLIC project_options fmt::fmt Microsoft.GSL::GSL
  PRIVATE project_warnings)

if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

add_executable(cpplox main.cpp)
target_link_libraries(cpplox PRIVATE project_options project_warnings lox_lib)

install(TARGETS cpplox RUNTIME_DEPENDENCY_SET deps RUNTIME DESTINATION bin)

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
  install(FILES "$<TARGET_FILE_DIR:hello_app>/cpplox.wasm" "$<TARGET_FILE_DIR:cpplox>/cpplox.js"
          DESTINATION bin)
endif()
