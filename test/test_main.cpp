#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "mstch/mstch.hpp"
#include "test_data.hpp"

using namespace mstchtest;

#define MSTCH_PARTIAL_TEST(x) TEST_CASE(#x) { \
    REQUIRE(x ## _txt == mstch::render(x ## _mustache, x ## _data, {{"partial", x ## _partial}})); \
}

#define MSTCH_TEST(x) TEST_CASE(#x) { \
    REQUIRE(x ## _txt == mstch::render(x ## _mustache, x ## _data)); \
}

MSTCH_TEST(ampersand_escape)
MSTCH_TEST(apostrophe)
MSTCH_TEST(array_of_strings)
MSTCH_TEST(backslashes)
MSTCH_TEST(bug_11_eating_whitespace)
MSTCH_TEST(bug_length_property)
MSTCH_TEST(comments)
MSTCH_TEST(context_lookup)
MSTCH_TEST(disappearing_whitespace)
MSTCH_TEST(double_render)
MSTCH_TEST(empty_list)
MSTCH_TEST(empty_sections)
MSTCH_TEST(empty_string)
MSTCH_TEST(empty_template)
MSTCH_TEST(error_not_found)
MSTCH_TEST(escaped)
MSTCH_TEST(falsy)
MSTCH_TEST(falsy_array)
MSTCH_TEST(grandparent_context)
MSTCH_TEST(implicit_iterator)
MSTCH_TEST(included_tag)
MSTCH_TEST(inverted_section)
MSTCH_TEST(keys_with_questionmarks)
MSTCH_TEST(multiline_comment)
MSTCH_TEST(nested_dot)
MSTCH_TEST(nested_higher_order_sections)
MSTCH_TEST(nested_iterating)
MSTCH_TEST(nesting)
MSTCH_TEST(nesting_same_name)
MSTCH_TEST(null_lookup_array)
MSTCH_TEST(null_lookup_object)
MSTCH_TEST(null_view)
MSTCH_PARTIAL_TEST(partial_array)
MSTCH_PARTIAL_TEST(partial_array_of_partials)
MSTCH_PARTIAL_TEST(partial_array_of_partials_implicit)
MSTCH_PARTIAL_TEST(partial_empty)
MSTCH_PARTIAL_TEST(partial_template)
MSTCH_TEST(recursion_with_same_names)
MSTCH_TEST(reuse_of_enumerables)
MSTCH_TEST(section_as_context)
MSTCH_PARTIAL_TEST(section_functions_in_partials)
MSTCH_TEST(string_as_context)
MSTCH_TEST(two_in_a_row)
MSTCH_TEST(two_sections)
MSTCH_TEST(unescaped)
MSTCH_TEST(whitespace)
MSTCH_TEST(zero_view)
