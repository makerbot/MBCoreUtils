""" This file was automatically generated, do not edit it! """

import ctypes

{{#structs}}

class {{name}}(ctypes.LittleEndianStructure):
	_fields_ = {{#inherits}}{{inherits}}._fields_ + {{/inherits}}(
		{{#fields}}
		("{{name}}", {{type}}),
		{{/fields}}
	)
{{/structs}}

{{#utility}}
class {{name}}(ctypes.LittleEndianStructure):
    _fields_ = (
        {{#fields}}
        ("{{name}}", {{type}}),
        {{/fields}}
    )
{{/utility}}
