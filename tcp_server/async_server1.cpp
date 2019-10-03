#include <boost/asio.hpp>

#include <deque>
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace boost;

class tcp_message {
public:
  enum { hdr_len = 2 };
  enum { max_body_len = 1024 };

  tcp_message() : body_len(0) { }

  const char* data() const { return data_; }
  char* data() { return data_; }

  size_t length() const { return hdr_len + body_len; }

  const char* body() const { return data_ + hdr_len;}
  char* body() { return data_ + hdr_len; }

  size_t body_length() const { return body_len; }

  void body_length(size_t len) {
    body_len = len;
    if (body_len > max_body_len)
      body_len = max_body_len;
  }

  bool decode_header() {
    char header[hdr_len + 1] = "";
    std::strncat(header, data_, hdr_len); // Appends bytes from data_ to dest. Chars copied do not exceed hdr_len.
    body_len = std::atoi(header); // Discards whitespace chars until first non-whitespace char found.
                                  // Then takes as many chars as possible to form a valid integer number representation
                                  // and converts them to an integer value.
    if (body_len > max_body_len) {
      body_len = 0;
      return false;
    }
    return true;
  }

  void encode_header() {
    char header[hdr_len + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(body_len));
    std::memcpy(data_, header, hdr_len);
  }

private:
  char data_[hdr_len + max_body_len];
  size_t body_len;
};

typedef std::deque<tcp_message> tcp_message_q;

class tcp_service {
private:
	asio::ip::tcp::socket sk;
	tcp_message read_msg_;
  tcp_message_q write_msgs_;
  tcp_message_q recent_msgs_;

  void read_header() {
    boost::asio::async_read(sk, boost::asio::buffer(read_msg_.data(), tcp_message::hdr_len),
        [this](boost::system::error_code ec, std::size_t) {
          if (!ec && read_msg_.decode_header())
            read_body();
          // else
            // erase the db_buffer entry 
        });
  }

  void write_msg() {
    boost::asio::async_write(sk, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
        [this](boost::system::error_code ec, std::size_t) {
          if (!ec) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
              write_msg();
          }
          //else
        });
           // erase the db_buffer entry 
  }
  

public:
	tcp_service(asio::ip::tcp::socket sock) : sk(std::move(sock))	{ }
  void start() { read_header(); }
  
  void deliver(const tcp_message& msg) {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
      write_msg();
    }

private:
  void read_body() {
    boost::asio::async_read(sk,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](boost::system::error_code ec, std::size_t) {
          if (!ec)
            deliver(); //the delivery will occur after SQL work has completed
            read_header();
          //else
            //erase the db_buffer entry 
        });
  }
};

class tcp_acceptor {
public:
	tcp_acceptor(asio::io_service& ios, short port) :
          m_ios(ios),
          acc(m_ios,	asio::ip::tcp::endpoint( asio::ip::address_v4::any(), port)),
          inactive(false)	{ }

	// Start accepting connection requests.
	void start() {
		acc.listen();
		accept_connections();
	}

	// Stop accepting connection requests.
	void stop() {
		inactive.store(true);
	}

private:
	void accept_connections(asio::ip::tcp::socket sk) {
    acc.async_accept(sk, [this](boost::system::error_code ec) {
                           if (!ec)
                             std::make_shared<tcp_service>(std::move(sk))->start();
                           accept_connections();
                         });
	}

private:
	asio::io_service& m_ios;
	asio::ip::tcp::acceptor acc;
  tcp::socket sk;
	std::atomic<bool> inactive;
};

class tcp_server {
public:
	tcp_server() { work.reset(new asio::io_service::work(ios) ); }

	// Start the server.
	void start(short port) {
		// Create and start tcp_acceptor.
		acc.reset(new tcp_acceptor(ios, port));
		acc->start();
	}

	void stop() { // Stop server.
		acc->stop();
		ios.stop();
	}

private:
	asio::io_service ios;
	std::unique_ptr<asio::io_service::work> work;
	std::unique_ptr<tcp_acceptor> acc;
};

int main() {
	short port = 3333;
	try {
		tcp_server srv;

    srv.start(port);
    std::string input_str;
    while(input_str != "q" && input_str != "Q") {
      std::cin >> input_str;
    }
		srv.stop();
	}
	catch (system::system_error &e) {
		std::cout << "Error code: "	<< e.code() << " : " << e.what();
	}

	return 0;
}
