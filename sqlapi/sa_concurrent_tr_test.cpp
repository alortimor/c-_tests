#include <future>
#include <iostream>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>

int main() {
    SAConnection con1;
    SACommand cmd1(&con1);
    SACommand cmd2(&con1);
 
    try {
      con1.Connect("links=tcpip(host=localhost;port=2638);databasename=ftnode_sa;servername=ftnode_sa", "sadb", "sadb", SA_SQLAnywhere_Client);
      con1.setIsolationLevel(SA_RepeatableRead);
      con1.setAutoCommit(SA_AutoCommitOff);
      cmd1.setCommandText("select a,b,d,e,f from t3");
      cmd2.setCommandText("select a,b,d,e,f from t3");

      std::cout << "Start T1 \n";
      std::future<void> select_result ( std::async([&cmd1]() { 
                                                               std::string str;
                                                               cmd1.Execute();
                                                               while (cmd1.FetchNext()) {
                                                                 str = (const char*)cmd1.Field(2).asString();
                                                                 std::cout << str << "\n";
                                                                }
                                                             } ));
      std::cout << "Start T2 \n";
      std::future<void> hash_result ( std::async([&cmd2]()  {
                                                               std::string str;
                                                               cmd2.Execute();
                                                               while (cmd2.FetchNext()) {
                                                                 str = (const char*)cmd2.Field(2).asString();
                                                                 std::cout << str << "\n";
                                                               }
                                                             } ));
      hash_result.get();
      select_result.get();

      con1.Commit();
      std::cout << "Transaction completed.\n";
    }
    catch(SAException &x) {
      std::cout << "Error : " << (const char*)x.ErrText() << "\n";
    }
    return 0;
};
