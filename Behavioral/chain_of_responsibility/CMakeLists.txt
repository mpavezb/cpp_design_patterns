project(chain_of_responsibility)

# pointer chain
add_executable(pointer_chain pointer_chain.cpp)
install(TARGETS pointer_chain DESTINATION Behavioral/${PROJECT_NAME})

# # signal chain
# add_executable(signal_chain signal_chain.cpp)
# install(TARGETS signal_chain DESTINATION Behavioral/${PROJECT_NAME})
