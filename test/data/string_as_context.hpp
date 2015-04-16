const auto string_as_context_data = mstch::map{
  {"a_string", std::string{"aa"}},
  {"a_list", mstch::array{std::string{"a"},std::string{"b"},std::string{"c"}}}
};