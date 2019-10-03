#include <chrono>
#include <iostream>

/*
  // time point represents a point in a time period
  // For example 25th Feb 2019 is a point in the period (modern day Augustine calendar).
  // Each point requires a reference point, for the 25th Dec 2019, the reference point is year 0, which is
  // the birth of Jesus Christ.


  // the reference point used for
  // std::chrono::time_point<>
  //   is 00:00 January 1, 1970 (Coordinated Universal Time - UTC) -- represents the epoch of a clock
  
  // point in time is therefore relatve to the epoch of a clock

  // therefore, for the following:
  // time_point<system_clock, milliseconds>: 
  // according to system_clock, elapsed time since epoch (00:00 January 1, 1970) in milliseconds

   a time_point therefore requires 2 parameters, a clock and a duration                                          
                                             
*/
  
int main() {

  // most important part of a clock is its frequency (or period)
  // In C++ a clocks period or frequency is represented with a ratio
  std::ratio<1,10> r; // this is a ratio of 1/10 (one tenth)
  
  // you can show a ratios numerator and denominator:
  std::cout << r.num << "/" << r.den << "\n";

  // if you change std::ration<1,10> to std::ration<2,10>, cout will show 1/5  
  // you can print out a clocks period with the same method:
  
  std::cout << std::chrono::system_clock::period::num << "/" << std::chrono::system_clock::period::den << "\n";
  std::cout << std::chrono::steady_clock::period::num << "/" << std::chrono::steady_clock::period::den << "\n";
  
  // on this laptop the period for both steady and system clocks is 100 nanoseconds, i.e. 1/1000000000

  std::chrono::microseconds mi(2700); // 2700 microseconds
  std::chrono::nanoseconds na = mi; // 2700000 nanoseconds
  
  // this will not compile as it converts a lower to a higher resolution
  // since some information might be lost
  // std::chrono::microseconds mill = mi;
  
  // Instead a cast has to be performed when converting from lower to a higher resolution, e.g.
  std::chrono::microseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>(mi);
  // 2 milliseconds, NOTE, 700 microseconds are lost due to truncation. It is not rounded to 3!
  
  mi = mill + mi; // 2000 + 2700 = 4700

  // use count to return current value
  std::cout << "mi " << mi.count() << " na " << na.count() << " mill " << mill.count() << "\n";
  
  // time_point usage
  std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
  std::cout << tp.time_since_epoch().count() << std::endl;
  // std::chrono::system_clock::now() returns current time of system clock
  
  tp += std::chrono::seconds(2);
  std::cout << tp.time_since_epoch().count() << std::endl;

  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  
  std::cout << "A random message to ensure elapsed time has occurred"  << std::endl;

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  
  std::chrono::steady_clock::duration d = end - start;
  
  // there might not be any elpased time, so verify by checking against zero
  /*
  if (d == 0)
    std::cout << "No elapsed time" << std::endl;

  //The above will not compile, since 0 is an integer, and not of
    the same type as std::chrono::steay_clock

  // So you have to use use std::chrono::steady_clock::duration::zero()
  */

  if (d == std::chrono::steady_clock::duration::zero())
    std::cout << "No elapsed time" << std::endl;
  else
    // std::cout << "Elapsed time: " <<  d.count() << std::endl; OR
    // if viewed in microseconds:
    std::cout << "Elapsed time: " <<  std::chrono::duration_cast<std::chrono::microseconds>(d).count() << std::endl;
    
  return 0;
}
