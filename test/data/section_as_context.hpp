const mstch::node section_as_context_data = mstch::map_wrapper{
        {{"a_object",
          mstch::map_wrapper{
                  {{"title", std::string{"this is an object"}},
                   {"description", std::string{"one of its attributes is a list"}},
                   {"a_list",
                    mstch::array_wrapper{
                            {mstch::map_wrapper{{{"label", std::string{"listitem1"}}}},
                             mstch::map_wrapper{{{"label", std::string{"listitem2"}}}}}}}}}}}};
