#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>

class thread_pool {
  private:
    boost::asio::io_service ios;
    boost::asio::io_service::work work_ios;
    boost::thread_group thread_grp;
    unsigned short threads_free;
    boost::mutex mx;
  public:

    // Constructor.
    thread_pool( int pool_size = 0 ) : work_ios( ios ), threads_free( pool_size )  {
      if(pool_size>0) 
        pool_size = boost::thread::hardware_concurrency()*2; // default to double number of cores
      for ( int i = 0; i < pool_size; ++i )
        thread_grp.create_thread( boost::bind( &boost::asio::io_service::run, &ios ) );
    }

    // Destructor.
    ~thread_pool() {
      ios.stop(); // Ensure all threads in ios::run() are stopped
      try { thread_grp.join_all(); }
      catch ( const std::exception& ) {}
    }

    // if thread is free, add a job
    template < typename Job >
    void run_job( Job job ) {
      boost::unique_lock< boost::mutex > lock( mx );
      if ( 0 == threads_free ) return; // exit if no available threads
      --threads_free; // Decrement thread count
      ios.dispatch(boost::bind( &thread_pool::wrapper, this, boost::function< void() >( job ) ));
      // ios.post( boost::bind( &thread_pool::wrapper, this, boost::function< void() >( job ) ) );
    }

  private:
    // Called from run_job
    //  Wrap the job and ensure thread free count is incremented safely
    void wrapper( boost::function< void() > job ) {
      try { job(); } // executes the job
      catch ( const std::exception& ) {}

      // increment available threads, once job finished
      boost::unique_lock< boost::mutex > lock( mx );
      ++threads_free;
    }
};

void work() { std::cout << "work()" << "\n";};

struct worker {
  void operator()() { std::cout << "struct work" << "\n"; };
};

void more_work( int ) {std::cout << "more_work( int )" << "\n"; };

void exec_sql(int i) {
    //std::cout << "Value of i " << i << "\n";
    //SAConnection con; // connection object
    //long ret{0};
    
    std::cout << "Before try "<< "\n";
    try {
     std::cout << "In try "<< "\n";
    /*  con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
      con.setAutoCommit(SA_AutoCommitOff);
      con.setIsolationLevel(SA_Serializable);
      SACommand cmd1(&con, std::string("update test1 set y = 'Black' where x in(2,3,4)").c_str());
      cmd1.Execute();

      //ret = cmd1.RowsAffected();
      con.Commit(); */
    }
    //catch (SAException &x) {
    catch (std::exception &x) {
      //std::cout << (const char*)x.ErrText() << "\n";
    }

    //con.Disconnect();
    //return ret; */
}

int main () {

  // boost::thread_group tgroup;
  
  std::string sql{"update test1 set y = 'Black' where x in(2,3,4)"};
  //tgroup.create_thread(boost::bind( &exec_sql, sql));

  // long ret = exec_sql("update test1 set y = 'Yellow' where x in(2,3,4)");  
  // std::cout << "return " << ret << "\n";
  thread_pool tp{4};
  
  tp.run_job( work );                        // Function pointer.
  tp.run_job( worker() );                    // Callable object.
  tp.run_job( boost::bind( more_work, 5 ) ); // Callable object.
  tp.run_job( boost::bind( exec_sql, 5 ) ); // Callable object.

  // tp.run_job( exec_sql);

  //tgroup.join_all();

  return 0;
  
};
