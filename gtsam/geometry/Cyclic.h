/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file   Cyclic.h
 * @brief  Cyclic group, i.e., the integers modulo N
 * @author Frank Dellaert
 **/

#include <gtsam/base/concepts.h>
#include <cstddef>

namespace gtsam {

/// Cyclic group of order N
template<size_t N>
class Cyclic {
  size_t i_; ///< we just use an unsigned int
public:
  /// Constructor
  Cyclic(size_t i) :
      i_(i) {
    assert(i<N);
  }
  // Idenity element
  static Cyclic Identity() {
    return Cyclic(0);
  }
  /// Cast to size_t
  operator size_t() const {
    return i_;
  }
  /// Addition modulo N
  Cyclic operator+(const Cyclic& h) const {
    return (i_ + h.i_) % N;
  }
  /// Subtraction modulo N
  Cyclic operator-(const Cyclic& h) const {
    return (N + i_ - h.i_) % N;
  }
  /// Inverse
  Cyclic operator-() const {
    return (N - i_) % N;
  }
  /// print with optional string
  void print(const std::string& s = "") const {
    std::cout << s << i_ << std::endl;
  }

  /// equals with an tolerance, prints out message if unequal
  bool equals(const Cyclic& other, double tol = 1e-9) const {
    return other.i_ == i_;
  }

};

#define CYCLIC_TEMPLATE size_t N
#define CYCLIC_TYPE Cyclic<N>

/// Define cyclic group traits to be a model of the Group concept
template <CYCLIC_TEMPLATE>
struct traits_x<CYCLIC_TYPE > {
  typedef group_tag structure_category;
  GTSAM_ADDITIVE_GROUP(CYCLIC_TYPE);
  static const CYCLIC_TYPE identity = CYCLIC_TYPE::Identity();
};

} // \namespace gtsam

