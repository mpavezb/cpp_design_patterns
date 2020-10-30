project(flyweight)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# # flyweight_handmade
# add_executable(flyweight_handmade flyweight_handmade.cpp)
# target_link_libraries(flyweight_handmade ${Boost_LIBRARIES})
# install(TARGETS flyweight_handmade DESTINATION Structural/${PROJECT_NAME})

# flyweight_boost
add_executable(flyweight_boost flyweight_boost.cpp)
target_link_libraries(flyweight_boost pthread)
install(TARGETS flyweight_boost DESTINATION Structural/${PROJECT_NAME})

# flyweight_text
add_executable(flyweight_text flyweight_text.cpp)
target_link_libraries(flyweight_text pthread)
install(TARGETS flyweight_text DESTINATION Structural/${PROJECT_NAME})
