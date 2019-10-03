#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

std::mutex mx;

void work_thread(boost::shared_ptr<boost::asio::io_service> ios, int cnt) {

  // Ensure iostream is locked each time a cout is performed
  mx.lock();
  std::cout << "Thread " << cnt << " Start.\n";
  mx.unlock();

  while(true) {
    try {
      boost::system::error_code ec;
      ios->run(ec);
      if (ec) {
        mx.lock();
        std::cout << "Error EC: " << ec << ".\n";
        mx.unlock();
      }
      break;
    }
    catch(std::exception &ex) {
      mx.lock();
      std::cout << "Error catch: " << ex.what() << ".\n";
      mx.unlock();
    }
  }
  mx.lock();
  std::cout << "Thread " << cnt << " End.\n";
  mx.unlock();
}


struct client_sender : public boost::enable_shared_from_this<client_sender> {
  boost::asio::ip::tcp::socket sk;
  std::vector<boost::uint8_t> recv_buf;
  size_t recv_buf_index;
  std::list<std::vector<boost::uint8_t> > send_buf;

  client_sender(boost::asio::io_service & io_service): sk(io_service), recv_buf_index(0) {
    recv_buf.resize(8192);
  }

  ~client_sender() { }

  void close() {
    boost::system::error_code ec;
    sk.shutdown(boost::asio::ip::tcp::socket::shutdown_both,ec);
    sk.close(ec);
  }

  void on_send(const boost::system::error_code &ec, std::list<std::vector<boost::uint8_t> >::iterator itr) {
    if(ec) {
      close();
    }
  
    send_buf.erase(itr);

    if(!send_buf.empty()) {
      boost::asio::async_write(sk
                              ,boost::asio::buffer(send_buf.front())
                              ,boost::bind(&client_sender::on_send
                                          ,shared_from_this()
                                          ,boost::asio::placeholders::error
                                          ,send_buf.begin()
                                          )
                              );
    }
  }

  void on_receive(const boost::system::error_code &ec, size_t bytes_transferred) {
    if (ec) {
      close();
    }
    else {
      // Increment number of bytes received thus far
      recv_buf_index += bytes_transferred;

      // Debug information
      mx.lock();
      std::cout << "Recv " << bytes_transferred << " bytes." << std::endl;
      mx.unlock();

      // Print all data in the buffer
      mx.lock();
      for(size_t x {0}; x < recv_buf_index; ++x) {
        std::cout << (char)recv_buf[x] << " ";
        if ((x + 1) % 16 == 0) {
          std::cout << std::endl;
        }
      }

      std::cout << std::endl << std::dec;
      mx.unlock();

      // Clear all the data
      recv_buf_index = 0;

      // Start the next receive cycle
      receive();
    }
  }

  void receive() {
    sk.async_read_some(boost::asio::buffer(&recv_buf[recv_buf_index]
                                          ,recv_buf.size() - recv_buf_index)
                                          ,boost::bind(&client_sender::on_receive, shared_from_this(), _1, _2)
                            );
  }
};

  void send(const void * buf, size_t len) {
    bool ok_to_send = false;
    std::vector<boost::uint8_t> output;
    std::copy((const boost::uint8_t *)buf, (const boost::uint8_t *)buf + len, std::back_inserter(output));
    
    // Is this the only send
    ok_to_send = send_buf.empty();

    // Save the buffer to be sent
    send_buf.push_back(output);

    // Only send if there are no more pending buffers waiting!
    if (ok_to_send) {
      // Start the next pending send
      boost::asio::async_write(sk
                              ,boost::asio::buffer(send_buf.front())
                              ,boost::bind(&client_sender::on_send
                                          ,shared_from_this()
                                          ,boost::asio::placeholders::error
                                          ,send_buf.begin()
                                          )
                              );
    }
  }
  
void on_accept(const boost::system::error_code &ec, boost::shared_ptr<client_sender> cs) {
  if (ec) {
    mx.lock();
    std::cout << "Accept Error: " << ec << ".\n";
    mx.unlock();
  }
  else {
    // 2 bytes message size, followed by the message
    cs->send("Hello World!", 12);
    cs->receive();
  }
}

int main() {

  boost::shared_ptr<boost::asio::io_service> ios (new boost::asio::io_service);
  boost::shared_ptr<boost::asio::io_service::work> worker (new boost::asio::io_service::work(*ios));

  boost::asio::io_service::strand strand(*ios);
  mx.lock();
  std::cout << "Enter to exit.\n";
  mx.unlock();

 // boost::thread_group threads;
  // for(int i=1; i<=6; i++)
 //   threads.create_thread(boost::bind(&work_thread, ios, 1));

  boost::shared_ptr< boost::asio::ip::tcp::acceptor > acceptor(new boost::asio::ip::tcp::acceptor(*ios));
  boost::shared_ptr<client_sender> client(new client_sender(*ios));

  try {
    // refer to asyn_server.cpp for a description of the following 3 lines.
    boost::asio::ip::tcp::resolver resolver(*ios);
    boost::asio::ip::tcp::resolver::query query("127.0.0.1", boost::lexical_cast<std::string>(3333));
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

    acceptor->set_option(boost::asio::ip::tcp::acceptor::reuse_address(false)); // do not reuse address
    acceptor->bind(endpoint);
    acceptor->listen(boost::asio::socket_base::max_connections);
    acceptor->async_accept(client->sk, boost::bind(on_accept, _1, client));

  }
  catch(std::exception &ex) {
    mx.lock();
    std::cout << "Message: " << ex.what() << ".\n";
    mx.unlock();
  }

  std::cin.get();
  boost::system::error_code ec;
  acceptor->close(ec);
  ios->stop();
//  threads.join_all();

  return 0;
}

















