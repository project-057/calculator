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

TEST split_to_tokens_should_split_to_tokens(void)
{
#define COUNT_OF_TESTS 9 
    char tests[COUNT_OF_TESTS][MAX_LENGTH] = {
        "",
        "1 + 2",
        "3 - 3*3",
        "2 + var -",
        "2*(7+exp(2^12.2 + 123)-12.7777+pow(12,var2))",
        "2*(7+exp(2^12.2 + 123)-12.7777+pow(12,var2))/27.7-12.0",
        "-1*(7+exp(2^12.2 + 123)-12.7777+pow(12,var2))/27.7-12.0",
        "-1*(7+exp(-2^12.2 + 123)-12.7777+pow(12,var2))/27.7-12.0",
        "(-1)*(7+exp(-2^12.2 + 123)-12.7777+pow(12,var2))/27.7-12.0"
    };
    
    char expects[COUNT_OF_TESTS][MAX_LENGTH][MAX_LENGTH] = {
        {""},
        {"1","+","2"},
        {"3", "-", "3", "*", "3"},
        {"2", "+", "var","-"},
        {"2","*","(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")"},
        {"2","*","(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0"},
        {"-1","*","(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0"},
        {"-1","*","(", "7", "+", "exp", "(", "-", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0"},
        {"(", "-1", ")","*","(", "7", "+", "exp", "(", "-", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0"}
    };

    for (int test_index = 0; test_index < COUNT_OF_TESTS; test_index++) {
        TokenArray getted = split_to_tokens(tests[test_index]);
        for (int j = 0; j < getted.size; j++) {
            ASSERT_STR_EQ(expects[test_index][j], getted.array[j]);
            printf("TEST NUMBER %d, EXPECTED \"%s\", GOT \"%s\"\n", test_index, expects[test_index][j], getted.array[j]);
        }
        free_token_array(&getted);
    }

    PASS();

}

SUITE(split_to_tokens_suit)
{
    RUN_TEST(split_to_tokens_should_split_to_tokens);
}



GREATEST_MAIN_DEFS();
int main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();
	RUN_SUITE(is_double_suit);
	RUN_SUITE(whitespace_cleaner_suit);
    RUN_SUITE(split_to_tokens_suit);
	GREATEST_MAIN_END();
}
