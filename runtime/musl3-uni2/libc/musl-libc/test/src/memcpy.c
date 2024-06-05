#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.1415926535897932
#endif

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// To check for corruption, we fill the start and end of alloc-ed chunk with some data.
// This define how many byte at maximum we fill on each end. This is so big malloc don't
// take tens of seconds to run during the test. If there is enough space to put two
// capabilities, then fill will add them regardless if it is more than this maximum
#define FILL_THICKNESS 128

#define test_success 0
#define copied_value_not_equal 1
#define null_capability 2
#define capability_tag_cleared 3
#define incorrect_permission 4
#define incorrect_bound 5
#define bad_test_number 10

/*
This factorise a lot of test. It just create two arrays, initialize them, do the memcpy, test that the shallow
copy is fine and can test more things on each element if needed (like for nested capabilities). This would
have been cleaner with templates or functional programming
*/
#define TEST_ARRAY(ELEM_TYPE,ARRAY_SIZE,ARRAY_INI_FUNC,ARRAY_ZERO_INIT,ELEM_EQUAL_FUNC,EXTRA_ELEM_TEST_FUNC)\
    {\
    ELEM_TYPE array_src[ARRAY_SIZE];\
    ELEM_TYPE array_dst[ARRAY_SIZE];\
\
    for(int i = 0; i < ARRAY_SIZE; i++) {\
        array_src[i] = ARRAY_INI_FUNC(i);\
        array_dst[i] = ARRAY_ZERO_INIT();\
    }\
\
    ELEM_TYPE* ptr_src = array_src;\
    ELEM_TYPE* ptr_dst = array_dst;\
\
    test_ptr_size((void**) &ptr_src,sizeof(ELEM_TYPE)*(ARRAY_SIZE));\
    memcpy(ptr_dst,ptr_src,sizeof(ELEM_TYPE)*(ARRAY_SIZE));\
    for(int i = 0; i < ARRAY_SIZE; i++) {\
        if(!(ELEM_EQUAL_FUNC(array_dst[i],array_src[i]))) exit(copied_value_not_equal);\
        EXTRA_ELEM_TEST_FUNC(array_dst[i]);\
    }\
    test_ptr_size((void**) &ptr_dst,sizeof(ELEM_TYPE)*(ARRAY_SIZE));\
    }



static void test_ptr_size(void** ptr,long long size)
{
    if(*ptr == NULL){
        exit(null_capability);
    }
    if(!__builtin_cheri_tag_get(*ptr)){
        exit(capability_tag_cleared);
    }
    unsigned long perm = __builtin_cheri_perms_get(*ptr);
    unsigned long perm_primitive_type = __CHERI_CAP_PERMISSION_PERMIT_LOAD__ | __CHERI_CAP_PERMISSION_PERMIT_STORE__;
    unsigned long perm_capability_type = __CHERI_CAP_PERMISSION_PERMIT_LOAD_CAPABILITY__ | __CHERI_CAP_PERMISSION_PERMIT_STORE_CAPABILITY__;
    unsigned long minimal_perm = perm_primitive_type | perm_capability_type;

    if((perm & minimal_perm) != minimal_perm){
        if(!(perm & __CHERI_CAP_PERMISSION_PERMIT_LOAD__)) {
            printf("ptr is missing load\n");
        }
        if(!(perm & __CHERI_CAP_PERMISSION_PERMIT_STORE__)) {
            printf("ptr is missing store\n");
        }
        if(!(perm & __CHERI_CAP_PERMISSION_PERMIT_LOAD_CAPABILITY__)) {
            printf("ptr is missing capability load\n");
        }
        if(!(perm & __CHERI_CAP_PERMISSION_PERMIT_STORE_CAPABILITY__)) {
            printf("ptr is missing capability store\n");
        }
        exit(incorrect_permission);
    }

    if(size > -1 && __builtin_cheri_length_get(*ptr) != size){
        exit(incorrect_bound);
    }
}

static int init_int(int i) {return 1+i*3;}
static int int_zero_init() {return 0;}
static int equal_int(int a,int b) {return a==b;}
static void null_int_func(int a) {}

static double init_double(int i) {return (1+3*i)*M_PI;}
static double double_zero_init() {return 0;}
static int equal_double(double a,double b) {return a==b;}
static void null_double_func(double a) {}

