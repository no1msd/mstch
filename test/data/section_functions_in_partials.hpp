const mstch::node section_functions_in_partials_data = mstch::map{
  {"bold", mstch::lambda{[](const std::string& text) -> mstch::node {
    return std::string{"<b>"} + text + std::string{"</b>"};
  }}}
};