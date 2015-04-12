#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "mstch/mstch.hpp"

#include "test_data.hpp"

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
MSTCH_TEST("Falsy array", mstchtest::falsy_array)
MSTCH_TEST("Grandparent context", mstchtest::grandparent_context)
MSTCH_TEST("Implicit iterator", mstchtest::implicit_iterator)
MSTCH_TEST("Included tag", mstchtest::included_tag)
MSTCH_TEST("Inverted section", mstchtest::inverted_section)
MSTCH_TEST("Keys with questionsmarks", mstchtest::keys_with_questionmarks)
MSTCH_TEST("Multiline comment", mstchtest::multiline_comment)
MSTCH_TEST("Nested dot", mstchtest::nested_dot)
MSTCH_TEST("Nested iterating", mstchtest::nested_iterating)
MSTCH_TEST("Nesting", mstchtest::nesting)
MSTCH_TEST("Nesting same name", mstchtest::nesting_same_name)
MSTCH_TEST("Null lookup array", mstchtest::null_lookup_array)
MSTCH_TEST("Null lookup object", mstchtest::null_lookup_object)
MSTCH_TEST("Null view", mstchtest::null_view)
MSTCH_TEST("Recursion with same names", mstchtest::recursion_with_same_names)
MSTCH_TEST("Reuse of enumerables", mstchtest::reuse_of_enumerables)
MSTCH_TEST("Section as context", mstchtest::section_as_context)
MSTCH_TEST("String as context", mstchtest::string_as_context)
MSTCH_TEST("Two in a row", mstchtest::two_in_a_row)
MSTCH_TEST("Two sections", mstchtest::two_sections)
MSTCH_TEST("Whitespace", mstchtest::whitespace)
MSTCH_TEST("Zero view", mstchtest::zero_view)
