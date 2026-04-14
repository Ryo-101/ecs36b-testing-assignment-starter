/* Put any extra functions you use to help you out with testing here.
 *
 */

#include "test_helpers.h"

#include "rapidcheck/Assertions.h"

void expect_sorted(const int* array, const int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        EXPECT_LE(array[i], array[i+1]);
    }
}

void rc_assert_sorted(const int* array, const int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        RC_ASSERT(array[i] <= array[i+1]);
    }
}
