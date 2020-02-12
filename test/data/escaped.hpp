const mstch::node escaped_data = mstch::map_wrapper{
        {{"title",
          mstch::lambda_wrapper{{[]() -> mstch::node { return std::string{"Bear > Shark"}; }}}},
         {"entities", mstch::lambda_wrapper{{[]() -> mstch::node {
              return std::string{"&quot; \"'<>/"};
          }}}}}};
