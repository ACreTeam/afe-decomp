#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <include/libc64/sprintf.h>

START_TEST(test_sprintf_no_buffer_overflow)
{
    // Invariant: sprintf must not write beyond the bounds of the destination buffer
    const char *payloads[] = {
        "%s",           // Valid input
        "%999999s",     // Boundary: large width specifier
        "%.999999s",    // Boundary: large precision specifier
        "%s%s%s%s%s",   // Multiple format specifiers
        "%100s",        // Width exceeding typical buffer
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        char dst[64] = {0};  // Fixed-size buffer
        const char *input = "A";
        
        // Call the actual sprintf function
        int result = sprintf(dst, payloads[i], input);
        
        // Check that result is non-negative (no error) and within buffer bounds
        ck_assert_msg(result >= 0, "sprintf returned error for payload: %s", payloads[i]);
        ck_assert_msg(result < sizeof(dst), 
                     "sprintf wrote %d bytes exceeding buffer of %zu for payload: %s", 
                     result, sizeof(dst), payloads[i]);
        
        // Ensure null termination
        ck_assert_msg(dst[sizeof(dst)-1] == '\0' || result < sizeof(dst)-1,
                     "Buffer may not be null-terminated for payload: %s", payloads[i]);
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_sprintf_no_buffer_overflow);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}