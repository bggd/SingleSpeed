#include <mutex>
#include <condition_variable>
#include <queue>


template <typename T>
struct ThreadChannel {

  std::mutex mtx;
  std::condition_variable cv;
  std::queue<T> queue;
  bool is_close = false;

  bool receive(T& ret)
  {
    std::unique_lock<std::mutex> lk(this->mtx);

    while(!this->is_close && this->queue.empty()) {
      this->cv.wait(lk);
    }

    if (this->is_close) return false;

    std::swap(ret, this->queue.front());
    this->queue.pop();
    return true;
  }

  bool send(T& val)
  {
    std::lock_guard<std::mutex> lk(this->mtx);
    if (this->is_close) return false;
    this->queue.push(val);
    this->cv.notify_one();
    return true;
  }

  void close()
  {
    std::lock_guard<std::mutex> lk(this->mtx);
    this->is_close = true;
    this->cv.notify_all();
  }

  bool empty() const
  {
    return this->queue.empty();
  }

};
