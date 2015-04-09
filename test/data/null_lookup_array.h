auto data = mstch::object{
    {"name", std::string{"David"}},
    {"twitter", std::string{"@dasilvacontin"}},
    {"farray", mstch::array{
    	mstch::array{std::string{"Flor"}, std::string{"@florrts"}},
    	mstch::array{std::string{"Miquel"}, mstch::node{}},
    }}
};
