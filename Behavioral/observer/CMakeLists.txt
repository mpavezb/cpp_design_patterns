project(observer)

# raw_observer
add_executable(raw_observer raw_observer.cpp)
install(TARGETS raw_observer DESTINATION Behavioral/${PROJECT_NAME})

# boost_observer
add_executable(boost_observer boost_observer.cpp)
install(TARGETS boost_observer DESTINATION Behavioral/${PROJECT_NAME})

# thread_safety
add_executable(thread_safety thread_safety.cpp)
install(TARGETS thread_safety DESTINATION Behavioral/${PROJECT_NAME})
