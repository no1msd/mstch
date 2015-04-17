class partial_template: public mstch::object {
public:
  partial_template() {
    register_method("title", this, &partial_template::title);
    register_method("again", this, &partial_template::again);
  }

  mstch::node title() {
    return std::string{"Welcome"};
  }

  mstch::node again() {
    return std::string{"Goodbye"};
  }
};

const auto partial_template_data = std::make_shared<partial_template>();