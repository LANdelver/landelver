# Code Style Guidelines

- Use real tabs which equate to 4 spaces
- Use tailing brackets:
```C
if (x) {
} else {
}
```
- Do not use one line if statements always use brackets
- Always use precision specification for floating point values
```C
correct:
float f = 0.5f;

incorrect:
float f = 0.5;
```
- All functions will start lowercase and use snake case
```C
void example_function() {}
```
- Prefix functions categorically such that it is obvious what the function is for
```C
correct:
void spr_draw();

incorrect:
void draw();
```
- Use the following template for function header comments
```C
/*
====================
function_name
description
====================
*/
```
- Use the same snake case format for variables
- Avoid unclear abbreviation, favor more explicit variable names
- End all typedefs with _t
- All defs and enums should be all caps snake case
- End all recursive functions with _r to ensure safety
- Default all variables to const until you need to mutate it
- Make a new file for new game systems ex: sprites, music, ai, animations, etc.
