#ifndef MACHINE_ERRORS_HH
#define MACHINE_ERRORS_HH
#ifndef BRONX
#include <string>
#include <sstream>
#endif

namespace machine {

enum Error {
    {{#machine_errors}}
        {{name}} = {{id}},
    {{/machine_errors}}

}; // enum

#ifndef BRONX
inline std::string stringify_error(Error val) {
    std::stringstream retval;
    switch(val){

    {{#machine_errors}}
    case {{id}}:
        retval << "machine::{{name}}";
        break;
    {{/machine_errors}}

    default:
        retval << "machine::Unknown or not implemented";
    }
    return retval.str();
} //stringify
#endif // BRONX
} // namespace
#endif // MACHINE_ERRORS_HH
