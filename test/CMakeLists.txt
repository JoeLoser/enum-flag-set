add_executable(test_flag_set
    test_flag_set.cpp
)

target_link_libraries(test_flag_set
    PUBLIC gtest_main
    PUBLIC gmock_main
    PRIVATE Enum-Flag-Set::flagset
)