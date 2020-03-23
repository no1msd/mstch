class method: public mstch::object {
private:
  int m_value;
public:
  method():
    m_value(10000)
  {
    register_methods({
      {"name", []()->mstch::node{return std::string{"Chris"};}},
      {"value", [this](){return mstch::node{m_value};}},
      {"taxed_value", std::bind(&method::taxed_value, this)},
      {"in_ca", [this](){return mstch::node{true};}}
    });
  }

  mstch::node taxed_value() {
    return m_value - (m_value * 0.4);
  }
};

const auto method_data = std::make_shared<method>();
