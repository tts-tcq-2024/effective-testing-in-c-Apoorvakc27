#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

int alertFailureCount = 0;
int printcount = 0;
char testbuffer[1024] = {0};
float convertedvalue = 0;

void print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(testbuffer, sizeof(testbuffer), format, args); // safer vsprintf
    va_end(args);
    printcount++;
}

int check_celcius_range(float celcius)
{
    convertedvalue = celcius;
    return 500; // Simulate a network failure
}

int networkAlertStub(float celcius) {
    print("ALERT: Temperature is %.1f celcius.\n", celcius);
    return check_celcius_range(celcius);
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        alertFailureCount += 1; // Increment the failure count
    }
}

void printtest(void)
{
    char testarr[3][50] = {
        "ALERT: Temperature is 204.7 celcius.",
        "ALERT: Temperature is 150.9 celcius.",
        "ALERT: Temperature is -12.2 celcius."
    };

    // Test alert output
    alertInCelcius(400.5); 
    assert(strcmp(testbuffer, testarr[0]) == 0); // Check  alert output

    alertInCelcius(303.6); 
    assert(strcmp(testbuffer, testarr[1]) == 0); 

    alertInCelcius(10); 
    assert(strcmp(testbuffer, testarr[2]) == 0); 
}

void alerttest(void)
{
    assert(alertFailureCount == 3); // Ensure all alerts failed
}

void conversiontest(void)
{
    alertInCelcius(400.5);
    assert(!(convertedvalue == 204.722229));

    alertInCelcius(303.6);
    assert(!(convertedvalue == 150.888885));
}

int main() {
    printtest();
    conversiontest();
    alerttest();
    printf("All tests passed for alerter.c\n");
    return 0;
}
