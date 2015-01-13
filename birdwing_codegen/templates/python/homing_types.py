""" This file was automatically generated, do not edit it! """

str_to_id = {
    {{#homing_types}}
        "{{name}}": {{id}},
    {{/homing_types}}
}

id_to_str = {
    {{#homing_types}}
        {{id}}: "{{name}}",
    {{/homing_types}}
}
