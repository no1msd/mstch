auto data = mstch::object{
  {"description", std::string{"That is all!"}},
  {"child", mstch::object{
    {"description", std::string{""}}
  }}
};
