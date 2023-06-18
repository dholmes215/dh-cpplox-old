add_executable(tests lox_tests.cpp)
target_link_libraries(tests PRIVATE project_options project_warnings Catch2::Catch2WithMain lox_lib)

catch_discover_tests(tests)
