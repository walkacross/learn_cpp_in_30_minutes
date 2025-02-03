# 1 Expressions

> any value or any valid combinaton of values and operators constitute an expression, and every c++ expression has a value

### (1) the simplest case
~~~
22 + 27   // add operator
x = 20    // assignment operator
~~~

### (2) relational expressions
~~~
x < y   // True is 1 and False is 0
~~~ 

# 2 Statements

### 2.1 expression statement

> from expression to state is a short step: you just add a semicolon. the reverse is not

~~~
age = 100   // is a expression
age = 100;  // is a statement, more particularly, it's a expression statement
~~~

### 2.2 declaration statement
~~~
int toad;
~~~

### 2.3 branching statement
~~~
// syntax
statement1
if (condition_expr)
    statement2
else
    statement3
statement4

// concrete example
int answer = 12;
if (answer > 10)
    std::cout << "answer is more than 10";
else
    std::cout << "answer is less than 10";
std::cout << "done" << std::endl;
~~~

### 2.4 loop statement
for states don't fit the statement = expression + semicolon mold.
~~~
// syntax
for (init_expression; condition_expression; update_expression)
    statement

// concrete example
int i;
for (i = 0; i<5; i++)
    std::cout << "i is " << i << std::endl;
~~~
