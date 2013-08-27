// Copyright 2013 MakerBot Industries

#ifndef CPP_INCLUDE_MBCOREUTILS_TAGGED_ID_H_
#define CPP_INCLUDE_MBCOREUTILS_TAGGED_ID_H_

#include <stdexcept>

namespace MakerBot {

/// Create a new ID type
///
/// The ID type will be a completely separate type from any other
/// tagged ID.
#define CREATE_TAGGED_ID_TYPE(name_, validator_, value_type_) \
  class name_##_tag_; \
  typedef MakerBot::TaggedID<value_type_, validator_, name_##_tag_> name_


/// Identifier template
///
/// This is a generic ID for ID types that can represent both valid
/// and invalid values (in other words, at least one value of
/// ValueType must be able to represent an invalid ID).
///
/// The Validator type must provide two static methods: invalidValue()
/// and valid(). The first returns a ValueType representing an invalid
/// ID. The second takes a ValueType parameter and returns true if the
/// parameter is valid, false otherwise.
///
/// The Tag type is used to make each TaggedID incompatible with all
/// other TaggedIDs so that type errors are caught. The
/// CREATE_TAGGED_ID_TYPE macro takes care of creating the Tag type.
///
/// Example:
///
///   If a valid ID is a number between 0 and 127 (inclusive), a
///   TaggedID could be created using a ValueType of signed
///   char. Validator::invalidValue() could return -1 (or any negative
///   number down to -128.)
///
///   Code:
///
///   struct MyIDValidator {
///     static signed char invalidValue() { return -1; }
///     static bool valid(const signed char value) { return value >= 0; }
///   };
///
///   CREATE_TAGGED_ID_TYPE(MyID, MyIDValidator, signed char);
template<typename ValueType, typename Validator, typename Tag>
class TaggedID {
 public:
  /// Error thrown when attempting to use an invalid ID
  class IDError : public std::runtime_error {
   public:
    IDError()
        : std::runtime_error("Invalid ID") {
    }
  };

  /// Construct an invalid ID
  TaggedID()
      : m_id(Validator::invalidValue()) {
  }

  /// Construct a valid ID
  ///
  /// If an invalid ID is given, an IDError is thrown.
  explicit TaggedID(const ValueType &id)
      : m_id(id) {
    if (!Validator::valid(id)) {
      throw IDError();
    }
  }

  /// Get the current ID
  ///
  /// If the current ID is invalid, an IDError is thrown.
  ValueType get() const {
    if (valid()) {
      return m_id;
    } else {
      throw IDError();
    }
  }

  /// Return true if the current ID is valid, false otherwise
  bool valid() const {
    return Validator::valid(m_id);
  }

 private:
  ValueType m_id;
};

/// TaggedID equality test
///
/// If both IDs are invalid they are considered equal. If one is valid
/// and the other not, they are not equal. If both are valid their
/// values are tested for equality.
template<typename A, typename B, typename C,
         typename D, typename E, typename F>
bool operator==(
    const TaggedID<A, B, C> &id1,
    const TaggedID<D, E, F> &id2) {
  const bool id1Valid(id1.valid());
  const bool id2Valid(id2.valid());

  if (id1Valid && id2Valid) {
    return id1.get() == id2.get();
  } else if (!id1Valid && !id2Valid) {
    return true;
  } else {
    return false;
  }
}

/// TaggedID comparison test
///
/// An invalid ID considered less than a valid ID. If both are invalid
/// they are considered equal. If both are valid their values are
/// tested for equality.
template<typename A, typename B, typename C,
         typename D, typename E, typename F>
bool operator<(
    const TaggedID<A, B, C> &id1,
    const TaggedID<D, E, F> &id2) {
  const bool id1Valid(id1.valid());
  const bool id2Valid(id2.valid());

  if (id1Valid && id2Valid) {
    return id1.get() < id2.get();
  } else if (!id1Valid && id2Valid) {
    return true;
  } else if (id1Valid && !id2Valid) {
    return false;
  } else {
    return false;
  }
}
}

#endif  // CPP_INCLUDE_MBCOREUTILS_TAGGED_ID_H_
