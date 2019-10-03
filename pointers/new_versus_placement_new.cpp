#include <new>
struct chaff {
  char dross[20];
  int slag;
};

char buffer1[50];
char buffer2[500];

int main() {

  chaff *p1, *p2;
  int *p3, *p4;
  
  // the regular forms of new
  p1 = new chaff;    // place structure in heap
  p3 = new int[20];  // place array in heap
  
  // forms of placement new!
  p2 = new (buffer1) chaff;   // place structure in buffer1
  p4 = new (buffer2) int[20]; // place structure in buffer2

  delete p1;
  delete [] p3;
  delete p2;
  delete [] p4;

  return  0;
}
