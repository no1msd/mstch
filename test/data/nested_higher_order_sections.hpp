const mstch::node nested_higher_order_sections_data = mstch::map{
  {"bold", mstch::lambda{[](const std::string& text) {
    return std::string{"<b>"} + text + std::string{"</b>"};
  }}},
  {"person", mstch::map{{"name", std::string{"Jonas"}}}}
};