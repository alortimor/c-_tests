#include <string>
#include <thread>
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <mutex>
#include <fstream>
#include <memory>
#include <cstdint>

class threadsafe_log {
  private:
    std::ofstream  file;
    std::string file_path;
    std::mutex mx;
    const std::chrono::time_point<std::chrono::system_clock>  start {std::chrono::system_clock::now()}; // since the loggers inception
    // std::chrono::duration d;

  public:
    threadsafe_log (const std::string & path) : file_path(path) {  
      file.open(file_path, std::fstream::app); // open file in append mode so nothing is ever overwritten
    }

    ~threadsafe_log() { file.close() ; }

    void write (const std::string & msg) {
      auto d = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
      std::lock_guard<std::mutex> lk(mx);
      file << d.count() << ": " << msg << std::endl; // assume a new line each time
    }
};

class logger {
  private:
    std::shared_ptr<threadsafe_log> lg;
  public:
    logger (std::shared_ptr<threadsafe_log> logger) : lg(logger) {  }
    void write (const std::string & msg ) { lg->write(msg); }
};

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

void write_to_file_randomly( logger & lg, Random & r, int id, int lines_to_write  ) {
  lines_to_write =  lines_to_write>0 ? lines_to_write : 10; 
  for (int i{0}; i <lines_to_write; i++) {
    lg.write( std::to_string(id) + "," + r.gen_random_string(10) );
    std::this_thread::sleep_for(std::chrono::milliseconds{r.generate(500)});
  }
}

int main() {
  
  Random r;
  // auto file = std::make_shared<threadsafe_log>("test_file.txt");
  logger lg( std::make_shared<threadsafe_log>("test_file.txt"));
  
  std::thread t1( ( write_to_file_randomly ), std::ref(lg), std::ref(r), 1, 5);
  std::thread t2( ( write_to_file_randomly ), std::ref(lg), std::ref(r), 2,12);

  t1.join();
  t2.join();

  return 0;
}
