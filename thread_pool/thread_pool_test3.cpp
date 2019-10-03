#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <unordered_map>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/condition_variable.hpp>
#include <mutex>
#include <string>

std::mutex mx2;


class thread_pool {
private:
  boost::asio::io_service ios; // asynch io process, has internal enque/dequeue processes based on proactor design pattern
  std::unique_ptr<boost::asio::io_service::work> work_ios; // prevents ios from shutting down
  boost::thread_group thread_grp;
  int threads_free;
  boost::mutex mx;
  boost::condition_variable cv;
public:

   thread_pool( int pool_size = 0 ) : work_ios{std::make_unique<boost::asio::io_service::work>(ios)}, threads_free{pool_size} {
      if(pool_size>0) 
        pool_size = boost::thread::hardware_concurrency()*2;
      for ( int i = 0; i < pool_size; ++i )
        thread_grp.create_thread( boost::bind( &boost::asio::io_service::run, &ios ) );
    }

  ~thread_pool() {
    work_ios.reset();
    try  { thread_grp.join_all(); }
    catch ( const std::exception& ) {}
    ios.stop();
  }

  void stop_service() {
    work_ios.reset(); // waits for all threads to complete
    thread_grp.join_all();
    ios.stop();
  }

  template < typename Job >
  void run_job( Job job ) {
    boost::unique_lock< boost::mutex > lock( mx );

    // if ( 0 == threads_free ) return;
    while (threads_free==0) cv.wait(lock);
    --threads_free;
    ios.dispatch( boost::bind( &thread_pool::wrap_job, this, boost::function< void() >(job) ));
  }

private:
  void wrap_job( boost::function< void() > job ) {
    try { job(); }
    catch ( const std::exception& ) {}

    {
      boost::unique_lock< boost::mutex > lock( mx );
      ++threads_free;
    }
    cv.notify_one();
  }
};


std::unordered_map<int, std::string> ht2;

void func1() { 
    int x{0}; 
    while (true) {
      //std::cout << "func1 done " << std::endl;
      x++; 
      if (x>100000000) break; 
    }
  ht2[1] = "func1 done";
  std::cout << "func1 done " << std::endl;
};

struct func2 {
  void operator()() { 
    int x{0}; 
    while (true) {
      x++; 
      //std::cout << "func2 done " << std::endl;
      if (x>100000) break; 
    }
    ht2[2] = "func2 done"; 
    std::cout << "func2 done " << std::endl;
  };
};

void func3( int ) { 
  int x{0}; 
  while (true) {
    x++; 
     //std::cout << "func3 done " << std::endl;
    if (x>1000000) break; 
  }
  ht2[3] = "func3 done"; 
  std::cout << "func3 done " << std::endl;
};

void func4(int i) {
  try { 
    int x{0}; 
    while (true) {
      x++; 
      if (x>1000000) break; 
    }
    
    ht2[4] = "func4 done"; 
    std::cout << "func4 done " << std::endl;
  }
  catch (std::exception &e) { }
}



int main () {


  thread_pool tp{2};
  

  tp.run_job( func1 ); 
  tp.run_job( func2() );
  tp.run_job( boost::bind( func3, -21 ) );
  tp.run_job( boost::bind( func4, 99 ) );
  tp.run_job( boost::bind( func4, 101 ) );
  tp.run_job( boost::bind( func3, -99 ) );
  tp.run_job( func2() );

  tp.stop_service();
  

  std::cout << "Main finished " << std::endl;
  return 0;  
};
