const auto falsy_data = mstch::map{
  {"emptyString", std::string{""}},
  {"emptyArray", mstch::array{}},
  {"zero", 0},
  {"null", mstch::node{}}
};