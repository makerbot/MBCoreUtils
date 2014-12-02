// This file was automatically generated, do not edit it!

#ifndef YONKERS_TOOL_MAPPINGS
#define YONKERS_TOOL_MAPPINGS

#include <stdint.h>
#include <string>

namespace bwcoreutils {

// This class takes a tool_id and exposes metadata for that tool.
// Primarily intended to be used for UI clients.
// TODO(jacksonh) - use qt to make these translatable.
class YonkersTool {
public:

    enum TOOL {
        {{#tools}}
        {{name}} = 0x{{id}},
        {{/tools}}
    };

    YonkersTool(uint8_t id) :
        m_tool(static_cast<TOOL>(id)) {}
    ~YonkersTool() {}

    std::string name() const {
        switch (m_tool) {
            {{#tools}}
            case {{name}}:
                return "{{pretty_name}}";
            {{/tools}}
            default:
                return "Unknown";
        }
    }

    TOOL tool() const { return m_tool; }

    bool operator==(const YonkersTool& rValue){ return this->m_tool == rValue.m_tool; }

private:
    TOOL m_tool;
};

} // namespace bwcoreutils

#endif // YONKERS_TOOL_MAPPINGS
