const auto context_lookup_data = mstch::map{
  {"outer", mstch::map{
    {"id", 1},
    {"second", mstch::map{
      {"nothing", 2}
    }}
  }}
};