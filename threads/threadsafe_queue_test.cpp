#include <queue>
#include <memory>
#include <mutex>
#include <iostream>
#include <condition_variable>

class tcp_session { // dummy session
  private:
    std::shared_ptr<int> m_sock;
  public:
    tcp_session(int sock) : m_sock{std::make_shared<int>(sock) } { }
    void set_x(int i) { m_sock = std::make_shared<int>(i); }
    std::shared_ptr<int> get_x() { return m_sock;}
};

template<typename T>
class threadsafe_queue {
  private:
    mutable std::mutex mx;
    std::queue<std::unique_ptr<T>> unique_ptr_q;
    std::condition_variable cv;
  public:
    threadsafe_queue() {}
    threadsafe_queue(const threadsafe_queue&) = delete;
    threadsafe_queue& operator=(const threadsafe_queue&) = delete;

    //void push_unique(std::unique_ptr<T> ptr) {
    void push_unique(std::unique_ptr<T>&& ptr) {
      std::lock_guard<std::mutex> lk(mx);
      unique_ptr_q.push(std::move(ptr));
      cv.notify_one();
    }

    std::unique_ptr<T> pop_unique() {
      std::unique_lock<std::mutex> lk(mx);
      cv.wait(lk,[this]{return !unique_ptr_q.empty();});
      std::unique_ptr<T> up =  std::move(unique_ptr_q.front());
      unique_ptr_q.pop();
      return up;
    }
    bool empty() const {
      std::lock_guard<std::mutex> lk(mx);
      return unique_ptr_q.empty();
    }
};

int main()  {

  std::unique_ptr<tcp_session> tcp_sess {std::make_unique<tcp_session>(1)};
  threadsafe_queue<tcp_session> q;

  tcp_sess->set_x(10);
  q.push_unique(std::move(tcp_sess));
  auto tcp_sess2 = q.pop_unique();
  std::cout << "x " << tcp_sess2->get_x() << "\n";
  return 0;
}

