*This project has been created as part of the 42 curriculum by rnovotny.*

# CPP Module 09 - STL

## Description

CPP Module 09 is the final module in the 42 C++ curriculum, focusing on advanced usage of the **Standard Template Library (STL)**. This module challenges students to apply different STL containers to solve real-world algorithmic problems while understanding the performance characteristics and appropriate use cases for each container.

### Project Goal
Master advanced STL container usage by:
1. Understanding when to use specific containers (map, stack, vector, deque)
2. Implementing algorithms that leverage container strengths
3. Comparing performance characteristics between different containers
4. Working with real-world data formats (CSV, mathematical expressions, sorting algorithms)

### Brief Overview
This module contains three exercises, each requiring a different STL container:
- **Exercise 00 (Bitcoin Exchange)**: Uses `std::map` to store and query bitcoin exchange rates by date
- **Exercise 01 (RPN Calculator)**: Uses `std::stack` to evaluate Reverse Polish Notation expressions
- **Exercise 02 (PmergeMe)**: Uses both `std::vector` and `std::deque` to implement the Ford-Johnson merge-insert sort algorithm and compare performance

All implementations follow C++98 standard and demonstrate practical applications of STL containers beyond simple storage.

## Instructions

### Compilation
Each exercise directory contains a Makefile that compiles the code with the required flags:
```bash
c++ -Wall -Wextra -Werror -std=c++98
```

### Building the Project

#### Exercise 00 - Bitcoin Exchange
```bash
cd ex00
make
./btc input.txt
```

The program requires:
- `data.csv`: Database of bitcoin exchange rates (provided)
- Input file with format: `date | value`
- Dates must be in YYYY-MM-DD format
- Values must be between 0 and 1000

Example input file:
```
date | value
2011-01-03 | 3
2011-01-03 | 2
2012-01-11 | 1
2012-01-11 | -1
```

#### Exercise 01 - RPN Calculator
```bash
cd ex01
make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

The program:
- Takes a Reverse Polish Notation expression as argument
- Supports operators: `+ - * /`
- Numbers must be single digits (< 10)
- Example: `"8 9 *"` equals 72

#### Exercise 02 - PmergeMe
```bash
cd ex02
make
./PmergeMe 3 5 9 7 4
```

The program:
- Takes a sequence of positive integers as arguments
- Sorts using Ford-Johnson merge-insert algorithm
- Displays timing for both `std::vector` and `std::deque`
- Can handle at least 3000 integers

Test with large input:
```bash
./PmergeMe $(jot -r 3000 1 100000 | tr '\n' ' ')  # macOS
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")  # Linux
```

Or with included testers:
```bash
python test_one.py <lower bound> <upper bound> <sequence size> # similar to above
python test.py # tests input parsing and random sequences of different sizes
python test_comparisons.py # checks number of comparisons against thoretical minimum
```
(The last tester requires that the `#define COUNT_COMPARISONS` line is uncommented in `PmergeMe.hpp`.)

### Cleaning
To remove object files and executables:
```bash
make clean    # Remove object files
make fclean   # Remove object files and executables
make re       # Rebuild from scratch
```

## Technical Concepts

### STL Container Selection Guide

| Container | Use Case | Time Complexity | Memory |
|-----------|----------|-----------------|---------|
| `std::map` | Ordered key-value pairs, fast lookup | O(log n) | Higher overhead |
| `std::stack` | LIFO operations, expression evaluation | O(1) push/pop | Minimal |
| `std::vector` | Sequential access, cache-friendly | O(1) access, O(n) insert | Contiguous |
| `std::deque` | Double-ended queue, flexible insertion | O(1) both ends | Non-contiguous |

### When to Use Each Container

**Use `std::map` when**:
- Need sorted key-value associations
- Frequent lookups by key
- Need to find ranges (lower_bound, upper_bound)
- Keys are naturally ordered

**Use `std::stack` when**:
- Need LIFO access pattern
- Only care about most recent element
- Implementing recursive algorithms iteratively
- Evaluating expressions (RPN, parentheses matching)

**Use `std::vector` when**:
- Need random access
- Mostly append operations
- Cache locality is important
- Memory is contiguous

**Use `std::deque` when**:
- Need insertion at both ends
- Don't need iterator stability
- Memory doesn't need to be contiguous
- Queue-like behavior required

### Container Performance Comparison

The PmergeMe exercise demonstrates that container choice affects performance:

1. **Memory Layout**:
   - Vector: `[1][2][3][4][5]` - continuous block
   - Deque: `[1,2] -> [3,4] -> [5]` - multiple blocks

2. **Cache Performance**:
   - Vector: Better cache hits (sequential memory)
   - Deque: More cache misses (scattered blocks)

3. **Allocation**:
   - Vector: Reallocates entire array when full
   - Deque: Allocates new blocks as needed

## Resources

### Classic References
- [C++ Reference - std::map](https://en.cppreference.com/w/cpp/container/map)
- [C++ Reference - std::stack](https://en.cppreference.com/w/cpp/container/stack)
- [C++ Reference - std::vector](https://en.cppreference.com/w/cpp/container/vector)
- [C++ Reference - std::deque](https://en.cppreference.com/w/cpp/container/deque)
- ["The Art of Computer Programming, Vol. 3: Sorting and Searching" by Donald Knuth - Ford-Johnson algorithm (p. 184)](https://seriouscomputerist.atariverse.com/media/pdf/book/Art%20of%20Computer%20Programming%20-%20Volume%203%20(Sorting%20&%20Searching).pdf)
- [Reverse Polish Notation - Wikipedia](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
- [Merge-insertion sort - Wikipedia](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- [Bitcoin Historical Data](https://www.coindesk.com/price/bitcoin/) - Understanding exchange rate data

### AI Usage
This project was completed with AI assistance (GitHub Copilot).:

**Specific AI Contributions by Exercise**:
- **ex00**: CSV parsing logic, date string manipulation, map usage patterns
- **ex01**: RPN algorithm implementation, stack operations, token parsing
- **ex02**: Ford-Johnson algorithm adaptation, timing code, dual container implementation

**Parts Completed Without AI**:
- Architectural decisions (which containers to use for each exercise)
- Testing and debugging of edge cases
- Final code review and optimization verification
- Understanding trade-offs between different implementations

All AI-generated code was thoroughly reviewed, tested, and understood before inclusion. The implementations follow 42 coding standards and C++98 requirements.
