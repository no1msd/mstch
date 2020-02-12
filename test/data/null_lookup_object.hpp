const mstch::node null_lookup_object_data = mstch::map_wrapper{
        {{"name", std::string{"David"}},
         {"twitter", std::string{"@dasilvacontin"}},
         {"fobject",
          mstch::array_wrapper{{{mstch::map_wrapper{{{"name", std::string{"Flor"}},
                                                     {"twitter", std::string{"@florrts"}}}}},
                                mstch::map_wrapper{{{"name", std::string{"Miquel"}},
                                                    {"twitter", mstch::node{}}}}}}}}};
