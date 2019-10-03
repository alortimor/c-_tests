#include "ftn_client.h"


std::string ftn_client::receive_response() {
  asio::streambuf buf;
  asio::read_until(m_sock, buf, '\n');
  std::istream input(&buf);
  std::string response;
  std::getline(input, response);
  return response;
}


void ftn_client::send_request(const std::string& request) {
  asio::write(m_sock, asio::buffer(request));
}
