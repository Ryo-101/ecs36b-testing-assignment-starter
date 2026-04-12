#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */

    int valueOne = 1;
    int valueTwo = 99;

    swap(&valueOne, &valueTwo);

    EXPECT_EQ(valueTwo, 1);
    EXPECT_EQ(valueOne, 99);

}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */

    int array[] = {1, 2, 4, 3, 5};

    swap(array + 2, array + 3);

    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 4);

}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */

    a_start = rc::gen::arbitrary<int>();
    b_start = rc::gen::arbitrary<int>();

    int tempA = a_start;
    int tempB = b_start;

    swap(&a_start, &b_start);

    RC_ASSERT(b_start == tempA);
    RC_ASSERT(a_start == tempB);

}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
}
