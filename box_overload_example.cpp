#include <iostream>

class Box {
   public:
      // constructor
      Box(const double l = 0.0, const double b = 0.0, const double h = 0.0)
      : length(l), breadth(b), height(h) { }

      double show_length() {
        return length;
      }
      void show_all_box_measurements(Box &b) {
      }   const;

      // Overload + operator to add two Box objects.
      Box operator+(const Box &b) {
         Box box(0.0,0.0,0.0);
         box.length = this->length + b.length;
         box.breadth = this->breadth + b.breadth;
         box.height = this->height + b.height;
         return box;
      }

   private:
      double length;      // Length of a box
      double breadth;     // Breadth of a box
      double height;      // Height of a box
};

// Main function for the program
int main( ) {
   Box Box1(1,4,2);                // Declare Box1 of type Box
   Box Box2(3,4,1);                // Declare Box2 of type Box
   Box Box3(0,1,1);                // Declare Box3 of type Box

 
   // Add two object as follows:
   Box3 = Box1 + Box2;

   std::cout << "Length : " << Box3.show_length() << std::endl;

   return 0;
}
