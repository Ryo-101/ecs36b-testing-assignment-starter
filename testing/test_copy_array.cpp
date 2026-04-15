#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {1, 2, 3, 4, 5};
    int* copy = copy_array(original, 5);

    expect_arrays_equal(original, copy, 5);

    free(copy);

}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {1, 2, 3, 4, 5};

    const auto replica(original);

    int* copy = copy_array(original, 5);

    expect_arrays_equal(original, replica, 5);

    free(copy);

}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {1, 2, 3, 4, 5};

    int* copy = copy_array(original, 5);

    for (int i = 0; i < 5; i++)
    {
        EXPECT_NE(original + i, copy + i);
    }

    free(copy);

}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              ()
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    auto values = *rc::gen::suchThat(
                                rc::gen::arbitrary<std::vector<int>>(),
                                [](const auto &vector)
                                {
                                    return vector.size() > 0;
                                }
                                ).as("vectorInt");

    int* copy = copy_array(values.data(), values.size());

    for (size_t i = 0; i < values.size(); i++)
    {
        RC_ASSERT(copy[i] == values[i]);
    }

    free(copy);

}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              ()
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    const auto values = *rc::gen::suchThat(
                                rc::gen::arbitrary<std::vector<int>>(),
                                [](const auto &vector)
                                {
                                    return vector.size() > 0;
                                }
                                ).as("vectorInt");


    auto original = (int*)calloc(values.size(), sizeof(int));

    copy_vector_to_array(values, original);

    auto replica(original);

    int* copy = copy_array(original, values.size());

    rc_assert_arrays_equal(original, replica, values.size());

    free(original);
    free(replica);
    free(copy);

}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              ()
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */

    const auto values = *rc::gen::suchThat(
                                rc::gen::arbitrary<std::vector<int>>(),
                                [](const auto &vector)
                                {
                                    return vector.size() > 0;
                                }
                                ).as("vectorInt");

    auto original = (int*)calloc(values.size(), sizeof(int));

    copy_vector_to_array(values, original);

    int* copy = copy_array(original, values.size());

    rc_assert_no_overlap(original, copy, values.size());

    free(original);
    free(copy);

}



