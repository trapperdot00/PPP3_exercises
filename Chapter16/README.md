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


## [Review 1](review/01.txt)
What does "Caveat emptor!" mean?

## [Review 2](review/02.txt)
What is an array?

## [Review 3](review/03.txt)
How do you copy an array?

## [Review 4](review/04.txt)
How do you initialize an array?

## [Review 5](review/05.txt)
When should you prefer a pointer argument over a reference argument?
Why?

## [Review 6](review/06.txt)
When should you prefer a `span` over a pointer?
Why?

## [Review 7](review/07.txt)
How does `std::array` differ from a built-in array?

## [Review 8](review/08.txt)
What good is range-checking?

## [Review 9](review/09.txt)
What information do you need to do range checking?

## [Review 10](review/10.txt)
What good can a `not_null` do?

## [Review 11](review/11.txt)
What is a C-style string?

## [Review 12](review/12.txt)
What is a palindrome?


## [Exercise 1](exercises/01/main.cpp)
Write a function, `void to_lower(char* s)`, that replaces all uppercase characters in the C-style string `s` with their lowercase equivalents.
For example, `Hello, World!` becomes `hello, world!`.
Do not use any standard-library function.
A C-style string is a zero-terminated array of characters, so if you find a `char` with the value `0` you are at the end.

## [Exercise 2](exercises/02/main.cpp)
Write a function, `char* str_dup(const char*)`, that copies a C-style string into memory it allocates on the free store.
Do not use any standard-library function.

## [Exercise 3](exercises/03/main.cpp)
Write a function, `char* find_x(const char* s, const char* x)`, that finds the first occurence of the C-style string `x` in `s`.

## [Exercise 4](exercises/04/main.cpp)
Write a function, `int str_cmp(const char* s1, const char* s2)`, that compares C-style strings.
Let it return a negative number if `s1` is lexicographically before `s2`.
Do not use any standard-library functions.
Do not use subscripting; use the dereference operator `*` instead.

## [Exercise 5](exercises/05/main.cpp)
Consider what happens if you give your `str_dup()`, `find_x()`, and `str_cmp()` a pointer argument that is not a C-style string.
Try it!
First figure out how to get a `char*` that doesn't point to a zero-terminated array of characters and then use it (never do this in real - non-experimental - code; it can create havoc).
Try it with free-store-allocated and stack-allocated "fake C-style strings."
If the results still look reasonable, turn off debug mode.
Redesign and re-implement those three functions so that they take another argument giving the maximum number of elements allowed in argument strings.
Then, test that with correct C-style strings and "bad" strings.

## [Exercise 6](exercises/06/main.cpp)
See what happens if you give the standard-library function `strcmp()` a pointer argument that is not a C-style string.

## [Exercise 7](exercises/07/main.cpp)
Write a function, `string cat_dot(const char* s1, const char* s2)`, that concatenates two strings with a dot in between.
For example, `cat_dot("Niels", "Bohr")` will return a string containing `Niels.Bohr`.

## [Exercise 8](exercises/08/main.cpp)
Write a version of `cat_dot()` that takes `const string&` arguments.

## [Exercise 9](exercises/09/main.cpp)
Modify `cat_dot()` from the previous two exercises to take a string to be used as the separator (rather than dot) as its third argument.

## [Exercise 10](exercises/10/main.cpp)
Write versions of the `cat_dot()`s from the previous exercises to take C-style strings as arguments and return a free-store-allocated C-style string as the result.
Do not use standard-library functions or types in the implementation.
Test these functions with several strings.
Be sure to free (using `delete`) all the memory you allocated from free store (using `new`).
Compare the effort involved in this exercise with the effort involved for exercises 5 and 6.

## [Exercise 11](exercises/11/main.cpp)
Rewrite all the functions in §16.5 (palindromes) to use the approach of making a backward copy of the string and then comparing; for example, take `"home"`, generate `"emoh"`, and compare those two strings to see that they are different, so _home_ isn't a palindrome.

## [Exercise 12](exercises/12/main.cpp)
Look at the "array solution" to the palindrome problem in §16.5.2.
Fix it to deal with long strings by (a) reporting if an input string was too long and (b) allowing an arbitrarily long string.
Comment on the complexity of the two versions.

## [Exercise 13](exercises/13/main.cpp)
Implement a version of the game "Hunt the Wumpus."
"Hunt the Wumpus" (or just "Wump") is a simple (non-graphical) computer game originally invented by Gregory Yob.
The basic premise is that a rather smelly monster lives in a dark cave consisting of connected rooms.
Your job is to slay the wumpus using bow and arrow.
In addition to the wumpus, the cave has two hazards: bottomless pits and giant bats.
If you enter a room with a bat, the bat picks you up and drops you into another room.
If you enter the room with the wumpus or he enters yours, he eats you.
When you enter a room, you will be told if a hazard is nearby:
 - "I smell the wumpus": It's in an adjoining room.
 - "I feel a breeze": One of the adjoining rooms is a bottomless pit.
 - "I hear a bat": A giant bat is in an adjoining room.
For your convenience, rooms are numbered.
Every room is connected by tunnels to three other rooms.
When entering a room, you are told something like "You are in room 12; there are tunnels to rooms 1, 13, and 4; move or shoot?"
Possible answers are `m13` ("Move to room 13") and `s13-4-3` ("Shoot an arrow through rooms 13, 4, and 3").
The range of an arrow is three rooms.
At the start of the game, you have five arrows.
The snag about shooting is that it wakes up the wumpus and he moves to a room adjoining the one he was in - that could be your room.

Probably the trickiest part of the exercise is to make the cave by selecting which rooms are connected with which other rooms.
You'll probably want to use a random number generator (e.g., `randint()` from `PPP_support`) to make different runs of the program use different caves and to move around the bats and the wumpus.
Hint: Be sure to have a way to produce a debug output of the state of the cave.
