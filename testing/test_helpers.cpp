/* Put any extra functions you use to help you out with testing here.
 *
 */

#include "test_helpers.h"

void expect_sorted(const int* array, const int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        EXPECT_LE(array[i], array[i+1]);
    }
}
