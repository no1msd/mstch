class higher_order_sections: public mstch::object {
 private:
  std::string m_helper;
 public:
  higher_order_sections(): m_helper{"To tinker?"} {
    register_methods(this, {
        {"name", &higher_order_sections::name},
        {"helper", &higher_order_sections::helper},
        {"bolder", &higher_order_sections::bolder}
    });
  }

  mstch::node name() {
    return std::string{"Tater"};
  }

  mstch::node helper() {
    return m_helper;
  }

  mstch::node bolder() {
    return mstch::lambda{[this](const std::string& text, mstch::renderer render) {
      return text + " => <b>" + render(text) + "</b> " + m_helper;
    }};
  }
};

const mstch::node higher_order_sections_data = std::make_shared<higher_order_sections>();