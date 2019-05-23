project(builder)

# builder
add_executable(builder builder.cpp)
install(TARGETS builder DESTINATION Creational/${PROJECT_NAME})
