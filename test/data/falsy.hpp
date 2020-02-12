const auto falsy_data = mstch::map_wrapper{{{"emptyString", std::string{""}},
                                            {"emptyArray", mstch::array_wrapper{}},
                                            {"zero", 0},
                                            {"null", mstch::node{}}}};
