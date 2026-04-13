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

    // Rule of Thumb:
    // If I need to constrain the generated values to specifics, must define generators with some function(s)
    // If I don't care about the specifics, just put parameters in the parenthesis at the top

    // Does the same as the parameters at the top, so can be deleted
    // Note: with every generator, it must be unreferenced to assign it to a variable
    a_start = *rc::gen::arbitrary<int>();
    b_start = *rc::gen::arbitrary<int>();

    const int tempA = a_start;
    const int tempB = b_start;

    swap(&a_start, &b_start);

    RC_ASSERT(b_start == tempA);
    RC_ASSERT(a_start == tempB);

}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              ()
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */

    // Generates a vector with the following constraints:
        // A arbitrary vector made of int values
        // Vector is of length greater than 1 (in order to swap 2 elements)
        // Refer to such vector as "vectorInt" in test logs
    auto values = *rc::gen::suchThat(
                                rc::gen::arbitrary<std::vector<int>>(), // generator
                                [](const auto &vector) // lambda function
                                {
                                    return vector.size() > 1; // min length of vectors is 2
                                }).as("vectorInt"); // refer to a vectorInt in test logs

    // Creates a copy of vector values and refer it as original
    const auto original(values);

    // Generates an int value with the following constraints:
        // An int value that is between 0 and the size of vector - 1
    const size_t index1 = *rc::gen::inRange<size_t>(0, values.size() - 1).as("index1");
    // Generates an int value with the following constraints:
        // An int value that is between 0 and size of vector - 1 BUT
        // Cannot be the same as the int value of index 1
    const size_t index2 = *rc::gen::distinctFrom(
        rc::gen::inRange<size_t>(0, values.size() - 1),
        index1
        );

    // Save the values to check later with RC_ASSERT
    const int tempOne = values[index1];
    const int tempTwo = values[index2];

    // Call the function being tested
    swap(values.data() + index1, values.data() + index2);

    // Check whether the values were actually swapped with RC_ASSERT
    RC_ASSERT(values[index1] == tempTwo);
    RC_ASSERT(values[index2] == tempOne);

    // Additionally, check if other int values haven't been changed
    for (size_t i = 0; i < original.size(); i++)
    {
        if (i != index1 && i != index2)
        {
            RC_ASSERT(original[i] == values[i]);
        }
    }


}