struct simple_struct{ // between 17B and 24B
    long long integer;
    char bitfield5:5;
    char bitfield3:3;
    double floating_point;

};

static struct simple_struct init_simple_struct(int i) {return (struct simple_struct){ .integer = 1+3*i, .bitfield5 = (5+i)%32, .bitfield3 = i%8, .floating_point = (1+3*i)*M_PI };}
static struct simple_struct simple_struct_zero_init() {return (struct simple_struct){ .integer = 0, .bitfield5 = 0, .bitfield3 = 0, .floating_point = 0 };}
static int equal_simple_struct(struct simple_struct a,struct simple_struct b) {return a.integer==b.integer && a.bitfield5==b.bitfield5 && a.bitfield3==b.bitfield3 && a.floating_point==b.floating_point;}
static void null_simple_struct_func(struct simple_struct a) {}

static int bad_target;
static int target;
struct complex_struct{ // between 33B and 40B
    long long integer;
    char bitfield5:5;
    int* capability;
    double floating_point;
};

static struct complex_struct init_complex_struct(int i) {return (struct complex_struct){ .integer = 1+3*i, .bitfield5 = (5+i)%32, .capability = &target, .floating_point = (1+3*i)*M_PI };}
static struct complex_struct complex_struct_zero_init() {return (struct complex_struct){ .integer = 0, .bitfield5 = 0, .capability = &bad_target, .floating_point = 0 };}
static int equal_complex_struct(struct complex_struct a,struct complex_struct b) {return a.integer==b.integer && a.bitfield5==b.bitfield5 && a.capability==b.capability && a.floating_point==b.floating_point;}
static void test_inner_cap(struct complex_struct a) {test_ptr_size((void**)&(a.capability),sizeof(int));}

static void test_small_copy() //less than 32B
{
    int int_var_src = 255;
    int int_var_dst = 0;
    memcpy(&int_var_dst,&int_var_src,MIN(sizeof(int_var_dst),sizeof(int_var_src)));
    if(int_var_dst != int_var_src) exit(copied_value_not_equal);

    int_var_dst = 0;
    int* int_ptr_src = &int_var_src;
    int* int_ptr_dst = &int_var_dst;
    test_ptr_size((void**) &int_ptr_src,sizeof(int_var_src));
    memcpy(&int_ptr_dst,&int_ptr_src,MIN(sizeof(int_ptr_dst),sizeof(int_ptr_src)));
    if(int_ptr_dst != int_ptr_src) exit(copied_value_not_equal);
    test_ptr_size((void**) &int_ptr_dst,sizeof(int_var_dst));

    return;
}

static void test_medium_array() { // between 32 and 128 B
    //test_primitive_array(10,5); // works with both 4B and 8B int, and 8B double
    TEST_ARRAY(int, 10, init_int, int_zero_init, equal_int, null_int_func)
    TEST_ARRAY(double, 5, init_double, double_zero_init, equal_double, null_double_func)
    TEST_ARRAY(struct simple_struct, 4, init_simple_struct, simple_struct_zero_init, equal_simple_struct, null_simple_struct_func)
}

static void test_big_array() { // above 128B
    //test_primitive_array(40,20); // works with both 4B and 8B int, and 8B double
    TEST_ARRAY(int, 40, init_int, int_zero_init, equal_int, null_int_func)
    TEST_ARRAY(double, 20, init_double, double_zero_init, equal_double, null_double_func)
    TEST_ARRAY(struct simple_struct, 8, init_simple_struct, simple_struct_zero_init, equal_simple_struct, null_simple_struct_func)
}

static void test_nested_capabilities() {
    //medium size
    TEST_ARRAY(struct complex_struct, 2, init_complex_struct, complex_struct_zero_init, equal_complex_struct, test_inner_cap)
    //large size
    TEST_ARRAY(struct complex_struct, 4, init_complex_struct, complex_struct_zero_init, equal_complex_struct, test_inner_cap)
}

int main(int argc, char **argv)
{
    switch (argv[1][0]) {
    case '0':
        test_small_copy();
        break;
    case '1':
        test_medium_array();
        break;
    case '2':
        test_big_array();
        break;
    case '3':
        test_nested_capabilities();
        break;
    default:
        return bad_test_number;
    }
    return test_success;
}
