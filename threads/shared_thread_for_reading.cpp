#include <map>
#include <string>
#include <mutex>
#include <string>
#include <boost/thread/shared_mutex.hpp>
#include <unordered_map>

class db_entry {
  private:
    std::string _dbn;
    std::string _ipa;
    int _port;    
  public:
    db_entry(const std::string & db_name, const std::string & ip_address, int port) : _dbn{db_name}, _ipa{ip_address}, _port{port} { }
    db_entry() { }
    ~db_entry() { }
    
    void set_db_details(const std::string & db_name, const std::string & ip_address, int port) {
      _dbn = db_name;
      _ipa = ip_address;
      _port = port;
    }
};

class db_results {
  private:
    std::unordered_map<std::string, db_entry> entries;
    mutable boost::shared_mutex entry_mutex;
  
  public:
    db_results() { }
    ~db_results() { }

    db_entry db_find_entry(const std::string & entry) const {
      boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
      
      std::unordered_map<std::string, db_entry>::const_iterator const it=entries.find(entry);

      return (it==entries.end()) ? db_entry() : it->second;
    }
    
    void update_or_add_entry(const std::string & entry, const db_entry & db_details) {
      std::lock_guard<boost::shared_mutex> lk(entry_mutex);
      entries[entry] = db_details;
    }
};

int main() {
  db_results dbr;
  return 0;
}

