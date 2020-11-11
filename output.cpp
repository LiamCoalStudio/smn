#define MODULE_simon
#define MODULE_simon$io
#include <simondev.h>

declare(void, test);

int main(int argc, char** argv) {
    println(argv[0]);
    int cat = 7;
    cat = 8;
    static short* jimmy = (short*)malloc(sizeof(short));
    *jimmy = cat;
    test();
    return 0;
}

void test() {
    println("This is coming from the test function!");
}
