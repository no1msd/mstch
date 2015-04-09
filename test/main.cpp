#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <mstch.h>

#include <string>
#include <fstream>
#include <streambuf>

std::string file_to_string(const std::string& filename) {
    std::ifstream t(filename);
    std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    return str;
}

/*TEST_CASE("Ampersand escape") {
    #include "data/ampersand_escape.h"
    auto tpl = file_to_string("data/ampersand_escape.mustache");
    auto exp = file_to_string("data/ampersand_escape.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Apostrophe") {
    #include "data/apostrophe.h"
    auto tpl = file_to_string("data/apostrophe.mustache");
    auto exp = file_to_string("data/apostrophe.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Array of strings") {
    #include "data/array_of_strings.h"
    auto tpl = file_to_string("data/array_of_strings.mustache");
    auto exp = file_to_string("data/array_of_strings.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Backslashes") {
    #include "data/backslashes.h"
    auto tpl = file_to_string("data/backslashes.mustache");
    auto exp = file_to_string("data/backslashes.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Bug 11 eating whitespace") {
    #include "data/bug_11_eating_whitespace.h"
    auto tpl = file_to_string("data/bug_11_eating_whitespace.mustache");
    auto exp = file_to_string("data/bug_11_eating_whitespace.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Bug length property") {
    #include "data/bug_length_property.h"
    auto tpl = file_to_string("data/bug_length_property.mustache");
    auto exp = file_to_string("data/bug_length_property.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Context lookup") {
    #include "data/context_lookup.h"
    auto tpl = file_to_string("data/context_lookup.mustache");
    auto exp = file_to_string("data/context_lookup.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Disappearing whitespace") {
    #include "data/disappearing_whitespace.h"
    auto tpl = file_to_string("data/disappearing_whitespace.mustache");
    auto exp = file_to_string("data/disappearing_whitespace.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Double render") {
    #include "data/double_render.h"
    auto tpl = file_to_string("data/double_render.mustache");
    auto exp = file_to_string("data/double_render.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Empty list") {
    #include "data/empty_list.h"
    auto tpl = file_to_string("data/empty_list.mustache");
    auto exp = file_to_string("data/empty_list.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Empty sections") {
    #include "data/empty_sections.h"
    auto tpl = file_to_string("data/empty_sections.mustache");
    auto exp = file_to_string("data/empty_sections.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Empty string") {
    #include "data/empty_string.h"
    auto tpl = file_to_string("data/empty_string.mustache");
    auto exp = file_to_string("data/empty_string.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Empty template") {
    #include "data/empty_template.h"
    auto tpl = file_to_string("data/empty_template.mustache");
    auto exp = file_to_string("data/empty_template.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Error not found") {
    #include "data/error_not_found.h"
    auto tpl = file_to_string("data/error_not_found.mustache");
    auto exp = file_to_string("data/error_not_found.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Falsy") {
    #include "data/falsy.h"
    auto tpl = file_to_string("data/falsy.mustache");
    auto exp = file_to_string("data/falsy.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}*/

TEST_CASE("Falsy array") {
    #include "data/falsy_array.h"
    auto tpl = file_to_string("data/falsy_array.mustache");
    auto exp = file_to_string("data/falsy_array.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

/*TEST_CASE("Grandparent context") {
    #include "data/grandparent_context.h"
    auto tpl = file_to_string("data/grandparent_context.mustache");
    auto exp = file_to_string("data/grandparent_context.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Implicit iterator") {
    #include "data/implicit_iterator.h"
    auto tpl = file_to_string("data/implicit_iterator.mustache");
    auto exp = file_to_string("data/implicit_iterator.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Included tag") {
    #include "data/included_tag.h"
    auto tpl = file_to_string("data/included_tag.mustache");
    auto exp = file_to_string("data/included_tag.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Inverted section") {
    #include "data/inverted_section.h"
    auto tpl = file_to_string("data/inverted_section.mustache");
    auto exp = file_to_string("data/inverted_section.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Keys with questionmarks") {
    #include "data/keys_with_questionmarks.h"
    auto tpl = file_to_string("data/keys_with_questionmarks.mustache");
    auto exp = file_to_string("data/keys_with_questionmarks.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Multiline comment") {
    #include "data/multiline_comment.h"
    auto tpl = file_to_string("data/multiline_comment.mustache");
    auto exp = file_to_string("data/multiline_comment.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Nested dot") {
    #include "data/nested_dot.h"
    auto tpl = file_to_string("data/nested_dot.mustache");
    auto exp = file_to_string("data/nested_dot.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Nested iterating") {
    #include "data/nested_iterating.h"
    auto tpl = file_to_string("data/nested_iterating.mustache");
    auto exp = file_to_string("data/nested_iterating.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Nesting") {
    #include "data/nesting.h"
    auto tpl = file_to_string("data/nesting.mustache");
    auto exp = file_to_string("data/nesting.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Nesting same name") {
    #include "data/nesting_same_name.h"
    auto tpl = file_to_string("data/nesting_same_name.mustache");
    auto exp = file_to_string("data/nesting_same_name.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Null lookup array") {
    #include "data/null_lookup_array.h"
    auto tpl = file_to_string("data/null_lookup_array.mustache");
    auto exp = file_to_string("data/null_lookup_array.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Null lookup object") {
    #include "data/null_lookup_object.h"
    auto tpl = file_to_string("data/null_lookup_object.mustache");
    auto exp = file_to_string("data/null_lookup_object.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Null view") {
    #include "data/null_view.h"
    auto tpl = file_to_string("data/null_view.mustache");
    auto exp = file_to_string("data/null_view.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Recursion with same names") {
    #include "data/recursion_with_same_names.h"
    auto tpl = file_to_string("data/recursion_with_same_names.mustache");
    auto exp = file_to_string("data/recursion_with_same_names.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Reuse of enumerables") {
    #include "data/reuse_of_enumerables.h"
    auto tpl = file_to_string("data/reuse_of_enumerables.mustache");
    auto exp = file_to_string("data/reuse_of_enumerables.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Section as context") {
    #include "data/section_as_context.h"
    auto tpl = file_to_string("data/section_as_context.mustache");
    auto exp = file_to_string("data/section_as_context.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("String as context") {
    #include "data/string_as_context.h"
    auto tpl = file_to_string("data/string_as_context.mustache");
    auto exp = file_to_string("data/string_as_context.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Two in a row") {
    #include "data/two_in_a_row.h"
    auto tpl = file_to_string("data/two_in_a_row.mustache");
    auto exp = file_to_string("data/two_in_a_row.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Two sections") {
    #include "data/two_sections.h"
    auto tpl = file_to_string("data/two_sections.mustache");
    auto exp = file_to_string("data/two_sections.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Whitespace") {
    #include "data/whitespace.h"
    auto tpl = file_to_string("data/whitespace.mustache");
    auto exp = file_to_string("data/whitespace.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}

TEST_CASE("Zero view") {
    #include "data/zero_view.h"
    auto tpl = file_to_string("data/zero_view.mustache");
    auto exp = file_to_string("data/zero_view.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}*/
