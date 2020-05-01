# how to compile a c++ source file into a executable

~~~
// step 1: compile a source file
g++ main.cpp ./src/hello1.cpp -o test1 -I ./include
~~~
> ./ mean the current directory
 
> g++ xx1.cpp xx2.cpp means combine these source file

> -o means output the target file

> -I: specify the search path of include file of external library 
~~~
// step2: execute
./test1
~~~

# [option] understand the functionality of head file and source file

try the following command, and then see what happens.
~~~
g++ main.cpp ./src/hello2.cpp -o test2 -I ./include
./test
~~~

the results imply that: the head file serves as interface, the source file serve as implementation. the example above shows that we can have different implementation regarding the interface, and then we can choose one implementation according our need. That is the benefit of such separation between interface and implementation. 


>
