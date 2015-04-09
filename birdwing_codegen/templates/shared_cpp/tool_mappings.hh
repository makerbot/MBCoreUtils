// This file was automatically generated, do not edit it!

#ifndef YONKERS_TOOL_MAPPINGS
#define YONKERS_TOOL_MAPPINGS

#include <stdint.h>
#include <string>

namespace bwcoreutils {

enum class TOOL : int {
    {{#tools}}
    {{name}} = {{id}},
    {{/tools}}
};

enum class TYPE : int {
    {{#types}}
    {{name}},
    {{/types}}
};

enum class MATERIALS : int {
    {{#materials}}
    {{name}} = {{id}},
    {{/materials}}
};
// This class takes a tool_id and exposes metadata for that tool.
// Primarily intended to be used for UI clients.
// TODO(jacksonh) - use qt to make these translatable.
class YonkersTool {
public:


    YonkersTool(uint8_t id) :
        m_tool(static_cast<TOOL>(id)) {}

    YonkersTool(TOOL id) : m_tool(id) {}
    ~YonkersTool() {}

    std::string name() const {
        switch (m_tool) {
            {{#tools}}
            case TOOL::{{name}}:
                return "{{pretty_name}}";
            {{/tools}}
            default:
                return "Unknown";
        }
    }

    TYPE type() const {
        switch (m_tool) {
            {{#tools}}
        case TOOL::{{name}}:
            return TYPE::{{type_name}};
        {{/tools}}
        default:
            return TYPE::UNKNOWN;
        }
    }

    static TYPE type_from_type_name(const std::string& type_name) {
        // This weird formatting brought to you by switch() only
        // knowing how to handle integral types for some reason
        if(type_name == "") {
            return TYPE::UNKNOWN;
        }
        {{#types}}
        else if(type_name == std::string("{{key}}")) {
            return TYPE::{{name}}; }
        {{/types}}
        else {
            return TYPE::UNKNOWN;
        }
    }

    static std::string material_from_material_type(const MATERIALS mat) {
        switch(mat) {
            {{#materials}}
        case MATERIALS::{{name}}:
            return std::string("{{name}}");
            {{/materials}}
        default:
            return std::string("Unknown");
        }
    }

    TOOL tool() const { return m_tool; }

    bool operator==(const YonkersTool& rValue) const {
        return this->m_tool == rValue.m_tool;
    }

    bool type_match(const YonkersTool& rValue) const {
        return type() == rValue.type();
    }

private:
    TOOL m_tool;
};

} // namespace bwcoreutils

#endif // YONKERS_TOOL_MAPPINGS
