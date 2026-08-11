# 16: Arrays, Pointers, and References

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/main.cpp)
Look up the definition of `std::strlen()` to see what the standard requires.
Then, try `char* p = nullptr; size_t x = strlen(p);` to see what your implementation does.


## [Drill 1.1](drill/01/01/main.cpp)
Define a global `int` array `ga` of ten `int`s initialized to 1, 2, 4, 8, 16, etc.

## [Drill 1.2](drill/01/02/main.cpp)
Define a function `f()` taking an `int` array argument and an `int` argument indicating the number of elements in the array.

## [Drill 1.3](drill/01/03/main.cpp)
In `f()`:
 - Define a local `int` array `la` of ten `int`s.
 - Copy the values from `ga` into `la`.
 - Print out the elements of `la`.
 - Define a pointer `p` to `int` and initialize it with an array allocated on the free store with the same number of elements as the argument array.
 - Copy the values from the argument array into the free-store array.
 - Print out the elements of the free-store array.
 - Deallocate the free-store array.

## [Drill 1.4](drill/01/04/main.cpp)
In `main()`:
 - Call `f()` with `ga` as its argument.
 - Define an array `aa` with ten elements and initialize it with the first ten factorial values (1, 2*1, 3*2*1, 4*3*2*1, etc.).
 - Call `f()` with `aa` as its argument.

## [Drill 2.1](drill/02/01/main.cpp)
Define a global `vector<int> gv`; initialize it with ten `int`s, 1, 2, 4, 8, 16, etc.

## [Drill 2.2](drill/02/02/main.cpp)
Define a function `f()` taking a `vector<int>` argument.

## [Drill 2.3](drill/02/03/main.cpp)
In `f()`:
 - Define a local `vector<int> lv` with the same number of elements as the argument `vector`.
 - Copy the values from `gv` into `lv`.
 - Print out the elements of `lv`.
 - Define a local `vector<int> lv2`; initialize it to be a copy of the argument `vector`.
 - Print out the elements of `lv2`.

## [Drill 2.4](drill/02/04/main.cpp)
In `main()`:
 - Call `f()` with `gv` as its argument.
 - Define a `vector<int> vv` and initialize it with the first ten factorial values (1, 2*1, 3*2*1, 4*3*2*1, etc.).
 - Call `f()` with `vv` as its argument.
