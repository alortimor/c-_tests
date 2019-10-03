#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>
#include <random>


std::random_device rd; // obtain a random number from hardware
std::mt19937 eng(rd()); // seed the generator
std::uniform_int_distribution<int> distr(300, 2000); // define the range


std::string zero_pad(int num) {
    std::ostringstream ss;
    ss << std::setw( 2 ) << std::setfill( '0' ) << num;
    return ss.str();
}

struct dt {
  public:
    int yyyy ;
    int mm ;
    int dd ;
    dt (int y, int m , int d) : yyyy{y}, mm{m}, dd{d} { }
};

dt random_date(int since_yr) {
    time_t timer;
    
    struct tm x_years;
    struct tm* current;
    int how_many_years = 10;
    srand (time(NULL));
    int randomYear = (rand()%how_many_years)+1;
    int randomMonth = (rand()%12)+1;
    int randomDays = (rand()%30)+1;

    time(&timer);
    current = localtime(&timer);
    x_years.tm_hour = 0;
    x_years.tm_min = 0;
    x_years.tm_sec = 0;
    x_years.tm_year = current->tm_year - randomYear;
    x_years.tm_mon = (current->tm_mon - randomMonth) <= 0 ? current->tm_mon + (12-randomMonth) : current->tm_mon - randomMonth;
    x_years.tm_mday = (current->tm_mday - randomDays) <= 0 ? current->tm_mday + (30-randomDays) : current->tm_mday - randomDays;
    
    dt td { x_years.tm_year+1900, x_years.tm_mon, x_years.tm_mday};
    return td;
}

std::string ins_prefix {"insert into customer (C_ID,C_D_ID,C_W_ID,C_FIRST,C_MIDDLE,C_LAST,C_STREET_1,C_STREET_2,C_CITY,C_STATE,C_ZIP,C_PHONE,C_SINCE,c_credit,c_credit_lim,c_discount,c_balance,c_ytd_payment,c_payment_cnt,c_delivery_cnt) values ("};

int main() {  
  
  unsigned short n{0};
  float f{0.0};
  SAConnection con; // connection object
  try {
    con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client); }
  catch(SAException &x) {
    std::cout << "Connection error " << (const char*)x.ErrText() << "\n";
    return 1;
  }

  SACommand cmd(&con, "begin transaction isolation level serializable"); // prevents warning about transaction not being on the go
  cmd.Execute();

  std::ifstream infile("/home/bluefrog/pl1_share/reference_data/california_data.csv"); // 3000 lines in the csv file
  std::vector <std::string> insert_sql; // each row will be loaded into a vector

  while (infile) {
    std::string s ;
    if (!getline( infile, s ))
      break;
    s = ins_prefix + s + ",:1,0,:2,:3,0,0,0,0)";
    
    insert_sql.push_back( s );
  }
  if (!infile.eof())
    std::cerr << "End of file.\n";

  for (auto const& e : insert_sql) {
    dt td {random_date(10)};
    SADateTime dtValue{td.yyyy, td.mm, td.dd}; 
    
    cmd.setCommandText(e.c_str()); // cannot pass a string directly, since SACommand takes a "const SAString &sCmd" as an argument, 
                                   // so you have to pass a pointer to the string, which is what c_str does
    cmd << dtValue ;

    n = (distr(eng) + 50) / 100 * 100;
    cmd << n; // rounds to nearest 100
    
    
    std::uniform_int_distribution<>::param_type pt(2, 20); // discount can be between 2% and 20%
    f = distr(eng, pt) /100;
    cmd << f; // allocate random discount
    cmd.Execute();
  }

  con.Commit();

  return 0;

}


