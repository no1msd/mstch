const mstch::node escaped_data = mstch::map{
    {"title", mstch::lambda{[]()->mstch::node{ return std::string{"Bear > Shark"}; }}},
    {"entities", mstch::lambda{[]()->mstch::node{ return std::string{"&quot; \"'<>/"}; }}}
};