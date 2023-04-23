# file read and write in CPP
C++ provides the following classes to perform output and input of characters to/from files: 

* ofstream: Stream class to write on files
* ifstream: Stream class to read from files
* fstream: Stream class to both read and write from/to files.

![](https://upload-images.jianshu.io/upload_images/580472-75ece018cc174c5a.png?imageMogr2/auto-orient/strip|imageView2/2/w/529/format/webp)

# 1 basic overview of input with file
~~~
// basic file operations
#include <iostream>
#include <fstream>
using namespace std;

int main () {
    ofstream myfile;
    myfile.open ("example.txt");
    myfile << "Writing this to a file.\n";
    myfile << "this is another line.\n";
    myfile.close();
    return 0;
}
~~~

# 2 output with file

> https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html

~~~
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  ifstream myfile ("example.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}
~~~
We have created a while loop that reads the file line by line, using getline. The value returned by getline is a reference to the stream object itself, which when evaluated as a boolean expression (as in this while-loop) is true if the stream is ready for more operations, and false if either the end of the file has been reached or if some other error occurred.


# 3 other attributes

## 3.1 checking state flags
The following member functions exist to check for specific states of a stream (all of them return a bool value): 

* bad() :Returns true if a reading or writing operation fails.
* fail() :
* eof() : Returns true if a file open for reading has reached the end.
* good() : It is the most generic state flag: it returns false in the same cases in which calling any of the previous functions would return true. Note that good and bad are not exact opposites

## 3.2 get and put stream positioning
All i/o streams objects keep internally -at least- one internal position:

ifstream, like istream, keeps an internal get position with the location of the element to be read in the next input operation.

ofstream, like ostream, keeps an internal put position with the location where the next element has to be written.

Finally, fstream, keeps both, the get and the put position, like iostream.

These internal stream positions point to the locations within the stream where the next reading or writing operation is performed. These positions can be observed and modified using the following member functions: 


### tellg() and tellp()
These two member functions with no parameters return a value of the member type streampos, which is a type representing the current get position (in the case of tellg) or the put position (in the case of tellp).

### seekg() and seekp()
These functions allow to change the location of the get and put positions. Both functions are overloaded with two different prototypes. The first form is:
~~~
seekg ( position );
seekp ( position );
~~~
Using this prototype, the stream pointer is changed to the absolute position position (counting from the beginning of the file). The type for this parameter is streampos, which is the same type as returned by functions tellg and tellp.

The other form for these functions is:
~~~
seekg ( offset, direction );
seekp ( offset, direction );
~~~
Using this prototype, the get or put position is set to an offset value relative to some specific point determined by the parameter direction.

~~~
// obtaining file size
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  streampos begin,end;
  ifstream myfile ("example.bin", ios::binary);
  begin = myfile.tellg();
  myfile.seekg (0, ios::end);
  end = myfile.tellg();
  myfile.close();
  cout << "size is: " << (end-begin) << " bytes.\n";
  return 0;
}
~~~
