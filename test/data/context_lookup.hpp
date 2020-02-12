const mstch::node context_lookup_data = mstch::map_wrapper{
        {{"outer",
          mstch::map_wrapper{{{"id", 1}, {"second", mstch::map_wrapper{{{"nothing", 2}}}}}}}}};
