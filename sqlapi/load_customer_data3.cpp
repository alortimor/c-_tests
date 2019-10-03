#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>
#include <random>

/* ensure the following table exists in schema:
CREATE TABLE C (C_ID NUMeric,C_D_ID NUMeric,C_W_ID NUMeric, d date, c_limit numeric(6), c_discount numeric(4,4) );
ensure the test_c_data.csv file exists and contains something like the following:
$ cat test_c_data.csv 
1,1,1,'CA'
1,2,1,'CA'
1,3,1,'CA'
*/

std::random_device rd; // obtain a random number from hardware
std::mt19937 eng(rd()); // seed the generator
std::uniform_int_distribution<int> distr(300, 2000); // define the range

unsigned int nth_occurrence(const std::string& str, const std::string& findMe, unsigned int nth) {
  unsigned int pos {0};
  unsigned int cnt {0};

  while( cnt != nth ) {
      pos-=1;
      pos = str.rfind(findMe, pos);
      if ( pos == std::string::npos )
          return -1;
      cnt++;
  }
  return pos;
}

/*
struct dt {
  public:
    int yyyy ; int mm ; int dd ;
    
    yyyy = distr(eng, decltype(distr)::param_type(1990, 2016))
    
    dt (int y, int m , int d) : yyyy{y}, mm{m}, dd{d} { }
    void set 
};

dt random_date(int since_yr) {
    dt td { x_years.tm_year+1900, x_years.tm_mon, x_years.tm_mday};
    return td;
}
*/

std::string ins_prefix {"insert into c (C_ID,C_D_ID,C_W_ID,d,c_limit,c_discount) values ("};

int main() {  
  
  unsigned short n{0};
  double f{0.0};

  SAConnection con; // connection object
  try {
    con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client); }
  catch(SAException &x) {
    std::cout << "Connection error " << (const char*)x.ErrText() << "\n";
    return 1;
  }

  SACommand cmd(&con, "begin transaction isolation level serializable"); // prevents warning about transaction not being on the go
  SACommand csel(&con, "select w_id from warehouse where w_state=:1");
  cmd.Execute();

  std::ifstream infile("/home/bluefrog/pl1_share/reference_data/test_c_data.csv"); // 3000 lines in the csv file
  std::vector <std::string> insert_sql; // each row will be loaded into a vector
  std::string s2 {","};
  std::string st;
  unsigned short nth {0};
  
  while (infile) {
    std::string s;
    if (!getline( infile, s ))
      break;
      
    nth = (nth_occurrence(s, s2, 1)+1);
    st = s.substr( nth+1, 2) ;
    s = ins_prefix + ":1,:2,:3,:4,:5,:6)";

    insert_sql.push_back( s );
  }

  if (!infile.eof())
    std::cerr << "End of file.\n";
  
  long client_id {0};
  long w {0};
  long did {0};
  long start {0};
  long end {0};
  
  for (auto const& e : insert_sql) {
    SADateTime dtValue {distr(eng, decltype(distr)::param_type(1990, 2016))
                       ,distr(eng, decltype(distr)::param_type(1, 12))
                       ,distr(eng, decltype(distr)::param_type(1, 28))
                     };
  
    csel << st.c_str();

    csel.Execute(); 
    while(csel.FetchNext())
      w = csel.Field("w_id").asLong();

    cmd.setCommandText(e.c_str()); // cannot pass a string directly, since SACommand takes a "const SAString &sCmd" as an argument, so you have to pass a pointer to the string, which is what c_str does

    cmd << (++client_id); // client id

    start = ((w*10)-10)+1;
    end = w*10;

    std::cout << "Start " << start << " End " << end << "\n";
    std::uniform_int_distribution<>::param_type pt2(start, end);
    did = (long)(distr(eng, pt2));
    std::cout << did << " Before assigning district id \n";
    cmd << did; // district id
    
    std::cout << w << " Before assigning warehouse id \n";
    cmd << w; // warehouse id

    std::cout << dtValue << " Before assigning date \n";
    cmd << dtValue ;

    n = (distr(eng) + 50) / 100 * 100;

    std::cout << n << " Before assigning credit limit \n";
    cmd << n; // rounds to nearest 100
    
    
    std::uniform_int_distribution<>::param_type pt(2, 20); // discount can be between 2% and 20%
    f = distr(eng, pt) /100.0;
    std::cout << f << " Before assigning discount \n";

    try {
      cmd << f; // allocate random discount
    }
    catch(SAException &x) {
      std::cout << "Discount error " << (const char*)x.ErrText() << "\n";
      return 1;
    }


    std::cout << "Before Insert \n";
    try {
      cmd.Execute(); }
    catch(SAException &x) {
      std::cout << "Insert error " << (const char*)x.ErrText() << "\n";
      return 1;
    }

  }

  con.Commit();

  return 0;

}
