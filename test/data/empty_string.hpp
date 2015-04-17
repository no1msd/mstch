const auto empty_string_data = mstch::map{
  {"description", std::string{"That is all!"}},
  {"child", mstch::map{
    {"description", std::string{""}}
  }}
};