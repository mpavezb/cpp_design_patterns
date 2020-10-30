project(memento)

# memento
add_executable(memento memento.cpp)
install(TARGETS memento DESTINATION Behavioral/${PROJECT_NAME})

# undo_redo
add_executable(undo_redo undo_redo.cpp)
install(TARGETS undo_redo DESTINATION Behavioral/${PROJECT_NAME})
