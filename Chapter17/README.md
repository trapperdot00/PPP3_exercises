# 17: Essential Operations

- [Try This](#try-this-1)
- [Drill](#drill)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/main.cpp)
Make a version of this `Vector` that is complete enough to compile and see what error message your compiler produces for `v[3]=x`.

## [Try This 2](try_this/02/main.cpp)
Try executing that.
Then remove the move operations and run it again.
The compilers can be very clever at avoiding unnecessary copies.
We really mean it: do run this example and try to explain the result.
If you do, you'll understand most of what there is to know about construction and destruction of objects.

## [Try This 3](try_this/03/main.txt)
What cases do we need to consider (and test) if we want to convince ourselves that this `resize()` is correct?
How about `newsize == 0`?
How about `newsize == -77`?


## [Drill](drill/main.cpp)
Write a class `Ptr` that has a `double*` private member called `p`.
Give `Ptr` the essential operations as described in §17.5.
A constructor should take a `double` argument, allocate a `double` on the free store, assign the pointer to it to `p`, and copy the argument into `*p`.
Give `Ptr` an operator `*` that allows you to read and write `*p`.
Test `Ptr`.


## [Review 1](review/01.txt)
What is the default meaning of copying for class objects?

## [Review 2](review/02.txt)
When is the default meaning of copying of class objects appropriate?
Inappropriate?

## [Review 3](review/03.txt)
What is a copy constructor?

## [Review 4](review/04.txt)
What is a copy assignment?

## [Review 5](review/05.txt)
What is a move constructor?

## [Review 6](review/06.txt)
What is a move assignment?

## [Review 7](review/07.txt)
What is a default constructor?

## [Review 8](review/08.txt)
What is the difference between a copy constructor and a move constructor?

## [Review 9](review/09.txt)
What is the difference between a copy constructor and a copy assignment?

## [Review 10](review/10.txt)
What is shallow copy?
What is deep copy?

## [Review 11](review/11.txt)
How does the copy of a `vector` compare to its source?

## [Review 12](review/12.txt)
What is the point of copy elision?

## [Review 13](review/13.txt)
What are the essential operations for a class?

## [Review 14](review/14.txt)
What is an `explicit` constructor?

## [Review 15](review/15.txt)
When would you prefer a constructor not to be `explicit`?

## [Review 16](review/16.txt)
How do you define traversal for a container?

## [Review 17](review/17.txt)
What operations may be invoked implicitly for a class object?

## [Review 18](review/18.txt)
What operators are often user-defined?

## [Review 19](review/19.txt)
What is _the rule of zero_?

## [Review 20](review/20.txt)
What is _the rule of all_?

## [Review 21](review/21.txt)
Why don't we just always define a `vector` with large enough size for all eventualities?

## [Review 22](review/22.txt)
Which `vector` operations can change the size of a `vector` after construction?

## [Review 23](review/23.txt)
What is the difference between `reserve()` and `resize()`?

## [Review 24](review/24.txt)
How much spare space do we allocate for a new `vector`?

## [Review 25](review/25.txt)
When must we copy `vector` elements to a new location?

## [Review 26](review/26.txt)
What is the value of a `vector` after a copy?


## [Exercise 1](exercises/01)
Define class `Matrix` to represent a two-dimensional matrix of `doubles`.
A constructor should take two integer arguments specifying the number of rows and columns, e.g., `Matrix{3,4}` has 3 rows and 4 columns.
Provide `Matrix` with operators `=` (assignment), `==` (equality), `[ ]` (subscript), and `+` (addition of corresponding elements).
The subscript operator should take a pairs of indices, e.g., `m[2, 3]` yields the element 3 of the 2nd row.
Indexing should be zero-based.
Range check your indices.
Reject operations on two `Matrix`s with different dimensions.
If your compiler doesn't allow multiple arguments for `[ ]`, use `( )` instead.
Store the elements of your `Matrix` in a single `vector`.
Test `Matrix`.

## [Exercise 2](exercises/02)
Provide `<<` and `>>` for your `Matrix`.
