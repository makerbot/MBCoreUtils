// This file was automatically generated, do not edit it!

#ifndef MACHINE_DEFINITIONS_HH
#define MACHINE_DEFINITIONS_HH
#ifndef BRONX
#include <set>
#include <array>
#include <string>
#endif

namespace machine {

{{#enums}}
enum {{name}} {
    {{#values}}
    {{#name_upper_xform}}
    {{name_upper_xform}} = {{value}},
    {{/name_upper_xform}}
    {{^name_upper_xform}}
    {{name}} = {{value}},
    {{/name_upper_xform}}
    {{/values}}
}; //enum {{name}}

#ifndef BRONX
{{#do_stringify?}}
inline std::string ToString({{name}} val) {
    switch(val) {
    {{#values}}
    {{#name_upper_xform}}
    case {{name_upper_xform}}: return "{{settings-key}}";
    {{/name_upper_xform}}
    {{^name_upper_xform}}
    case {{name}}: return "{{settings-key}}";
    {{/name_upper_xform}}
    {{/values}}
    default: return std::string("<invalid axis ")
        + std::to_string(static_cast<int>(val)) + ">";
    }
}
inline {{name}} FromString(const std::string& val) {
    if (false) {
    {{#values}}
    } else if (val == "{{settings-key}}") {
        {{#name_upper_xform}}
        return {{name_upper_xform}};
        {{/name_upper_xform}}
        {{^name_upper_xform}}
        return {{name}};
         {{/name_upper_xform}}
    {{/values}}
    } else {
        return static_cast<{{name}}>(-1);
    }
}
 {{/do_stringify?}}


#endif

{{/enums}}

 #ifndef BRONX
// Still need this for Birdwing-Machine for now
typedef std::set<AxisName> AxisSet;

inline std::array<machine::AxisName, 3> GantryAxes() {
    return {machine::kX, machine::kY, machine::kZ};
}

inline std::array<machine::AxisName, 2> ExtruderAxes() {
    return {machine::kA, machine::kB};
}
 #endif
} //namespace
#endif // MACHINE_DEFINITIONS_HH
