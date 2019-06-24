project(proxy)

# proxy_property
add_executable(proxy_property proxy_property.cpp)
install(TARGETS proxy_property DESTINATION Structural/${PROJECT_NAME})

# proxy_virtual
add_executable(proxy_virtual proxy_virtual.cpp)
install(TARGETS proxy_virtual DESTINATION Structural/${PROJECT_NAME})

# proxy_communication
add_executable(proxy_communication proxy_communication.cpp)
install(TARGETS proxy_communication DESTINATION Structural/${PROJECT_NAME})

