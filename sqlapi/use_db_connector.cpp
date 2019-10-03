#include </home/bluefrog/SQLAPI/include/SQLAPI.h>
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <utility>

struct db_info {
  std::string product;
  std::string con_str; // connection string used to connect to remote database
  std::string usr;
  std::string pswd;
  std::string modify_begin; // command string used to initiate update/delete/insert transaction, i.e. begin (postgre) or set (oracle)
  std::string select_begin; // command string used to initiate select transaction, i.e. begin (postgre) or set (oracle)
  SAClient_t con_cl; // type of connection
  std::unique_ptr<SAConnection> con; //actual connection
};

class db_connector {
  using info_map = std::map<int, db_info>;

public:
  db_connector() { }
  ~db_connector() { }
  using const_iterator = info_map::const_iterator;

  const_iterator begin() const { return db_cons.begin(); }
  const_iterator end() const { return db_cons.end(); }

  void add_connection(int, db_info &&);
  db_info * get_db_info(int db_id) { return &db_cons.at(db_id); }
  
  bool connect(int);
  bool disconnect(int);


private:
    info_map db_cons;
};

void db_connector::add_connection(int db_id, db_info && dbi) {
  db_cons.insert(std::make_pair(db_id, std::forward<db_info>(dbi)));
}

bool db_connector::connect(int db_id) {
  db_info * dbi =  & db_cons.at(db_id) ;
  try {
    db_cons.at(db_id).con->Connect(dbi->con_str.c_str(), dbi->usr.c_str(), dbi->pswd.c_str(), dbi->con_cl);
  }
  catch (SAException &x) {
  // thread safe log message required
  // std::cout << (const char*)x.ErrText() << "\n";
  return false;
}

return true;
}

bool db_connector::disconnect(int db_id) {
  try {
    db_cons.at(db_id).con->Disconnect();
  }
  catch (SAException &x) {
    // thread safe log message required
    // std::cout << (const char*)x.ErrText() << "\n";
    return false;
  }
  return true;
}


int main() {
  db_connector dbc;

  dbc.add_connection(1, db_info{ "postgre"
                                ,"localhost,5432@ft_node"
                                , "bluefrog"
                                , "bluefrog"
                                , "begin transaction isolation level repeatable read"
                                , "begin transaction read only"
                                , SA_PostgreSQL_Client
                                , std::make_unique<SAConnection>()
                                }
                     );

  if ( dbc.connect(1) ) {
    for (auto d = dbc.begin(); d != dbc.end(); ++d) {
      std::cout << (d->second).product << std::endl;
    }
  }

  db_info * dbi =  dbc.get_db_info(1) ;
  SACommand cmd(dbi->con.get());
  cmd.setCommandText("begin transaction isolation level repeatable read");
  cmd.Execute();
  cmd.setCommandText("insert into test1 (x,y) values (6,'Orange')");
  cmd.Execute();

  dbi->con->Commit();

  return 0;
}
