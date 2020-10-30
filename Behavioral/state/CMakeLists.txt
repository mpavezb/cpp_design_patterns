project(state)

# old_school_fsm
add_executable(old_school_fsm old_school_fsm.cpp)
install(TARGETS old_school_fsm DESTINATION Behavioral/${PROJECT_NAME})

# handmade_fsm
add_executable(handmade_fsm handmade_fsm.cpp)
install(TARGETS handmade_fsm DESTINATION Behavioral/${PROJECT_NAME})

# boost_msm
add_executable(boost_msm boost_msm.cpp)
install(TARGETS boost_msm DESTINATION Behavioral/${PROJECT_NAME})
