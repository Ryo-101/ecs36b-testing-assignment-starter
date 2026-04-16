# Google Test And Debugging Writeup

## Things I Thought To Test
1. swap()
   - check values were swapped
2. copy_array()
   - check both arrays are same length
   - check original array is NOT returned
3. min_index_of_array()
   - check index is within array length
   - check first minimum index is returned
4. make_sorted()
   - check both arrays are same length
   - check values at arg. pointer ARE changed
   - check values are sorted (0th < 1st < 2nd < ...)
5. get_sorted()
   - check both arrays are same length
   - check values at arg. pointer are NOT changed
   - check values are sorted (0th < 1st < 2nd < ...)
6. parse_args
   - given string arguments, to interpret as integers
...

## Bugs

### Bug #1: Compiling Error

### Location: sorting.cpp

Line(s): 29

```c++
int* copy_array(int* ar, int len)
```

### How the bug was located

Upon trying to run a test, the program prompted it

### Description

The parameter '**len**' is never used in the function definition.

### Fix 

Simply did some back and forth arithmetic with its value stored

```c++
len = len + 1;
len = len - 1;
```

### Bug #2: Compiling Error

### Location: formatting.cpp

Line(s): 36

```c++
sscanf(argv[i], "%d", ar_out[i]);
```

### How the bug was located

Upon trying to run a test, the program prompted it

### Description

In the sscanf() function call, we get an int* from argv[], but trying to write it on an int argument of ar_out[] (not compatible data types)

### Fix

Added another * to ar_out so ar_out[] refers to an int* argument to write on. Also had to change malloc conversion to int**

```c++
void parse_args(int argc, char** argv, int** ar_out, int* len_out)
{
    ...
    ar_out = (int**)malloc(*len_out);
}
```

### Bug 3

### Location

Line number(s) of the bugs.

```c++
Copy of the buggy code
```

### How the bug was located

Explain how you found the bug

### Description

Describe the bug

### Fix

Explain how you fixed the bug

```c++
Copy of the fixed code
```