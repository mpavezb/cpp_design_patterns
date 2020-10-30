project(mediator)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# chat_room
add_executable(chat_room main.cpp Person.cpp ChatRoom.cpp)
install(TARGETS chat_room DESTINATION Bahavioral/${PROJECT_NAME})
