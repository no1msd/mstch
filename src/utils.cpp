#include "utils.hpp"

#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

std::string mstch::strip_whitespace(const std::string& tmplt) {
    boost::regex comment_match("\\{\\{![^\\}]*\\}\\}");
    boost::regex tag_match("\\{{2}[ ]*[#|/|^|!|>]{1}[^\\}]*\\}{2}");
    boost::regex whitespace_match("^\\s*$");
    std::ostringstream out;
    std::istringstream in(boost::regex_replace(tmplt, comment_match, "{{!}}"));
    for(std::string line; std::getline(in, line);) {
        std::string no_tags = boost::regex_replace(line, tag_match, "");
        if (no_tags != line && boost::regex_match(no_tags, whitespace_match))
            out << boost::regex_replace(line, boost::regex("\\s"), "");
        else
            out << line << (in.eof()?"":"\n");
    }
    return out.str();
    return tmplt;
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
