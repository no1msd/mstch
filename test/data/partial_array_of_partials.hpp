const auto partial_array_of_partials_data = mstch::map{
  {"numbers", mstch::array{
    mstch::map{{"i", std::string{"1"}}},
    mstch::map{{"i", std::string{"2"}}},
    mstch::map{{"i", std::string{"3"}}},
    mstch::map{{"i", std::string{"4"}}}
  }}
};