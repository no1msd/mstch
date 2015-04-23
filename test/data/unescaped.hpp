const mstch::node unescaped_data = mstch::map{
    {"title", mstch::lambda{[](){ return std::string{"Bear > Shark"}; }}}
};