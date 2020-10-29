project(command)

# command
add_executable(command command.cpp)
install(TARGETS command DESTINATION Bahavioral/${PROJECT_NAME})

# command_undo
add_executable(command_undo command_undo.cpp)
install(TARGETS command DESTINATION Bahavioral/${PROJECT_NAME})

# composite_command
add_executable(composite_command composite_command.cpp)
install(TARGETS command DESTINATION Bahavioral/${PROJECT_NAME})
