export module riptide.client.app;

namespace riptide::client::app {

export class App {
public:
    App() = default;
    App(const App &) = delete("app is not copyable");
    App(App &&) = delete("app is not movable");

    auto run() -> void;

    App &operator =(const App &) = delete("app is not copyable");
    App &operator =(App &&) = delete("app is not movable");
};

} // namespace riptide::client::app