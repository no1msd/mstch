class partial_whitespace: public mstch::object {
private:
  int m_value;
public:
  partial_whitespace(): m_value(10000) {
    register_methods(this, std::map<std::string,mstch::node(partial_whitespace::*)()>{
      {"greeting", &partial_whitespace::greeting},
      {"farewell", &partial_whitespace::farewell},
      {"name", &partial_whitespace::name},
      {"value", &partial_whitespace::value},
      {"taxed_value", &partial_whitespace::taxed_value},
      {"in_ca", &partial_whitespace::in_ca}
    });
  }

  mstch::node greeting() {
    return std::string{"Welcome"};
  }

  mstch::node farewell() {
    return std::string{"Fair enough, right?"};
  }

  mstch::node name() {
    return std::string{"Chris"};
  }

  mstch::node value() {
    return m_value;
  }

  mstch::node taxed_value() {
    return static_cast<int>(m_value - (m_value * 0.4));
  }

  mstch::node in_ca() {
    return true;
  }
};

const auto partial_whitespace_data = std::make_shared<partial_whitespace>();