// ***************************************************************************
// * Copyright (c) 2024-2025 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="has_propagate_on_container_copy_assignment.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_HAS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT_H
#define PSTL_HAS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT_H

#include "../helper/integral_constant.h"
#include "../other_transformations/void_t.h"

namespace portable_stl {
namespace type_properties_helper {

  /**
   * @brief Check type t_type has the propagate_on_container_copy_assignment inner type.
   * @tparam t_type the type for check.
   */
  template<class t_type, class = void> class has_propagate_on_container_copy_assignment final {
  public:
    /**
     * @brief Result value.
     */
    using type = ::portable_stl::false_type;
  };

  /**
   * @brief Check type t_type has the propagate_on_container_copy_assignment inner type.
   *
   * @tparam t_type the type for check.
   */
  template<class t_type>
  class has_propagate_on_container_copy_assignment<
    t_type,
    ::portable_stl::void_t<typename t_type::propagate_on_container_copy_assignment>>
    final {
  public:
    /**
     * @brief Result value.
     */
    using type = ::portable_stl::true_type;
  };
} // namespace type_properties_helper

/**
 * @brief Check type t_type has the propagate_on_container_copy_assignment inner type.
 *
 * @tparam t_type the type for check.
 */
template<class t_type>
using has_propagate_on_container_copy_assignment =
  typename type_properties_helper::has_propagate_on_container_copy_assignment<t_type>::type;
} // namespace portable_stl

#endif // PSTL_HAS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT_H
