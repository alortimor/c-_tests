#include <vector>
#include <future>
#include <cstdlib>

// int rn = (std::rand() % (100 + 1));

struct fdv {
  private:
    int _num; int _denom;
  public:
    fdv(int num, int denom ) : _num{num}, _denom{denom} { }
    bool get_result() const {
      try { num/denom; return true; }
      catch (const std::exception& e) { return false; }
    }
}

struct executor {

  private:
    std::vector<fdv> v_fdv;
    int rn{0};
  public:
    void set_all() {
      std::srand(std::time(0));
      for (int i{10}; i<1000; ++i) {
        rn = rand() % 30 + (-10);
        v_fdv.emplace_back(i, rn);
      }
      
    }
    void execute_all() {
      std::vector<std::future<void>> futures;

      for ( auto & d : v_fdv )
        futures.push_back(std::async([&d] () { d.execute_sql_grains(); } ));

  for (auto & fut : futures)
    fut.get();
    }
}

int main() {

  return 0;
}

