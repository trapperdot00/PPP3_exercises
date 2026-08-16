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

## [Drill](drill/main.cpp)
Write a class `Ptr` that has a `double*` private member called `p`.
Give `Ptr` the essential operations as described in §17.5.
A constructor should take a `double` argument, allocate a `double` on the free store, assign the pointer to it to `p`, and copy the argument into `*p`.
Give `Ptr` an operator `*` that allows you to read and write `*p`.
Test `Ptr`.
