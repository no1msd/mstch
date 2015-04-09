#ifndef _MSTCH_UTILS_H_
#define _MSTCH_UTILS_H_

#include <string>

namespace mstch {
    std::string& ltrim(std::string& s);
    std::string& rtrim(std::string& s);
    std::string& trim(std::string& s);
    std::string replace_all(std::string str, const std::string& from, const std::string& to);
    std::string html_escape(std::string str);
}

#endif //_MSTCH_UTILS_H_
