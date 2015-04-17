class complex_item: public mstch::object {
private:
  const std::string name;
  const bool current;
  const std::string url;
public:
  complex_item(const std::string& name, bool current, const std::string& url):
      name{name}, current{current}, url{url}
  {
    register_method("name", {name});
    register_method("current", {current});
    register_method("url", {url});
    register_method("link", this, &complex_item::link);
  }

  mstch::node link() {
    return !current;
  }
};

class complex: public mstch::object {
private:
  const std::string header;
  const mstch::array item;
public:
  complex():
      header{"Colors"},
      item{
        std::make_shared<complex_item>("red", true, "#Red"),
        std::make_shared<complex_item>("green", false, "#Green"),
        std::make_shared<complex_item>("blue", false, "#Blue")
      }
  {
    register_method("header", {header});
    register_method("item", {item});
    register_method("list", this, &complex::list);
    register_method("empty", this, &complex::empty);
  }

  mstch::node list() {
    return item.size() != 0;
  }

  mstch::node empty() {
    return item.size() == 0;
  }
};

const auto complex_data = std::make_shared<complex>();