/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_LE_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_CMP_LE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/detail/null/compare.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


SIMDPP_INL mask_float32x4 i_cmp_le(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return detail::null::cmp_le(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_LE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmple_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_u32(vcleq_f32(a, b));
#elif SIMDPP_USE_ALTIVEC
    return vec_cmple((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float32x8 i_cmp_le(float32x8 a, float32x8 b)
{
    return _mm256_cmp_ps(a, b, _CMP_LE_OQ);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_float32<16> i_cmp_le(float32<16> a, float32<16> b)
{
    return _mm512_cmp_ps_mask(a, b, _CMP_LE_OQ);
}
#endif

template<unsigned N> SIMDPP_INL
mask_float32<N> i_cmp_le(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, i_cmp_le, a, b);
}

// -----------------------------------------------------------------------------

SIMDPP_INL mask_float64x2 i_cmp_le(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::cmp_le(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_LE_OQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmple_pd(a, b);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL mask_float64x4 i_cmp_le(float64x4 a, float64x4 b)
{
    return _mm256_cmp_pd(a, b, _CMP_LE_OQ);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL mask_float64<8> i_cmp_le(float64<8> a, float64<8> b)
{
    return _mm512_cmp_pd_mask(a, b, _CMP_LE_OQ);
}
#endif

template<unsigned N> SIMDPP_INL
mask_float64<N> i_cmp_le(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, i_cmp_le, a, b);
}


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

