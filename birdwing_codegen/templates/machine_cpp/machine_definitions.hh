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
enum {{enum_name}} {
    {{#values}}
    {{^name}}
    {{name_upper_xform}} = {{value}},
    {{/name}}
    {{^name_upper_xform}}
    {{name}} = {{value}},
    {{/name_upper_xform}}
    {{/values}}
}; //enum {{enum_name}}

#ifndef BRONX
{{#do_stringify?}}
inline std::string ToString({{enum_name}} val) {
    switch(val) {
    {{#values}}
    {{^name}}
    case {{name_upper_xform}}: return "{{settings-key}}";
    {{/name}}
    {{^name_upper_xform}}
    case {{name}}: return "{{settings-key}}";
    {{/name_upper_xform}}
    {{/values}}
    default: return std::string("<invalid axis ")
        + std::to_string(static_cast<int>(val)) + ">";
    }
}
inline {{enum_name}} {{enum_name}}FromString(const std::string& val) {
    if (false) {
    {{#values}}
    } else if (val == "{{settings-key}}") {
        {{^name}}
        return {{name_upper_xform}};
        {{/name}}
        {{^name_upper_xform}}
        return {{name}};
         {{/name_upper_xform}}
    {{/values}}
    } else {
        return static_cast<{{enum_name}}>(-1);
    }
}
 {{/do_stringify?}}
inline {{enum_name}} Next{{enum_name}}(const {{enum_name}}& c) {
    return static_cast<{{enum_name}}>(static_cast<size_t>(c)+1);
}
inline {{enum_name}} Previous{{enum_name}}(const {{enum_name}}& c) {
    return static_cast<{{enum_name}}>(static_cast<size_t>(c)-1);
}

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
