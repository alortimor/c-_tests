#include <thread>
#include "ftnode_mw.h"

void ftnode_mw::start() {

  // create/use default tcp object
  def_tcp_server_ = std::make_unique<tcp_server>(&_db_service);

  tcp_server_ = def_tcp_server_.get();

  if(def_tcp_server_ == nullptr) {
    std::cout << "Error: no tcp server.\n";
    return;
  }

  // endpoint has only one element at position 0
  auto _end_point = settings().get(xmls::ftnode_mw::ENDPOINT).at(0).get();
  const unsigned short port_num = static_cast<xmls::end_point*>(_end_point)->port;
  try {
    unsigned int thread_pool_size = std::thread::hardware_concurrency()*2;
    def_tcp_server_->start(port_num, thread_pool_size);


    
    def_tcp_server_->stop();
  }
  catch (system::system_error&e) {
    std::cerr << e.what();
    excep_log(e.what());
  }
}
