#ifndef CONFIG_H
#define CONFIG_H

// --- SANDBOX TESTING ENVIRONMENT ---
// Set to 1 to run isolated hardware tests instead of the main RTOS UI
#define RUN_SANDBOX_TEST 0

// If RUN_SANDBOX_TEST is 1, define which module to test:
#define TEST_MODULE_DISPLAY 1
#define TEST_MODULE_NFC     0
#define TEST_MODULE_IR      0
#define TEST_MODULE_SUBGHZ  0

#endif // CONFIG_H
