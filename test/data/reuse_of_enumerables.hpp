const auto reuse_of_enumerables_data = mstch::map{
  {"terms", mstch::array{
    mstch::map{{"name", std::string{"t1"}}, {"index", 0}},
    mstch::map{{"name", std::string{"t2"}}, {"index", 1}}
  }}
};