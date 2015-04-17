class section_functions_in_partials: public mstch::object {
public:
  section_functions_in_partials() {
    register_method("bold", this, &section_functions_in_partials::bold);
  }

  mstch::node bold() {
    return std::string{""};
    /*return [](const std::string& text, mstch::renderer render) {
        return std::string{"<b>"} + render(text) + std::string{"</b>"};
    };*/
  }
};

const auto section_functions_in_partials_data = std::make_shared<section_functions_in_partials>();