// statements.cpp  -- using all kinds of statements
#include <iostream>

int main()
{
    using std::cout;
    using std::endl;

    int space = 10;   // expression statements
    int total = 0;

    if (space < 12)
    {
        space = space + 3;
    }
    else
    {
        space = space - 2;
    }

    int counter;
    for (counter =0; counter < 5; counter++)
    {
        total = total + counter;
        cout << "the number of total now is " << total << endl; 
    }
    cout << "done" << endl;
    return 0;
}
