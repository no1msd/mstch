const mstch::node partial_template_data = mstch::map{
    {"title", mstch::lambda{[](){ return std::string{"Welcome"}; }}},
    {"again", mstch::lambda{[](){ return std::string{"Goodbye"}; }}},
};