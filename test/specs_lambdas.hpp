std::map<std::string,std::function<mstch::node(const std::string&)>> specs_lambdas {
    {"Interpolation", [](const std::string&) {
      return std::string{"world"};
    }},
    {"Interpolation - Expansion", [](const std::string&) {
      return std::string{"{{planet}}"};
    }},
    {"Interpolation - Multiple Calls", [](const std::string&) {
      static int calls = 0; return ++calls;
    }},
    {"Escaping", [](const std::string&) {
      return std::string{">"};
    }},
    {"Section", [](const std::string& txt) {
      return std::string{(txt == "{{x}}") ? "yes" : "no"};
    }},
    {"Section - Expansion", [](const std::string& txt) {
      return txt + std::string{"{{planet}}"} + txt;
    }},
    {"Section - Multiple Calls", [](const std::string& txt) {
      return "__" + txt + "__";
    }},
    {"Inverted Section", [](const std::string& txt) {
      return false;
    }}
};