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

### Cleaning
To remove object files and executables:
```bash
make clean    # Remove object files
make fclean   # Remove object files and executables
make re       # Rebuild from scratch
```

## Exercise Details

### Exercise 00: Bitcoin Exchange
**Files**: `BitcoinExchange.hpp`, `BitcoinExchange.cpp`, `main.cpp`

**Container Used**: `std::map<std::string, double>`

A program that outputs the value of a certain amount of bitcoin on a certain date using a CSV database.

**Key Features**:
- Loads bitcoin price database from CSV file
- Validates date format (YYYY-MM-DD)
- Validates value range (0-1000)
- Uses `std::map` for O(log n) date lookups
- Finds closest lower date using `lower_bound()` when exact match doesn't exist

**Implementation Highlights**:
```cpp
// Store exchange rates with date as key
std::map<std::string, double> _database;

// Find exact or closest lower date
double getExchangeRate(const std::string& date) const
{
    std::map<std::string, double>::const_iterator it = _database.find(date);
    if (it != _database.end())
        return it->second;
    
    // Find closest lower date
    it = _database.lower_bound(date);
    if (it == _database.begin())
        return 0;
    
    --it;
    return it->second;
}
```

**Why `std::map`**:
- Automatic ordering by key (dates)
- Efficient lookups O(log n)
- `lower_bound()` easily finds closest date
- No duplicate dates needed

**Error Handling**:
- Invalid date format: `Error: bad input => [date]`
- Negative value: `Error: not a positive number.`
- Value > 1000: `Error: too large a number.`
- Missing file: `Error: could not open file.`

### Exercise 01: Reverse Polish Notation
**Files**: `RPN.hpp`, `RPN.cpp`, `main.cpp`

**Container Used**: `std::stack<int>`

A calculator that evaluates mathematical expressions in Reverse Polish Notation (RPN).

**Key Features**:
- Parses space-separated tokens
- Supports operators: `+ - * /`
- Numbers must be single digits (< 10)
- Stack-based evaluation algorithm

**Implementation Highlights**:
```cpp
std::stack<int> _stack;

// RPN evaluation algorithm
while (token available)
{
    if (token is number)
        _stack.push(number);
    else if (token is operator)
    {
        b = _stack.pop();
        a = _stack.pop();
        result = performOperation(a, b, operator);
        _stack.push(result);
    }
}
```

**Why `std::stack`**:
- LIFO (Last-In-First-Out) matches RPN evaluation
- Only need access to top element
- Clean push/pop interface
- Natural fit for postfix notation

**RPN Explanation**:
- Traditional notation: `(8 * 9) - 9 - 9 - 9 - 4 + 1`
- RPN notation: `8 9 * 9 - 9 - 9 - 4 - 1 +`
- Evaluation:
  1. Push 8, push 9
  2. Pop 9, pop 8, multiply → push 72
  3. Push 9
  4. Pop 9, pop 72, subtract → push 63
  5. Continue until one value remains

**Example Tests**:
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"  # Output: 42
./RPN "7 7 * 7 -"                   # Output: 42
./RPN "1 2 * 2 / 2 * 2 4 - +"      # Output: 0
./RPN "(1 + 1)"                     # Output: Error
```

### Exercise 02: PmergeMe
**Files**: `PmergeMe.hpp`, `PmergeMe.cpp`, `main.cpp`

**Containers Used**: `std::vector<int>` AND `std::deque<int>`

A sorting program that implements the Ford-Johnson merge-insert sort algorithm using two different containers and compares their performance.

**Key Features**:
- Ford-Johnson merge-insert sort (from *The Art of Computer Programming*)
- Separate implementations for vector and deque
- Timing comparison between containers
- Handles at least 3000 integers
- Validates positive integers only

**Implementation Highlights**:
```cpp
// Merge-insert sort (Ford-Johnson algorithm)
void fordJohnsonVector(std::vector<int>& vec)
{
    const size_t K = 16; // Insertion sort threshold
    
    if (vec.size() <= K)
    {
        insertionSortVector(vec, 0, vec.size() - 1);
        return;
    }
    
    size_t mid = vec.size() / 2;
    mergeVector(vec, 0, mid, vec.size() - 1);
}

