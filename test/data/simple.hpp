class simple: public mstch::object {
private:
  std::string m_name;
  int m_value;
  bool m_in_ca;
public:
  simple():
    m_name{"Chris"},
    m_value{10000},
    m_in_ca{true}
  {
    register_methods(this, {
      {"name", &simple::name}, {"value", &simple::value},
      {"taxed_value", &simple::taxed_value}, {"in_ca", &simple::in_ca}});
  }
  
  mstch::node name() {
    return m_name;
  }

  mstch::node value() {
    return m_value;
  }

  mstch::node taxed_value() {
    return static_cast<int>(m_value - (m_value * 0.4));
  }

  mstch::node in_ca() {
    return m_in_ca;
  }
};

const auto simple_data = std::make_shared<simple>();
