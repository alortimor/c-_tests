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
unsigned int nth_occurrence(const std::string& str, const std::string& findMe, unsigned int nth) {
  unsigned int pos {0};
  unsigned int cnt {0};

  while( cnt != nth ) {
    pos+=1;
    pos = str.find(findMe, pos);
    if ( pos == std::string::npos )
      return -1;ata
  }
  return pos;
}
*/

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


std::random_device rd; // obtain a random number from hardware
std::mt19937 eng(rd()); // seed the generator
std::uniform_int_distribution<int> distr(300, 2000); // define the range

std::string ins_prefix {"insert into item (i_id,i_im_id,i_name,i_price,i_data) values (:1,:2,:3,"};

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

  std::vector <std::string> insert_sql; // each row will be loaded into a vector

  float f{0.0};
  unsigned short n{0};
  std::string s2 {","};
  std::string st;
  unsigned short nth {0};
  int  c{0};

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


