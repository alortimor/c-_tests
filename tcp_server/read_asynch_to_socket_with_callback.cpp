#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

// Step 1.
// Define a structure that contains a pointer to a socket, the buffer to write to and a total written count
struct Session {
  std::shared_ptr<asio::ip::tcp::socket> sk;
  std::unique_ptr<char[]> buf;
  std::size_t total_read;
  unsigned int buf_sz;
};

struct Write_Session {
  std::shared_ptr<asio::ip::tcp::socket> sk;
  std::string buf;
};


// Step 2
// Define a callback function, which is called once the asynchronous reading is completed
void callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s) {
  if (ec != 0) {
    std::cout << "Error occured! Error code = " << ec.value() << ". Message: " << ec.message();
    return;
  }
  s->total_read += bytes_transferred;
  // one needs to keep track of  the total read to ensure
  // that no more than the buffer size is in fact read
  if (s->total_read == s->buf_sz) {
    return;
  }
  // it is recursive since we do not know when all data has been read!
  // hence the bind to the same callable object
  s->sk->async_read_some(asio::buffer(s->buf.get()+s->total_read, s->buf_sz-s->total_read)
                        ,std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
}

void read_from_socket(std::shared_ptr<asio::ip::tcp::socket> sk) {
  std::shared_ptr<Session> s(new Session);
  // Step 4. Allocating the buffer.
  const unsigned int MESSAGE_SIZE = 7;
  s->buf.reset(new char[MESSAGE_SIZE]);
  s->total_read = 0;
  s->sk = sk;
  s->buf_sz = MESSAGE_SIZE;

  // Step 5. Initiating asynchronous reading operation.
  s->sk->async_read_some(asio::buffer(s->buf.get(), s->buf_sz), std::bind(callback,std::placeholders::_1,std::placeholders::_2,s));
}


void write_callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s) {
  if (ec != 0) {
    std::cout << "Error occured! Error code = " << ec.value() << ". Message: " << ec.message();
    return;
  }
  // All data sucessfully written
}


void write_to_socket(const std::shared_ptr<asio::ip::tcp::socket> & sk, const std::string & msg) {
  std::shared_ptr<Write_Session> s(std::make_shared<Write_Session>());

  // Step 4. Allocating and filling the buffer.
  s->buf = msg;
  s->sk = sk;
  // Step 5. Initiating asynchronous write operation.
  s->sk->async_write(asio::buffer(s->buf), std::bind(write_callback, std::placeholders::_1, std::placeholders::_2, s));
};

int main() {
  std::string ip_addr {"127.0.0.1"};
  unsigned short port {3333};
  
  try {
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(ip_addr), port);
    asio::io_service ios;
    
    // Step 3. Allocating, opening and connecting a socket.
    //std::shared_ptr<asio::ip::tcp::socket> sk( n  ew asio::ip::tcp::socket(ios, ep.protocol())); sk->connect(ep);
    std::shared_ptr<asio::ip::tcp::socket> sk(std::make_shared<asio::ip::tcp::socket>( ios, ep.protocol() ) );

    sk->connect(ep);
    write_to_socket(sk,"Hello World\n");
    read_from_socket(sk);

    // Step 6.
    ios.run();
  }
  catch (system::system_error &e) {
    std::cout << "Error: " << e.code() << " " << e.what();
    return e.code().value();
  }
  return 0;
}
