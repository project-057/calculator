#include <string.h>
#include <stdio.h>

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

TEST to_rpn_should_transform_token_array_to_reverse_polish_notation(void)
{
	TokenArray infix_expr = create_token_array();
    // infix_expr = split_to_tokens("128 + 256 * 42.45 / ( -2.42 − 324.01 ) ^ 2192.1 ^ 4214.2");
	infix_expr.array[0] = "128";	
	infix_expr.array[1] = "+";	
	infix_expr.array[2] = "256";	
	infix_expr.array[3] = "*";	
	infix_expr.array[4] = "42.45";	
	infix_expr.array[5] = "/";	
	infix_expr.array[6] = "(";	
	infix_expr.array[7] = "-2.42";	
	infix_expr.array[8] = "-";	
	infix_expr.array[9] = "324.01";	
	infix_expr.array[10] = ")";	
	infix_expr.array[11] = "^";	
	infix_expr.array[12] = "2192.1";	
	infix_expr.array[13] = "^";	
	infix_expr.array[14] = "4214.2";	
	infix_expr.size = 15;

	TokenArray postfix_expr = to_rpn(infix_expr);

    TokenArray correct_postfix_expr = create_token_array(); 
	correct_postfix_expr.array[0] = "128";	
	correct_postfix_expr.array[1] = "256";	
	correct_postfix_expr.array[2] = "42.45";	
	correct_postfix_expr.array[3] = "*";	
	correct_postfix_expr.array[4] = "-2.42";	
	correct_postfix_expr.array[5] = "324.01";	
	correct_postfix_expr.array[6] = "-";	
	correct_postfix_expr.array[7] = "2192.1";	
	correct_postfix_expr.array[8] = "4214.2";	
	correct_postfix_expr.array[9] = "^";	
	correct_postfix_expr.array[10] = "^";	
	correct_postfix_expr.array[11] = "/";	
	correct_postfix_expr.array[12] = "+";	
	correct_postfix_expr.size = 13;

	for (int i = 0; i < postfix_expr.size; i++) {
		ASSERT_STR_EQ(correct_postfix_expr.array[i], postfix_expr.array[i]);
	}

	free_token_array(&infix_expr);

	PASS();
}

SUITE(to_rpn_suit)
{
	RUN_TEST(to_rpn_should_transform_token_array_to_reverse_polish_notation);
}

TEST split_to_tokens_should_split_to_tokens(void)
{
    enum {COUNT_OF_TESTS = 9};
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
        {"0", "-", "1","*","(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0"},
        {"0", "-", "1","*","(", "7", "+", "exp", "(", "0", "-", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0"},
        {"(", "0", "-", "1", ")","*","(", "7", "+", "exp", "(", "0", "-", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0"},
    };

    for (int test_index = 0; test_index < COUNT_OF_TESTS; test_index++) {
        TokenArray getted = split_to_tokens(tests[test_index]);
        for (int j = 0; j < getted.size; j++) {
            ASSERT_STR_EQ(expects[test_index][j], getted.array[j]);
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
	RUN_SUITE(to_rpn_suit);
    RUN_SUITE(split_to_tokens_suit);
	GREATEST_MAIN_END();
}
