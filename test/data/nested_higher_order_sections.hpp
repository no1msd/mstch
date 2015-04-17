class nested_higher_order_sections: public mstch::object {
public:
  nested_higher_order_sections() {
    register_method("bold", this, &nested_higher_order_sections::bold);
    register_method("person", this, &nested_higher_order_sections::person);
  }

  mstch::node bold() {
    return std::string{""};
    /*return [](const std::string& text, mstch::renderer render) {
      return std::string{"<b>"} + render(text) + std::string{"</b>"};
    };*/
  };

  mstch::node person() {
    return mstch::map{{"name", std::string{"Jonas"}}};
  }
};

const mstch::node nested_higher_order_sections_data = std::make_shared<nested_higher_order_sections>();