#pragma once

#include <memory>
#include <algorithm>
#include <functional>
#include <vector>


namespace ss {


struct EventListener {

  static uint_fast64_t count;

  std::function<void()> dtor;

  ~EventListener() { this->dtor(); }

};


template <typename Arg>
struct Event {

  struct FuncPtr {
    //int prioirty;
    uint_fast64_t id;
    std::function<void(Arg&)> fn;
  };

  std::shared_ptr<std::vector<FuncPtr>> functors;

  Event()
  {
    this->functors = std::make_shared<std::vector<FuncPtr>>();
  }
  Event(Event&& other) : functors(std::move(other.functors)) {}
  Event(const Event& other) = delete;
  Event& operator=(const Event& other) = delete;
  Event& operator=(Event&& other)
  {
    this->functors = std::move(other.functors);
    return *this;
  }

  std::unique_ptr<EventListener> make_listener(std::function<void(Arg&)> lambda)
  {
    uint_fast64_t id = EventListener::count;
    this->functors->push_back(FuncPtr{id, lambda});
    EventListener::count++;

    auto listener = std::make_unique<EventListener>();
    std::weak_ptr<std::vector<FuncPtr>> weak_functors = this->functors;
    listener->dtor = [weak_functors, id]() {
      auto methods = weak_functors.lock();
      if (methods) {
        auto it = std::remove_if(methods->begin(), methods->end(), [id](const FuncPtr& fncptr) { return id == fncptr.id; });
        methods->erase(it, methods->end());
      }
    };
    return listener;
  }

  template <typename Instance>
  std::unique_ptr<EventListener> make_listener(Instance* instance, void(Instance::*method) (Arg&))
  {
    return this->make_listener(std::bind(method, instance, std::placeholders::_1));
  }

  void notify(Arg& arg)
  {
    for (auto it : *this->functors) {
      it.fn(arg);
    }
  }

};


} // namespace ss
