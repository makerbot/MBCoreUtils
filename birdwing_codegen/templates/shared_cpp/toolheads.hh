#ifndef TOOLHEADS_H
#define TOOLHEADS_H

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace bwcoreutils {

enum ToolheadType {
    kUnknownToolheadType,
    {{#toolhead_types}}
    {{name}},
    {{/toolhead_types}}
};

inline ToolheadType ToolheadTypeFromStr(const std::string &str) {
    const static std::unordered_map<std::string, ToolheadType> strmap = {
        {{#toolhead_types}}
        {"{{str}}", ToolheadType::{{name}}},
        {{/toolhead_types}}
    };
    try {
        return strmap.at(str);
    } catch (std::out_of_range &) {
        return ToolheadType::kUnknownToolheadType;
    }
}

}

#endif // TOOLHEADS_H
