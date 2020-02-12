const mstch::node nesting_data = mstch::map_wrapper{
        {{"foo",
          mstch::array_wrapper{
                  {mstch::map_wrapper{{{"a", mstch::map_wrapper{{{"b", 1}}}}}},
                   mstch::map_wrapper{{{"a", mstch::map_wrapper{{{"b", 2}}}}}},
                   mstch::map_wrapper{{{"a", mstch::map_wrapper{{{"b", 3}}}}}}}}}}};
