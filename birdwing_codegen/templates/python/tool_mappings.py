""" This file was automatically generated, do not edit it! """

tool_to_string = {
    {{#tools}}
        0x{{id}}: {'pretty_name' : u'{{pretty_name}}',
                   'short_name' : u'{{name}}',
                   'type_name': u'{{type_name}}'},
    {{/tools}}
}

name_to_id = {
    {{#tools}}
        "{{name}}": {{id}},
    {{/tools}}
}

id_to_material = {
    {{#materials}}
        {{id}} : "{{name}}",
    {{/materials}}
}
