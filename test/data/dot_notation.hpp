class dot_notation_price: public mstch::object {
private:
  const int value;
  const mstch::map currency;
public:
  dot_notation_price():
    value{200}, currency{{"symbol", std::string{"$"}}, {"name", std::string{"USD"}}}
  {
    register_method("value", {value});
    register_method("vat", this, &dot_notation_price::vat);
    register_method("currency", {currency});
  }

  mstch::node vat() {
    return static_cast<int>(value * 0.2);
  }
};

const auto dot_notation_data = mstch::map{
  {"name", std::string{"A Book"}},
  {"authors", mstch::array{std::string{"John Power"}, std::string{"Jamie Walsh"}}},
  {"price", std::make_shared<dot_notation_price>()},
  {"availability", mstch::map{{"status", true}, {"text", std::string{"In Stock"}}}},
  {"truthy", mstch::map{{"zero", 0}, {"notTrue", false}}}
};