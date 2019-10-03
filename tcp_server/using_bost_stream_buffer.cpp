#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

int main() {
  asio::streambuf buf;
  std::ostream output(&buf);
  // Writw message to the stream-based buffer.
  output << "Hello World!\n";
  
  // Read data out of a streambuf
  // until '\n' delimiter.
  // So an istream is used for input, as opposed to ostream above
  std::istream input(&buf);
  
  // Read into string
  std::string input_msg;
  std::getline(input, input_msg);
  
  // Display message
  std::cout << input_msg;
  return 0;
}

