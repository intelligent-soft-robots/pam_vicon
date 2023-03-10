# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.8)
project(pam_vicon)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# libraries need to be position independent for building Python modules
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wfatal-errors -Werror=return-type)
endif()

include(GNUInstallDirs)

# find dependencies
find_package(ament_cmake REQUIRED)
# add mpi_cmake_modules first as it provides FindX-files for some libraries
find_package(mpi_cmake_modules REQUIRED)

find_package(cli_utils REQUIRED)
find_package(o80 REQUIRED)
find_package(serialization_utils REQUIRED)
find_package(spatial_transformation REQUIRED)
find_package(vicon_transformer REQUIRED)

find_package(fmt REQUIRED)
find_package(pybind11 REQUIRED)
find_package(spdlog REQUIRED)

ament_export_dependencies(fmt spdlog)

ament_python_install_package(${PROJECT_NAME} PACKAGE_DIR ${PROJECT_NAME})


add_executable(compute_tennicam_to_vicon_transform
    src/compute_tennicam_to_vicon_transform.cpp
)
target_include_directories(compute_tennicam_to_vicon_transform PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(compute_tennicam_to_vicon_transform
    Eigen3::Eigen
    spdlog::spdlog
    fmt::fmt
    cli_utils::program_options
    spatial_transformation::transformation
    spatial_transformation::pointcloud
)

## Python Bindings
add_pybind11_module(o80 srcpy/o80.cpp
    LINK_LIBRARIES 
        vicon_transformer::vicon_receiver
        vicon_transformer::vicon_transformer
        o80::o80
        serialization_utils::serialization_utils
)


install(DIRECTORY include/ DESTINATION include)

install(
    TARGETS
        compute_tennicam_to_vicon_transform
    EXPORT export_${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install_scripts(
    scripts/record_tennicam_vicon_trajectory.py

    DESTINATION bin
)


if(BUILD_TESTING)
    find_package(ament_cmake_pytest REQUIRED)
    find_package(ament_cmake_gmock REQUIRED)

    # Python tests
    # Note: The default working directory for tests run by colon is the package root.
    # Python tests that use the C++ bindings need to be run in a different directory,
    # otherwise the local Python source will shadow the installed package and thus the
    # pybind11 modules will be missing.
    ament_add_pytest_test(test_pam_vicon_py tests/test_pam_vicon.py
        WORKING_DIRECTORY /tmp)

endif()


ament_export_interfaces(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_package()
