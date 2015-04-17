class unescaped: public mstch::object {
public:
  unescaped() {
    register_method("title", this, &unescaped::title);
  }

  mstch::node title() {
    return std::string{"Bear > Shark"};
  }
};

const auto unescaped_data = std::make_shared<unescaped>();