#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>


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


    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    current = localtime(&timer);
    x_years.tm_hour = 0;
    x_years.tm_min = 0;
    x_years.tm_sec = 0;
    x_years.tm_year = current->tm_year - randomYear;
    x_years.tm_mon = (current->tm_mon - randomMonth) <= 0 ? current->tm_mon + (12-randomMonth) : current->tm_mon - randomMonth;
    x_years.tm_mday = (current->tm_mday - randomDays) <= 0 ? current->tm_mday + (30-randomDays) : current->tm_mday - randomDays;
    
    return std::stoi(std::to_string(x_years.tm_year+1900) + zero_pad (x_years.tm_mon) + zero_pad( x_years.tm_mday));
}

int main() {  

  std::cout << random_date(10) << "\n";
  return 0;

}
