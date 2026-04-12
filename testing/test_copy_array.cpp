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

    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(original[i], copy[i]);
    }

    free(copy);

}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int original[] = {1, 2, 3, 4, 5};

    int replica[5];

    for (int i = 0; i < 5; i++)
    {
        replica[i] = original[i];
    }

    int* copy = copy_array(original, 5);

    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(original[i], replica[i]);
    }

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
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    values = rc::gen::suchThat(
                                rc::gen::arbitrary<std::vector<int>>(),
                                [](const auto vector)
                                {
                                    return vector.size() > 1;
                                }
                                ).as("vectorInt");

    int* copy = copy_array(values, values.size());

    for (int i = 0; i < values.size(); i++)
    {
        RC_ASSERT(copy[i] == values[i]);
    }

    free(copy);

}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    values = rc::gen::suchThat(
                                rc::gen::arbitrary<std::vector<int>>(),
                                [](const auto vector)
                                {
                                    return vector.size() > 1;
                                }
                                ).as("vectorInt");

    int replica[values.size()];

    for (int i = 0; i < replica.size(); i++)
    {
        replica[i] = values[i];
    }

    int* copy = copy_array(values, values.size());

    for (int i = 0; i < values.size(); i++)
    {
        RC_ASSERT(values[i] == replica[i]);
    }

}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */

}



