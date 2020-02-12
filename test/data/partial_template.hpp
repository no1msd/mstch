const mstch::node partial_template_data = mstch::map_wrapper{{
        {"title",
         mstch::lambda_wrapper{{[]() -> mstch::node { return std::string{"Welcome"}; }}}},
        {"again",
         mstch::lambda_wrapper{{[]() -> mstch::node { return std::string{"Goodbye"}; }}}},
}};
