#include <iostream>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>



int main(int argc, char* argv[]) {
    SAConnection con; // connection object

    try {
      con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
      con.setAutoCommit(SA_AutoCommitOff);
      con.setIsolationLevel(SA_Serializable);
      //SACommand cmd1(&con, "begin transaction isolation level serializable");
      //cmd1.Execute();
      SACommand cmd1(&con);
      cmd1.setCommandText("delete from test1 where x in (5,6,1)");
      cmd1.Execute();
      std::cout << "Rows affected : " << cmd1.RowsAffected() << "\n";

      cmd1.setCommandText("insert into test1 (x,y) values (6,'Black')");
      cmd1.Execute();
      std::cout << "Rows affected : " << cmd1.RowsAffected() << "\n";
      cmd1.setCommandText("insert into test1 (x,y) values (5,'White')");
      cmd1.Execute();


      // con.Commit();
      
      /*cmd1.setCommandText("begin transaction isolation level serializable");
      cmd1.Execute();
      cmd1.setCommandText("insert into test1 (x,y) values (6,'Orange')");
      cmd1.Execute();

      con.Commit(); // commit without a begin in PostgreSQL generates a WARNING message that there is no other transaction on the go

      cmd1.setCommandText("begin transaction read only");
      cmd1.Execute();
      cmd1.setCommandText("select x,y from test1 where x in (-99)");

      cmd1.Execute();
      std::cout << "Is Result : " << cmd1.isResultSet() << "\n";
      while(cmd1.FetchNext()) {
        std::cout << (const char*)cmd1.Field(1).Name() <<  " " << (const long)cmd1.Field(1).FieldNativeType() << (const long)cmd1[1].Pos() << " "  << cmd1.Field(1).asLong() << ", "
                  << (const char*)cmd1.Field("y").asString() << "\n";
      }
      con.Commit(); */
    }
    catch(SAException &x) {
      std::cout << (const char*)x.ErrText() << "\n";
    }
    return 0;
};
