#define MODULE_simon$io
#include <simondev.h>


int main(int argc, char** argv) {
    if(!(1 == 1)) {
        println("Test failed: ""1 is 1");
        return 1;
    }
    if(!(2 == 2)) {
        println("Test failed: ""2 is 2");
        return 1;
    }
}
