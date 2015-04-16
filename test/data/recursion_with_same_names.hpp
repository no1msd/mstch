const auto recursion_with_same_names_data = mstch::map{
  {"name", std::string{"name"}},
  {"description", std::string{"desc"}},
  {"terms", mstch::array{
    mstch::map{{"name", std::string{"t1"}}, {"index", 0}},
    mstch::map{{"name", std::string{"t2"}}, {"index", 1}}
  }}
};