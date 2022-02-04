include_directories(../include)
add_library(lib do_something.cpp  )
add_executable( automake main.cpp  )
target_link_libraries(automake lib  stdc++fs  )
