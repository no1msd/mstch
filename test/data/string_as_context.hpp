const mstch::node string_as_context_data = mstch::map_wrapper{
        {{"a_string", std::string{"aa"}},
         {"a_list",
          mstch::array_wrapper{{std::string{"a"}, std::string{"b"}, std::string{"c"}}}}}};
