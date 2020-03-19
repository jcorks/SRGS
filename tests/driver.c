#include "driver.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "../srgs.h"

static uint64_t memoryCount = 0;

typedef struct  {
    void * buffer;
    size_t size;
} MemoryBlock;



static uint32_t blocksAllocSize = 0;
static uint32_t blocksSize = 0;
static MemoryBlock ** blocks = NULL;
static int64_t  blockTotalMemory;
static uint32_t blockCount = 0;
static uint32_t blockCountAligned = 0;
static uint64_t blockPeakMemory = 0;

static void srgs_test_alloc_reset() {
    uint32_t i;
    for(i = 0; i < blocksSize; ++i) {
        free(blocks[i]->buffer);
        free(blocks[i]);
    }
    blocksSize = 0;
    blockCountAligned = 0;
    blockCount = 0;
    blockTotalMemory = 0;
    blockPeakMemory = 0;

}

void * srgs_test_alloc(size_t t) {
    MemoryBlock * b = calloc(1, sizeof(MemoryBlock));
    b->size = t;
    b->buffer = malloc(t);

    blockCountAligned += (t%4==0);
    blockCount++;
    blockTotalMemory += t;


    if (blocksSize >= blocksAllocSize) {
        blocksAllocSize = (blocksAllocSize + 1)*1.4;
        blocks = realloc(blocks, blocksAllocSize*sizeof(MemoryBlock*));
    }

    if (blockTotalMemory > blockPeakMemory)
        blockPeakMemory = blockTotalMemory;


    blocks[blocksSize++] = b;
    return b->buffer;
}

void srgs_test_dealloc(void * buffer) {
    if (!buffer) return;

    uint32_t i;
    for(i = 0; i < blocksSize; ++i) {
        if (blocks[i]->buffer == buffer) {
            blockTotalMemory -= blocks[i]->size;
            free(blocks[i]->buffer);
            blocks[i]->buffer = NULL;
            return;
        }
    }
    assert(!"Invalid free");
}


void * srgs_test_realloc(void * buffer, size_t s) {
    if (!buffer) return srgs_test_alloc(s);

    uint32_t i;
    for(i = 0; i < blocksSize; ++i) {
        if (blocks[i]->buffer == buffer) {
            blockTotalMemory -= blocks[i]->size;
            blocks[i]->size = s;
            blockTotalMemory += s;
            blocks[i]->buffer = realloc(blocks[i]->buffer, s);
            blockCountAligned += (s%4==0);
            blockCount++;
            return blocks[i]->buffer;
        }
    }
    assert(!"Invalid realloc");
    return NULL;
}


static int srgs_test_alloc_report() {
    printf(
        "Memory unfreed:     %d bytes (%dKB).\n"
        "Peak memory usage:  %d bytes (%dKB).\n"
        "Allocation count:   %d\n"
        "Aligned percentage: %.2f\n",

        blockTotalMemory, blockTotalMemory / 1024,
        blockPeakMemory, blockPeakMemory / 1024,
        blockCount,
        (blockCountAligned / (float) blockCount) * 100.0
    );

    return blockTotalMemory;
}















typedef void(*RUNFN)();
static RUNFN testCases[1024];
static int testCount = 0;


void srgs_test_add(void (*testCase)()) {
    testCases[testCount++] = testCase;
}


void srgs_test_start() {
    uint32_t i;
    for(i = 0; i < testCount; ++i) {
        srgs_test_alloc_reset();
        testCases[i]();
        if (srgs_test_alloc_report()) {
            printf("Stopping due to memory leak.");
            exit(10);
        }  
    }

}

void srgs_test_assert_(int expression, const char * file, int line) {
    if (!expression) {
        printf("Test FAILED @ %s:%d\n", file, line);
        exit(1);
    }
}





void srgs_test_print_framebuffer(srgs_t * s) {
    const uint8_t * data = srgs_texture_get_data(s, srgs_get_framebuffer_texture(s));

    uint32_t w = srgs_texture_get_width(s, srgs_get_framebuffer_texture(s));
    uint32_t h = srgs_texture_get_height(s, srgs_get_framebuffer_texture(s));


    uint32_t x, y;
    for(y = 0; y < h; ++y) {
        for(x = 0; x < w; ++x) {
            
            printf("%c", *data ? '*' : '.');
            data+=4;
        }
        printf("\n");
    }
    printf("\n");



}
