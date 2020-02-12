class simple: public mstch::object {
private:
  int m_value;
public:
  simple():
    m_value(10000)
  {
    register_methods(this, std::map<std::string,mstch::node(simple::*)()>{
      {"name", &simple::name},
      {"value", &simple::value},
      {"taxed_value", &simple::taxed_value},
      {"in_ca", &simple::in_ca}});
  }
  
  mstch::node name() {
    return std::string{"Chris"};
  }

  mstch::node value() {
    return m_value;
  }

  mstch::node taxed_value() {
    return m_value - (m_value * 0.4);
  }

  mstch::node in_ca() {
    return true;
  }
};

const mstch::node simple_data = mstch::object_wrapper{std::make_shared<simple>()};
