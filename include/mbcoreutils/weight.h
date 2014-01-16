// Copyright 2014 MakerBot Industries

#ifndef INCLUDE_MBCOREUTILS_WEIGHT_H_
#define INCLUDE_MBCOREUTILS_WEIGHT_H_

namespace MakerBot {

/// Stores a measurement of weight
///
/// The purpose of this class is to avoid dealing in raw numbers
/// without corresponding units.
///
/// The internal storage is in kilograms. The other accessor and set
/// functions do numeric conversion.
class Weight {
 public:
  typedef double ValueType;

  /// Initialize with zero weight
  Weight()
      : m_kilograms(0) {
  }

  /// Get the weight in kilograms
  ValueType kilograms() const {
    return m_kilograms;
  }

  /// Get the weight in grams
  ValueType grams() const {
    return m_kilograms * 1000;
  }

  ValueType pounds() const {
    return m_kilograms * 2.20462;
  }

  /// Set the weight in kilograms
  void setKilograms(const ValueType kilograms) {
    m_kilograms = kilograms;
  }

  /// Set the weight in grams
  void setGrams(const ValueType grams) {
    m_kilograms = grams * 0.001;
  }

  /// Set the weight in pounds
  void setPounds(const ValueType pounds) {
    m_kilograms = pounds * 0.453592;
  }

 private:
  /// Internal storage is in kilograms
  double m_kilograms;
};
}

#endif  // INCLUDE_MBCOREUTILS_WEIGHT_H_
