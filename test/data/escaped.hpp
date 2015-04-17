class escaped: public mstch::object {
public:
  escaped() {
    register_method("title", this, &escaped::title);
    register_method("entities", this, &escaped::entities);
  }

  mstch::node title() {
    return std::string{"Bear > Shark"};
  };

  mstch::node entities() {
    return std::string{"&quot; \"'<>/"};
  }
};

const mstch::node escaped_data = std::make_shared<escaped>();