#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

#include <map>

namespace json {

namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

using node = boost::make_recursive_variant<
    std::nullptr_t, std::string, int, double, bool,
    std::map<const std::string, boost::recursive_variant_>,
    std::vector<boost::recursive_variant_>>::type;
using map = std::map<const std::string, node>;
using array = std::vector<node>;

template<class Iterator, class Node, class Map, class Array>
struct json_grammar: qi::grammar<Iterator, Node(), ascii::space_type> {
  struct esc_parser: qi::symbols<char,char> {
    esc_parser() {
      add("\\\\" , '\\') ("\\\"" , '"' ) ("\\n"  , '\n') ("\\r"  , '\r')
         ("\\b"  , '\b') ("\\f"  , '\f') ("\\t"  , '\t');
    }
  } escaped;

  json_grammar(): json_grammar::base_type(value_rule) {
    value_rule %= string_rule                            |
                  qi::double_                            |
                  object_rule                            |
                  array_rule                             |
                  qi::lit("true" )[spirit::_val = true ] |
                  qi::lit("false")[spirit::_val = false] |
                  "null";
    string_rule = spirit::lexeme['"' >> *(escaped | (qi::char_ - '"')) >> '"'];
    object_rule = '{' >> -((string_rule >> ':' >> value_rule) % ',') >> '}';
    array_rule  = '[' >> -(value_rule % ',') >> ']';
  }

  qi::rule<Iterator, Node(),        ascii::space_type> value_rule;
  qi::rule<Iterator, Map(),         ascii::space_type> object_rule;
  qi::rule<Iterator, Array(),       ascii::space_type> array_rule;
  qi::rule<Iterator, std::string(), ascii::space_type> string_rule;
};

struct json_visitor: boost::static_visitor<std::string> {
  std::string escape(const std::string& str) const {
    std::string ret{str};
    boost::replace_all(ret, "\\", "\\\\");
    boost::replace_all(ret, "\"", "\\\"");
    return ret;
  }

  std::string operator()(const std::nullptr_t& value) const {
    return "null";
  }

  std::string operator()(const std::string& value) const {
    return "\"" + escape(value) + "\"";
  }

  std::string operator()(const int& value) const {
    return std::to_string(value);
  }

  std::string operator()(const double& value) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
  }

  std::string operator()(const bool& value) const {
    return value ? "true" : "false";
  }

  std::string operator()(const json::map& value) const {
    std::string out;
    bool comma = false;
    for(auto& item: value)
      out += (comma++ ? ", \"" : "\"") + escape(item.first) + "\": " +
             boost::apply_visitor(json_visitor(), item.second);
    return "{" + out + "}";
  }

  std::string operator()(const json::array& value) const {
    std::string out;
    bool comma = false;
    for(auto& item: value)
      out += (comma++ ? ", " : "") + boost::apply_visitor(json_visitor(), item);
    return "[" + out + "]";
  }
};

template<class Node = node, class Map = map, class Array = array>
Node parse(const std::string& str) {
  Node out;
  json_grammar<std::string::const_iterator, Node, Map, Array> json;
  auto first = str.begin(), last = str.end();
  bool ret = qi::phrase_parse(first, last, json, ascii::space, out);
  return (!ret || first != last) ? Node() : out;
}

template<class Node = node>
std::string stringify(const Node& node) {
  return boost::apply_visitor(json_visitor(), node);
}

}
