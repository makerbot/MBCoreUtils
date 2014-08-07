#ifndef TOOLHEAD_ERRORS_HH
#define TOOLHEAD_ERRORS_HH
#ifndef BRONX
#include <string>
#include <sstream>
#endif

namespace toolhead {

enum Error {
    {{#toolhead_errors}}
        {{name}} = {{id}},
    {{/toolhead_errors}}

}; // enum

#ifndef BRONX
inline std::string stringify_error(Error val) {
    std::stringstream retval;
    switch(val){

    {{#toolhead_errors}}
    case {{id}}:
        retval << "toolhead::{{name}}";
        break;
    {{/toolhead_errors}}

    default:
        retval << "toolhead::Unknown or not implemented";
    }
    return retval.str();
} //stringify
#endif // BRONX
} // namespace
#endif // TOOLHEAD_ERRORS_HH
