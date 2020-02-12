class dot_notation_price : public mstch::object {
private:
    int m_value;
    mstch::map m_currency;

public:
    dot_notation_price()
        : m_value(200)
        , m_currency(mstch::map{{"symbol", std::string{"$"}}, {"name", std::string{"USD"}}})
    {
        register_methods(this,
                         std::map<std::string, mstch::node (dot_notation_price::*)()>{
                                 {"value", &dot_notation_price::value},
                                 {"vat", &dot_notation_price::vat},
                                 {"currency", &dot_notation_price::currency}});
    }

    mstch::node value() { return m_value; }

    mstch::node vat() { return m_value * 0.2; }

    mstch::node currency() { return mstch::map_wrapper{m_currency}; }
};

const mstch::node dot_notation_data = mstch::map_wrapper{
        {{"name", std::string{"A Book"}},
         {"authors",
          mstch::array_wrapper{{std::string{"John Power"}, std::string{"Jamie Walsh"}}}},
         {"price", mstch::object_wrapper{std::make_shared<dot_notation_price>()}},
         {"availability",
          mstch::map_wrapper{{{"status", true}, {"text", std::string{"In Stock"}}}}},
         {"truthy", mstch::map_wrapper{{{"zero", 0}, {"notTrue", false}}}}}};
