const mstch::node nested_higher_order_sections_data = mstch::map_wrapper{
        {{"bold", mstch::lambda_wrapper{{[](const std::string& text) -> mstch::node {
              return std::string{"<b>"} + text + std::string{"</b>"};
          }}}},
         {"person", mstch::map_wrapper{{{"name", std::string{"Jonas"}}}}}}};
