// This file was automatically generated, do not edit it!
// Intended for use in the machine-driver.

#ifndef TOOLHEAD_TOOL_IDENTIFIER
#define TOOLHEAD_TOOL_IDENTIFIER

namespace toolhead {

    enum ToolIdentifier {
        {{#tools}}
        {{name}} = 0x{{id}},
        {{/tools}}
    };

} // namespace toolhead

#endif // TOOLHEAD_TOOL_IDENTIFIER
