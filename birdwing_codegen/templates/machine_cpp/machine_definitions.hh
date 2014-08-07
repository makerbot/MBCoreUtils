// This file was automatically generated, do not edit it!

#ifndef MACHINE_DEFINITIONS_HH
#define MACHINE_DEFINITIONS_HH
#ifndef BRONX
#include <string>
#include <sstream>
#endif

namespace machine {

{{#enums}}
enum {{name}} {
	{{#values}}
	{{name}} = {{value}},
	{{/values}}
}; //enum

{{/enums}}

} //namespace
#endif // MACHINE_DEFINITIONS_HH
