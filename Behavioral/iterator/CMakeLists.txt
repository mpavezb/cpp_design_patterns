project(iterator)

# iterators_in_stl
add_executable(iterators_in_stl iterators_in_stl.cpp)
install(TARGETS iterators_in_stl DESTINATION Bahavioral/${PROJECT_NAME})

# binary_tree_iterator
add_executable(binary_tree_iterator binary_tree_iterator.cpp)
install(TARGETS binary_tree_iterator DESTINATION Bahavioral/${PROJECT_NAME})
