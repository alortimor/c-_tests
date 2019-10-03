
std::mutex m_mutex;

// Thread 1

      con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
     
     {
      std::lock_guard<std::mutex> locker(m_mutex);
      SACommand cmd1(&con, "begin transaction isolation level serializable");
      cmd1.Execute();
     }
      cmd1.setCommandText("delete from test1 where x in (5,6,1)");
      cmd1.Execute();
      cmd1.setCommandText("insert into test1 (x,y) values (5,'White')");
      cmd1.Execute();

     {
      std::lock_guard<std::mutex> locker(m_mutex);
      con.Commit();
     }


// Thread 2
      con.Connect("//10.11.12.18:1521/ftnode", "ordb", "ordb", SA_Oracle_Client);
     {
      std::lock_guard<std::mutex> locker(m_mutex);
      SACommand cmd1(&con, "set isolation level serializable");    // command object
      cmd1.Execute();
     }

      cmd1.setCommandText("delete from test1 where x in (5,6,1)");
      cmd1.Execute();
      cmd1.setCommandText("insert into test1 (x,y) values (5,'White')");
      cmd1.Execute();
     {
      std::lock_guard<std::mutex> locker(m_mutex);
      con.Commit();
     }


std::mutex m_mutex;

// Thread 1

      con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
      con.setAutoCommit(SA_AutoCommitOff);
     {
      std::lock_guard<std::mutex> locker(m_mutex);
      con.setIsolationLevel(SA_Serializable);
     }
      cmd1.setCommandText("delete from test1 where x in (5,6,1)");
      cmd1.Execute();
      cmd1.setCommandText("insert into test1 (x,y) values (5,'White')");
      cmd1.Execute();

     {
      std::lock_guard<std::mutex> locker(m_mutex);
      con.Commit();
     }


// Thread 2
      con.Connect("//10.11.12.18:1521/ftnode", "ordb", "ordb", SA_Oracle_Client);
     {
      std::lock_guard<std::mutex> locker(m_mutex);
      SACommand cmd1(&con, "set isolation level serializable");    // command object
      cmd1.Execute();
     }

      cmd1.setCommandText("delete from test1 where x in (5,6,1)");
      cmd1.Execute();
      cmd1.setCommandText("insert into test1 (x,y) values (5,'White')");
      cmd1.Execute();
     {
      std::lock_guard<std::mutex> locker(m_mutex);
      con.Commit();
     }




