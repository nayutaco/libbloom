//https://github.com/bitcoin/bitcoin/blob/master/src/test/bloom_tests.cpp
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MURMURHASH_VERSION  3
#include "bloom.h"

static const uint8_t CASE1[] = {
    0x99, 0x10, 0x8a, 0xd8, 0xed, 0x9b, 0xb6, 0x27,
    0x4d, 0x39, 0x80, 0xba, 0xb5, 0xa8, 0x5c, 0x04,
    0x8f, 0x09, 0x50, 0xc8,
};

static const uint8_t CASE1F[] = {
    0x19, 0x10, 0x8a, 0xd8, 0xed, 0x9b, 0xb6, 0x27,
    0x4d, 0x39, 0x80, 0xba, 0xb5, 0xa8, 0x5c, 0x04,
    0x8f, 0x09, 0x50, 0xc8,
};

static const uint8_t CASE2[] = {
    0xb5, 0xa2, 0xc7, 0x86, 0xd9, 0xef, 0x46, 0x58,
    0x28, 0x7c, 0xed, 0x59, 0x14, 0xb3, 0x7a, 0x1b,
    0x4a, 0xa3, 0x2e, 0xee,
};

static const uint8_t CASE3[] = {
    0xb9, 0x30, 0x06, 0x70, 0xb4, 0xc5, 0x36, 0x6e,
    0x95, 0xb2, 0x69, 0x9e, 0x8b, 0x18, 0xbc, 0x75,
    0xe5, 0xf7, 0x29, 0xc5,
};


static int bloom_create_insert_serialize(void)
{
    int ret;
    struct bloom blm;

    ret = bloom_init(&blm, 3, 0.01, 0);
    assert(ret == 0);
    //bloom_print(&blm);

    ret = bloom_add(&blm, CASE1, sizeof(CASE1));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE1, sizeof(CASE1));
    assert(ret == 1);
    ret = bloom_check(&blm, CASE1F, sizeof(CASE1F));
    assert(ret == 0);


    ret = bloom_add(&blm, CASE2, sizeof(CASE2));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE2, sizeof(CASE2));
    assert(ret == 1);


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


static int bloom_create_insert_serialize_with_tweak(void)
{
    int ret;
    struct bloom blm;

    ret = bloom_init(&blm, 3, 0.01, 2147483649UL);
    assert(ret == 0);
    //bloom_print(&blm);

    ret = bloom_add(&blm, CASE1, sizeof(CASE1));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE1, sizeof(CASE1));
    assert(ret == 1);
    ret = bloom_check(&blm, CASE1F, sizeof(CASE1F));
    assert(ret == 0);


    ret = bloom_add(&blm, CASE2, sizeof(CASE2));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE2, sizeof(CASE2));
    assert(ret == 1);


    ret = bloom_add(&blm, CASE3, sizeof(CASE3));
    assert(ret == 0);
    ret = bloom_check(&blm, CASE3, sizeof(CASE3));
    assert(ret == 1);

    const uint8_t VCT[] = {
        0xce, 0x42, 0x99
    };
    assert(0 == (memcmp(VCT, blm.bf, blm.bytes)));

    printf(" === OK!: %s ===\n", __func__);

    return 0;
}


static int bloom_create_insert_key(void)
{
    int ret;
    struct bloom blm;

    const uint8_t PUBKEY[] = {
        0x04,
        0x5b, 0x81, 0xf0, 0x01, 0x7e, 0x20, 0x91, 0xe2,
        0xed, 0xcd, 0x5e, 0xec, 0xf1, 0x0d, 0x5b, 0xdd,
        0x12, 0x0a, 0x55, 0x14, 0xcb, 0x3e, 0xe6, 0x5b,
        0x84, 0x47, 0xec, 0x18, 0xbf, 0xc4, 0x57, 0x5c,
        0x6d, 0x5b, 0xf4, 0x15, 0xe5, 0x4e, 0x03, 0xb1,
        0x06, 0x79, 0x34, 0xa0, 0xf0, 0xba, 0x76, 0xb0,
        0x1c, 0x6b, 0x9a, 0xb2, 0x27, 0x14, 0x2e, 0xe1,
        0xd5, 0x43, 0x76, 0x4b, 0x69, 0xd9, 0x01, 0xe0,
    };
    const uint8_t PUBKEYHASH[] = {
        0x47, 0x7a, 0xbb, 0xac, 0xd4, 0x11, 0x3f, 0x2e,
        0x6b, 0x10, 0x05, 0x26, 0x22, 0x2e, 0xed, 0xd9,
        0x53, 0xc2, 0x6a, 0x64,
    };

    ret = bloom_init(&blm, 2, 0.001, 0);
    assert(ret == 0);
    //bloom_print(&blm);

    ret = bloom_add(&blm, PUBKEY, sizeof(PUBKEY));
    assert(ret == 0);
    ret = bloom_add(&blm, PUBKEYHASH, sizeof(PUBKEYHASH));
    assert(ret == 0);

    const uint8_t VCT[] = {
        0x8f, 0xc1, 0x6b
    };
    assert(0 == (memcmp(VCT, blm.bf, blm.bytes)));

    printf(" === OK!: %s ===\n", __func__);

    return 0;
}


int main(void)
{
    int ret;

    ret = bloom_create_insert_serialize();
    assert(ret == 0);
    ret = bloom_create_insert_serialize_with_tweak();
    assert(ret == 0);
    ret = bloom_create_insert_key();
    assert(ret == 0);

    printf("===== ALL OK! =====\n");
    return 0;
}
