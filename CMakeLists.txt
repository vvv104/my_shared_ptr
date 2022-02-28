cmake_minimum_required(VERSION 3.0.0)
project(my_shared_ptr VERSION 0.1.0)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  shared_ptr_test
  shared_ptr_test.cpp
)

target_link_libraries(
  shared_ptr_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(shared_ptr_test)

#add_executable(my_shared_ptr main.cpp)
#set_target_properties(my_shared_ptr PROPERTIES
#            CXX_STANDARD 17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
