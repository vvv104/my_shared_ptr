cmake_minimum_required(VERSION 3.0.0)
project(my_shared_ptr VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(my_shared_ptr main.cpp)
set_target_properties(my_shared_ptr PROPERTIES
            CXX_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
