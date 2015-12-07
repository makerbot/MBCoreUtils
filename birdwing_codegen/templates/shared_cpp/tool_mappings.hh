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
    {{key}} = {{id}},
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
        return TYPE::{{type_key}};
        {{/tools}}
        default:
            return TYPE::UNKNOWN_TYPE;
        }
    }

    static TYPE type_from_type_name(const std::string& type_name) {
        // This weird formatting brought to you by switch() only
        // knowing how to handle integral types for some reason
        {{#types}}
        if(type_name == std::string("{{key_string}}")
           || type_name == std::string("{{name}}")) {
            return TYPE::{{key}}; }
        {{/types}}
        return TYPE::UNKNOWN_TYPE;
    }

    static std::string type_name_from_type(const TYPE type) {
        {{#types}}
        if(type == TYPE::{{key}}) { return "{{name}}";}
        {{/types}}
        return "Unknown";
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

    static bool toolpaths_equivalent(const TYPE a, const TYPE b) {
        switch(a) {
            {{#types}}
        case TYPE::{{key}}:
            switch(b) {
            {{#toolpath_equivalents}}
            case TYPE::{{key}}: return true; break;
            {{/toolpath_equivalents}}
            case TYPE::{{key}}: return true; break;
            default: return false; break;
            }
            {{/types}}
        default: return false; break;
        }
    }

private:
    TOOL m_tool;
};

} // namespace bwcoreutils

#endif // YONKERS_TOOL_MAPPINGS
