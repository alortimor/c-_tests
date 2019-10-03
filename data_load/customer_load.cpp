#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>
#include <random>

/*
unsigned int nth_occurrence(const std::string& search_str, const std::string& find_str, unsigned int nth) {
  unsigned int pos {0};
  unsigned int cnt {0};

  while( cnt != nth ) {
    pos+=1;
    pos = search_str.find(find_str, pos);
    if ( pos == std::string::npos )
      return -1;
    cnt++;
  }
  return pos;
}
*/

unsigned int nth_occurrence(const std::string& search_str, const std::string& find_str, unsigned int nth) {
  unsigned int pos {0};
  unsigned int cnt {0};

  while( cnt != nth ) {
      pos-=1;
      pos = search_str.rfind(find_str, pos);
      if ( pos == std::string::npos )
          return -1;
      cnt++;
  }
  return pos;
}


std::random_device rd; // obtain a random number from hardware
std::mt19937 eng(rd()); // seed the generator
std::uniform_int_distribution<int> distr(300, 2000); // define the range

std::string ins_prefix {"insert into customer (C_ID,C_D_ID,C_W_ID,C_FIRST,C_MIDDLE,C_LAST,C_STREET_1,C_STREET_2,C_CITY,C_STATE,C_ZIP,C_PHONE,C_SINCE,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt) values (:1,:2,:3,"};

int main() {  
  
  SAConnection con; // connection object
  try {
    con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client); }
  catch(SAException &x) {
    std::cout << "Connection error " << (const char*)x.ErrText() << "\n";
    return 1;
  }

  SACommand cmd(&con, "begin transaction isolation level serializable"); // prevents warning about transaction not being on the go
  cmd.Execute();

  std::ifstream infile("/home/bluefrog/pl1_share/reference_data/customer_data.csv"); // 3000 lines in the csv file
  std::vector <std::string> insert_sql; // each row will be loaded into a vector

  float f{0.0};
  unsigned short n{0};
  std::string s2 {","};
  std::string st;
  unsigned short nth {0};
  int  c{0};

  while (infile) {
    std::string s ;
    if (!getline( infile, s ))
      break;
    nth = (nth_occurrence(s, s2, 3)+1);
    st = s.substr( nth+1, 2) ;
    std::cout << "state " << st << "\n";
    s = ins_prefix + s + ",:4,0,:5,:6,0,0,0,0)";
    
    insert_sql.push_back( s );
    c++;
  }
  std::cout << "lines read " << c << "\n";
  if (!infile.eof())
    std::cerr << "End of file.\n";

  c = 0; 
  long client_id {0};
  long w {0}; // warehouse id
  long did {0}; // district id
  long start {0}; // start range for district
  long end {0};

  SACommand csel(&con, "select w_id from warehouse where w_state=:1"); // find the nearest warehouse, based on state (part of address).
  for (auto const& e : insert_sql) {
    SADateTime dtValue {distr(eng, decltype(distr)::param_type(1990, 2016)) // random year
                       ,distr(eng, decltype(distr)::param_type(1, 12))      // random month
                       ,distr(eng, decltype(distr)::param_type(1, 28))      // random day
                     };

    csel << st.c_str();
    csel.Execute(); 
    while(csel.FetchNext())
      w = csel.Field("w_id").asLong();

    cmd.setCommandText(e.c_str()); // cannot pass string directly, since SACommand takes a "const SAString &sCmd" as argument, pointer to string needed, which is what c_str does
    cmd << (++client_id); // client id
    start = ((w*10)-10)+1;
    end = w*10;

    std::uniform_int_distribution<>::param_type pt2(start, end);
    did = (long)(distr(eng, pt2));
    cmd << did; // district id

    cmd << w ;
    cmd << dtValue ;

    n = (distr(eng) + 50) / 100 * 100;
    cmd << n; // rounds to nearest 100

    std::uniform_int_distribution<>::param_type pt(2, 20); // discount can be between 2% and 20%
    f = distr(eng, pt) /100.0;
    cmd << f; // allocate random discount


    try { cmd.Execute(); }
    catch(SAException &x) {
      std::cout << "Insert Error " << (const char*)x.ErrText() << " c = " << c << "\n";
      return 1;
    }
    c++; // count number of sucessfull inserts
    std::cout << "Sucessfully inserted : " <<  c << "\n";
  }

  con.Commit();

  return 0;

}


