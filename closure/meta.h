#pragma once
#ifndef __META_H__
#define __META_H__

#include <cloak.h>

/* count arguments */
#define VA_ARGC_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N
#define VA_ARGC(...) VA_ARGC_(__VA_ARGS__,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)

/* concatenate args */
#define VA_ARG_CAT(A, B) VA_ARG_CAT_(A, B)
#define VA_ARG_CAT_(A, B) A##B

/* argument indexing */
#define VA_ARG(N, ...) VA_ARG_CAT(VA_ARG_, N)(__VA_ARGS__)
#define VA_ARG_0(_0, ...) _0
#define VA_ARG_1(_0, _1, ...) _1
#define VA_ARG_2(_0, _1, _2, ...) _2
#define VA_ARG_3(_0, _1, _2, _3, ...) _3
#define VA_ARG_4(_0, _1, _2, _3, _4, ...) _4
#define VA_ARG_5(_0, _1, _2, _3, _4, _5, ...) _5
#define VA_ARG_6(_0, _1, _2, _3, _4, _5, _6, ...) _6
#define VA_ARG_7(_0, _1, _2, _3, _4, _5, _6, _7, ...) _7
#define VA_ARG_8(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) _8
#define VA_ARG_9(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _9
#define VA_ARG_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _10
#define VA_ARG_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) _11
#define VA_ARG_12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) _12
#define VA_ARG_13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) _13
#define VA_ARG_14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) _14
#define VA_ARG_15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15

/* get the last entry in the list */
#define VA_ARG_LAST(...) VA_ARG(VA_ARGC(__VA_ARGS__), _, __VA_ARGS__ ,,,,,,,,,,,)

/* leave only the first N entries */
#define VA_ARG_TAKE(N, ...) VA_ARG_CAT(VA_ARG_TAKE_, N)(__VA_ARGS__)
#define VA_ARG_TAKE_0(...)
#define VA_ARG_TAKE_1(_0, ...) _0
#define VA_ARG_TAKE_2(_0, _1, ...) _0, _1
#define VA_ARG_TAKE_3(_0, _1, _2, ...) _0, _1, _2, _3,
#define VA_ARG_TAKE_4(_0, _1, _2, _3, ...) _0, _1, _2, _3, _4
#define VA_ARG_TAKE_5(_0, _1, _2, _3, _4, ...) _0, _1, _2, _3, _4, _5
#define VA_ARG_TAKE_6(_0, _1, _2, _3, _4, _5, ...) _0, _1, _2, _3, _4, _5, _6
#define VA_ARG_TAKE_7(_0, _1, _2, _3, _4, _5, _6, ...) _0, _1, _2, _3, _4, _5, _6, _7
#define VA_ARG_TAKE_8(_0, _1, _2, _3, _4, _5, _6, _7, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8
#define VA_ARG_TAKE_9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9
#define VA_ARG_TAKE_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10
#define VA_ARG_TAKE_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11
#define VA_ARG_TAKE_12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12
#define VA_ARG_TAKE_13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13
#define VA_ARG_TAKE_14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14
#define VA_ARG_TAKE_15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15

/* skip the first N entries */
#define VA_ARG_SKIP(N, ...) VA_ARG_CAT(VA_ARG_SKIP_, N)(__VA_ARGS__)
#define VA_ARG_SKIP_0(...) __VA_ARGS__
#define VA_ARG_SKIP_1(_0, ...) __VA_ARGS__
#define VA_ARG_SKIP_2(_0, _1, ...) __VA_ARGS__
#define VA_ARG_SKIP_3(_0, _1, _2, ...) __VA_ARGS__
#define VA_ARG_SKIP_4(_0, _1, _2, _3, ...) __VA_ARGS__
#define VA_ARG_SKIP_5(_0, _1, _2, _3, _4, ...) __VA_ARGS__
#define VA_ARG_SKIP_6(_0, _1, _2, _3, _4, _5, ...) __VA_ARGS__
#define VA_ARG_SKIP_7(_0, _1, _2, _3, _4, _5, _6, ...) __VA_ARGS__
#define VA_ARG_SKIP_8(_0, _1, _2, _3, _4, _5, _6, _7, ...) __VA_ARGS__
#define VA_ARG_SKIP_9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) __VA_ARGS__
#define VA_ARG_SKIP_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) __VA_ARGS__
#define VA_ARG_SKIP_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) __VA_ARGS__
#define VA_ARG_SKIP_12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) __VA_ARGS__
#define VA_ARG_SKIP_13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) __VA_ARGS__
#define VA_ARG_SKIP_14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) __VA_ARGS__
#define VA_ARG_SKIP_15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) __VA_ARGS__


/*
 * Format variadic arguments to conform to C99.
 *
 * For macros that may take 0 variadic arguments, you must eliminate the last formal parameter
 * and process it as the first variadic parameter. So:
 *    #define FOO(x, ...) some_function(x, __VA_ARGS__)
 * must become:
 *    #define FOO(...) some_function(VA_ARG_FMT(VA_ARG(0,__VA_ARGS__), __VA_ARGS__))
 * This way the variadic arguments always have values, thus conforming to C99.
 */
#define VA_ARG_FMT(...) VA_ARG_CAT(VA_ARG_FMT_,VA_ARGC(__VA_ARGS__))(__VA_ARGS__)
#define VA_ARG_FMT_2(_0, ...) _0
#define VA_ARG_FMT_3(_0, ...) _0, VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_4(_0, ...) _0, VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_5(_0, ...) _0, VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_6(_0, ...) _0, VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_7(_0, ...) _0, VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_8(_0, ...) _0, VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_9(_0, ...) _0, VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_10(_0, ...) _0,VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_11(_0, ...) _0,VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_12(_0, ...) _0,VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_13(_0, ...) _0,VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_14(_0, ...) _0,VA_ARG_SKIP_1(__VA_ARGS__)
#define VA_ARG_FMT_15(_0, ...) _0,VA_ARG_SKIP_1(__VA_ARGS__)

#define VA_EMPTY

/*
 * A usable syntax for function pointers up to 16 arguments. The return
 * value shows up last like in lambda function types:
 *   int(*)(char*, void*)
 * looks like:
 *   fn(char*, void*, int)
 *
 * NOTE: requires support for anonymous structs (typically C11).
 */
#define fn(...) struct {\
    VA_ARG_LAST(__VA_ARGS__) (*call)(VA_ARG_TAKE(DEC(VA_ARGC(__VA_ARGS__)),__VA_ARGS__)); \
}
#define fn_new(f) { .call = f }

// clever bit of code for static_assert by Paul Eggert:
// https://sourceware.org/ml/libc-alpha/2015-02/msg00102.html
#if (!defined _Static_assert \
     && (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) < 201112 \
     && (defined __STRICT_ANSI__))
#define _Static_assert(expr, diagnostic) \
    extern int (*__Static_assert_function (void)) \
      [!!sizeof (struct { int __error_if_negative: (expr) ? 2 : -1; })]
#endif

#ifndef static_assert
#define static_assert(e,d) _Static_assert(e,d)
#endif

#if !defined(typeof) && defined(__typeof__)
#define typeof(e) __typeof__(e)
#elif !defined(typeof) && defined(decltype)
#define typeof(e) decltype(e)
#endif

#endif /*__META_H__*/
