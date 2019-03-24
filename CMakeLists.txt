set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
project(sample_hist)

set(SOURCE_FILES sample_hist.cc)

message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

add_executable(sample_hist ${SOURCE_FILES})
