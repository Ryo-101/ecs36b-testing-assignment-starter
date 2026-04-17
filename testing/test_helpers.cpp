/* Put any extra functions you use to help you out with testing here.
 *
 */

#include "test_helpers.h"

#include "rapidcheck/Assertions.h"


// TESTING HELPER FUNCTIONS
void expect_sorted(const int* array, const int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        EXPECT_LE(array[i], array[i+1]);
    }
}

void expect_arrays_equal(const int* arrayOne, const int* arrayTwo, const int len)
{
    for (int i = 0; i < len; i++)
    {
        EXPECT_EQ(arrayOne[i], arrayTwo[i]);
    }
}

void rc_assert_arrays_equal(const int* arrayOne, const int* arrayTwo, const int len)
{
    for (int i = 0; i < len; i++)
    {
        RC_ASSERT(arrayOne[i] == arrayTwo[i]);
    }
}


void rc_assert_sorted(const int* array, const int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        RC_ASSERT(array[i] <= array[i+1]);
    }
}

void rc_assert_no_overlap(const int* arrayOne, const int* arrayTwo, const int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            RC_ASSERT(arrayOne + i != arrayTwo + j);
        }
    }
}


char** string_vector_to_array_of_strings(std::vector<std::string>& commandArgs)
{
    char** argsAsPointers = (char**)calloc(commandArgs.size(), sizeof(char*));

    for (size_t i = 0; i < commandArgs.size(); i++)
    {
        argsAsPointers[i] = commandArgs[i].data();
    }

    return argsAsPointers;
}

void free_array_of_strings(char** array, const int len)
{
    for (int i = 0; i < len; i++)
    {
        free(array[i]);
    }

    free(array);
}
