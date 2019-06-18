project(composite)

# composite_shapes
add_executable(composite_shapes composite_shapes.cpp)
install(TARGETS composite_shapes DESTINATION Structural/${PROJECT_NAME})

## composite_neural_network
#add_executable(composite_neural_network composite_neural_network.cpp)
#install(TARGETS composite_neural_network DESTINATION Structural/${PROJECT_NAME})

# composite_array_backed_prop
add_executable(composite_array_backed_prop composite_array_backed_prop.cpp)
install(TARGETS composite_array_backed_prop DESTINATION Structural/${PROJECT_NAME})

# composite_exercise
add_executable(composite_exercise composite_exercise.cpp)
install(TARGETS composite_exercise DESTINATION Structural/${PROJECT_NAME})
