#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "mstch.h"
#include "test_data.h"

#define MSTCH_TEST(x,y) TEST_CASE(x) { REQUIRE(y ## _txt == mstch::render(y ## _mustache, y ## _data)); }

MSTCH_TEST("Ampersand escape", mstchtest::ampersand_escape)
MSTCH_TEST("Apostrophe", mstchtest::apostrophe)
MSTCH_TEST("Array of strings", mstchtest::array_of_strings)
MSTCH_TEST("Backslashes", mstchtest::backslashes)
MSTCH_TEST("Eating whitespace", mstchtest::bug_11_eating_whitespace)
MSTCH_TEST("Length property", mstchtest::bug_length_property)
MSTCH_TEST("Context lookup", mstchtest::context_lookup)
MSTCH_TEST("Disappearing whitespace", mstchtest::disappearing_whitespace)
MSTCH_TEST("Double render", mstchtest::double_render)
MSTCH_TEST("Empty list", mstchtest::empty_list)
MSTCH_TEST("Empty sections", mstchtest::empty_sections)
MSTCH_TEST("Empty string", mstchtest::empty_string)
MSTCH_TEST("Empty template", mstchtest::empty_template)
MSTCH_TEST("Error not found", mstchtest::error_not_found)
MSTCH_TEST("Falsy", mstchtest::falsy)

/*TEST_CASE("Falsy array") {
    #include "data/falsy_array.h"
    auto tpl = file_to_string("data/falsy_array.mustache");
    auto exp = file_to_string("data/falsy_array.txt");
    REQUIRE(exp == mstch::render(tpl, data));
}*/

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
