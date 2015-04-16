class partial_template: public mstch::object {
public:
  partial_template() {
    register_methods(this, {
        {"title", &partial_template::title},
        {"again", &partial_template::again}});
  }

  mstch::node title() {
    return std::string{"Welcome"};
  }

  mstch::node again() {
    return std::string{"Goodbye"};
  }
};

const auto partial_template_data = std::make_shared<partial_template>();