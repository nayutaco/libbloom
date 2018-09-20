#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MURMURHASH_VERSION  3
#include "bloom.h"


//bloom_create_insert_serialize
static int test_case0(void)
{
    int ret;
    struct bloom blm;

    ret = bloom_init(&blm, 3, 0.01, 0);
    assert(ret == 0);
    //bloom_print(&blm);

    const uint8_t CASE1[] = {
        0x99, 0x10, 0x8a, 0xd8, 0xed, 0x9b, 0xb6, 0x27,
        0x4d, 0x39, 0x80, 0xba, 0xb5, 0xa8, 0x5c, 0x04,
        0x8f, 0x09, 0x50, 0xc8,
    };
    ret = bloom_add(&blm, CASE1, sizeof(CASE1));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE1, sizeof(CASE1));
    assert(ret == 1);

    const uint8_t CASE1F[] = {
        0x19, 0x10, 0x8a, 0xd8, 0xed, 0x9b, 0xb6, 0x27,
        0x4d, 0x39, 0x80, 0xba, 0xb5, 0xa8, 0x5c, 0x04,
        0x8f, 0x09, 0x50, 0xc8,
    };
    ret = bloom_check(&blm, CASE1F, sizeof(CASE1F));
    assert(ret == 0);


    const uint8_t CASE2[] = {
        0xb5, 0xa2, 0xc7, 0x86, 0xd9, 0xef, 0x46, 0x58,
        0x28, 0x7c, 0xed, 0x59, 0x14, 0xb3, 0x7a, 0x1b,
        0x4a, 0xa3, 0x2e, 0xee,
    };
    ret = bloom_add(&blm, CASE2, sizeof(CASE2));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE2, sizeof(CASE2));
    assert(ret == 1);


    const uint8_t CASE3[] = {
        0xb9, 0x30, 0x06, 0x70, 0xb4, 0xc5, 0x36, 0x6e,
        0x95, 0xb2, 0x69, 0x9e, 0x8b, 0x18, 0xbc, 0x75,
        0xe5, 0xf7, 0x29, 0xc5,
    };
    ret = bloom_add(&blm, CASE3, sizeof(CASE3));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE3, sizeof(CASE3));
    assert(ret == 1);

    const uint8_t VCT[] = {
        0x61, 0x4e, 0x9b,
    };
    assert(0 == (memcmp(VCT, blm.bf, blm.bytes)));

    ret = bloom_check(&blm, CASE1, sizeof(CASE1));
    assert(ret == 1);

    printf(" === OK!: %s ===\n", __func__);

    return 0;

}

int main(void)
{
    int ret = test_case0();

    printf("===== ALL OK! =====\n");
    return 0;
}
