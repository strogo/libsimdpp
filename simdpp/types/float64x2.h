/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64X2_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64X2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/int64x2.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <simdpp/detail/array.h>
#include <simdpp/detail/null/mask.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_fp
/// @{

/// Class representing float64x2 vector
template<>
class float64<2, void> : public any_float64<2, float64<2,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using element_type = double;
    using base_vector_type = float64<2,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128d;
#else
    using native_type = detail::array<double, 2>;
#endif

    float64<2>() = default;
    float64<2>(const float64<2> &) = default;
    float64<2> &operator=(const float64<2> &) = default;

    template<class E> SIMDPP_INL float64<2>(const float64<2,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit float64<2>(const any_vec<16,V>& d)
    {
        *this = bit_cast<float64<2>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL float64<2>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<float64<2>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    float64<2>(const native_type& d) : d_(d) {}
    float64<2>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL float64<2>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL float64<2>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const float64<2>& vec(unsigned) const { return *this; }
          float64<2>& vec(unsigned)       { return *this; }
    /// @}

    float64<2> eval() const { return *this; }

#ifndef SIMDPP_DOXYGEN
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    /// For internal use only
    const double& el(unsigned i) const { return d_[i]; }
          double& el(unsigned i)       { return d_[i]; }
#endif
#endif

    /** Creates a float64x2 vector with the contens set to zero

        @code
        r0 = 0.0
        r1 = 0.0
        @endcode
    */
    static float64<2> zero() { return detail::make_zero(); }

private:
    union {
        native_type d_;
#if SIMDPP_USE_NEON
        float32x4_t align_;
#elif SIMDPP_USE_ALTIVEC
        __vector float align_;
#endif
    };
};


/// Class representing possibly optimized mask data for 2x 64-bit floating point
/// vector
template<>
class mask_float64<2, void> : public any_float64<2, mask_float64<2,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float64<2,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128d;
#else // NULL, NEON, ALTIVEC
    using native_type = detail::array<bool, 2>;
#endif

    mask_float64<2>() = default;
    mask_float64<2>(const mask_float64<2> &) = default;
    mask_float64<2> &operator=(const mask_float64<2> &) = default;

    mask_float64<2>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_SSE2
    mask_float64<2>(const float64<2>& d) : d_(d) {}
#endif

    template<class E> SIMDPP_INL explicit mask_float64<2>(const mask_int64<2,E>& d)
    {
        *this = bit_cast<mask_float64<2>>(d.eval());
    }
    template<class E> SIMDPP_INL mask_float64<2>& operator=(const mask_int64<2,E>& d)
    {
        *this = bit_cast<mask_float64<2>>(d.eval()); return *this;
    }

    operator native_type() const { return d_; }

    /// Access the underlying type
    float64<2> unmask() const
    {
    #if SIMDPP_USE_NULL || SIMDPP_USE_NEON
        return detail::null::unmask_mask<float64<2>>(*this);
    #else
        return float64<2>(d_);
    #endif
    }

#if !SIMDPP_USE_SSE2 && !SIMDPP_DOXYGEN
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    const mask_float64<2>& vec(unsigned) const { return *this; }
          mask_float64<2>& vec(unsigned)       { return *this; }

    mask_float64<2> eval() const { return *this; }

private:
    native_type d_;
};
/// @} -- end ingroup

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
