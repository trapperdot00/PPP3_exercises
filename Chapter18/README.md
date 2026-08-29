# 18: Templates and Exceptions

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/main.cpp)
Add `try`-blocks to this last example to ensure that all resources are properly released in all cases where an exception might be thrown.

## [Drill 1](drill/01/main.cpp)
Define `template <typename T> struct S { T val; };`.

## [Drill 2](drill/02/main.cpp)
Add a constructor, so that you can initialize with a `T`.

## [Drill 3](drill/03/main.cpp)
Define variables of types `S<int>`, `S<char>`, `S<double>`, `S<string>`, and `S<vector<int>>`; initialize them with values of your choice.

## [Drill 4](drill/04/main.cpp)
Read those values and print them.

## [Drill 5](drill/05/main.cpp)
Make `val` private.

## [Drill 6](drill/06/main.cpp)
Add a member function `access()` that returns a reference to `val`.

## [Drill 7](drill/07/main.cpp)
Put the definition of `access()` outside the class.

## [Drill 8](drill/08/main.cpp)
Do 4 again using `access()`.

## [Drill 9](drill/09/main.cpp)
Add a `S<T>::operator=(const T&)`.
Hint: Much simpler than §17.8.5.

## [Drill 10](drill/10/main.cpp)
Provide `const` and non-`const` versions of `access()`.

## [Drill 11](drill/11/main.cpp)
Define a function `template <typename T> read_val(T& v)` that reads from `cin` into `v`.

## [Drill 12](drill/12/main.cpp)
Use `read_val()` to read into each of the variables from exercise 3 except the `S<vector<int>>` variable.

## [Drill 13](drill/13/main.cpp)
Bonus: Define input and output operators (`>>` and `<<`) for `vector<T>`s.
For both input and output use a `{ val, val, val }` format.
That will allow `read_val()` to also handle the `S<vector<int>>` variable.
