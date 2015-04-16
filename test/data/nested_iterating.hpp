const auto nested_iterating_data = mstch::map{
  {"inner", mstch::array{mstch::map{
    {"foo", std::string{"foo"}},
    {"inner", mstch::array{mstch::map{
      {"bar", std::string{"bar"}}
    }}}
  }}}
};