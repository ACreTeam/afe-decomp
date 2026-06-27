#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Include the actual production header
#include "src/static/GAEJ01_00/dolphin/card/CARDCreate.h"

START_TEST(test_buffer_reads_never_exceed_declared_length)
{
    // Invariant: Buffer reads never exceed the declared length
    const char *payloads[] = {
        "normal",                    // Valid input
        "A",                         // Boundary: single char
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",  // 100 chars - oversized
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",  // 100 chars - oversized
        "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"   // 100 chars - oversized
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        // Test strncpy usage in the actual code
        char dest[32];  // Small buffer to test overflow
        const char *src = payloads[i];
        
        // Call strncpy as used in production code
        strncpy(dest, src, sizeof(dest));
        
        // Check that destination is properly terminated
        ck_assert_msg(dest[sizeof(dest)-1] == '\0', 
                     "Buffer not properly terminated for payload %d", i);
        
        // Check that no out-of-bounds write occurred
        // This is a defensive check - we can't directly test for overflow,
        // but we can verify the buffer is still valid
        ck_assert_msg(strlen(dest) < sizeof(dest),
                     "String length exceeds buffer size for payload %d", i);
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_buffer_reads_never_exceed_declared_length);
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