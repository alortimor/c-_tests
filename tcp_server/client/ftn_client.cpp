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

std::string ftn_client::send_to_server(std::string str) {
  send_request(str + "\n");
}

void ftn_client::close() {
  m_sock.shutdown(
  boost::asio::ip::tcp::socket::shutdown_both);
  m_sock.close();
}

