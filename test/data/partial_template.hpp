const mstch::node partial_template_data = mstch::map{
    {"title", mstch::lambda{[]()->mstch::node{ return std::string{"Welcome"}; }}},
    {"again", mstch::lambda{[]()->mstch::node{ return std::string{"Goodbye"}; }}},
};