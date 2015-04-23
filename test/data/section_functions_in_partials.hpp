const mstch::node section_functions_in_partials_data = mstch::map{
  {"bold", mstch::lambda{[](const std::string& text, mstch::renderer render) {
    return std::string{"<b>"} + render(text) + std::string{"</b>"};
  }}}
};