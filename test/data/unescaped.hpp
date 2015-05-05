const mstch::node unescaped_data = mstch::map{
    {"title", mstch::lambda{[]()->mstch::node{ return std::string{"Bear > Shark"}; }}}
};