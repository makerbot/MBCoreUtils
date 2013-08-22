// Copyright 2013 MakerBot Industries

#ifndef CPP_INCLUDE_MBCOREUTILS_JSON_H_
#define CPP_INCLUDE_MBCOREUTILS_JSON_H_

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>

#include <stdexcept>
#include <string>

/// Header-only utilities for JSON parsing and manipulation
///
/// Mostly this is just adding exceptions to Json-cpp.
namespace Json {
class TypeError : public std::runtime_error {
 public:
  TypeError(const std::string &what)
      : std::runtime_error(what) {
  }
};

class KeyError : public std::runtime_error {
 public:
  KeyError(const std::string &what)
      : std::runtime_error(what) {
  }
};

class ParseError : public std::runtime_error {
 public:
  ParseError(const std::string &what)
      : std::runtime_error(what) {
  }
};

/// Parse a UTF-8 string into JSON
///
/// Throws a ParseError if unsuccessful.
inline Json::Value parse(const std::string &text);

/// Return the JSON value for the specified key
///
/// Throws a TypeError if the input is not an object or a KeyError if
/// the key is not present.
///
/// Json::Value is a template type here rather than explicitly stated
/// so that separate const and non-const versions don't need to be
/// written.
template<typename T>
T &objectMember(T &json, const std::string &key);

/// Return the value for the specified key as type Result
///
/// Throws a TypeError if the input is not an object, a KeyError if
/// the key is not present, or a TypeError if the key's value is not
/// of the requested type.
template<typename Result>
Result objectMemberAs(const Json::Value &json, const std::string &key);
}

#include "mbcoreutils/json_impl.h"

#endif  // CPP_INCLUDE_MBCOREUTILS_JSON_H_
