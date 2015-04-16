const auto nesting_same_name_data = mstch::map{
  {"items", mstch::array{
    mstch::map{
      {"name", std::string{"name"}},
      {"items", mstch::array{1, 2, 3, 4}}
    }
  }}
};