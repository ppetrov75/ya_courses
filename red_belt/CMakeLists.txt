cmake_minimum_required(VERSION 3.17)
project(red_belt)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer  -fbounds-check  -g -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer  -fbounds-check  -fsanitize=undefined,shift,integer-divide-by-zero,signed-integer-overflow,bounds -g -O1")

#find_package(Threads)

add_executable(red_belt
#        w1/main.cpp
#        w1/test_runner.h
#        w1/max_element_if.cpp
#        w1/logger.cpp
#        w1/airline_ticket.h
#        w1/sort_by.cpp
#        w1/update_field.cpp
#        w1/print_values.cpp
#        w1/uniq_id.cpp
#        w1/table.cpp
#        w1/Deque.h w1/DequeTest.cpp
#        w1/paginator.cpp

#        w2/main.cpp
#        w2/sort_students.cpp
#        w2/learner.cpp
#        w2/express_route.cpp
#        w2/read_manager.cpp
#        w2/hotel_book.cpp

        test_runner.h
#        w3/object_pool.cpp
#        w3/swap_sort_copy.cpp
#        w3/simple_vector.cpp w3/simple_vector.h
#        w3/linked_list.cpp

#        w4/main.cpp
#        w4/athlete_numbers.cpp
#        w4/stack_vector.cpp w4/stack_vector.h
#        w4/translator.cpp
#        w4/airport_counter.cpp
#        w4/airport_example.cpp
#        w4/text_editor.cpp
#        w4/server_stats.cpp

#        w5/main.cpp
#        w5/josephus_permutation.cpp
#        w5/group_heavy_strings.cpp
#        w5/simple_vector_copy_assignment.cpp
#        w5/split_into_sentences.cpp
#        w5/simple_vector_2.cpp
#        w5/merge_sort_3.cpp
#        w5/priority_collection_2.cpp
#        w5/async_example.cpp
#        w5/execution_example.cpp
#        w5/matrix_sum.cpp
#        w5/explore_key_words.cpp
#        w5/synchronized.cpp
#        w5/concurrent_map.cpp
        w6/main.cpp w6/parse.cpp w6/search_server.cpp
        w6/profile_advanced.cpp
#        w6/tmp.cpp
        )


target_link_libraries(red_belt pthread tbb)
