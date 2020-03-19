#ifndef H__SRGS__TEST_DRIVER__DEFINED
#define G__SRGS__TEST_DRIVER__DEFINED

#include <stdlib.h>

typedef struct srgs_test_t srgs_test_t;
typedef struct srgs_t srgs_t;

void srgs_test_add(void (*testCase)());



void * srgs_test_alloc(size_t);

void srgs_test_dealloc(void *);

void * srgs_test_realloc(void *, size_t);



void srgs_test_assert_(int mustBeTrue, const char * file, int line);
#define srgs_test_assert(__S__) srgs_test_assert_(__S__, __FILE__, __LINE__)

void srgs_test_start();


void srgs_test_print_framebuffer(srgs_t *);

#endif
