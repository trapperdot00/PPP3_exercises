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


## [Review 1](review/01.txt)
Why would we want to have different element types for different `vector`s?

## [Review 2](review/02.txt)
What is a template?

## [Review 3](review/03.txt)
what is generic programming?

## [Review 4](review/04.txt)
How does generic programming differ from object-oriented programming?

## [Review 5](review/05.txt)
What is a concept?

## [Review 6](review/06.txt)
What benefits do we get from the use of concepts?

## [Review 7](review/07.txt)
Name four standard-library concepts.

## [Review 8](review/08.txt)
How does `resize()` differ from `reserve()`?

## [Review 9](review/09.txt)
What is a resource?
Define and give examples.

## [Review 10](review/10.txt)
What is a resource leak?

## [Review 11](review/11.txt)
List the three resource-management guarantees.

## [Review 12](review/12.txt)
How can the use of a built-in pointer lead to a resource leak?
Give examples.

## [Review 13](review/13.txt)
What is RAII?
What problem does it address?

## [Review 14](review/14.txt)
What is `unique_ptr` good for?

## [Review 15](review/15.txt)
What is `shared_ptr` good for?


## [Exercise 1](exercises/01/main.cpp)
Write a template function `add()` that adds the elements of one `vector<T>` to the elements of another; for example, `add(v1, v2)` should do `v1[i] += v2[i]` for each element of `v1`.

## [Exercise 2](exercises/02/main.cpp)
Write a template function that takes a `vector<T> vt` and a `vector<U> vu` as arguments and returns the sum of all `vt[i] * vu[i]`s.

## [Exercise 3](exercises/03/main.cpp)
Write a template class `Pair` that can hold a pair of values of any type.
Use this to implement a simple symbol table like the one we used in the calculator (§6.8).
