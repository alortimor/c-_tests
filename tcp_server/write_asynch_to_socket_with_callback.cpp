#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

// Step 1.
// Define a structure that contains a pointer to a socket, the buffer to write to and a total written count
struct Session {
  std::shared_ptr<asio::ip::tcp::socket> sk;
  std::string buf;
  std::size_t total_written;
};

// Step 2
// Define a callback function, which is called once the asynchronous writing is completed
void callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s) {
  if (ec != 0) {
    std::cout << "Error occured! Error code = " << ec.value() << ". Message: " << ec.message();
    return;
  }

  s->total_written += bytes_transferred;
  if (s->total_written == s->buf.length()) {
    return;
  }

  s->sk->async_write_some(asio::buffer(s->buf.c_str() + s->total_written
                         ,s->buf.length() - s->total_written)
                         ,std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
};

void write_to_socket(const std::shared_ptr<asio::ip::tcp::socket> & sk, const std::string & msg) {
  std::shared_ptr<Session> s(std::make_shared<Session>());

  // Step 4. Allocating and filling the buffer.
  s->buf = msg;
  s->total_written = 0;
  s->sk = sk;
  // Step 5. Initiating asynchronous write operation.
  s->sk->async_write_some(asio::buffer(s->buf), std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
};

int main() {
  std::string ip_addr {"127.0.0.1"};
  unsigned short port {3333};
  
  try {
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(ip_addr), port);
    asio::io_service ios;
    
    // Step 3. Allocating, opening and connecting a socket.
    //std::shared_ptr<asio::ip::tcp::socket> sk( new asio::ip::tcp::socket(ios, ep.protocol())); sk->connect(ep);
    std::shared_ptr<asio::ip::tcp::socket> sk(std::make_shared<asio::ip::tcp::socket>( ios, ep.protocol() ) );

    sk->connect(ep);
    write_to_socket(sk,"Hello World\n");

    // Step 6.
    ios.run();
  }
  catch (system::system_error &e) {
    std::cout << "Error: " << e.code() << " " << e.what();
    return e.code().value();
  }
  return 0;
}
