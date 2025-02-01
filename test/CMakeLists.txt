include(FetchContent)
file(GLOB SOURCES *.cpp)

# Fetch google test framework
message(STATUS "Fetching GoogleTest...")
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/2b6b042a77446ff322cd7522ca068d9f2a21c1d1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

# Setup testing
enable_testing()

add_executable(
  ${PROJECT_NAME}_test
  "test_utils.cpp"
)
target_link_libraries(
  ${PROJECT_NAME}_test
  GTest::gtest_main
  ${PROJECT_NAME}_lib
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
