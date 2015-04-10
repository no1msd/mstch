#include "utils.h"

#include <algorithm>

std::string& mstch::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(
            s.begin(),
            s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string& mstch::rtrim(std::string& s) {
    s.erase(std::find_if(
            s.rbegin(),
            s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string& mstch::trim(std::string& s) {
    return ltrim(rtrim(s));
}

std::string mstch::replace_all(
        std::string str,
        const std::string& from,
        const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string mstch::html_escape(std::string str) {
    str = replace_all(str, "&", "&amp;");
    str = replace_all(str, "'", "&#39;");
    str = replace_all(str, "\"", "&quot;");
    str = replace_all(str, "<", "&lt;");
    str = replace_all(str, ">", "&gt;");
    str = replace_all(str, "/", "&#x2F;");
    return str;
}
