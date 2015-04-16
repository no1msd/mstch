const auto double_render_data = mstch::map{
  {"foo", true},
  {"bar", std::string{"{{win}}"}},
  {"win", std::string{"FAIL"}}
};