// ***************************************************************************
// * Copyright (c) 2024-2025 Paragon Software Group
// *
// * Project="Paragon Portable STL" File="cpp17_bidirectional_iterator.h"
// * 
// * This program and the accompanying materials are made available under the
// * terms of the MIT License which is available at
// * https://opensource.org/licenses/MIT.
// * 
// * SPDX-License-Identifier: MIT
// ***************************************************************************
#ifndef PSTL_CPP17_BIDIRECTIONAL_ITERATOR_H
#define PSTL_CPP17_BIDIRECTIONAL_ITERATOR_H

#include "../../common/size_t.h"
#include "../../concepts/same_as.h"
#include "../../metaprogramming/composite_type/is_reference.h"
#include "../../metaprogramming/logical_operator/conjunction.h"
#include "../../metaprogramming/other_transformations/void_t.h"
#include "../../utility/general/declval.h"
#include "../iter_reference_t.h"
#include "cpp17_forward_iterator.h"

namespace portable_stl {
namespace iterator_helper {
  /**
   * @brief Base LegacyForwardIterator requirement.
   * @tparam t_type Tested iterator type.
   */
  template<class t_iterator> class cpp17_bidirectional_iterator_req1 final {
    /**
     * @brief Test function.
     * @tparam T1
     * @return ::portable_stl::true_type
     */
    template<class T1>

    static auto test(::portable_stl::size_t) -> decltype(--::portable_stl::declval<T1 &>(),
                                                         ::portable_stl::declval<T1 &>()--,
                                                         *::portable_stl::declval<T1 &>()--,
                                                         ::portable_stl::true_type{});

    /**
     * @brief Test function.
     * @tparam T1
     * @return ::portable_stl::false_type
     */
    template<class T1> static auto test(...) -> ::portable_stl::false_type;

  public:
    /**
     * @brief Result type.
     */
    using type = decltype(test<t_iterator>(0));
  };

  /**
   * @brief Helper to check common_reference_t requirements.
   * Primary template.
   * @tparam t_iterator Tested iterator type.
   */
  template<class t_iterator, class = void> class cpp17_bidirectional_iterator_req2 final {
  public:
    /**
     * @brief Result type.
     */
    using type = ::portable_stl::false_type;
  };

  /**
   * @brief Helper to check common_reference_t requirements.
   * Primary template.
   * @tparam t_iterator Tested iterator type.
   */
  template<class t_iterator>
  class cpp17_bidirectional_iterator_req2<t_iterator,
                                          ::portable_stl::void_t<::portable_stl::iter_reference_t<t_iterator>>>
    final {
  public:
    /**
     * @brief Main check and result type.
     */
    using type = ::portable_stl::conjunction<
      ::portable_stl::cpp17_forward_iterator<t_iterator>,
      ::portable_stl::same_as<decltype(--::portable_stl::declval<t_iterator &>()), t_iterator &>,
      ::portable_stl::convertible_to<decltype(::portable_stl::declval<t_iterator &>()--), t_iterator const &>,
      ::portable_stl::same_as<decltype(*::portable_stl::declval<t_iterator &>()--),
                              ::portable_stl::iter_reference_t<t_iterator>>>;
  };

  /**
   * @brief Helper to check base (cpp17_bidirectional_iterator_req1) requirements.
   * Primary template.
   * @tparam t_iterator Tested iterator type.
   */
  template<class t_iterator, class = typename cpp17_bidirectional_iterator_req1<t_iterator>::type>
  class cpp17_bidirectional_iterator_impl final {
  public:
    /**
     * @brief Result type.
     */
    using type = typename cpp17_bidirectional_iterator_req2<t_iterator>::type;
  };

  /**
   * @brief Helper to check base (cpp17_bidirectional_iterator_req1) requirements.
   * @tparam t_iterator Tested iterator type.
   */
  template<class t_iterator> class cpp17_bidirectional_iterator_impl<t_iterator, ::portable_stl::false_type> final {
  public:
    /**
     * @brief Result type.
     */
    using type = ::portable_stl::false_type;
  };

} // namespace iterator_helper

/**
 * @brief A LegacyBidirectionalIterator/cpp17_bidirectional_iterator is a LegacyForwardIterator/cpp17_forward_iterator
 * that can be moved in both directions (i.e. incremented and decremented).
 *
 * @tparam t_iterator Tested iterator type.
 */
template<class t_iterator>
using cpp17_bidirectional_iterator = typename iterator_helper::cpp17_bidirectional_iterator_impl<t_iterator>::type;

} // namespace portable_stl

#endif /* PSTL_CPP17_BIDIRECTIONAL_ITERATOR_H */
