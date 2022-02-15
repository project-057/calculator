#include <stdio.h>
#include <string.h>

#include "../src/eval.h"
#include "../src/utils.h"

#include "greatest.h"

const double EPS = 1e-5;

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
    char arg[] = "1+ 2/3    *7";
    whitespace_cleaner(arg);
    ASSERT_STR_EQ(arg, "1+2/3*7");

    char arg2[] = " ";
    whitespace_cleaner(arg2);
    ASSERT_STR_EQ(arg2, "");

    PASS();
}

SUITE(whitespace_cleaner_suit)
{
    RUN_TEST(whitespace_cleaner_should_remove_whitespaces);
}

TEST to_rpn_should_transform_token_array_to_reverse_polish_notation(void)
{
    char test_expr[] = "128 + 256 * 42.45 / ( -2.42 - 324.01 ) ^ 2192.1 ^ 4214.2";
    char correct_answ[MAX_LENGTH][MAX_TOKEN_LENGTH] = {
        "128", "256", "42.45",
        "*",
        "0", "2.42",
        "-",
        "324.01",
        "-",
        "2192.1", "4214.2",
        "^",
        "^",
        "/",
        "+"
    };

    TokenArray postfix_expr = to_rpn(split_to_tokens(test_expr));

    for (int i = 0; i < postfix_expr.size; i++) {
        ASSERT_STR_EQ(correct_answ[i], postfix_expr.array[i]);
    }

    PASS();
}

SUITE(to_rpn_suit)
{
    RUN_TEST(to_rpn_should_transform_token_array_to_reverse_polish_notation);
}

