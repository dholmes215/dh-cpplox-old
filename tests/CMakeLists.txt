add_executable(tests hello_tests.cpp)
target_link_libraries(tests PRIVATE project_options project_warnings Catch2::Catch2WithMain hello)

catch_discover_tests(tests)
