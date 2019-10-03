#ifndef FTNODE_MW_H
#define FTNODE_MW_H
#include <memory>
#include "tcp_server.h"

class ftnode_mw {
public:
  void start();

private:
  // working objects. You change which object you want to use
  // by assigning other values to these pointers.
  tcp_server* tcp_server_{nullptr};

  // default objects - used by default when the object is created
  std::unique_ptr<tcp_server> def_tcp_server_;
};


#endif // FTNODE_MW_H
