const auto null_lookup_array_data = mstch::map{
    {"name", std::string{"David"}},
    {"twitter", std::string{"@dasilvacontin"}},
    {"farray", mstch::array{
    	mstch::array{std::string{"Flor"}, std::string{"@florrts"}},
    	mstch::array{std::string{"Miquel"}, mstch::node{}},
    }}
};