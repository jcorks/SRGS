#ifndef TESTSIMPLEINCLUDED
#define TESTSIMPLEINCLUDED

#include <stdio.h>
#include <unistd.h>
#include <math.h>
void test_simple() {
    printf("Starting: simple test\n\n");

    srgs_t * context = srgs_create(
        86, 64,
        srgs_test_alloc,
        srgs_test_dealloc,
        srgs_test_realloc     
    );



    uint32_t object = srgs_object_create(context);
    srgs_test_assert(srgs_object_verify(context, object));
    srgs_object_set_vertex_count(context, object, 4*6);
    srgs_object_set_render_mode(context, object, srgs__object_render_mode__texture);

    float position[] = {
        -.5f,  .5f, .5f,
         .5f,  .5f, .5f,
         .5f, -.5f, .5f,
        -.5f, -.5f, .5f,

        -.5f,  .5f,-.5f,
         .5f,  .5f,-.5f,
         .5f, -.5f,-.5f, 
        -.5f, -.5f,-.5f,



        -.5f,  .5f, .5f,
         .5f,  .5f, .5f,
         .5f, -.5f, .5f,
        -.5f, -.5f, .5f,

        -.5f,  .5f,-.5f,
         .5f,  .5f,-.5f,
         .5f, -.5f,-.5f, 
        -.5f, -.5f,-.5f,


        -.5f,  .5f, .5f,
         .5f,  .5f, .5f,
         .5f, -.5f, .5f,
        -.5f, -.5f, .5f,

        -.5f,  .5f,-.5f,
         .5f,  .5f,-.5f,
         .5f, -.5f,-.5f, 
        -.5f, -.5f,-.5f,

    };
    float uvs[] = {
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,


        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,

        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,


    };

    {
        srgs_matrix_t m = *srgs_utility_matrix_get_identity();
        srgs_utility_matrix_rotate(&m, 90, 0, 1, 0);

        srgs_vector3_t * iter = (srgs_vector3_t*)(position+24);
        int i;
        for(i = 0; i < 8; ++i, iter++)
            *iter = srgs_utility_matrix_transform(&m, iter);
    }

    {
        srgs_matrix_t m = *srgs_utility_matrix_get_identity();
        srgs_utility_matrix_rotate(&m, 90, 1, 0, 0);

        srgs_vector3_t * iter = (srgs_vector3_t*)(position+48);
        int i;
        for(i = 0; i < 8; ++i, iter++)
            *iter = srgs_utility_matrix_transform(&m, iter);
    }


    float color[] = {
         .5f, 0, 0, 1.f,
         .5f, 0, 0, 1.f,
         .5f, 0, 0, 1.f,
         .5f, 0, 0, 1.f,

         .2f, 0, 0, 1.f,
         .2f, 0, 0, 1.f,
         .2f, 0, 0, 1.f,
         .2f, 0, 0, 1.f,

         .6f, 0, 0, 1.f,
         .6f, 0, 0, 1.f,
         .6f, 0, 0, 1.f,
         .6f, 0, 0, 1.f,

         1.0f, 0, 0, 1.f,
         1.0f, 0, 0, 1.f,
         1.0f, 0, 0, 1.f,
         1.0f, 0, 0, 1.f,

         1.f, 0, 0, 1.f,
         .5f, 0, 0, 1.f,
         .2f, 0, 0, 1.f,
         .0f, 0, 0, 1.f,

         .6f, 0, 0, 1.f,
         .6f, 0, 0, 1.f,
         .6f, 0, 0, 1.f,
         .6f, 0, 0, 1.f,

    };


    
 


    srgs_object_define_vertices(
        context,
        object,
        srgs__object_vertex_channel__position,
        position
    );

    srgs_object_define_vertices(
        context,
        object,
        srgs__object_vertex_channel__uvs,
        uvs
    );


    srgs_object_define_vertices(
        context,
        object,
        srgs__object_vertex_channel__color,
        color
    );



    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,





        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,




        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,



        24, 25, 26,
        26, 27, 24,


        28, 29, 30,
        30, 31, 28,

        32, 33, 34,
        34, 35, 32,
        
    };

    srgs_object_define_indices(
        context,
        object,
        36,
        indices
    );



    uint32_t matrixID = srgs_matrix_create(context);
    srgs_object_set_transform(context, object, matrixID);
    srgs_matrix_t matrixData = *srgs_utility_matrix_get_identity();



    
    uint32_t perspectiveID = srgs_matrix_create(context);
    srgs_matrix_t persp = *srgs_utility_matrix_get_identity();
    srgs_matrix_t camera = *srgs_utility_matrix_get_identity();
    srgs_utility_matrix_translate(&camera, .1, .1, -1.5);
    srgs_utility_matrix_projection_perspective(&persp, 45, .6, 0.001, 20.0);
    srgs_matrix_t result;
    srgs_utility_matrix_multiply(&result, &persp,  &camera);


    srgs_matrix_set(context, perspectiveID, &result);
    



    uint32_t list = srgs_renderlist_create(context);
    srgs_renderlist_set_objects(context, list, 1, &object);
    srgs_renderlist_set_transform(context, list, perspectiveID);

    int iframe = 0;
    while(1) {

        srgs_utility_matrix_rotate(&matrixData, sin(iframe/30.0)*2+1.2, 1, 0, 0);
        srgs_utility_matrix_rotate(&matrixData, sin(iframe/30.0)*1+1.2, 0, 1, 0);
        srgs_utility_matrix_rotate(&matrixData, sin(iframe/30.0)*.3+1.49, 0, 0, 1);
        
        { // temp
            iframe++;
            srgs_matrix_t persp = *srgs_utility_matrix_get_identity();
            srgs_matrix_t camera = *srgs_utility_matrix_get_identity();
            //srgs_utility_matrix_translate(&camera, .1, .1, sin(iframe/60.f));
            srgs_utility_matrix_projection_perspective(&persp, 90, .46, 0.0001, 10);
            srgs_matrix_t result;
            srgs_utility_matrix_multiply(&result,  &persp, &camera);
                srgs_matrix_set(context, perspectiveID, &result);
        }
        


        srgs_matrix_set(context, matrixID, &matrixData);

        srgs_clear_color(context);
        srgs_clear_depth(context);
        srgs_render(context, 1, &list);

        printf("\033[H\033[J");
        srgs_test_print_framebuffer(context);
        printf("z@%f\n", sin(iframe/60.0));
        fflush(stdout);
        usleep(1000*16.6);
    }


    srgs_texture_destroy(context, object);
    srgs_destroy(context);
}



#endif
