const auto null_lookup_object_data = mstch::map{
	{"name", std::string{"David"}},
  {"twitter", std::string{"@dasilvacontin"}},
  {"fobject", mstch::array{
		mstch::map{
  		{"name", std::string{"Flor"}},
    	{"twitter", std::string{"@florrts"}}
  	},
  	mstch::map{
			{"name", std::string{"Miquel"}},
	  	{"twitter", mstch::node{}}
		}
	}}
};