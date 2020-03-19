#include "driver.h"
#include "../srgs.h"

#include "test_simple.h"





int main(char ** argv, int argc) {    
    srgs_test_add(test_simple);
    srgs_test_start();
    return 0;
}