// Copyright 2013 MakerBot Industries

#ifndef INCLUDE_MBCOREUTILS_VECTOR_VERSION_H_
#define INCLUDE_MBCOREUTILS_VECTOR_VERSION_H_

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace MakerBot {

/// Generic version of arbitrary length containing unsigned integers
///
/// The version is ordered from most significant to least significant.
class VectorVersion {
 public:
  typedef unsigned Element;

  /// Create an empty version
  VectorVersion() {
  }

  /// Create a one-element version
  explicit VectorVersion(const Element e0) {
    append(e0);
  }

  /// Create a two-element version
  VectorVersion(const Element e0, const Element e1) {
    append(e0);
    append(e1);
  }

  /// Create a three-element version
  VectorVersion(const Element e0, const Element e1, const Element e2) {
    append(e0);
    append(e1);
    append(e2);
  }

  /// Create a four-element version
  VectorVersion(
      const Element e0,
      const Element e1,
      const Element e2,
      const Element e3) {
    append(e0);
    append(e1);
    append(e2);
    append(e3);
  }

  /// Return true if the version is empty, false otherwise
  bool empty() const {
    return m_vec.empty();
  }

  /// Get the number of elements in the version
  std::vector<Element>::size_type size() const {
    return m_vec.size();
  }

  /// Get the specified element (throws if out of bounds)
  Element operator[](const std::vector<Element>::size_type index) {
    return m_vec.at(index);
  }

  /// Append an element to the end of the version
  void append(const Element e) {
    m_vec.emplace_back(e);
  }

  /// Return a period-separated version string
  std::string str() const {
    std::string result;
    for (const auto &v : m_vec) {
      if (!result.empty()) {
        result += '.';
      }
      result += std::to_string(v);
    }
    return result;
  }

  bool operator==(const VectorVersion &other) const {
    return cmp(other) == 0;
  }

  bool operator!=(const VectorVersion &other) const {
    return cmp(other) != 0;
  }

  bool operator<(const VectorVersion &other) const {
    return cmp(other) < 0;
  }

  bool operator<=(const VectorVersion &other) const {
    return cmp(other) <= 0;
  }

  bool operator>(const VectorVersion &other) const {
    return cmp(other) > 0;
  }

  bool operator>=(const VectorVersion &other) const {
    return cmp(other) >= 0;
  }

  /// Return -1 if this is less than other, 0 if equal, otherwise 1
  ///
  /// Note: a.b < a.b.c
  int cmp(const VectorVersion &other) const {
    const auto end(std::min(m_vec.size(), other.m_vec.size()));
    for (std::size_t i(0); i < end; ++i) {
      if (m_vec[i] < other.m_vec[i]) {
        return -1;
      } else if (m_vec[i] > other.m_vec[i]) {
        return 1;
      }
    }

    if (m_vec.size() < other.m_vec.size()) {
      return -1;
    } else if (m_vec.size() > other.m_vec.size()) {
      return 1;
    } else {
      return 0;
    }
  }

 private:
  std::vector<Element> m_vec;
};
}

#endif  // INCLUDE_MBCOREUTILS_VECTOR_VERSION_H_
