cmake_minimum_required(VERSION 3.21.0)

option(PROJECT_USE_VCPKG "Use vcpkg for library dependencies" ON)
option(PROJECT_GIT_SUBMODULE "Update submodules during build" OFF)
if(PROJECT_USE_VCPKG)
  # Optionally update vcpkg submodule (mainly for use by CI)
  include(cmake/UpdateSubmodule.cmake)
  update_submodule("${CMAKE_CURRENT_LIST_DIR}/vcpkg")

  # Configure vcpkg
  include(cmake/ConfigureVcpkg.cmake)
  configure_vcpkg("${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()
set(CMAKE_SYSTEM_PROCESSOR x86)

project(
  hello
  VERSION 0.0.1
  DESCRIPTION "Application to print \"Hello World!\""
  HOMEPAGE_URL https://github.com/dholmes215/cpp-template-2
  LANGUAGES CXX)

# Find dependencies.
if(BUILD_TESTING)
  find_package(Catch2 REQUIRED)
endif()
find_package(fmt REQUIRED)

# Targets can "link" this "library" to inherit project options.
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20) # Require _at least_ C++20.

# Targets can "link" this "library" to inherit the warnings specified in CompilerWarnings.cmake.
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Allow for static analysis options.
include(cmake/StaticAnalyzers.cmake)

add_subdirectory(src)

if(BUILD_TESTING)
  include(CTest)
  include(Catch)
  add_subdirectory(tests)
endif()

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

  set(CPACK_PACKAGE_NAME MyProj)
  set(CPACK_PACKAGE_VENDOR MyCompany)
  set(CPACK_PACKAGE_CONTACT "John Doe")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CPack example project")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_VERBATIM_VARIABLES YES)

  # set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_LIST_DIR}/Description.txt) set(CPACK_RESOURCE_FILE_WELCOME
  # ${CMAKE_CURRENT_LIST_DIR}/Welcome.txt) set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_LIST_DIR}/License.txt)
  # set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_LIST_DIR}/Readme.txt)

  if(WIN32)
    set(CPACK_GENERATOR ZIP WIX)
  elseif(APPLE)
    set(CPACK_GENERATOR TGZ productbuild)
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CPACK_GENERATOR TGZ RPM DEB)
  else()
    set(CPACK_GENERATOR TGZ)
  endif()

  include(CPack)
endif()
