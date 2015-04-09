auto data = mstch::object{
  {"inner", mstch::array{mstch::object{
    {"foo", std::string{"foo"}},
    {"inner", mstch::array{mstch::object{
      {"bar", std::string{"bar"}}
    }}}
  }}}
};
