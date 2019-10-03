#include <memory>
#include <thread>

class tcp_session { // dummy session
  private:
    std::unique_ptr<int> m_sock;
  public:
    tcp_session(int sock) : m_sock{std::make_unique<int>(sock) } { }
    void set_x(int i) { m_sock = std::make_unique<int>(i); }
    std::make_unique<int> get_x() { return m_sock;}
};

void initialise() {
  int sk;
  std::thread th{ [this,sk](const int& ec) { process_accept(ec, sk); }) };
}

void process_accept(const int&ec, int* sock) {
  if (ec == 0)
    session = std::make_unique<tcp_session>(std::move(sock));
  else
    excep_log("Error code = " + std::to_string(ec.value()) + ": " + ec.message());

  initialise();
}


int main() {


  return 0;
}
