/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_BIT_NOT_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_BIT_NOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/bit_or.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<unsigned N, class E> SIMDPP_INL
mask_int32<N> expr_eval(expr_bit_not<mask_int32<N,E>> q)
{
    return insn::i_bit_not(q.a.eval());
}

template<unsigned N, class E> SIMDPP_INL
mask_int64<N> expr_eval(expr_bit_not<mask_int64<N,E>> q)
{
    return insn::i_bit_not(q.a.eval());
}

template<unsigned N, class E> SIMDPP_INL
mask_float32<N> expr_eval(expr_bit_not<mask_float32<N,E>> q)
{
    return insn::i_bit_not(q.a.eval());
}

template<unsigned N, class E> SIMDPP_INL
mask_float64<N> expr_eval(expr_bit_not<mask_float64<N,E>> q)
{
    return insn::i_bit_not(q.a.eval());
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
