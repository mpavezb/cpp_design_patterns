project(prototype)

if(NOT TARGET boost::serialization)
  find_package(Boost REQUIRED COMPONENTS serialization)
  add_library(boost::serialization INTERFACE IMPORTED)
  set_target_properties(boost::serialization PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${Boost_SERIALIZATION_LIBRARIES}")
endif()

# motivation
add_executable(motivation motivation.cpp)
install(TARGETS motivation DESTINATION Creational/${PROJECT_NAME})

# prototype
add_executable(prototype prototype.cpp)
install(TARGETS prototype DESTINATION Creational/${PROJECT_NAME})

# prototype_factory
add_executable(prototype_factory prototype_factory.cpp)
install(TARGETS prototype_factory DESTINATION Creational/${PROJECT_NAME})

# prototype_serialization
add_executable(prototype_serialization prototype_serialization.cpp)
target_link_libraries(prototype_serialization boost::serialization)
install(TARGETS prototype_serialization DESTINATION Creational/${PROJECT_NAME})

# exercise
add_executable(prototype_exercise exercise.cpp)
target_link_libraries(prototype_exercise boost::serialization)
install(TARGETS prototype_exercise DESTINATION Creational/${PROJECT_NAME})
