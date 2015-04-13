#include "utils.hpp"

#include <regex>
#include <boost/algorithm/string/replace.hpp>

std::string mstch::strip_whitespace(const std::string& tmplt) {
    std::regex comment_match("\\{\\{![^\\}]*\\}\\}");
    std::regex tag_match("\\{{2}[ ]*[#|/|^|!|>]{1}[^\\}]*\\}{2}");
    std::regex whitespace_match("^\\s*$");
    std::ostringstream out;
    std::istringstream in(std::regex_replace(tmplt, comment_match, "{{!}}"));
    for(std::string line; std::getline(in, line);) {
        std::string no_tags = std::regex_replace(line, tag_match, "");
        if (no_tags != line && std::regex_match(no_tags, whitespace_match))
            out << std::regex_replace(line, std::regex("\\s"), "");
        else
            out << line << (in.eof()?"":"\n");
    }
    return out.str();
}

std::string mstch::html_escape(std::string str) {
    boost::replace_all(str, "&", "&amp;");
    boost::replace_all(str, "'", "&#39;");
    boost::replace_all(str, "\"", "&quot;");
    boost::replace_all(str, "<", "&lt;");
    boost::replace_all(str, ">", "&gt;");
    boost::replace_all(str, "/", "&#x2F;");
    return str;
}
