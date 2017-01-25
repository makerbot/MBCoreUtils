// Copyright MakerBot Inc, 2017

/*
 * jsoncpp_wrappers.h: functionality that jsoncpp should have provided
 * This header file contains wrappers that make it much easier to safely
 * (i.e. without crashing or causing exceptions) extract values from a
 * Json::Value tree, even in the face of missing keys, keys with different
 * and incompatible types, and various trees of same.
 */

#ifndef INCLUDE_MBCOREUTILS_JSONCPP_WRAPPERS_H_
#define INCLUDE_MBCOREUTILS_JSONCPP_WRAPPERS_H_

#include <jsoncpp/json/json.h>
#include <string>

namespace MakerBot {
namespace SafeJson {
    /**
     * type_correct - check if a value is present in the right type
     * Returns true if the key contains a value, and that value
     * is the same type as type.
     * This is probably not a useful function for library consumers to call.
     */
    // This is the base templated type, we should fall back to it for string
    // types

    template<typename KeyType>
    bool type_correct(const Json::Value& val,
                      const KeyType& key,
                      Json::ValueType type) {
        return val.isObject()
            && val.isMember(key)
            && !val[key].isNull()
            && val[key].isConvertibleTo(type);
    }

    // Overloads for Json::ArrayIndex and int that check if val is an array
    template<>
    bool type_correct<Json::ArrayIndex>(const Json::Value& val,
                                        const Json::ArrayIndex& idx,
                                        Json::ValueType type) {
        return val.isArray()
            && val.isValidIndex(idx)
            && !val[idx].isNull()
            && val[idx].isConvertibleTo(type);
    }

    template<>
    bool type_correct<int>(const Json::Value& val,
                           const int& idx,
                           Json::ValueType type) {
        return type_correct(val, Json::ArrayIndex(idx), type);
    }


    /**
     * get_leaf (and overloads) - get C++ typed versions of leaf values
     * The first two arguments are always the same, the value and the key.
     * The key is templated so you can use a string, char array, or array index.
     * The third argument is both a default value and an overload resolution.
     */
    template<typename KeyType>
    float get_leaf(const Json::Value& val,
                   const KeyType& key,
                   float default_val) {
        if (type_correct(val, key, Json::realValue)) {
            return val[key].asFloat();
        } else {
            return default_val;
        }
    }

    template<typename KeyType>
    unsigned int get_leaf(const Json::Value& val,
                          const KeyType& key,
                          unsigned int default_val) {
        if (type_correct(val, key, Json::uintValue)) {
            return val[key].asUInt();
        } else {
            return default_val;
        }
    }

    template<typename KeyType>
    int get_leaf(const Json::Value& val,
                 const KeyType& key,
                 int default_val) {
        if (type_correct(val, key, Json::intValue)) {
            return val[key].asInt();
        } else {
            return default_val;
        }
    }

    template<typename KeyType>
    std::string get_leaf(const Json::Value& val,
                         const KeyType& key,
                         const std::string& default_val) {
        if (type_correct(val, key, Json::stringValue)) {
            return val[key].asString();
        } else {
            return default_val;
        }
    }

    template<typename KeyType>
    std::string get_leaf(const Json::Value& val,
                         const KeyType& key,
                         const char* default_val) {
        return get_leaf(val, key, std::string(default_val));
    }

    template<typename KeyType>
    bool get_leaf(const Json::Value& val,
                  const KeyType& key,
                  const bool& default_val) {
        if (type_correct(val, key, Json::booleanValue)) {
            return val[key].asBool();
        } else {
            return default_val;
        }
    }

    template<typename KeyType>
    Json::Value get_obj(const Json::Value& val,
                        const KeyType& key) {
        if (type_correct(val, key, Json::objectValue)) {
            return val[key];
        } else {
            return Json::Value(Json::objectValue);
        }
    }

    template<typename KeyType>
    Json::Value get_arr(const Json::Value& val,
                        const KeyType& key) {
        if (type_correct(val, key, Json::arrayValue)) {
            return val[key];
        } else {
            return Json::Value(Json::arrayValue);
        }
    }
};
};

#endif  // INCLUDE_MBCOREUTILS_JSONCPP_WRAPPERS_H_
