project(decorator)

# decorator_dynamic
add_executable(decorator_dynamic decorator_dynamic.cpp)
install(TARGETS decorator_dynamic DESTINATION Structural/${PROJECT_NAME})

# decorator_static
add_executable(decorator_static decorator_static.cpp)
install(TARGETS decorator_static DESTINATION Structural/${PROJECT_NAME})

# decorator_functional
add_executable(decorator_functional decorator_functional.cpp)
install(TARGETS decorator_functional DESTINATION Structural/${PROJECT_NAME})
