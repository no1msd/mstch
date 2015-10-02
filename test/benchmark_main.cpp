#define BENCHPRESS_CONFIG_MAIN

#include <benchpress.hpp>

#include "mstch/mstch.hpp"

benchpress::auto_register basic_usage("basic usage", [](benchpress::context* ctx) {
    std::string comment_tmp{
        "<div class=\"comments\"><h3>{{header}}</h3><ul>"
        "{{#comments}}<li class=\"comment\"><h5>{{name}}</h5>"
        "<p>{{body}}</p></li>{{/comments}}</ul></div>"};

    auto comment_view = mstch::map{
        {"header", std::string{"My Post Comments"}},
            {"comments", mstch::array{
                mstch::map{{"name", std::string{"Joe"}}, {"body", std::string{"Thanks for this post!"}}},
                mstch::map{{"name", std::string{"Sam"}}, {"body", std::string{"Thanks for this post!"}}},
                mstch::map{{"name", std::string{"Heather"}}, {"body", std::string{"Thanks for this post!"}}},
                mstch::map{{"name", std::string{"Kathy"}}, {"body", std::string{"Thanks for this post!"}}},
                mstch::map{{"name", std::string{"George"}}, {"body", std::string{"Thanks for this post!"}}}}}};

    ctx->reset_timer();

    for (size_t i = 0; i < ctx->num_iterations(); ++i)
        mstch::render(comment_tmp, comment_view);
});
