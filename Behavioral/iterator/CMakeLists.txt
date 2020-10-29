project(iterator)

# iterators_in_stl
add_executable(iterators_in_stl iterators_in_stl.cpp)
install(TARGETS iterators_in_stl DESTINATION Bahavioral/${PROJECT_NAME})

# binary_tree_iterator
add_executable(binary_tree_iterator binary_tree_iterator.cpp)
install(TARGETS binary_tree_iterator DESTINATION Bahavioral/${PROJECT_NAME})

# requires generator!
# # binary_tree_iterator_coroutines
# add_executable(binary_tree_iterator_coroutines binary_tree_iterator_coroutines.cpp)
# target_compile_options(binary_tree_iterator_coroutines PRIVATE -fcoroutines)
# install(TARGETS binary_tree_iterator_coroutines DESTINATION Bahavioral/${PROJECT_NAME})

# boost_iterator_facade
add_executable(boost_iterator_facade boost_iterator_facade.cpp)
install(TARGETS boost_iterator_facade DESTINATION Bahavioral/${PROJECT_NAME})
