#include <iostream>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>

// SET OPTION PUBLIC.isolation_level = 2

// Ensure the following command is executed on the server, prior to executing transaction in snapshot isolation level
// SET OPTION PUBLIC.allow_snapshot_isolation = 'On' // By default 
                                                     // This command must be issued in the database before running any programs

// To identify whether a database server is in SI mode, run the following query:
// SELECT DB_PROPERTY ( 'SnapshotIsolationState' )

// To increase the maximum number of allowable connections, run the following server command:
// set OPTION PUBLIC.max_connections=20

int main(int argc, char* argv[]) {
    SAConnection con;
    SACommand cmd(&con);
    
    SAConnection con1;
    SACommand cmd1(&con1);

    try {
      con.Connect("links=tcpip(host=localhost;port=2638);databasename=ftnode_sa;servername=ftnode_sa", "sadb", "sadb", SA_SQLAnywhere_Client);
      con1.Connect("links=tcpip(host=localhost;port=2638);databasename=ftnode_sa;servername=ftnode_sa", "sadb", "sadb", SA_SQLAnywhere_Client);
      
      con.setAutoCommit(SA_AutoCommitOff);
      con.setIsolationLevel(SA_RepeatableRead);


//      cmd1.setCommandText("begin snapshot");
  //    cmd.Execute();
      

      cmd.setCommandText( std::string("insert into test1 (x,y) values (1,'Green')").c_str() );
      cmd.Execute();

      cmd.setCommandText( std::string("update test1 set y = 'Grey' where x = 1").c_str() );
      cmd.Execute();

      cmd.setCommandText("select x, y from test1");
      cmd.Execute();
      
      while(cmd.FetchNext())
        std::cout << "Row : x = " << cmd.Field("x").asLong() << ", y = " << (const char*)cmd.Field("y").asString() << "\n";

      con.Commit();
      
      std::cout << "Transaction completed sucessfully.\n";
    }
    catch(SAException &x) {
      std::cout << "Error : " << (const char*)x.ErrText() << "\n";
    }
    return 0;
};