TEST split_to_tokens_should_split_to_tokens(void)
{
    enum { COUNT_OF_TESTS = 9 };
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
        { "" },
        { "1", "+", "2" },
        { "3", "-", "3", "*", "3" },
        { "2", "+", "var", "-" },
        { "2", "*", "(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")" },
        { "2", "*", "(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0" },
        { "0", "-", "1", "*", "(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0" },
        { "0", "-", "1", "*", "(", "7", "+", "exp", "(", "0", "-", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0" },
        { "(", "0", "-", "1", ")", "*", "(", "7", "+", "exp", "(", "0", "-", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "var2", ")", ")", "/", "27.7", "-", "12.0" },
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

TEST eval_should_count_correct(void)
{
    char tests[5][MAX_LENGTH] = {
        "10 + 5",
        "2 * 128 / 2",
        "5 / 0",
        "214.4 * 4.7 + (32.11 / 2)",
        "128 + 4.45 * (- 2.42 - 3.01 ) ^ 2 ^ 3"
    };

    TokenArray first_test = to_rpn(split_to_tokens(tests[0]));
    TokenArray second_test = to_rpn(split_to_tokens(tests[1]));
    TokenArray third_test = to_rpn(split_to_tokens(tests[2]));
    TokenArray fourth_test = to_rpn(split_to_tokens(tests[3]));
    TokenArray fifth_test = to_rpn(split_to_tokens(tests[4]));

    double correct_answ[5] = {
        15,
        128,
        INFINITY,
        1023.735,
        3363374.10333
    };

    ASSERT_IN_RANGE(correct_answ[0], eval(first_test), EPS);
    ASSERT_IN_RANGE(correct_answ[1], eval(second_test), EPS);
    ASSERT_IN_RANGE(correct_answ[2], eval(third_test), EPS);
    ASSERT_IN_RANGE(correct_answ[3], eval(fourth_test), EPS);
    ASSERT_IN_RANGE(correct_answ[4], eval(fifth_test), EPS);

    free_token_array(&first_test);
    free_token_array(&second_test);
    free_token_array(&third_test);
    free_token_array(&fourth_test);
    free_token_array(&fifth_test);

    PASS();
}

SUITE(eval_suit)
{
    RUN_TEST(eval_should_count_correct);
}

TEST variables_to_values_should_replace_variables_to_values()
{
    enum { COUNT_OF_TESTS = 9 };
    char tests[COUNT_OF_TESTS][MAX_LENGTH] = {
        "1 - x",
        "1 + x",
        "3 - x*3",
        "2 + var -",
        "2*(7+exp(2^12.2 + 123)-12.7777+pow(12,var2))",
        "2*(7+exp(2^12.2 + 123)-12.7777+pow1(12,var2))/27.7-12.0",
        "-1*(7+exp1(2^12.2 + 123)-12.7777+pow(12,var2))/27.7-12.0",
        "-1*(7+exp2(2^12.2 + 123)-12.7777+pow12(12,var2))/27.7-12.0",
        "(-1)*(7+exp4(-2^12.2 + 123)-12.7777+powder(12, JINX))"
    };

    Variable tests_vars[COUNT_OF_TESTS][MAX_VARS_AMOUNT] = {
        { { .name = "x", .value = -2 } },
        { { .name = "x", .value = -3 } },
        { { .name = "x", .value = -2 } },
        { { .name = "var", .value = -100 } },
        { { .name = "var2", .value = 3.14 } },
        { { .name = "var2", .value = 354 }, { .name = "pow1", .value = 1.0 } },
        { { .name = "exp1", .value = 2.78 }, { .name = "var2", .value = 2.0 } },
        { { .name = "exp2", .value = 9.999 }, { .name = "pow12", .value = 12.2 }, { .name = "var2", .value = 13.2 } },
        { { .name = "exp4", .value = 123.123 }, { .name = "powder", .value = 312.321 }, { .name = "JINX", .value = 321.123 } }
    };

    int tests_var_sizes[COUNT_OF_TESTS] = {
        1,
        1,
        1,
        1,
        1,
        2,
        2,
        3,
        3
    };

    char expects[COUNT_OF_TESTS][MAX_LENGTH][MAX_LENGTH] = {
        { "1", "-", "-2" },
        { "1", "+", "-3" },
        { "3", "-", "-2", "*", "3" },
        { "2", "+", "-100", "-" },
        { "2", "*", "(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "3.14", ")", ")" },
        { "2", "*", "(", "7", "+", "exp", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "1.0", "(", "12", ",", "354", ")", ")", "/", "27.7", "-", "12.0" },
        { "0", "-", "1", "*", "(", "7", "+", "2.78", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "pow", "(", "12", ",", "2.0", ")", ")", "/", "27.7", "-", "12.0" },
        { "0", "-", "1", "*", "(", "7", "+", "9.999", "(", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "12.2", "(", "12", ",", "13.2", ")", ")", "/", "27.7", "-", "12.0" },
        { "(", "0", "-", "1", ")", "*", "(", "7", "+", "123.123", "(", "0", "-", "2", "^", "12.2", "+", "123", ")", "-", "12.7777", "+", "312.321", "(", "12", ",", "321.123", ")", ")" }
    };

    for (int test_index = 0; test_index < COUNT_OF_TESTS; test_index++) {
        TokenArray test = split_to_tokens(tests[test_index]);
        TokenArray got = variables_to_values(test, tests_vars[test_index], tests_var_sizes[test_index]);

        for (int i = 0; i < MAX_LENGTH; i++) {
            if (*expects[test_index][i] == '\0') {
                break;
            }
            if (is_double(expects[test_index][i])) {
                char* end_ptr;
                double exp_double = strtod(expects[test_index][i], &end_ptr);
                double got_double = strtod(got.array[i], &end_ptr);
                ASSERT_IN_RANGE(exp_double, got_double, EPS);
            } else {
                ASSERT_STR_EQ(expects[test_index][i], got.array[i]);
            }
        }

        free_token_array(&test);
        free_token_array(&got);
    }

    PASS();
}

SUITE(vtv_test_suit)
{
    RUN_TEST(variables_to_values_should_replace_variables_to_values);
}

GREATEST_MAIN_DEFS();
int main(int argc, char** argv)
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(is_double_suit);
    RUN_SUITE(whitespace_cleaner_suit);
    RUN_SUITE(split_to_tokens_suit);
    RUN_SUITE(vtv_test_suit);
    RUN_SUITE(eval_suit);
    GREATEST_MAIN_END();
}
