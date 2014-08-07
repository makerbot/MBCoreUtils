#ifndef ALL_ERRORS_HH
#define ALL_ERRORS_HH
#ifndef BRONX
#include <string>
#include <sstream>
#endif

namespace bwcoreutils {

enum Error {
    {{#machine_errors}}
    {{name}} = {{id}},
    {{/machine_errors}}
    {{#toolhead_errors}}
    {{name}} = {{id}},
    {{/toolhead_errors}}

}; // enum

} // namespace
#endif // TOOLHEAD_ERRORS_HH
