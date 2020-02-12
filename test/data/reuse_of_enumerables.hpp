const mstch::node reuse_of_enumerables_data = mstch::map_wrapper{
        {{"terms",
          mstch::array_wrapper{
                  {mstch::map_wrapper{{{"name", std::string{"t1"}}, {"index", 0}}},
                   mstch::map_wrapper{{{"name", std::string{"t2"}}, {"index", 1}}}}}}}};
