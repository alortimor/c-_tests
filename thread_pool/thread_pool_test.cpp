#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/bind.hpp>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>

const std::string left_string("Much ado about nothing");
const std::string right_string("A midsummer night's dream");

void play_title(const std::string & words, boost::posix_time::time_duration interval , bool indent=false) {
    std::stringstream iss;
    iss.str(words);
    std::string current;
    int x{0};
    do {
      iss >> current;
      if (iss) {
        if (indent)
          std::cout << current << "\n";
        std::cout << current << "\n";
        // boost::this_thread::sleep_for(boost::posix_time::milliseconds(interval));
        while (x < 10000) x++;
      }
    } while (!iss.bad() && !iss.eof() );
    std::cout << "\n";
}

class Play_Title{
    std::string m_words;
    boost::posix_time::time_duration m_interval;
    bool m_indent;
    
  public:
    Play_Title(const std::string & words, boost::posix_time::time_duration interval , bool indent) 
         : m_words(words), m_interval(interval), m_indent(indent) { }
         
    void perform() {
      play_title(m_words, m_interval, m_indent);
    }
};

int main()  {

  using namespace boost::posix_time;
  boost::thread_group tgroup;
  
  
  time_duration interval( milliseconds(250) );
  auto delay (milliseconds(60));
  
  
  //play_title(left_string, interval);
  
  tgroup.create_thread(boost::bind( &play_title, left_string, interval, false));
  boost::this_thread::sleep_for(boost::chrono::seconds{250});
  //boost::this_thread::sleep_for(boost::posix_time::milliseconds(delay));
  // int x{0};
  // while (x < 10000) x++;

  Play_Title right(right_string,interval,true);

  tgroup.create_thread(boost::bind( &Play_Title::perform, &right));
  // right.perform();
  
  return 0;
}
