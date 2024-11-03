#include <stdio.h>
#include <assert.h>

char size(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    } else if(cms > 38 && cms < 42) {
        sizeName = 'M';
    } else if(cms > 42) {
        sizeName = 'L';
    }
    return sizeName;
}
void runTests() {
    // Test cases
    assert(size(-1) == 'S'); // Should be Small (negative case)
    assert(size(37) == 'S'); // Should be Small
    assert(size(38) == 'S'); // Should be Small (boundary)
    assert(size(39) == 'M'); // Should be Medium
    assert(size(41) == 'M'); // Should be Medium (boundary)
    assert(size(42) == 'L'); // Should be Large (boundary)
    assert(size(44) == 'L'); // Should be Large
    assert(size(100) == 'L'); // Should be Large

    printf("All is well (maybe!)\n");
}

int main() {
    runTests();
    return 0;
}
