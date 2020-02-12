const mstch::node null_lookup_array_data = mstch::map_wrapper{
        {{"name", std::string{"David"}},
         {"twitter", std::string{"@dasilvacontin"}},
         {"farray",
          mstch::array_wrapper{{
                  mstch::array_wrapper{{std::string{"Flor"}, std::string{"@florrts"}}},
                  mstch::array_wrapper{{std::string{"Miquel"}, mstch::node{}}},
          }}}}};
