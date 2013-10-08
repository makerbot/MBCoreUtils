// Copyright 2013 MakerBot Industries

#ifndef CPP_INCLUDE_MBCOREUTILS_JSON_IMPL_H_
#define CPP_INCLUDE_MBCOREUTILS_JSON_IMPL_H_

#include <cstdint>
#include <limits>
#include <string>

namespace Json {
inline Json::Value parse(const std::string &text) {
  Json::Reader reader;
  Json::Value root;
  if (reader.parse(text, root)) {
    return root;
  } else {
    throw ParseError(reader.getFormattedErrorMessages());
  }
}

template<typename T>
T &objectMember(T &json, const std::string &key) {
  if (json.isObject()) {
    if (json.isMember(key)) {
      return json[key];
    } else {
      throw KeyError(json.toStyledString());
    }
  } else {
    throw TypeError(json.toStyledString());
  }
}

template<>
inline std::string objectMemberAs<std::string>(
    const Json::Value &json,
    const std::string &key) {
  const auto member(objectMember(json, key));
  if (member.isString()) {
    return member.asString();
  } else {
    throw TypeError(json.toStyledString());
  }
}

template<>
inline unsigned int objectMemberAs<unsigned int>(
    const Json::Value &json,
    const std::string &key) {
  const auto member(objectMember(json, key));
  if (member.isNumeric()) {
    return member.asUInt();
  } else {
    throw TypeError(json.toStyledString());
  }
}

template<>
inline uint16_t objectMemberAs<uint16_t>(
    const Json::Value &json,
    const std::string &key) {
  const auto member(objectMember(json, key));
  if (member.isNumeric()) {
    const auto v(member.asUInt());
    if (v <= std::numeric_limits<uint16_t>::max()) {
      return static_cast<uint16_t>(v);
    } else {
      throw std::out_of_range("objectMemberAs<uint16_t>: range error");
    }
  } else {
    throw TypeError(json.toStyledString());
  }
}
}

#endif  // CPP_INCLUDE_MBCOREUTILS_JSON_IMPL_H_
