std::map<std::string,std::function<std::string(const std::string&)>> specs_lambdas {
    {"Interpolation", [](const std::string&) {
      return "world";
    }},
    {"Interpolation - Expansion", [](const std::string&) {
      return "{{planet}}";
    }},
    {"Interpolation - Alternate Delimiters", [](const std::string&) {
      return "|planet| => {{planet}}";
    }},
    {"Interpolation - Multiple Calls", [](const std::string&) {
      static int calls = 0; return std::to_string(++calls);
    }},
    {"Escaping", [](const std::string&) {
      return ">";
    }},
    {"Section", [](const std::string& txt) {
      return (txt == "{{x}}") ? "yes" : "no";
    }},
    {"Section - Expansion", [](const std::string& txt) {
      return txt + "{{planet}}" + txt;
    }},
    {"Section - Alternate Delimiters", [](const std::string& txt) {
      return txt + "{{planet}} => |planet|" + txt;
    }},
    {"Section - Multiple Calls", [](const std::string& txt) {
      return "__" + txt + "__";
    }},
    {"Inverted Section", [](const std::string& txt) {
      return "";
    }}
};