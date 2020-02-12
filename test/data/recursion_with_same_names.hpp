const mstch::node recursion_with_same_names_data = mstch::map_wrapper{
        {{"name", std::string{"name"}},
         {"description", std::string{"desc"}},
         {"terms",
          mstch::array_wrapper{
                  {mstch::map_wrapper{{{"name", std::string{"t1"}}, {"index", 0}}},
                   mstch::map_wrapper{{{"name", std::string{"t2"}}, {"index", 1}}}}}}}};
