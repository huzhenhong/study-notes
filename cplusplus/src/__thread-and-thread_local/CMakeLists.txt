set(target __thread)
add_executable(${target} __thread.cpp)
target_link_libraries(${target} PRIVATE pthread)

set(target thread_local)
add_executable(${target} thread_local.cpp)
target_link_libraries(${target} PRIVATE pthread)