#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {1, 2, 3, 4, 5};

    int* sorted = get_sorted(original, 5);

    expect_sorted(sorted, 5);

    free(sorted);

}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {5, 4, 3, 2, 1};

    int* sorted = get_sorted(original, 5);

    expect_sorted(sorted, 5);

    free(sorted);

}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {4, 3, 6, 1, 7};

    int* sorted = get_sorted(original, 5);

    expect_sorted(sorted, 5);

    free(sorted);

}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {6, 2, 5, 2, 4};

    int* sorted = get_sorted(original, 5);

    expect_sorted(sorted, 5);

    free(sorted);

}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {4, 2, 6, 1, 5};

    const auto copy(original);

    int* sorted = get_sorted(original, 5);

    expect_arrays_equal(original, copy, 5);

    free(sorted);

}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {6, 3, 5, 2, 7};

    int* sorted = get_sorted(original, 5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            EXPECT_NE(original + i, sorted + j);
        }
    }

    free(sorted);

}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */

    int* original = (int*)calloc(values.size(), sizeof(int));

    copy_vector_to_array(values, original);

    int* sorted = get_sorted(original, values.size());

    rc_assert_sorted(sorted, values.size());

    free(original);
    free(sorted);

}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    ;

    int* original = (int*)calloc(values.size(), sizeof(int));

    copy_vector_to_array(values, original);

    const auto copy(original);

    int* sorted = get_sorted(original, values.size());

    rc_assert_arrays_equal(original, copy, values.size());

    free(original);
    free(sorted);

}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int* original = (int*)calloc(values.size(), sizeof(int));

    copy_vector_to_array(values, original);

    int* sorted = get_sorted(original, values.size());

    rc_assert_no_overlap(original, sorted, values.size());

    free(original);
    free(sorted);

}











