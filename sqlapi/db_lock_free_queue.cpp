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

SAConnection pcon; // PostgeSQL connection
SAConnection scon; // SQL Anywhere connection


bool dbconn() {

  try {
    pcon.Connect("localhost,5432@ft_node", 
                    "bluefrog", "bluefrog", SA_PostgreSQL_Client);
    scon.Connect("links=tcpip(host=localhost;port=2638);databasename=ftnode_sa;servername=ftnode_sa",
                    "sadb", "sadb", SA_SQLAnywhere_Client);
  }
  catch (SAException &x) {
    std::cout << "Connection error : " << (const char*)x.ErrText() << "\n";
    return false; 
  }
  return true;
}

int main(int argc, char* argv[]) {
      
  if (!dbconn()) return 1;

  try {
    SACommand cmd1(&pcon, "begin transaction isolation level serializable");
    cmd1.Execute();
    cmd1.setCommandText("select x,y from test1");
    cmd1.Execute();

    pcon.Commit();
    
    while(cmd1.FetchNext()) {
      std::cout << cmd1.Field("x").asLong() << ", "
                << (const char*)cmd1.Field("y").asString() << "\n";
    }
  }
  catch (SAException &x) {    
    std::cout << "DML error " << (const char*)x.ErrText() << "\n";
    return 1;
  }

  return 0;
};
