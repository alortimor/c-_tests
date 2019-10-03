#ifndef LOGGER_H
#define LOGGER_H
#include <memory>
#include <mutex>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <iostream>

inline std::string time_stamp() {
	std::stringstream buffer;
	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());

	struct std::tm * ptm = std::localtime(&tt);
	buffer << std::put_time(ptm, "%Y%m%d%H%M%S");
	return buffer.str();
}

class threadsafe_log {
  private:
    std::string file_path;
    std::mutex mx;
    const std::chrono::time_point<std::chrono::system_clock>  start {std::chrono::system_clock::now()}; // since the loggers inception

  public:
    explicit threadsafe_log (const std::string & path, const std::string & file_name) {
		if(!file_name.empty())
			file_path = path + "";
	  	file_path += file_name + "_" + time_stamp() + ".log";
      std::ofstream file{file_path, std::fstream::app}; // open file in append mode so nothing is ever overwritten
      if(file) {
        auto d = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
        file << "Start: " << d.count() << std::endl; // write initial duration so as to simplify benchmarking
      }
      else 
        std::cerr << "Failed to create log file: " << file_path << std::endl;
    }

    threadsafe_log (const threadsafe_log &) = delete;
    threadsafe_log & operator=(const threadsafe_log &) = delete;

    ~threadsafe_log() {
      if(!file_path.empty()) {
        std::ofstream file{file_path, std::fstream::app};
        if(file) {
          auto d = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
          file << "End: " << d.count() << std::endl;
        }
        else 
          std::cerr << "Failed to open/create log file: " << file_path << std::endl;
      }
    }

    void write (const std::string & msg) {
      // ensure the blocking duration is not included in the calculation written to file.
      auto d = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start); // calculate duration prior to blocking
      // now block if other threads are writing as well
      {
        std::lock_guard<std::mutex> lk(mx);
        if (!file_path.empty()) {
          std::ofstream file{file_path, std::fstream::app};
          if(file)
            file << d.count() << ": " << msg << std::endl; // assume a new line each time
          else          
            std::cerr << "Failed to open/create log file: " << file_path << std::endl;
        }        
      }
    }
};

class logger {
  private:
    std::shared_ptr<threadsafe_log> lg;
  public:
    logger (std::shared_ptr<threadsafe_log> logger) : lg(logger) { }
    void write (const std::string & msg ) { lg->write(msg); }
};

#define EXCEPTION_LOG

#ifdef EXCEPTION_LOG
inline void excep_log_(const std::string & msg) {
	static logger exception_log( std::make_shared<threadsafe_log>("./", "exceptions"));
	exception_log.write(msg);
}

#define excep_log(x) excep_log_(x)
#else
#define excep_log(x)
#endif

#endif // LOGGER_H
