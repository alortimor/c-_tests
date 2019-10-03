#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client {
public:
  chat_client(boost::asio::io_service& ios,
      tcp::resolver::iterator endpoint_iterator) : ios_(ios), socket_(ios) { do_connect(endpoint_iterator); }

  void write(const chat_message& msg) {
    ios_.post(
        [this, msg]() {
          bool write_in_progress = !write_msgs_.empty();
          write_msgs_.push_back(msg);
          if (!write_in_progress)
            write_msg();
        });
  }

  void close() {
    ios_.post([this]() { socket_.close(); });
  }

private:
  void do_connect(tcp::resolver::iterator endpoint_iterator) {
    boost::asio::async_connect(socket_, endpoint_iterator,
        [this](boost::system::error_code ec, tcp::resolver::iterator) {
          if (!ec)
            read_header();
        });
  }

  void read_header() {
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), chat_message::hdr_len),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec && read_msg_.decode_header())
            read_body();
          else
            socket_.close();
        });
  }

  void read_body() {
    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](boost::system::error_code ec, std::size_t) {
          if (!ec) {
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";
            read_header();
          }
          else
            socket_.close();
        });
  }

  void write_msg() {
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
              write_msg();
          }
          else
            socket_.close();
        });
  }

private:
  boost::asio::io_service& ios_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
    chat_client c (io_service, endpoint_iterator);

    std::thread t ( [&io_service]() { io_service.run(); });

    char line[chat_message::max_body_len + 1];
    while (std::cin.getline(line, chat_message::max_body_len + 1)) {
      chat_message msg;
      msg.body_length(std::strlen(line));
      std::memcpy(msg.body(), line, msg.body_length());
      msg.encode_header();
      c.write(msg);
    }

    c.close();
    t.join();
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
