const mstch::node section_functions_in_partials_data = mstch::map_wrapper{
        {{"bold", mstch::lambda_wrapper{{[](const std::string& text) -> mstch::node {
              return std::string{"<b>"} + text + std::string{"</b>"};
          }}}}}};
