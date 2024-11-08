cmake_minimum_required(VERSION 3.29)
project(CODING)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(CODING
    c/College_Practice/Array_problems_3rd_sem/1D_Array_BinSearch.c
    c/College_Practice/Array_problems_3rd_sem/1D_Array_Delval.c
    c/College_Practice/Array_problems_3rd_sem/1D_Array_EvenOdd_sum.c
    c/College_Practice/Array_problems_3rd_sem/1D_Array_Instval.c
    c/College_Practice/Array_problems_3rd_sem/1D_Array_LinSearch.c
    c/College_Practice/Array_problems_3rd_sem/Array_reverse.c
    c/College_Practice/Array_problems_3rd_sem/Matrix_Addition.c
    c/College_Practice/Array_problems_3rd_sem/Matrix_Multiplication.c
    c/College_Practice/Array_problems_3rd_sem/Matrix_Subtraction.c
    c/College_Practice/C_problems_4th_sem/12-2-23/additionOfTwoMatrices.c
    c/College_Practice/C_problems_4th_sem/12-2-23/arrayCopy.c
    c/College_Practice/C_problems_4th_sem/12-2-23/arrayReversal.c
    c/College_Practice/C_problems_4th_sem/12-2-23/elementFrequencyCountArray.c
    c/College_Practice/C_problems_4th_sem/12-2-23/lengthOfStringCalc.c
    c/College_Practice/C_problems_4th_sem/12-2-23/maxMinNumInArray.c
    c/College_Practice/C_problems_4th_sem/12-2-23/stringCopy.c
    c/College_Practice/C_problems_4th_sem/12-2-23/stringPalindromeCheck.c
    c/College_Practice/C_problems_4th_sem/12-2-23/stringReversal.c
    c/College_Practice/C_problems_4th_sem/12-2-23/swap.c
    c/College_Practice/C_problems_4th_sem/3-3-23/alphabeticalOrderOfNames.c
    c/College_Practice/C_problems_4th_sem/3-3-23/armstrongNumberUsingFunction.c
    c/College_Practice/C_problems_4th_sem/3-3-23/fibonacciSeriesUsingRecursion.c
    c/College_Practice/C_problems_4th_sem/3-3-23/findPowerOfAnyNumRecursion.c
    c/College_Practice/C_problems_4th_sem/3-3-23/lowerToUpperUsingReference.c
    c/College_Practice/C_problems_4th_sem/3-3-23/primeNosUsingFunction.c
    c/College_Practice/C_problems_4th_sem/3-3-23/sinSeries.c
    c/College_Practice/C_problems_4th_sem/3-3-23/stringConcatUsingRef.c
    c/College_Practice/Computer_networking/checksum_receiver.c
    c/College_Practice/Computer_networking/checksum_sender.c
    c/College_Practice/Computer_networking/crc_full_implement.c
    c/College_Practice/Computer_networking/crc_receiver.c
    c/College_Practice/Computer_networking/crc_sender.c
    c/College_Practice/Computer_networking/parity_checker.c
    c/College_Practice/Computer_networking/parity_generator.c
    c/College_Practice/Computer_networking/test.c
    c/College_Practice/DAA_5th_sem/bubble_sort.c
    c/College_Practice/DAA_5th_sem/insertion_sort.c
    c/College_Practice/DAA_5th_sem/merge_sort.c
    c/College_Practice/DAA_5th_sem/parthib_sorting.c
    c/College_Practice/DAA_5th_sem/quick_sort.c
    c/College_Practice/DAA_5th_sem/selection_sort.c
    c/College_Practice/DAA_5th_sem/signal_test.c
    c/College_Practice/DAA_5th_sem/tower_of_hanoi.c
    c/College_Practice/DSA_problems_3rd_sem/array_ops_prasenjit_sir.c
    c/College_Practice/DSA_problems_3rd_sem/avl_tree.c
    c/College_Practice/DSA_problems_3rd_sem/binary_search_tree.c
    c/College_Practice/DSA_problems_3rd_sem/Circular_queue.c
    c/College_Practice/DSA_problems_3rd_sem/Circular_queue_modulo_op.c
    c/College_Practice/DSA_problems_3rd_sem/DoublyLinkedList.c
    c/College_Practice/DSA_problems_3rd_sem/heap_ds.c
    c/College_Practice/DSA_problems_3rd_sem/Insertion_Sort.c
    c/College_Practice/DSA_problems_3rd_sem/Linked_List_Full.c
    c/College_Practice/DSA_problems_3rd_sem/LinkedList_as_Queue.c
    c/College_Practice/DSA_problems_3rd_sem/LinkedList_as_Stack.c
    c/College_Practice/DSA_problems_3rd_sem/LinkedListTry.c
    c/College_Practice/DSA_problems_3rd_sem/Queue.c
    c/College_Practice/DSA_problems_3rd_sem/radix_sort.c
    c/College_Practice/DSA_problems_3rd_sem/Selection_Sort.c
    c/College_Practice/DSA_problems_3rd_sem/sparse_matrix.c
    c/College_Practice/DSA_problems_3rd_sem/Stack.c
    c/College_Practice/DSA_problems_3rd_sem/threaded_binary_tree.c
    c/College_Practice/Numerical_methods_3rdSem/Bisection/bisection_method1.c
    c/College_Practice/Numerical_methods_3rdSem/Bisection/bisection_method2.c
    c/College_Practice/Numerical_methods_3rdSem/Bisection/bisection_method3.c
    c/College_Practice/Numerical_methods_3rdSem/Bisection/bisection_test.c
    c/College_Practice/Numerical_methods_3rdSem/Newton_raphson/newton_raphson.c
    c/College_Practice/Numerical_methods_3rdSem/Regula_falsi/regula_falsi_method1.c
    c/College_Practice/Numerical_methods_3rdSem/Regula_falsi/regula_falsi_method2.c
    c/College_Practice/Numerical_methods_3rdSem/Regula_falsi/regula_falsi_method3.c
    c/College_Practice/Numerical_methods_3rdSem/SIMPSON/SIMPSON1.c
    c/College_Practice/Numerical_methods_3rdSem/SIMPSON/SIMPSON2.c
    c/College_Practice/Numerical_methods_3rdSem/SIMPSON/SIMPSON3.c
    c/College_Practice/Numerical_methods_3rdSem/Weddle's_Rule/Weddles_rule1.c
    "c/College_Practice/problem solving 2nd sem/Aray_max_min_num_find.c"
    "c/College_Practice/problem solving 2nd sem/Area_of_triangle.c"
    "c/College_Practice/problem solving 2nd sem/Armstrong_number.c"
    "c/College_Practice/problem solving 2nd sem/Array_find_the_avg.c"
    "c/College_Practice/problem solving 2nd sem/Array_max_num_find.c"
    "c/College_Practice/problem solving 2nd sem/Array_sorting_ascending.c"
    "c/College_Practice/problem solving 2nd sem/Avg_of_three_number.c"
    "c/College_Practice/problem solving 2nd sem/Cel_to_Farh.c"
    "c/College_Practice/problem solving 2nd sem/CosX_series_PrintAndSum.c"
    "c/College_Practice/problem solving 2nd sem/Even_Odd.c"
    "c/College_Practice/problem solving 2nd sem/Factorial_using_recursion.c"
    "c/College_Practice/problem solving 2nd sem/Fibonacci_series.c"
    "c/College_Practice/problem solving 2nd sem/Krishnamurthy_number.c"
    "c/College_Practice/problem solving 2nd sem/Largest_Number.c"
    "c/College_Practice/problem solving 2nd sem/Leap_year_check.c"
    "c/College_Practice/problem solving 2nd sem/Leap_year_usdeffunc.c"
    "c/College_Practice/problem solving 2nd sem/Marks_grade.c"
    "c/College_Practice/problem solving 2nd sem/markstest.c"
    "c/College_Practice/problem solving 2nd sem/No_of_digits.c"
    "c/College_Practice/problem solving 2nd sem/NumberPattern2.c"
    "c/College_Practice/problem solving 2nd sem/NumberPattern3.c"
    "c/College_Practice/problem solving 2nd sem/NumPattern1.c"
    "c/College_Practice/problem solving 2nd sem/palindrome_check.c"
    "c/College_Practice/problem solving 2nd sem/Pattern1.c"
    "c/College_Practice/problem solving 2nd sem/Pattern2.c"
    "c/College_Practice/problem solving 2nd sem/Pattern3.c"
    "c/College_Practice/problem solving 2nd sem/Pattern4.c"
    "c/College_Practice/problem solving 2nd sem/Pattern5.c"
    "c/College_Practice/problem solving 2nd sem/PerfectNos_in_range.c"
    "c/College_Practice/problem solving 2nd sem/prime_factors_ofA_num.c"
    "c/College_Practice/problem solving 2nd sem/prime_nos.c"
    "c/College_Practice/problem solving 2nd sem/reversal_of_number.c"
    "c/College_Practice/problem solving 2nd sem/Series_with_loop-1.c"
    "c/College_Practice/problem solving 2nd sem/Series_with_loop-2.c"
    "c/College_Practice/problem solving 2nd sem/Series_with_loop-3.c"
    "c/College_Practice/problem solving 2nd sem/SeriesPrint1plus1divsi.c"
    "c/College_Practice/problem solving 2nd sem/SinX_series_PrintAndSum.c"
    "c/College_Practice/problem solving 2nd sem/sum_of-digits.c"
    "c/College_Practice/problem solving 2nd sem/Sum_of_2_numbers.c"
    "c/College_Practice/problem solving 2nd sem/Sum_of_row_diag.c"
    "c/College_Practice/problem solving 2nd sem/Swapping_function.c"
    "c/College_Practice/problem solving 2nd sem/tanX_series_PrintAndSum.c"
    "c/College_Practice/problem solving 2nd sem/Temp_con_by_choice.c"
    "c/College_Practice/problem solving 2nd sem/Temp_conv.c"
    c/COMPT_PRG/Codechef/bread.c
    c/COMPT_PRG/Codechef/chef-gym.c
    c/COMPT_PRG/Codechef/Chef-mask.c
    c/COMPT_PRG/Codechef/dnastrain.c
    c/COMPT_PRG/Codechef/mango-truck.c
    c/COMPT_PRG/Codechef/Roller-coaster.c
    c/COMPT_PRG/Codechef/six_friends.c
    c/COMPT_PRG/Codechef/volcontrol.c
    c/COMPT_PRG/Codechef/who_is_taller.c
    c/Own_practice/Basic_C/power_calc_useF.c
    c/Own_practice/Basic_C/String-pal_check.c
    c/Own_practice/Basic_C/String-pal_check2.c
    c/Own_practice/Basic_C/structure_impl.c
    "c/Own_practice/Basic_C/Xn _calc_useF.c"
    c/Own_practice/C_based_DSA/2_sum/problem1.c
    c/Own_practice/DSA_Kanetkar/Infix_Postfix/Infix_to_postfix.c
    c/Own_practice/DSA_Kanetkar/Infix_Postfix/Postfix_expression_eval.c
    c/Own_practice/DSA_Kanetkar/Infix_Postfix/Postfix_to_prefix.c
    c/Own_practice/DSA_Kanetkar/Sparse_matrices/SparceMatrix_3TupleForm.c
    c/Own_practice/DSA_Kanetkar/Sparse_matrices/SparceMatrix_Addition.c
    c/Own_practice/DSA_Kanetkar/Sparse_matrices/SparceMatrix_Transpose.c
    c/Own_practice/DSA_Kanetkar/Stack/Stack.c
    c/Test_progs/decimal_to_binary.c
    c/Test_progs/Extern_und2.c
    c/Test_progs/local_var.c
    c/Test_progs/matrix_addition.c
    c/Test_progs/my_concept.c
    c/Test_progs/no_diff.c
    c/Test_progs/parthib_numericals.c
    c/Test_progs/print_c.c
    c/Test_progs/print_cpp.cpp
    "c/Test_progs/shift _operator.c"
    c/Test_progs/stringLength.c
    c/Test_progs/Structure_problem.c
    c/Test_progs/structure_test.c
    c/Test_progs/structure_test2.c
    c/Test_progs/test.c
    c/Test_progs/test2.c
    c/Test_progs/Test3.c
    c/Test_progs/test4.c
    c/Test_progs/tild_operator.c
    c/Test_progs/Variable_und.c
    c++/17-8-23/armstrong_class.cpp
    c++/17-8-23/factorial_using_class.cpp
    c++/17-8-23/fibonacci_class.cpp
    c++/17-8-23/leap_year_class.cpp
    c++/17-8-23/palindrome_class.cpp
    c++/17-8-23/power_of_num_class.cpp
    c++/17-8-23/prime_check_class.cpp
    c++/23-11-23/copy_constructor.cpp
    c++/23-11-23/multiple_inheritance.cpp
    c++/23-11-23/virtual_function.cpp
    c++/7-9-23/sro_access_static_var_class.cpp
    c++/7-9-23/sro_def_func_out_class.cpp
    c++/7-9-23/sro_global_local_var.cpp
    c++/7-9-23/sro_mult_inheritance.cpp
    c++/7-9-23/sro_namespace.cpp
    c++/7-9-23/sro_nested_class.cpp
    c++/9-11-23/avg_of_four_nums_inline.cpp
    c++/9-11-23/friend_function.cpp
    c++/9-11-23/max_of_two_inline.cpp
    c++/9-11-23/result_of_series_inline.cpp
    c++/9-11-23/simple_inheritance.cpp
    c++/own_practice/hackerrank_pointer/pointer1.cpp
    c++/own_practice/complex_number_operator_overloading.cpp
    c++/own_practice/matrix_add_mult_op_overload.cpp
    c++/own_practice/quick_sort.cpp
    c++/addition.cpp
    c++/factorial.cpp
    c++/fibonacci.cpp
    c++/leap_year_check.cpp
    c++/op_overload.cpp
    c++/palindrome_check.cpp
    c++/power_of_num.cpp
    c++/practice2.cpp
    c++/prime_check.cpp
    c++/test.cpp)
