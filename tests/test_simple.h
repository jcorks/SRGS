#ifndef TESTSIMPLEINCLUDED
#define TESTSIMPLEINCLUDED

#include <stdio.h>

void test_simple() {
    printf("Starting: simple test\n\n");

    srgs_t * context = srgs_create(
        64, 64,
        srgs_test_alloc,
        srgs_test_dealloc,
        srgs_test_realloc     
    );


    uint32_t id = srgs_texture_create(context, 20, 20);
    srgs_texture_blank(context, id, 0xaa);
    srgs_test_assert(srgs_texture_verify(context, id));



    srgs_texture_resize(context, id, 64, 32);
    srgs_test_assert(srgs_texture_get_width(context, id) == 64);
    srgs_test_assert(srgs_texture_get_height(context, id) == 32);


    uint32_t object = srgs_object_create(context);
    srgs_test_assert(srgs_object_verify(context, object));
    srgs_object_set_vertex_count(context, object, 3);
    srgs_object_set_texture(context, object, id);
    srgs_object_set_render_mode(context, object, srgs__object_render_mode__texture);

    float position[9] = {
        -.3f,  .1f, 0.f,
         .1f,  .4f, 0.f,
         .2f, -.7f, 0.f 
    };

    srgs_object_define_vertices(
        context,
        object,
        srgs__object_vertex_channel__position,
        position
    );


    uint32_t indices[] = {
        0, 1, 2
    };

    srgs_object_define_indices(
        context,
        object,
        3,
        indices
    );






    uint32_t list = srgs_renderlist_create(context);
    srgs_renderlist_set_objects(context, list, 1, &object);


    srgs_clear_color(context);
    srgs_clear_depth(context);
    srgs_render(context, 1, &list);


    srgs_test_print_framebuffer(context);




    srgs_texture_destroy(context, object);
    srgs_texture_destroy(context, id);
    srgs_destroy(context);
}



#endif
