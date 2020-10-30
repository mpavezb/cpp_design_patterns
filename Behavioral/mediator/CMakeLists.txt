project(mediator)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# chat_room
add_executable(chat_room main.cpp Person.cpp ChatRoom.cpp)
install(TARGETS chat_room DESTINATION Behavioral/${PROJECT_NAME})

# soccer_event_broker
add_executable(soccer_event_broker soccer_event_broker.cpp)
target_link_libraries(soccer_event_broker ${Boost_LIBRARIES})
install(TARGETS soccer_event_broker DESTINATION Behavioral/${PROJECT_NAME})
