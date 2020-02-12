const mstch::node double_render_data = mstch::map_wrapper{
        {{"foo", true}, {"bar", std::string{"{{win}}"}}, {"win", std::string{"FAIL"}}}};
