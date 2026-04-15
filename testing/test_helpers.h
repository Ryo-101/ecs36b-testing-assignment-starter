#ifndef TESTINGANDDEBUGGING_TEST_HELPERS_H
#define TESTINGANDDEBUGGING_TEST_HELPERS_H
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"

void expect_sorted(const int* array, int len);

void expect_arrays_equal(const int* arrayOne, const int* arrayTwo, int len);

void rc_assert_arrays_equal(const int* arrayOne, const int* arrayTwo, int len);

void rc_assert_sorted(const int* array, int len);

void rc_assert_no_overlap(const int* arrayOne, const int* arrayTwo, int len);


template <typename T>
void copy_vector_to_array(const std::vector<T>& vector_values, T* array_values) {
    /* Copy the elements from vector_values into array values
     * space for array_values needs to already be allocated
     */
    std::copy(vector_values.cbegin(), vector_values.cend(), array_values);
}

template <typename T>
bool elements_in_vector_and_array_are_same(const std::vector<T>& vector_values, const T* array_values) {
    /* check that the elements in vector_values are the same as those in array_values
     * array_values needs to have the same length as vector_values
     */

    return std::equal(vector_values.cbegin(), vector_values.cend(), array_values);
}



#endif //TESTINGANDDEBUGGING_TEST_HELPERS_H
