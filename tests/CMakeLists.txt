

setup_target_for_coverage(all_coverage all_checks results)

add_executable(template_checks template_checks.cpp)
set_target_properties(template_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(template_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} mpfr gmp)

add_executable(macro_checks    macro_checks.cpp)
set_target_properties(macro_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(macro_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_executable(trucate_checks  truncate_and_round_checks.cpp)
set_target_properties(trucate_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(trucate_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} error_helper_def)

add_executable(to_fixed_checks  to_fixed_string_checks.cpp)
set_target_properties(to_fixed_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(to_fixed_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} error_helper_def)

add_executable(to_exponent_checks  to_exponent_checks.cpp)
set_target_properties(to_exponent_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(to_exponent_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} error_helper_def)

add_executable(symmetric_error_checks  symmetric_error_checks.cpp)
set_target_properties(symmetric_error_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(symmetric_error_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} error_helper_def symmetric_error )

add_executable(multiple_errors_checks  multiple_errors_checks.cpp)
set_target_properties(multiple_errors_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(multiple_errors_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} symmetric_error error_helper_def)

add_executable(stream_output_checks  stream_output_checks.cpp)
set_target_properties(stream_output_checks PROPERTIES COMPILE_DEFINITIONS "STAND_ALONE")
target_link_libraries(stream_output_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} stream_output_proxy symmetric_error error_helper_def)

#${Boost_LIBRARIES}
#${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY}
#add_definitions( -DBOOST_ALL_NO_LIB )
#add_definitions( -DBOOST_ALL_DYN_LINK )

add_executable(all_checks all_tests.cpp template_checks.cpp macro_checks.cpp truncate_and_round_checks.cpp to_fixed_string_checks.cpp to_exponent_checks.cpp symmetric_error_checks.cpp multiple_errors_checks.cpp stream_output_checks.cpp)
target_link_libraries(all_checks gcov ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} mpfr gmp error_helper_def symmetric_error type)

add_test(NAME template_test          COMMAND template_checks        --show_progress=yes --log_level=all)
add_test(NAME macro_tests            COMMAND macro_checks           --show_progress=yes --log_level=all)
add_test(NAME trucate_tests          COMMAND trucate_checks         --show_progress=yes --log_level=all)
add_test(NAME to_fixed_tests         COMMAND to_fixed_checks        --show_progress=yes --log_level=all)
add_test(NAME to_exponent_tests      COMMAND to_exponent_checks     --show_progress=yes --log_level=all)
add_test(NAME symmetric_error_tests  COMMAND symmetric_error_checks --show_progress=yes --log_level=all)
add_test(NAME multiple_error_tests   COMMAND multiple_errors_checks --show_progress=yes --log_level=all)
add_test(NAME stream_output_tests    COMMAND stream_output_checks   --show_progress=yes --log_level=all)
add_test(NAME all_tests              COMMAND all_checks             --show_progress=yes --log_level=all)

#execute_process(COMMAND dir RESULT_VARIABLE rv)
#message("rv='${rv}'")


##define a macro to simplify adding tests
#macro (do_test arg result)
#  add_test (TutorialComp${arg} Tutorial ${arg})
#  set_tests_properties (TutorialComp${arg}
#    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
#    )
#endmacro (do_test)
#
## do a bunch of result based tests
#do_test (4 "4 is 2")
#do_test (9 "9 is 3")
#do_test (5 "5 is 2.236")
#do_test (7 "7 is 2.645")
#do_test (25 "25 is 5")
#do_test (-25 "-25 is 0")
#do_test (0.0001 "0.0001 is 0.01")




#run all the tests

