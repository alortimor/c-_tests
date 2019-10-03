#include <chrono>
#include <iostream>

// elapsed time can be represented by  seconds, milliseconds, microseconds, nano seconds and picel seconds
// chrono is a precision-neutral library

// types of chrono clocks:
// 1 - std::chrono::system_clock: current time based on system clock (which can be modified by user)
                                  // system_clock is not steady
// 2 - std::chrono::steady_clock: goes at a uniform rate (true elapsed time, independent of user intervention)
// 3 - std::chrono::high_resolution_clock: provides smallest possible tick period

/*
 Duration is represented by
std::chrono::duration<>: represents time duration
  
  // this is the default for duration
  duration<int, ratio<1,1>> // ratio<1,1> is 1 second, which is stored as int in duration
   
  // non-default setting
  duration<double, ratio<60,1>> // ratio<60,1> is 1 minute, which is stored as double in duration

  // chrono provides convenient type defs:
    nanoseconds, microseconds, milliseconds, seconds, minutes, hours
     

  // Each type of clock has its own predefined duration, for example the system clock has a duration:
  system_clock::duration -- duration<T, system_clock::period>
  which is a duration of type T, T can be any signed arithmetic type




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
  
  return 0;
}
