#include <regex>
#include <iostream>

#include "mstch/mstch.hpp"
#include "render_context.hpp"

using namespace mstch;

std::string strip_whitespace(std::string tmplt) {
    std::regex comment_match("\\{\\{![^\\}]*\\}\\}");
    tmplt = std::regex_replace(tmplt, comment_match, "{{!}}");
    std::ostringstream out;
    std::istringstream in(tmplt);
    std::string line;
    std::regex tag_match("\\{{2}[ ]*[#|/|^|!]{1}[^\\}]*\\}{2}");
    std::regex whitespace_match("^\\s*$");
    while (std::getline(in, line)) {
        std::string no_tags = std::regex_replace(line, tag_match, "");
        if (no_tags != line && std::regex_match(no_tags, whitespace_match)) {
            out << std::regex_replace(line, std::regex("\\s"), "");
        } else {
            out << line;
            if(!in.eof()) out << std::endl;
        }
    }
    return out.str();
}

std::string mstch::render(
        const std::string& tmplt,
        const object& root_object,
        const std::map<std::string,std::string>& partials)
{
    return render_context(root_object, partials)
            .render(strip_whitespace(tmplt));
}
