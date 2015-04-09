#include "render_section.h"
#include "is_node_empty.h"

using namespace mstch;

visitor::render_section::render_section(render_context& context, const std::string& section):
        context(context),
        section(section)
{
}

std::string visitor::render_section::operator()(const boost::blank& blank) const {
    return "";
}

std::string visitor::render_section::operator()(const int& i) const {
    return render_context(mstch::object{{".", i}}, context).render(section);
}

std::string visitor::render_section::operator()(const bool& b) const {
    return render_context(mstch::object{{".", b}}, context).render(section);
}

std::string visitor::render_section::operator()(const std::string& str) const {
    return render_context(mstch::object{{".", str}}, context).render(section);
}

std::string visitor::render_section::operator()(const array& arr) const {
    std::ostringstream out;
    for (auto& item: arr)
        if (!boost::apply_visitor(visitor::is_node_empty(), item))
            out << boost::apply_visitor(*this, item);
    return out.str();
}

std::string visitor::render_section::operator()(const object& obj) const {
    return render_context(obj, context).render(section);
}
