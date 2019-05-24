project(factory)

# factory method
add_executable(factory_method factory_method.cpp)
install(TARGETS factory_method DESTINATION Creational/${PROJECT_NAME})

# factory
add_executable(factory factory.cpp)
install(TARGETS factory DESTINATION Creational/${PROJECT_NAME})

# inner factory
add_executable(inner_factory inner_factory.cpp)
install(TARGETS inner_factory DESTINATION Creational/${PROJECT_NAME})

# abstract factory
add_executable(abstract_factory abstract/main.cpp)
install(TARGETS abstract_factory DESTINATION Creational/${PROJECT_NAME})

# exercise
add_executable(factory_exercise exercise.cpp)
install(TARGETS factory_exercise DESTINATION Creational/${PROJECT_NAME})
