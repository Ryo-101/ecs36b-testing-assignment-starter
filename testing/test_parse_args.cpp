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

    std::vector<std::string> strings;

    for (size_t i = 0; i < numbers.size(); i++)
    {
        strings.push_back(std::to_string(numbers[i]));
    }

    return strings;

}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */

    char** strings = (char**)calloc(6, sizeof(char*));
    strings[0] = (char*)calloc(6, sizeof(char));

    for (int i = 1; i < 6; i++)
    {
        strings[i] = (char*)calloc(3, sizeof(char));
    }

    int* integers = (int*)88;
    int len;

    strcpy(strings[0], "hello");
    strcpy(strings[1], "1");
    strcpy(strings[2], "2");
    strcpy(strings[3], "3");
    strcpy(strings[4], "4");
    strcpy(strings[5], "5");

    parse_args(6, strings, integers, &len);

    for (int j = 0; j < 5; j++)
    {
        EXPECT_EQ(integers[j], std::atoi(strings[j+1]));
    }

    EXPECT_EQ(len, 5);

    for (int k = 0; k < 6; k++)
    {
        free(strings[k]);
    }

    free(strings);

}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */

    char** strings = (char**)calloc(1, sizeof(char*));
    strings[0] = (char*)calloc(6, sizeof(char));

    strcpy(strings[0], "hello");

    int* integers = (int*)88;
    int len;

    parse_args(1, strings, integers, &len);

    EXPECT_EQ(integers, nullptr);
    EXPECT_EQ(len, 0);

    free(strings[0]);
    free(strings);

}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              (std::vector<int> values)
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */

    const std::string programName = *word_generator();
    std::vector<std::string> commandArgs = vector_of_ints_to_vector_of_strings(values);
    commandArgs.insert(commandArgs.begin(), programName);

    char** argsAsPointers = (char**)calloc(commandArgs.size(), sizeof(char*));

    for (size_t i = 0; i < commandArgs.size(); i++)
    {
        argsAsPointers[i] = commandArgs[i].data();
    }

    int* integers = (int*)88;
    int len;

    parse_args(values.size() + 1, argsAsPointers, integers, &len);

    RC_ASSERT(len == (int)values.size());

    for (size_t i = 0; i < values.size(); i++)
    {
        RC_ASSERT(integers[i] == values[i]);
    }

    for (size_t j = 0; j < commandArgs.size(); j++)
    {
        free(argsAsPointers[j]);
    }

    free(argsAsPointers);

}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */

    const std::string programName = *word_generator();
    std::vector<std::string> commandArgs;
    commandArgs.push_back(programName);

    char** argsAsPointers = (char**)calloc(commandArgs.size(), sizeof(char*));

    argsAsPointers[0] = commandArgs[0].data();

    int* integers = (int*)88;
    int len;

    parse_args(1, argsAsPointers, integers, &len);

    RC_ASSERT(integers == nullptr);
    RC_ASSERT(len == 0);

}
