add_library(${PROJECT_NAME}_lib STATIC "utils.cpp" "affinity_propagation.cpp")
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
