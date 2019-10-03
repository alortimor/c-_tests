#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>


std::string zero_pad(int num) {
    std::ostringstream ss;
    ss << std::setw( 2 ) << std::setfill( '0' ) << num;
    return ss.str();
}

int random_date(int since_yr) {
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
    
    return std::stoi(std::to_string(x_years.tm_year+1900) + zero_pad (x_years.tm_mon) + zero_pad( x_years.tm_mday));
}

std::string ins_prefix {'insert into customer (C_ID,C_D_ID,C_W_ID,C_FIRST,C_MIDDLE,C_LAST,C_STREET_1,C_STREET_2,C_CITY,C_STATE,C_ZIP,C_PHONE,C_SINCE,C_CREDIT,C_CREDIT_LIM,C_DISCOUNT,C_BALANCE,C_YTD_PAYMENT,C_PAYMENT_CNT,C_DELIVERY_CNT) values ('};

int main() {  

  // int x{0};
  std::ifstream infile("/home/bluefrog/pl1_share/reference_data/california_data.csv"); // 3000 lines in the csv file
  std::vector < std::vector <std::string> > data; // each row will be loaded into a vector


  while (infile) {
    std::string s;
    if (!getline( infile, s ))
      break;

    s += ins_prefix;

    std::istringstream ss( s );
    std::vector <std::string> record;
 //   x++;
    while (ss) {
      std::string s;
      if (!getline( ss, s, ',' )) 
        break;
   
      record.push_back( s );
    }

    data.push_back( record );
  }
  if (!infile.eof())
    std::cerr << "End of file.\n";

/*  for(auto const& value: data) {
    for (auto const& s : value) {
      std::cout  << s << ", ";
    }
    std::cout  << "\n";
  }
*/

//  std::cout << random_date(10) << "\n";
//  std::cout << "x = " << x << "\n";
  return 0;

}


