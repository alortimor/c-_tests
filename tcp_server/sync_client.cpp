#include <boost/asio.hpp>
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

  void body_length(size_t new_length) {
    body_len = new_length;
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

class tcp_client {
private:
	asio::io_service m_ios;
	asio::ip::tcp::endpoint m_ep;
	asio::ip::tcp::socket m_sock;
	void send_request(const std::string& request) {
    std::size_t bytes_transferred
		asio::write(m_sock, asio::buffer(request), bytes_transferred);
	}

	std::string receive_response() {
		asio::streambuf buf;
		asio::read_until(m_sock, buf, '\n');

		std::istream input(&buf);
		std::string response;
		std::getline(input, response);
		return response;
	}

public:
	tcp_client(const std::string& ip_addr,	short port) :	m_ep(asio::ip::address::from_string(ip_addr),	port)
                                                       ,m_sock(m_ios) {
    m_sock.open(m_ep.protocol());
  }

	void connect() {
		m_sock.connect(m_ep);
	}

	void close() {
		m_sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		m_sock.close();
	}

	std::string do_some_work(int x) {
		send_request("Request#: " + std::to_string(x) + "\n");
		return receive_response();
	};
};

int main() {
	const std::string ip_addr = "127.0.0.1";
	const short port = 3333;

	try {
		tcp_client client(ip_addr, port);
		client.connect(); // Synchronous connect.

    for (int i{0}; i<10; i++) {
      std::cout << "Sending request to the server... " << std::endl;
      std::string response = client.do_some_work(i);
      std::cout << "Response received: " << response << std::endl;
    }
		client.close();
	}
	catch (system::system_error &e) {
		std::cout << "Error code = " << e.code()	<< " : " << e.what();

		return e.code().value();
	}

	return 0;
}
