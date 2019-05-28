project(bridge)

# pimpl_idiom
add_executable(bridge_pimpl_idiom pimpl_idiom.cpp)
install(TARGETS bridge_pimpl_idiom DESTINATION Structural/${PROJECT_NAME})

# bridge
add_executable(bridge bridge.cpp)
install(TARGETS bridge DESTINATION Structural/${PROJECT_NAME})
