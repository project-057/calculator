#include <string.h>

#include "../src/utils.h"

#include "greatest.h"

TEST is_double_should_mark_doubles_test(void)
{
	ASSERT(is_double("123"));
	ASSERT(is_double("123.456"));
	ASSERT(is_double("-0.7"));
	PASS();
}

TEST is_double_shouldnt_mark_incorrect_doubles_test(void)
{
	ASSERT_FALSE(is_double(""));
	ASSERT_FALSE(is_double("-0."));
	ASSERT_FALSE(is_double("-"));
	ASSERT_FALSE(is_double("12three4"));
	ASSERT_FALSE(is_double("127.0.0.1"));
	PASS();
}

SUITE(is_double_suit)
{
	RUN_TEST(is_double_should_mark_doubles_test);
	RUN_TEST(is_double_shouldnt_mark_incorrect_doubles_test);
}

TEST whitespace_cleaner_should_remove_whitespaces(void)
{
	char arg[] = "1+ 2/3    *7"; whitespace_cleaner(arg);
	ASSERT_STR_EQ(arg, "1+2/3*7");

	char arg2[] = " "; whitespace_cleaner(arg2);
	ASSERT_STR_EQ(arg2, "");

	PASS();
}

SUITE(whitespace_cleaner_suit)
{
	RUN_TEST(whitespace_cleaner_should_remove_whitespaces);
}

GREATEST_MAIN_DEFS();
int main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(is_double_suit);
	RUN_SUITE(whitespace_cleaner_suit);
	GREATEST_MAIN_END();
}
