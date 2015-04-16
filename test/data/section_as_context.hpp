const auto section_as_context_data = mstch::map{
  {"a_object", mstch::map{
    {"title", std::string{"this is an object"}},
    {"description", std::string{"one of its attributes is a list"}},
    {"a_list", mstch::array{
      mstch::map{{"label", std::string{"listitem1"}}},
      mstch::map{{"label", std::string{"listitem2"}}}
    }}
  }}
};