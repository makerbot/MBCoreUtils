// This file was automatically generated, do not edit it!

#ifndef MACHINE_STRUCTS_HH
#define MACHINE_STRUCTS_HH

namespace machine {
{{#structs}}

    struct {{name}} {{#inherits}}: {{inherits}} {{/inherits}}{
        {{#fields}}
    	{{type}} {{name}};
        {{/fields}}
    };
{{/structs}}

}
#endif // MACHINE_STRUCTS_HH
