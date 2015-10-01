class dot_notation_price: public mstch::object {
private:
  int m_value;
  mstch::map m_currency;
public:
  dot_notation_price():
    m_value(200), m_currency(mstch::map{{"symbol", std::string{"$"}}, {"name", std::string{"USD"}}})
  {
    register_methods(this, std::map<std::string,mstch::node(dot_notation_price::*)()>{
      {"value", &dot_notation_price::value},
      {"vat", &dot_notation_price::vat},
      {"currency", &dot_notation_price::currency}});
  }

  mstch::node value() {
    return m_value;
  }

  mstch::node vat() {
    return m_value * 0.2;
  }

  mstch::node currency() {
    return m_currency;
  }
};

const auto dot_notation_data = mstch::map{
  {"name", std::string{"A Book"}},
  {"authors", mstch::array{std::string{"John Power"}, std::string{"Jamie Walsh"}}},
  {"price", std::make_shared<dot_notation_price>()},
  {"availability", mstch::map{{"status", true}, {"text", std::string{"In Stock"}}}},
  {"truthy", mstch::map{{"zero", 0}, {"notTrue", false}}}
};