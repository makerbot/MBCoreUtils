// This file was automatically generated, do not edit it!

#ifndef MACHINE_DEFINITIONS_HH
#define MACHINE_DEFINITIONS_HH
#ifndef BRONX
#include <set>
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

{{/enums}}

#ifndef BRONX
typedef std::set<AxisName> AxisSet;
#endif

} //namespace
#endif // MACHINE_DEFINITIONS_HH
