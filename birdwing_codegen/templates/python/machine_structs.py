""" This file was automatically generated, do not edit it! """

import ctypes

{{#structs}}

class {{name}}({{#inherits}}{{inherits}}, {{/inherits}}ctypes.LittleEndianStructure):
    _fields_ = {{#inherits}}{{inherits}}._fields_ + {{/inherits}}(
        {{#fields}}
        ("{{name}}", {{type}}),
        {{/fields}}
    )

    def get_dict(self):
        field_dict = {}
        {{#fields}}
        if hasattr(self.{{name}}, "get_dict"):
            field_dict["{{name}}"] = self.{{name}}.get_dict()
        else:
            field_dict["{{name}}"] = self.{{name}}

        {{/fields}}
        {{#inherits}}field_dict.update(super({{name}}, self).get_dict()){{/inherits}}
        return field_dict
{{/structs}}

{{#utility}}
class {{name}}(ctypes.LittleEndianStructure):
    _fields_ = (
        {{#fields}}
        ("{{name}}", {{type}}),
        {{/fields}}
    )

    def get_dict(self):
        field_dict = {}
        {{#fields}}
        if hasattr(self.{{name}}, "get_dict"):
            field_dict["{{name}}"] = self.{{name}}.get_dict()
        else:
            field_dict["{{name}}"] = self.{{name}}

        {{/fields}}
        return field_dict

{{/utility}}
