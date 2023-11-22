# SPLAB-3

File Format:

The input file should consist of several lines of ASCII text, with each row representing a datum as a regular decimal number.

Statistics Computed:

Mean (average)
Median
Standard Deviation

Memory Management:

The program dynamically allocates memory for the array storing the values. If the initial capacity is reached, it reallocates space for a new array twice the size of the current one.

Additional Notes:

Ensure proper error handling for file opening and memory allocation.
The code has been designed for modularity and readability.
No global variables are used.

Complilation:

1. Open the terminal and make sure the directory is the right directory
2. gcc basicstate.c -o basicstate
3. ./basicstate small.txt (large.txt)
