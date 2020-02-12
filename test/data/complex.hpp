class complex_item : public mstch::object {
private:
    std::string m_name;
    bool m_current;
    std::string m_url;

public:
    complex_item(const std::string& name, bool current, const std::string& url)
        : m_name(name), m_current(current), m_url(url)
    {
        register_methods(this,
                         std::map<std::string, mstch::node (complex_item::*)()>{
                                 {"name", &complex_item::name},
                                 {"current", &complex_item::current},
                                 {"url", &complex_item::url},
                                 {"link", &complex_item::link}});
    }

    mstch::node current() { return m_current; }

    mstch::node url() { return m_url; }

    mstch::node name() { return m_name; }

    mstch::node link() { return !m_current; }
};

class complex : public mstch::object {
private:
    std::string m_header;
    mstch::array m_item;

public:
    complex()
        : m_header("Colors")
        , m_item(mstch::array{mstch::object_wrapper{
                                      std::make_shared<complex_item>("red", true, "#Red")},
                              mstch::object_wrapper{
                                      std::make_shared<complex_item>("green", false, "#Green")},
                              mstch::object_wrapper{std::make_shared<complex_item>("blue",
                                                                                   false,
                                                                                   "#Blue")}})
    {
        register_methods(
                this,
                std::map<std::string, mstch::node (complex::*)()>{{"header", &complex::header},
                                                                  {"item", &complex::item},
                                                                  {"list", &complex::list},
                                                                  {"empty", &complex::empty}});
    }

    mstch::node header() { return m_header; }

    mstch::node item() { return mstch::array_wrapper{m_item}; }

    mstch::node list() { return m_item.size() != 0; }

    mstch::node empty() { return m_item.size() == 0; }
};

const auto complex_data = mstch::object_wrapper{std::make_shared<complex>()};
