project(builder)

# builder
add_executable(builder builder.cpp)
install(TARGETS builder DESTINATION Creational/${PROJECT_NAME})

# fluent interface
add_executable(fluent_builder fluent_builder.cpp)
install(TARGETS fluent_builder DESTINATION Creational/${PROJECT_NAME})

# groovy builder
add_executable(groovy_builder groovy_builder.cpp)
install(TARGETS groovy_builder DESTINATION Creational/${PROJECT_NAME})

# builder facade
add_executable(builder_facade facade/main.cpp facade/Person.cpp facade/PersonBuilder.cpp)
install(TARGETS builder_facade DESTINATION Creational/${PROJECT_NAME})
