#include <stdio.h>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>

int main(int argc, char* argv[]) {
    SAConnection con; // connection object

    try {
      con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
      SACommand cmd1(&con, "set transaction read write");
      cmd1.Execute();
      SACommand cmd2(&con, "select x, y from test1");
      cmd2.Execute();
      while(cmd2.FetchNext()) {
        printf("Row fetched: x = %ld, y = '%s'\n",
          cmd2.Field("x").asLong(),
          (const char*)cmd2.Field("y").asString());
      }
      con.Commit();
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
