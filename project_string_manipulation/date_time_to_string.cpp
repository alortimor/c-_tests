#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>

class Random {
  private:
    std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<unsigned int> uniform_dist{0, UINT32_MAX};
  public:
    Random() = default;
    Random(const Random &) = delete;
    Random & operator=(const Random &) = delete;
    Random(std::mt19937::result_type seed) : eng{seed} {}

    unsigned int generate();
    unsigned int generate(unsigned int max);

    std::string gen_random_string (int size);
};

unsigned int Random::generate() {
  return uniform_dist(eng);
}

unsigned int Random::generate(unsigned int max) {
  return uniform_dist(eng, decltype(uniform_dist)::param_type(0, max));
}

std::string Random::gen_random_string (int size ) {

  const std::string VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string str;

  std::generate_n(std::back_inserter(str), size, [&]() {
    return VALID_CHARS[generate(VALID_CHARS.size()-1)];
  });
  return str;
}


template<typename Clock, typename Duration>
std::ostream &operator<<(std::ostream &stream,
  const std::chrono::time_point<Clock, Duration> &time_point) {
  const time_t time = Clock::to_time_t(time_point);
  struct tm tm;
  localtime_r(&time, &tm);
  return stream << std::put_time(&tm, "%c"); // Print standard date&time
}


int main () {
  
  
  // this uses the template
  std::cout << std::chrono::system_clock::now() << std::endl;
  
  // three different ways to convert date time to a string
  
  // method 1
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
  std::string str(buffer);

  std::cout << "Method 1 " <<  str << std::endl;

  // method 2

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  auto output_tm = std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
  std::cout << "Method 2 " << output_tm   << std::endl;


  // method 3
  std::time_t now;
  now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  char buf[100] = {0};
  std::strftime(buf, sizeof(buf), "%Y%m%d %H:%M:%S", std::localtime(&now));
  std::cout << "Method 3 " << buf << std::endl;
  
  
  // To find the difference in duration between 2 time points.
  Random r;
  // std::chrono::time_point<std::chrono::system_clock> tp;
  std::chrono::time_point<std::chrono::system_clock>  start, end;

  start = std::chrono::system_clock::now();
  
  std::this_thread::sleep_for(std::chrono::milliseconds{r.generate(500)});
  end = std::chrono::system_clock::now();

  auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << difference.count() << std::endl;
  
  return 0;
}
