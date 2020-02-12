const mstch::node partial_array_of_partials_data = mstch::map_wrapper{
        {{"numbers",
          mstch::array_wrapper{{mstch::map_wrapper{{{"i", std::string{"1"}}}},
                                mstch::map_wrapper{{{"i", std::string{"2"}}}},
                                mstch::map_wrapper{{{"i", std::string{"3"}}}},
                                mstch::map_wrapper{{{"i", std::string{"4"}}}}}}}}};
