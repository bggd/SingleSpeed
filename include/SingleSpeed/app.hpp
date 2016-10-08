#pragma once


namespace ss {


struct App {
  virtual void setup() {}
  virtual void teardown() {}

  virtual void enter_app() {}
  virtual void exit_app() {}

  virtual void enter_frame() {}
  virtual void exit_frame() {}

  virtual void update() {}
  virtual void draw() {}
};


struct AppStack {

  static std::vector<App*> stack;
  static App* current;

  template <typename T>
  static void push()
  {
    if (AppStack::current) AppStack::current->exit_app();
    AppStack::stack.emplace_back(std::move(new T));
    AppStack::current = AppStack::stack.back();
    AppStack::current->setup();
    AppStack::current->enter_app();
  }

  static void pop()
  {
    AppStack::current->exit_app();
    AppStack::current->teardown();
    delete AppStack::current;
    AppStack::current = nullptr;
    AppStack::stack.pop_back();
    if (!AppStack::stack.empty()) {
      AppStack::current = AppStack::stack.back();
      AppStack::current->enter_app();
    }
  }

  template <typename T>
  static void replace()
  {
    AppStack::pop();
    AppStack::push<T>();
  }

  template <typename T>
  struct PreOpenWindow : App {
    void exit_frame() override
    {
      AppStack::replace<T>();
    }
  };

  template <typename T>
  static void run(const WindowSettings& settings)
  {
    AppStack::push<PreOpenWindow<T>>();
    AppStack::_start_game_loop(settings);
  }

  private:
    static void _start_game_loop(const WindowSettings& settings);
};


} // namespace ss
