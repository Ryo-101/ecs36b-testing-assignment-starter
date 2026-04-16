#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"
#include "test_helpers.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray)
{
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */

    int array[] = {3, 5, 6, 4, 9};

    int minIndex = min_index_of_array(array, 5);

    EXPECT_EQ(minIndex, 0);

}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */

    int array[] = {6, 4, 3, 7, 2};

    int minIndex = min_index_of_array(array, 5);

    EXPECT_EQ(minIndex, 4);

}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */

    int array[] = {7, 9, 1, 3, 6};

    int minIndex = min_index_of_array(array, 5);

    EXPECT_EQ(minIndex, 2);

}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */

    int array[] = {3, 0, 2, 7, 0};

    int minIndex = min_index_of_array(array, 5);

    EXPECT_EQ(minIndex, 1);

}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */

    int array[] = {5, 3, 6, 2, 9};

    int minIndex = min_index_of_array(array, 5);

    EXPECT_EQ(minIndex, 3);

    EXPECT_EQ(array[0], 5);
    EXPECT_EQ(array[1], 3);
    EXPECT_EQ(array[2], 6);
    EXPECT_EQ(array[3], 2);
    EXPECT_EQ(array[4], 9);

}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              ()) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */

    const auto values = *rc::gen::suchThat(
                            rc::gen::arbitrary<std::vector<int>>(),
                            [](const auto &vector)
                            {
                                return vector.size() > 1;
                            }
                            );

    int* original = (int*)calloc(values.size(), sizeof(int));

    copy_vector_to_array(values, original);

    const int minIndex = min_index_of_array(original, values.size());

    for (size_t i = 0; i < values.size(); i++)
    {
        RC_ASSERT(original[minIndex] <= original[i]);
    }

    free(original);

}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              ()) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */

    const auto values = *rc::gen::suchThat(
                                            rc::gen::arbitrary<std::vector<int>>(),
                                            [](const auto &vector)
                                            {
                                                return vector.size() > 1;
                                            }
                                            );

    int* original = (int*)calloc(values.size(), sizeof(int));

    copy_vector_to_array(values, original);

    const int minIndex = min_index_of_array(original, values.size());

    for (size_t i = 0; i < values.size(); i++)
    {
        RC_ASSERT(original[minIndex] <= original[i]);
    }

    for (size_t i = 0; i < values.size(); i++)
    {
        RC_ASSERT(original[i] == values[i]);
    }

    free(original);

}
