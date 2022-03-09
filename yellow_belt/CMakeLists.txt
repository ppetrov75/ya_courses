cmake_minimum_required(VERSION 3.17)
project(yellow_belt)

set(CMAKE_CXX_STANDARD 14)

add_executable(yellow_belt
#        main.cpp
#        template_print_collection.cpp
#        average_temp.cpp
#        regions_base.cpp
#        task_tracker.cpp
#        sqr_template.cpp
#        get_ref.cpp
#        unit_test_example.cpp
#        print_vector_part.cpp
#        find_greater_elements.cpp
#        split_into_words.cpp
#        remove_duplicates.cpp
#        permutations.cpp
#        gender_stat.cpp
#        merge_sort1.cpp
#        merge_sort2.cpp
#        merge_sort_bench.cpp
#        find_nearest_element.cpp
#        change_firstlast_name.cpp
#        find_start_with_ch.cpp
#        build_exp.cpp
#        eval_exp_shunting_yard.cpp
#        animal.cpp
#        notifier.cpp
#        figures.cpp
        # week6 task's files:
        source_w6/main.cpp
        source_w6/date.cpp source_w6/date.h
        source_w6/database.cpp source_w6/database.h
        source_w6/condition_parser.cpp source_w6/condition_parser.h
        source_w6/token.cpp source_w6/token.h
        source_w6/node.cpp source_w6/node.h
        source_w6/condition_parser_test.cpp
        source_w6/event.cpp source_w6/event.h source_w6/test_runner.cpp source_w6/test_runner.h source_w6/unit_tests.cpp source_w6/unit_tests.h)