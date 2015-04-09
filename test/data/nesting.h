auto data = mstch::object{
  {"foo", mstch::array{
    mstch::object{{"a", mstch::object{{"b", 1}}}},
    mstch::object{{"a", mstch::object{{"b", 2}}}},
    mstch::object{{"a", mstch::object{{"b", 3}}}}
  }}
};
