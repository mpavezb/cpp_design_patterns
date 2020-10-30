project(singleton)

# singleton
add_executable(singleton singleton.cpp)
install(TARGETS singleton DESTINATION Creational/${PROJECT_NAME})

# singleton_test_issues_and_di
add_executable(singleton_test_issues_and_di singleton_test_issues_and_di.cpp)
install(TARGETS singleton_test_issues_and_di DESTINATION Creational/${PROJECT_NAME})

# singleton_in_di_container
add_executable(singleton_in_di_container singleton_in_di_container.cpp)
install(TARGETS singleton_in_di_container DESTINATION Creational/${PROJECT_NAME})

# singleton_monostate
add_executable(singleton_monostate singleton_monostate.cpp)
install(TARGETS singleton_monostate DESTINATION Creational/${PROJECT_NAME})

# singleton_multiton
add_executable(singleton_multiton singleton_multiton.cpp)
install(TARGETS singleton_multiton DESTINATION Creational/${PROJECT_NAME})

# singleton_exercise
add_executable(singleton_exercise singleton_exercise.cpp)
install(TARGETS singleton_exercise DESTINATION Creational/${PROJECT_NAME})
