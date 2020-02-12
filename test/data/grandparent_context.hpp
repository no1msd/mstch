const auto grandparent_context_data = mstch::map_wrapper{
        {{"grand_parent_id", std::string{"grand_parent1"}},
         {"parent_contexts",
          mstch::array_wrapper{
                  {mstch::map_wrapper{
                           {{"parent_id", std::string{"parent1"}},
                            {"child_contexts",
                             mstch::array_wrapper{
                                     {mstch::map_wrapper{
                                              {{"child_id", std::string{"parent1-child1"}}}},
                                      mstch::map_wrapper{
                                              {{"child_id",
                                                std::string{"parent1-child2"}}}}}}}}},
                   mstch::map_wrapper{
                           {{"parent_id", std::string{"parent2"}},
                            {"child_contexts",
                             mstch::array_wrapper{
                                     {mstch::map_wrapper{
                                              {{"child_id", std::string{"parent2-child1"}}}},
                                      mstch::map_wrapper{
                                              {{"child_id",
                                                std::string{"parent2-child2"}}}}}}}}}}}}}};
