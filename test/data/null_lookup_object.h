auto data = mstch::object{
    {"name", std::string{"David"}},
    {"twitter", std::string{"@dasilvacontin"}},
    {"fobject", mstch::array{
		mstch::object{
    		{"name", std::string{"Flor"}},
    		{"twitter", std::string{"@florrts"}}
    	},
    	mstch::object{
	        {"name", std::string{"Miquel"}},
	        {"twitter", mstch::node{}}
		}
    }}
};
