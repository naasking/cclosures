#ifndef VAL_H
#define VAL_H

#include <stdint.h>

#if defined(_WIN64) || defined(WIN64) || defined(__sparc64__) || defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(__ppc64__) || defined(__PPC64__) || defined(__ppc64) || defined(__LP__) || defined(_LP64) || defined(_AMD64_) || defined(_____LP64_____) || defined(__LP64__)
#define WD64BIT
#endif

/**
 * = Closures for C =
 *
 * This implements eval/apply style closures for C based around a universal value type 'val',
 * which is currently defined to be machine word-sized.
 */

 /* alloca.h is not provided by MSVC */
 //#ifdef _MSC_VER
 //#include <malloc.h>
 //#define alloca _alloca
 //#else
 //#include <alloca.h>
 //#endif

 /* native machine word type */
typedef uintptr_t word;

/*
* The universal representation for all values.
*/
typedef union val {
	/* platform-specific types */
	void *p;
	signed   char sc;
	unsigned char uc;
	signed   short ss;
	unsigned short us;
	signed   int si;
	unsigned int ui;
	//signed   long long sl;	//FIXME: may be 64-bit
	//unsigned long long ul;
	word w;

	/* fixed width types */
	float f;
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	int8_t i8;
	int16_t i16;
	int32_t i32;

	/* 64-bit types are either inlined, or pointed to depending on word size */
#ifdef WD64BIT
	double d;
	uint64_t u64;
	int64_t i64;
#else
	double *d;
	uint64_t *u64;
	int64_t *i64;
#endif // WD64BIT

	/* pointers/arrays of the primitive types */
	union val *a;
	float *a_f;
	double *a_d;
	void *a_p;
	signed char *a_sc;
	unsigned char *a_uc;
	signed short *a_ss;
	unsigned short *a_us;
	signed int *a_si;
	unsigned int *a_ui;
	signed long *a_sl;
	unsigned long *a_ul;
	uint8_t *a_u8;
	uint16_t *a_u16;
	uint32_t *a_u32;
	uint64_t *a_u64;
	int8_t *a_i8;
	int16_t *a_i16;
	int32_t *a_i32;
	int64_t *a_i64;
	ptrdiff_t pdiff;
	word *a_w;
	struct fn *fn;
} val;


#endif
