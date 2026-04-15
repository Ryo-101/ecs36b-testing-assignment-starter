#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */

    return rc::gen::container<std::string>(rc::gen::inRange<char>('a', 'z' + 1));

}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */

    std::vector<std::string> strings(numbers.size());

    for (size_t i = 0; i < numbers.size(); i++)
    {
        strings[i] = std::to_string(numbers[i]);
    }

    return strings;

}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */

    char** strings = (char**)calloc(1, sizeof(char*));
    strings[0] = (char*)calloc(6, sizeof(char));

    strcpy(strings[0], "hello");

    int* integers = nullptr;
    int len = 1;

    parse_args(1, strings, integers, &len);

    EXPECT_EQ(integers, nullptr);

    free(strings[0]);
    free(strings);

}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
}
