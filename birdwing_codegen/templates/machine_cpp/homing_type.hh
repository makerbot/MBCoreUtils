// This file was automatically generated, do not edit it!
// Intended for use in the machine-driver.
// Copyright 2015 MakerBot


#ifndef BIRDWING_CODEGEN_TEMPLATES_MACHINE_CPP_HOMING_TYPE_HH_
#define BIRDWING_CODEGEN_TEMPLATES_MACHINE_CPP_HOMING_TYPE_HH_

    enum HomingType {
        {{#homing_types}}
        {{name}} = {{id}},
        {{/homing_types}}
    };

#endif // BIRDWING_CODEGEN_TEMPLATES_MACHINE_CPP_HOMING_TYPE_HH_
