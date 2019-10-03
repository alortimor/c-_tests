#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <iostream>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>
#include <boost/atomic.hpp>

boost::atomic_int producer_count(0);
boost::atomic_int consumer_count(0);

boost::lockfree::queue<int> queue(128);

const int iterations = 10000000;
const int producer_thread_count = 4;
const int consumer_thread_count = 4;


int main(int argc, char* argv[]) {
    SAConnection pconn; // PostgeSQL connection
    SAConnection sconn; // SQL Anywhere connection


    try {
      con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
      SACommand cmd1(&con, "begin transaction isolation level serializable");
      cmd1.Execute();
      cmd1.setCommandText("select x,y from test1");
      cmd1.Execute();

      con.Commit();
      
      while(cmd1.FetchNext()) {
        std::cout << cmd1.Field("x").asLong() << ", "
                  << (const char*)cmd1.Field("y").asString() << "\n";
      }
    }
    catch(SAException &x) {
      try {
        con.Rollback();
      }
      catch(SAException &) { }
      printf("%s\n", (const char*)x.ErrText());
    }
    return 0;
};
