#include "mstch/mstch.hpp"

#include <chrono>
#include <iostream>

int main() {
    std::string complex_html{
        "<h1>{{header}}</h1>\n"
        "{{#list}}\n"
        "  <ul>\n"
        "  {{#item}}\n"
        "    {{#current}}\n"
        "      <li><strong>{{name}}</strong></li>\n"
        "    {{/current}}\n"
        "    {{#link}}\n"
        "      <li><a href=\"{{url}}\">{{name}}</a></li>\n"
        "    {{/link}}\n"
        "  {{/item}}\n"
        "  </ul>\n"
        "{{/list}}\n"
        "{{#empty}}\n"
        "  <p>The list is empty.</p>\n"
        "{{/empty}}\n"
        "{{^empty}}\n"
        "  <p>The list is not empty.</p>\n"
        "{{/empty}}"
    };



    std::string comment_tmp{
        "<div class=\"comments\"><h3>{{header}}</h3><ul>"
        "{{#comments}}<li class=\"comment\"><h5>{{name}}</h5>"
        "<p>{{body}}</p></li>{{/comments}}</ul></div>"
    };
    auto comment_view = mstch::object{
        {"header", std::string{"My Post Comments"}},
        {"comments", mstch::array{
          mstch::object{{"name", std::string{"Joe"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::object{{"name", std::string{"Sam"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::object{{"name", std::string{"Heather"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::object{{"name", std::string{"Kathy"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::object{{"name", std::string{"George"}}, {"body", std::string{"Thanks for this post!"}}}
        }}
    };

    std::vector<int> times;
    for(int j = 0; j < 10; j++) {
        unsigned long start =
                std::chrono::system_clock::now().time_since_epoch() /
                std::chrono::milliseconds(1);
        for(int i = 0; i < 5000; i++) {
            mstch::render(comment_tmp, comment_view);
        }
        times.push_back((std::chrono::system_clock::now().time_since_epoch() /
                std::chrono::milliseconds(1)) - start);
    }

    float avg = 0;
    for(int i: times) avg += i;
    avg /= times.size();

    std::cout << avg << std::endl;

    return 0;
}