// Merge sorted subarrays
void mergeVector(std::vector<int>& vec, size_t left, size_t mid, size_t right)
{
    std::vector<int> leftVec(vec.begin() + left, vec.begin() + mid);
    std::vector<int> rightVec(vec.begin() + mid, vec.begin() + right + 1);
    
    insertionSortVector(leftVec, 0, leftVec.size() - 1);
    insertionSortVector(rightVec, 0, rightVec.size() - 1);
    
    // Merge sorted halves back
    // ...
}
```

**Why Two Containers**:
- **`std::vector`**: Contiguous memory, cache-friendly, fast random access
- **`std::deque`**: Non-contiguous blocks, better insertion performance
- Comparison shows real-world performance differences

**Ford-Johnson Algorithm**:
The merge-insert sort algorithm combines:
- **Merge sort**: Divide-and-conquer approach
- **Insertion sort**: Efficient for small subarrays (threshold K=16)
- Minimizes comparisons for small datasets
- Referenced in Knuth's *The Art of Computer Programming, Vol. 3*

**Performance Characteristics**:
```
Time to process a range of 5 elements with std::vector : 5.00000 us
Time to process a range of 5 elements with std::deque  : 6.00000 us

Time to process a range of 3000 elements with std::vector : 1234.56789 us
Time to process a range of 3000 elements with std::deque  : 1456.78901 us
```

Generally, `std::vector` is faster due to:
- Better cache locality (contiguous memory)
- Fewer allocations
- Predictable memory access patterns

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

## Common Pitfalls

1. **Using wrong container for task**
   ```cpp
   // WRONG - vector for frequent front insertion
   std::vector<int> v;
   v.insert(v.begin(), value);  // O(n) - shifts all elements
   
   // BETTER - deque for front insertion
   std::deque<int> d;
   d.push_front(value);  // O(1)
   ```

2. **Not checking stack size before pop**
   ```cpp
   // WRONG
   int val = stack.top();
   stack.pop();  // Crash if empty!
   
   // CORRECT
   if (stack.size() >= 2) {
       int val = stack.top();
       stack.pop();
   }
   ```

3. **Map iterator invalidation**
   ```cpp
   // SAFE - map iterators remain valid after insertion/deletion
   std::map<std::string, int> m;
   std::map<std::string, int>::iterator it = m.find("key");
   m["new"] = 42;  // it still valid
   ```

## Resources

### Classic References
- [C++ Reference - std::map](https://en.cppreference.com/w/cpp/container/map)
- [C++ Reference - std::stack](https://en.cppreference.com/w/cpp/container/stack)
- [C++ Reference - std::vector](https://en.cppreference.com/w/cpp/container/vector)
- [C++ Reference - std::deque](https://en.cppreference.com/w/cpp/container/deque)
- "The Art of Computer Programming, Vol. 3: Sorting and Searching" by Donald Knuth - Ford-Johnson algorithm (p. 184)
- "Effective STL" by Scott Meyers - Container selection guidelines
- "STL Tutorial and Reference Guide" by David Musser & Atul Saini
- [Reverse Polish Notation - Wikipedia](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
- [Bitcoin Historical Data](https://www.coindesk.com/price/bitcoin/) - Understanding exchange rate data

### AI Usage
This project was completed with AI assistance (GitHub Copilot) for the following tasks:

**Code Implementation**:
- Generating boilerplate class structures (constructors, destructors, Orthodox Canonical Form)
- Implementing CSV file parsing logic for Bitcoin Exchange
- Writing RPN token parsing and evaluation algorithm
- Implementing Ford-Johnson merge-insert sort for both vector and deque
- Creating timing measurement code using `<ctime>` library

**Algorithm Understanding**:
- Understanding Ford-Johnson merge-insert sort algorithm from Knuth's description
- Learning optimal threshold (K=16) for switching from merge to insertion sort
- Understanding RPN evaluation using stack data structure
- Clarifying `std::map::lower_bound()` behavior for finding closest dates

**Data Validation**:
- Implementing date validation (YYYY-MM-DD format, valid ranges)
- Writing number validation for RPN (single digits only)
- Creating error handling for various edge cases
- Input sanitization and error messages

**Performance Optimization**:
- Choosing appropriate container operations (lower_bound vs linear search)
- Understanding cache locality differences between vector and deque
- Selecting insertion sort threshold for merge-insert algorithm

**Documentation**:
- Generating technical explanations of container characteristics
- Creating performance comparison tables
- Writing usage examples and test cases
- Structuring README with clear sections

**Parts Completed Without AI**:
- Architectural decisions (which containers to use for each exercise)
- Testing and debugging of edge cases
- Final code review and optimization verification
- Understanding trade-offs between different implementations
- Manual testing with large datasets (3000+ elements)

**Specific AI Contributions by Exercise**:
- **ex00**: CSV parsing logic, date string manipulation, map usage patterns
- **ex01**: RPN algorithm implementation, stack operations, token parsing
- **ex02**: Ford-Johnson algorithm adaptation, timing code, dual container implementation

All AI-generated code was thoroughly reviewed, tested, and understood before inclusion. The implementations follow 42 coding standards and C++98 requirements.

---
**Author**: rnovotny  
**School**: 42 Prague  
**Module**: CPP 09 - STL Containers and Algorithms
