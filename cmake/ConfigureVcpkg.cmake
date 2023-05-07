include(CMakePrintHelpers)

# Configure CMake to use the vcpkg CMake toolchain file, found in the vcpkg submodule
function(configure_vcpkg VCPKG_TOOLCHAIN_FILE)
  if(NOT EXISTS ${VCPKG_TOOLCHAIN_FILE})
    message(
      WARNING
        "The vcpkg submodule was not found! If using a vcpkg submodule, check that submodule is initialized and updated and try again."
    )
  else()
    if(DEFINED CMAKE_TOOLCHAIN_FILE)
      if(NOT ${VCPKG_TOOLCHAIN_FILE} EQUAL ${CMAKE_TOOLCHAIN_FILE})
        message(STATUS "Non-vcpkg toolchain file will be chainloaded: ${CMAKE_TOOLCHAIN_FILE}")
        set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE
            ${CMAKE_TOOLCHAIN_FILE}
            CACHE FILEPATH "Former value of CMAKE_TOOLCHAIN_FILE to be chain-loaded by vcpkg toolchain" FORCE)
      else()
        message(STATUS "Toolchain is already set to vcpkg toolchain file; chainload file will not be modified.")
      endif()
    else()
      message(STATUS "No toolchain file is set, so it will not be chainloaded.")
    endif()
    set(CMAKE_TOOLCHAIN_FILE
        ${VCPKG_TOOLCHAIN_FILE}
        CACHE FILEPATH "CMake toolchain file" FORCE)
  endif()
endfunction()
