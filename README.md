# Project Description and General Info
This project was done as an assignment for an undergrad-level data structures and algorithms course. It is designed to take an input file on the console and then output data to the console line relating to the huffman encoding process/results.  
1. Outputs all alphabetical characters in the input file in uppercase.
2. Prints the frequency of each alphabetical character (case-insensitive) and the total frequency.
3. Displays a tree that can be used to produce huffman codes for each alphabetical character.
4. Prints the huffman codes for each alphabetical.
5. Prints the total number of bits required to store the alphabetical characters in the input file using fixed-width, 5-bit codes for each character and then prints the total number of bits required to store the same data using the generated huffman codes.

# Sources
- `tree_printer.hpp` was supplied by my instructor. I performed minor modifications to enable it to work with my code. 
    - `tree_printer.hpp` was adapted by my instructor from [Techie Delight](https://www.techiedelight.com/c-program-print-binary-tree/).
- Other minor sources used are referenced in `huffman.cpp` where applicable

# Usage
This program is a console app. To compile on a macOS terminal:
`g++ -Wall -Wextra -std=c++20 huffman.cpp`
To run with text file `info.txt`:
`./a.out < info.txt`

# Limitations
- This program considers only alphabetical characters in the input; any other characters will be ignored. 
- Different letter cases of the same letter are treated the same.  
