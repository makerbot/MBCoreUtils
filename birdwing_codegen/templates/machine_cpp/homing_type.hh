// This file was automatically generated, do not edit it!
// Intended for use in the machine-driver.
// Copyright 2015 MakerBot

#ifndef BIRDWING_CODEGEN_TEMPLATES_MACHINE_CPP_HOMING_TYPE_HH_
#define BIRDWING_CODEGEN_TEMPLATES_MACHINE_CPP_HOMING_TYPE_HH_

#include <string>


namespace machine {

// Find a nice way of calculating number of valid homing types via pystache

static const int NUM_HOMING_TYPES = {{number_homing_types}};

    enum HomingType {
        {{#homing_types}}
        {{name}} = {{id}},
        {{/homing_types}}
    };

inline std::string homing_type_to_string(HomingType homing_type) {
    switch (homing_type) {
    {{#homing_types}}
    case {{name}}:
        return "{{name_str}}";

    {{/homing_types}}
    default:
        return "";
    }
}

inline HomingType string_to_homing_type(std::string string) {
    {{#homing_types}}
    if (string.compare("{{name_str}}") == 0) {
        return {{name}};
    }
    {{/homing_types}}
    else {
        return HomingType::kInvalid;
    }
}


} // end machine namespace


#endif  // BIRDWING_CODEGEN_TEMPLATES_MACHINE_CPP_HOMING_TYPE_HH_
