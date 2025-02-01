// ***************************************************************************
// * Copyright (c) 2024-2025 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_trivially_copy_constructible_v.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_V_H
#define PSTL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_V_H

#include "is_trivially_copy_constructible.h"
namespace portable_stl {
/**
 * @brief Check t_type is a copy Trivially-constructible . ( Can copy construct with trivial function. )
 * @tparam t_type type for check.
 */
template<class t_type>
constexpr inline bool is_trivially_copy_constructible_v = ::portable_stl::is_trivially_copy_constructible<t_type>{}();
} // namespace portable_stl

#endif // PSTL_IS_TRIVIALLY_COPY_CONSTRUCTIBLE_V_H
