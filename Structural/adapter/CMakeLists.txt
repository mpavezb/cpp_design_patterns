project(adapter)

# adapter_inheritance
add_executable(adapter_inheritance adapter_inheritance.cpp)
install(TARGETS adapter_inheritance DESTINATION Structural/${PROJECT_NAME})

# adapter_external
add_executable(adapter_external adapter_external.cpp)
install(TARGETS adapter_external DESTINATION Structural/${PROJECT_NAME})

# adapter_exercise
add_executable(adapter_exercise adapter_exercise.cpp)
install(TARGETS adapter_exercise DESTINATION Structural/${PROJECT_NAME})
