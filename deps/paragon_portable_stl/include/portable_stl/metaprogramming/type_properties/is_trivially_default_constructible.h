// ***************************************************************************
// * Copyright (c) 2024-2025 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="is_trivially_default_constructible.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_H
#define PSTL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_H

#include "is_trivially_constructible.h"

namespace portable_stl {

/**
 * @brief Check t_type is a default Trivially-constructible . ( Can default construct with trivial function. )
 * @tparam t_type type for check.
 */
template<class t_type> using is_trivially_default_constructible = ::portable_stl::is_trivially_constructible<t_type>;
} // namespace portable_stl

#endif // PSTL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_H
