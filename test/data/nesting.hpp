const auto nesting_data = mstch::map{
  {"foo", mstch::array{
    mstch::map{{"a", mstch::map{{"b", 1}}}},
    mstch::map{{"a", mstch::map{{"b", 2}}}},
    mstch::map{{"a", mstch::map{{"b", 3}}}}
  }}
};