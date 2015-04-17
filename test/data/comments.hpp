class comments: public mstch::object {
public:
  comments() {
    register_method("title", this, &comments::title);
  }

  mstch::node title() {
    return std::string{"A Comedy of Errors"};
  }
};

const mstch::node comments_data = std::make_shared<comments>();