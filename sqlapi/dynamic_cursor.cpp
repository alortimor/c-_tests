#include <stdlib.h>
#include <iostream>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>
// #include <samisc.h>

void test_scroll(SAConnection &con) {
	SACommand cmd(&con);
    cmd.setOption(SACMD_SCROLLABLE) = SAOPT_TRUE;
	cmd.setOption("UseCursor") = "1";
	//cmd.setOption("UseDynamicCursor") = "1";
  bool bResult = false;

	cmd.setCommandText("select x,y from test1");
	cmd.Execute();

  bResult = cmd.FetchNext();
  std::cout << bResult << "\n";

/*	int ch;
	std::cout << "ENTER n,p,f,l,a,r or q to quit.\n";

	do {
		std::cin >> ch;
		bool bResult = false;


		try {
			switch(ch)
			{
			case 'n':
				bResult = cmd.FetchNext();
				break;
			case 'p':
				bResult = cmd.FetchPrior();
				break;
			case 'f':
				bResult = cmd.FetchFirst();
				break;
			case 'l':
				bResult = cmd.FetchLast();
				break;
            case 'a':
                std::cout << "ENTER row count: ";
                std::cin >> ch;
                if (1 == ch ) {
                    std::cout << ch << "\n" ;
                    bResult = cmd.FetchPos(ch, false);
                }
                break;
            case 'r':
                std::cout << "ENTER row count: ";
                std::cin >> ch;
                if (1 == ch )  {
                    std::cout << ch << "\n";
                    bResult = cmd.FetchPos(ch, true);
                }
                break;
            }
		}
		catch(SAException &x) {
			std::cout << "ERROR: " << x.ErrText().GetMultiByteChars() << "\n";
		}

		if( bResult )
      std::cout << cmd[1].asString().GetMultiByteChars() << "\n";
		else if( ch != 'q' )
			std::cout << "No Data\n";

	} while ( ch != 'q' ); */
}

int main(int argc, char **argv) {
  SAConnection con; // connection object
	con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);

	try
	{
		//con.setOption("UseAPI") = "OCI7";
		//con.Connect( "ora111", "sys", "java", SA_Oracle_Client);
		//con.setOption("UseAPI") = "DB-Library";
		//con.setOption("SSPROP_INIT_MARSCONNECTION") = "VARIANT_FALSE";
		//con.Connect( "BEDLAM-M\\EN2014@test", "sa", "java", SA_SQLServer_Client);
		//con.Connect( "LocalServer", "sa", "java", SA_ODBC_Client);
        //con.Connect("TestAccess", "", "", SA_ODBC_Client);
		//con.Connect( "test", "postgres", "java", SA_PostgreSQL_Client);
		//con.setAutoCommit(SA_AutoCommitOff);
	
        test_scroll(con);
    }
	catch( SAException& x )
	{
		printf("ERROR: %s\n", (const char*) x.ErrText());
		exit(1);
	}

	return 0;
}
