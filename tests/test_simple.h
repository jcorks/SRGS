#ifndef TESTSIMPLEINCLUDED
#define TESTSIMPLEINCLUDED

#include <stdio.h>

void test_simple() {
    printf("Starting: simple test\n\n");

    srgs_t * context = srgs_create(
        256, 256,
        srgs_test_alloc,
        srgs_test_dealloc,
        srgs_test_realloc     
    );


    uint32_t id = srgs_texture_create(context, 32, 32);
    srgs_texture_blank(context, id, 0xaa);
    srgs_test_assert(srgs_texture_verify(context, id));

    srgs_texture_resize(context, id, 64, 32);
    srgs_test_assert(srgs_texture_get_width(context, id) == 64);
    srgs_test_assert(srgs_texture_get_height(context, id) == 32);


    srgs_texture_destroy(context, id);
    srgs_destroy(context);
}



#endif