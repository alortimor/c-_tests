#include <iostream>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>

int main(int argc, char* argv[]) {
    SAConnection con; // connection object

    try {
      con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
      SACommand cmd1(&con, "begin transaction read only");
      cmd1.Execute();
      cmd1.setCommandText("select x,y from test1");
      cmd1.setOption("SetCursorName") = "curs";
      cmd1.Execute();

      while(cmd1.FetchNext()) {
        std::cout << cmd1.Field("x").asLong() << ", "
                  << (const char*)cmd1.Field("y").asString() << "\n";
      }

      con.Commit();
    }
    catch(SAException &x) {
      std::cout << (const char*)x.ErrText() << "\n";
    }
    return 0;
};
