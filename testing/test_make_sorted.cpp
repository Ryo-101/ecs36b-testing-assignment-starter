#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {1, 2, 5, 7, 8};

    make_sorted(original, 5);

    expect_sorted(original, 5);

}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {9, 8, 4, 3, 2};

    make_sorted(original, 5);

    expect_sorted(original, 5);

}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {6, 8, 3, 1, 7};

    make_sorted(original, 5);

    expect_sorted(original, 5);

}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {9, 4, 6, 4, 2};

    make_sorted(original, 5);

    expect_sorted(original, 5);

}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              (std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int* arrayCopy = (int*)calloc(sizeof(int), values.size());

    copy_vector_to_array(values, arrayCopy);

    make_sorted(arrayCopy, values.size());

    for (size_t i = 0; i < values.size() - 1; i++)
    {
        RC_ASSERT(arrayCopy[i] <= arrayCopy[i+1]);
    }

}
