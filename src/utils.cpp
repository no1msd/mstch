#include "utils.h"

#include <boost/algorithm/string/replace.hpp>

std::string mstch::html_escape(std::string str) {
    boost::replace_all(str, "&", "&amp;");
    boost::replace_all(str, "'", "&#39;");
    boost::replace_all(str, "\"", "&quot;");
    boost::replace_all(str, "<", "&lt;");
    boost::replace_all(str, ">", "&gt;");
    boost::replace_all(str, "/", "&#x2F;");
    return str;
}
