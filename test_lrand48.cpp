#include <iostream>
#include <cstdlib>

using namespace std;

void display(char alpha[], int lo, int hi);
void display(int num[], int lo, int hi);

int main(void) {

  char alpha[52];
  int num[100];
  int i, k;
  k = 0;
  for (i=0; i<26; i++) {
   alpha[i] = 'a' + i;
  }

  for (i=26; i<52; i++) {
    alpha[i] = 'A' + k;
    k = k + 1;
  }
  
  display(alpha, 0, 26);
  display(alpha, 26, 52);

  for (i = 0; i<100; i++) {
    num[i] = lrand48()%99 + i;
  }

  display(num, 0, 10);
  display(num, 90,100);

  for(i=0; i<100; i++) {
    display(num, i, i+1);
  }

  cout << "Done.\n";

  return 0;
}

void display(char alpha[], int lo, int hi) {
  int t;
  for(t=lo; t<hi; t++) {
    cout<< alpha[t]<<" ";
  }
  cout << endl;
}

void display(int num[], int lo, int hi) {
  int i;
  for(i=lo; i<hi; i++) {
    cout << num[i] << " ";
  }
  cout<<endl;
}
