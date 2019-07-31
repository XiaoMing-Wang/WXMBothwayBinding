//
//  WXMKVOObjectMacro.h
//  ModuleDebugging
//
//  Created by edz on 2019/7/29.
//  Copyright © 2019 wq. All rights reserved.
//

#ifndef WXMKVOObjectMacro_h
#define WXMKVOObjectMacro_h

#define wxmmetamacro_exprify(...) \
((__VA_ARGS__), true)

#define wxmmetamacro_stringify(VALUE) \
wxmmetamacro_stringify_(VALUE)

#define wxmmetamacro_concat(A, B) \
wxmmetamacro_concat_(A, B)

#define wxmmetamacro_at(N, ...) \
wxmmetamacro_concat(wxmmetamacro_at, N)(__VA_ARGS__)

#define wxmmetamacro_argcount(...) \
wxmmetamacro_at(20, __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define wxmmetamacro_foreach(MACRO, SEP, ...) \
wxmmetamacro_foreach_cxt(wxmmetamacro_foreach_iter, SEP, MACRO, __VA_ARGS__)

#define wxmmetamacro_foreach_cxt(MACRO, SEP, CONTEXT, ...) \
wxmmetamacro_concat(wxmmetamacro_foreach_cxt, wxmmetamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

#define wxmmetamacro_foreach_cxt_recursive(MACRO, SEP, CONTEXT, ...) \
wxmmetamacro_concat(wxmmetamacro_foreach_cxt_recursive, wxmmetamacro_argcount(__VA_ARGS__))(MACRO, SEP, CONTEXT, __VA_ARGS__)

#define wxmmetamacro_foreach_concat(BASE, SEP, ...) \
wxmmetamacro_foreach_cxt(wxmmetamacro_foreach_concat_iter, SEP, BASE, __VA_ARGS__)

#define wxmmetamacro_for_cxt(COUNT, MACRO, SEP, CONTEXT) \
wxmmetamacro_concat(wxmmetamacro_for_cxt, COUNT)(MACRO, SEP, CONTEXT)

#define wxmmetamacro_head(...) \
wxmmetamacro_head_(__VA_ARGS__, 0)

#define wxmmetamacro_tail(...) \
wxmmetamacro_tail_(__VA_ARGS__)

#define wxmmetamacro_take(N, ...) \
wxmmetamacro_concat(wxmmetamacro_take, N)(__VA_ARGS__)

#define wxmmetamacro_drop(N, ...) \
wxmmetamacro_concat(wxmmetamacro_drop, N)(__VA_ARGS__)

#define wxmmetamacro_dec(VAL) \
wxmmetamacro_at(VAL, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19)

#define wxmmetamacro_inc(VAL) \
wxmmetamacro_at(VAL, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21)

#define wxmmetamacro_if_eq(A, B) \
wxmmetamacro_concat(wxmmetamacro_if_eq, A)(B)

#define wxmmetamacro_if_eq_recursive(A, B) \
wxmmetamacro_concat(wxmmetamacro_if_eq_recursive, A)(B)

#define wxmmetamacro_is_even(N) \
wxmmetamacro_at(N, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1)

#define wxmmetamacro_not(B) \
wxmmetamacro_at(B, 1, 0)

#define wxmmetamacro_stringify_(VALUE) # VALUE
#define wxmmetamacro_concat_(A, B) A ## B
#define wxmmetamacro_foreach_iter(INDEX, MACRO, ARG) MACRO(INDEX, ARG)
#define wxmmetamacro_head_(FIRST, ...) FIRST
#define wxmmetamacro_tail_(FIRST, ...) __VA_ARGS__
#define wxmmetamacro_consume_(...)
#define wxmmetamacro_expand_(...) __VA_ARGS__

#define wxmmetamacro_foreach_concat_iter(INDEX, BASE, ARG) wxmmetamacro_foreach_concat_iter_(BASE, ARG)
#define wxmmetamacro_foreach_concat_iter_(BASE, ARG) BASE ## ARG

#define wxmmetamacro_at0(...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at1(_0, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at2(_0, _1, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at3(_0, _1, _2, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at4(_0, _1, _2, _3, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at5(_0, _1, _2, _3, _4, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at6(_0, _1, _2, _3, _4, _5, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at7(_0, _1, _2, _3, _4, _5, _6, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at8(_0, _1, _2, _3, _4, _5, _6, _7, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at17(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at18(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at19(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, ...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_at20(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, ...) wxmmetamacro_head(__VA_ARGS__)

// wxmmetamacro_foreach_cxt expansions
#define wxmmetamacro_foreach_cxt0(MACRO, SEP, CONTEXT)
#define wxmmetamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define wxmmetamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
wxmmetamacro_foreach_cxt1(MACRO, SEP, CONTEXT, _0) \
SEP \
MACRO(1, CONTEXT, _1)

#define wxmmetamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
wxmmetamacro_foreach_cxt2(MACRO, SEP, CONTEXT, _0, _1) \
SEP \
MACRO(2, CONTEXT, _2)

#define wxmmetamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
wxmmetamacro_foreach_cxt3(MACRO, SEP, CONTEXT, _0, _1, _2) \
SEP \
MACRO(3, CONTEXT, _3)

#define wxmmetamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
wxmmetamacro_foreach_cxt4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
SEP \
MACRO(4, CONTEXT, _4)

#define wxmmetamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
wxmmetamacro_foreach_cxt5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
SEP \
MACRO(5, CONTEXT, _5)

#define wxmmetamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
wxmmetamacro_foreach_cxt6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
SEP \
MACRO(6, CONTEXT, _6)

#define wxmmetamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
wxmmetamacro_foreach_cxt7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
SEP \
MACRO(7, CONTEXT, _7)

#define wxmmetamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
wxmmetamacro_foreach_cxt8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
SEP \
MACRO(8, CONTEXT, _8)

#define wxmmetamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
wxmmetamacro_foreach_cxt9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
SEP \
MACRO(9, CONTEXT, _9)

#define wxmmetamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
wxmmetamacro_foreach_cxt10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
SEP \
MACRO(10, CONTEXT, _10)

#define wxmmetamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
wxmmetamacro_foreach_cxt11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
SEP \
MACRO(11, CONTEXT, _11)

#define wxmmetamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
wxmmetamacro_foreach_cxt12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
SEP \
MACRO(12, CONTEXT, _12)

#define wxmmetamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
wxmmetamacro_foreach_cxt13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
SEP \
MACRO(13, CONTEXT, _13)

#define wxmmetamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
wxmmetamacro_foreach_cxt14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
SEP \
MACRO(14, CONTEXT, _14)

#define wxmmetamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
wxmmetamacro_foreach_cxt15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
SEP \
MACRO(15, CONTEXT, _15)

#define wxmmetamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
wxmmetamacro_foreach_cxt16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
SEP \
MACRO(16, CONTEXT, _16)

#define wxmmetamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
wxmmetamacro_foreach_cxt17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
SEP \
MACRO(17, CONTEXT, _17)

#define wxmmetamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
wxmmetamacro_foreach_cxt18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
SEP \
MACRO(18, CONTEXT, _18)

#define wxmmetamacro_foreach_cxt20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
wxmmetamacro_foreach_cxt19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
SEP \
MACRO(19, CONTEXT, _19)

// wxmmetamacro_foreach_cxt_recursive expansions
#define wxmmetamacro_foreach_cxt_recursive0(MACRO, SEP, CONTEXT)
#define wxmmetamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) MACRO(0, CONTEXT, _0)

#define wxmmetamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
wxmmetamacro_foreach_cxt_recursive1(MACRO, SEP, CONTEXT, _0) \
SEP \
MACRO(1, CONTEXT, _1)

#define wxmmetamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
wxmmetamacro_foreach_cxt_recursive2(MACRO, SEP, CONTEXT, _0, _1) \
SEP \
MACRO(2, CONTEXT, _2)

#define wxmmetamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
wxmmetamacro_foreach_cxt_recursive3(MACRO, SEP, CONTEXT, _0, _1, _2) \
SEP \
MACRO(3, CONTEXT, _3)

#define wxmmetamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
wxmmetamacro_foreach_cxt_recursive4(MACRO, SEP, CONTEXT, _0, _1, _2, _3) \
SEP \
MACRO(4, CONTEXT, _4)

#define wxmmetamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
wxmmetamacro_foreach_cxt_recursive5(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4) \
SEP \
MACRO(5, CONTEXT, _5)

#define wxmmetamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
wxmmetamacro_foreach_cxt_recursive6(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5) \
SEP \
MACRO(6, CONTEXT, _6)

#define wxmmetamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
wxmmetamacro_foreach_cxt_recursive7(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6) \
SEP \
MACRO(7, CONTEXT, _7)

#define wxmmetamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
wxmmetamacro_foreach_cxt_recursive8(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7) \
SEP \
MACRO(8, CONTEXT, _8)

#define wxmmetamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
wxmmetamacro_foreach_cxt_recursive9(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
SEP \
MACRO(9, CONTEXT, _9)

#define wxmmetamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
wxmmetamacro_foreach_cxt_recursive10(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
SEP \
MACRO(10, CONTEXT, _10)

#define wxmmetamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
wxmmetamacro_foreach_cxt_recursive11(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
SEP \
MACRO(11, CONTEXT, _11)

#define wxmmetamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
wxmmetamacro_foreach_cxt_recursive12(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
SEP \
MACRO(12, CONTEXT, _12)

#define wxmmetamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
wxmmetamacro_foreach_cxt_recursive13(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
SEP \
MACRO(13, CONTEXT, _13)

#define wxmmetamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
wxmmetamacro_foreach_cxt_recursive14(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
SEP \
MACRO(14, CONTEXT, _14)

#define wxmmetamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
wxmmetamacro_foreach_cxt_recursive15(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
SEP \
MACRO(15, CONTEXT, _15)

#define wxmmetamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
wxmmetamacro_foreach_cxt_recursive16(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
SEP \
MACRO(16, CONTEXT, _16)

#define wxmmetamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
wxmmetamacro_foreach_cxt_recursive17(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
SEP \
MACRO(17, CONTEXT, _17)

#define wxmmetamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
wxmmetamacro_foreach_cxt_recursive18(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
SEP \
MACRO(18, CONTEXT, _18)

#define wxmmetamacro_foreach_cxt_recursive20(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
wxmmetamacro_foreach_cxt_recursive19(MACRO, SEP, CONTEXT, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
SEP \
MACRO(19, CONTEXT, _19)

// wxmmetamacro_for_cxt expansions
#define wxmmetamacro_for_cxt0(MACRO, SEP, CONTEXT)
#define wxmmetamacro_for_cxt1(MACRO, SEP, CONTEXT) MACRO(0, CONTEXT)

#define wxmmetamacro_for_cxt2(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt1(MACRO, SEP, CONTEXT) \
SEP \
MACRO(1, CONTEXT)

#define wxmmetamacro_for_cxt3(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt2(MACRO, SEP, CONTEXT) \
SEP \
MACRO(2, CONTEXT)

#define wxmmetamacro_for_cxt4(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt3(MACRO, SEP, CONTEXT) \
SEP \
MACRO(3, CONTEXT)

#define wxmmetamacro_for_cxt5(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt4(MACRO, SEP, CONTEXT) \
SEP \
MACRO(4, CONTEXT)

#define wxmmetamacro_for_cxt6(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt5(MACRO, SEP, CONTEXT) \
SEP \
MACRO(5, CONTEXT)

#define wxmmetamacro_for_cxt7(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt6(MACRO, SEP, CONTEXT) \
SEP \
MACRO(6, CONTEXT)

#define wxmmetamacro_for_cxt8(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt7(MACRO, SEP, CONTEXT) \
SEP \
MACRO(7, CONTEXT)

#define wxmmetamacro_for_cxt9(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt8(MACRO, SEP, CONTEXT) \
SEP \
MACRO(8, CONTEXT)

#define wxmmetamacro_for_cxt10(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt9(MACRO, SEP, CONTEXT) \
SEP \
MACRO(9, CONTEXT)

#define wxmmetamacro_for_cxt11(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt10(MACRO, SEP, CONTEXT) \
SEP \
MACRO(10, CONTEXT)

#define wxmmetamacro_for_cxt12(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt11(MACRO, SEP, CONTEXT) \
SEP \
MACRO(11, CONTEXT)

#define wxmmetamacro_for_cxt13(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt12(MACRO, SEP, CONTEXT) \
SEP \
MACRO(12, CONTEXT)

#define wxmmetamacro_for_cxt14(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt13(MACRO, SEP, CONTEXT) \
SEP \
MACRO(13, CONTEXT)

#define wxmmetamacro_for_cxt15(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt14(MACRO, SEP, CONTEXT) \
SEP \
MACRO(14, CONTEXT)

#define wxmmetamacro_for_cxt16(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt15(MACRO, SEP, CONTEXT) \
SEP \
MACRO(15, CONTEXT)

#define wxmmetamacro_for_cxt17(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt16(MACRO, SEP, CONTEXT) \
SEP \
MACRO(16, CONTEXT)

#define wxmmetamacro_for_cxt18(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt17(MACRO, SEP, CONTEXT) \
SEP \
MACRO(17, CONTEXT)

#define wxmmetamacro_for_cxt19(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt18(MACRO, SEP, CONTEXT) \
SEP \
MACRO(18, CONTEXT)

#define wxmmetamacro_for_cxt20(MACRO, SEP, CONTEXT) \
wxmmetamacro_for_cxt19(MACRO, SEP, CONTEXT) \
SEP \
MACRO(19, CONTEXT)

// wxmmetamacro_if_eq expansions
#define wxmmetamacro_if_eq0(VALUE) \
wxmmetamacro_concat(wxmmetamacro_if_eq0_, VALUE)

#define wxmmetamacro_if_eq0_0(...) __VA_ARGS__ wxmmetamacro_consume_
#define wxmmetamacro_if_eq0_1(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_2(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_3(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_4(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_5(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_6(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_7(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_8(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_9(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_10(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_11(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_12(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_13(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_14(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_15(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_16(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_17(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_18(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_19(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq0_20(...) wxmmetamacro_expand_

#define wxmmetamacro_if_eq1(VALUE) wxmmetamacro_if_eq0(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq2(VALUE) wxmmetamacro_if_eq1(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq3(VALUE) wxmmetamacro_if_eq2(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq4(VALUE) wxmmetamacro_if_eq3(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq5(VALUE) wxmmetamacro_if_eq4(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq6(VALUE) wxmmetamacro_if_eq5(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq7(VALUE) wxmmetamacro_if_eq6(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq8(VALUE) wxmmetamacro_if_eq7(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq9(VALUE) wxmmetamacro_if_eq8(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq10(VALUE) wxmmetamacro_if_eq9(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq11(VALUE) wxmmetamacro_if_eq10(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq12(VALUE) wxmmetamacro_if_eq11(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq13(VALUE) wxmmetamacro_if_eq12(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq14(VALUE) wxmmetamacro_if_eq13(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq15(VALUE) wxmmetamacro_if_eq14(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq16(VALUE) wxmmetamacro_if_eq15(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq17(VALUE) wxmmetamacro_if_eq16(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq18(VALUE) wxmmetamacro_if_eq17(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq19(VALUE) wxmmetamacro_if_eq18(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq20(VALUE) wxmmetamacro_if_eq19(wxmmetamacro_dec(VALUE))

// wxmmetamacro_if_eq_recursive expansions
#define wxmmetamacro_if_eq_recursive0(VALUE) \
wxmmetamacro_concat(wxmmetamacro_if_eq_recursive0_, VALUE)

#define wxmmetamacro_if_eq_recursive0_0(...) __VA_ARGS__ wxmmetamacro_consume_
#define wxmmetamacro_if_eq_recursive0_1(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_2(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_3(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_4(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_5(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_6(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_7(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_8(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_9(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_10(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_11(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_12(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_13(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_14(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_15(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_16(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_17(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_18(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_19(...) wxmmetamacro_expand_
#define wxmmetamacro_if_eq_recursive0_20(...) wxmmetamacro_expand_

#define wxmmetamacro_if_eq_recursive1(VALUE) wxmmetamacro_if_eq_recursive0(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive2(VALUE) wxmmetamacro_if_eq_recursive1(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive3(VALUE) wxmmetamacro_if_eq_recursive2(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive4(VALUE) wxmmetamacro_if_eq_recursive3(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive5(VALUE) wxmmetamacro_if_eq_recursive4(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive6(VALUE) wxmmetamacro_if_eq_recursive5(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive7(VALUE) wxmmetamacro_if_eq_recursive6(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive8(VALUE) wxmmetamacro_if_eq_recursive7(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive9(VALUE) wxmmetamacro_if_eq_recursive8(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive10(VALUE) wxmmetamacro_if_eq_recursive9(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive11(VALUE) wxmmetamacro_if_eq_recursive10(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive12(VALUE) wxmmetamacro_if_eq_recursive11(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive13(VALUE) wxmmetamacro_if_eq_recursive12(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive14(VALUE) wxmmetamacro_if_eq_recursive13(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive15(VALUE) wxmmetamacro_if_eq_recursive14(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive16(VALUE) wxmmetamacro_if_eq_recursive15(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive17(VALUE) wxmmetamacro_if_eq_recursive16(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive18(VALUE) wxmmetamacro_if_eq_recursive17(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive19(VALUE) wxmmetamacro_if_eq_recursive18(wxmmetamacro_dec(VALUE))
#define wxmmetamacro_if_eq_recursive20(VALUE) wxmmetamacro_if_eq_recursive19(wxmmetamacro_dec(VALUE))

// wxmmetamacro_take expansions
#define wxmmetamacro_take0(...)
#define wxmmetamacro_take1(...) wxmmetamacro_head(__VA_ARGS__)
#define wxmmetamacro_take2(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take1(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take3(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take2(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take4(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take3(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take5(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take4(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take6(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take5(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take7(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take6(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take8(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take7(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take9(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take8(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take10(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take9(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take11(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take10(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take12(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take11(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take13(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take12(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take14(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take13(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take15(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take14(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take16(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take15(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take17(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take16(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take18(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take17(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take19(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take18(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_take20(...) wxmmetamacro_head(__VA_ARGS__), wxmmetamacro_take19(wxmmetamacro_tail(__VA_ARGS__))

// wxmmetamacro_drop expansions
#define wxmmetamacro_drop0(...) __VA_ARGS__
#define wxmmetamacro_drop1(...) wxmmetamacro_tail(__VA_ARGS__)
#define wxmmetamacro_drop2(...) wxmmetamacro_drop1(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop3(...) wxmmetamacro_drop2(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop4(...) wxmmetamacro_drop3(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop5(...) wxmmetamacro_drop4(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop6(...) wxmmetamacro_drop5(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop7(...) wxmmetamacro_drop6(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop8(...) wxmmetamacro_drop7(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop9(...) wxmmetamacro_drop8(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop10(...) wxmmetamacro_drop9(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop11(...) wxmmetamacro_drop10(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop12(...) wxmmetamacro_drop11(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop13(...) wxmmetamacro_drop12(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop14(...) wxmmetamacro_drop13(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop15(...) wxmmetamacro_drop14(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop16(...) wxmmetamacro_drop15(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop17(...) wxmmetamacro_drop16(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop18(...) wxmmetamacro_drop17(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop19(...) wxmmetamacro_drop18(wxmmetamacro_tail(__VA_ARGS__))
#define wxmmetamacro_drop20(...) wxmmetamacro_drop19(wxmmetamacro_tail(__VA_ARGS__))

#define wxmkeypath(...) \
wxmmetamacro_if_eq(1, \
wxmmetamacro_argcount(__VA_ARGS__)) \
(wxmkeypath1(__VA_ARGS__))(wxmkeypath2(__VA_ARGS__))

#define wxmkeypath1(PATH) \
(((void)(NO && ((void)PATH, NO)), strchr(# PATH, '.') + 1))

#define wxmkeypath2(OBJ, PATH) \
(((void)(NO && ((void)OBJ.PATH, NO)), # PATH))

#define WXMPreventCrashBegin  @try {
#define WXMPreventCrashEnd    } @catch (NSException *exception) {} @finally {}

typedef void (^KVOCallBack)(id newVal);
#endif /* WXMKVOObjectMacro_h */
