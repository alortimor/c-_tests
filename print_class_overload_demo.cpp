#include <iostream>
// #include <string>

using std::cout;
using std::endl;

class printData
{
   public:
      void print(int i) {
        cout << "Printing int: " << i << endl;
      }

      void print(double  f) {
        cout << "Printing float: " << f << endl;
      }

      void print(char *c) {
        cout << "Printing character: " << c << endl;
      }
};

int main(void)
{
   printData pd;
 
   // Call print to print integer
   pd.print(5);
   // Call print to print float
   pd.print(500.263);

   // std::string s = "Hello World!";
  
   char s[20] = "Hello World!";
   // Call print to print character - might give a warning in modern compilers
   pd.print(s);
 
   return 0;
}
