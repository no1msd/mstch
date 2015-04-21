class partial_view: public mstch::object {
private:
  int m_value;
public:
    partial_view(): m_value{10000} {
    register_methods(this, {
      {"greeting", &partial_view::greeting},
      {"farewell", &partial_view::farewell},
      {"name", &partial_view::name},
      {"value", &partial_view::value},
      {"taxed_value", &partial_view::taxed_value},
      {"in_ca", &partial_view::in_ca},});
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

const auto partial_view_data = std::make_shared<partial_view>();