const mstch::node escaped_data = mstch::map{
    {"title", mstch::lambda{[](){ return std::string{"Bear > Shark"}; }}},
    {"entities", mstch::lambda{[](){ return std::string{"&quot; \"'<>/"}; }}}
};