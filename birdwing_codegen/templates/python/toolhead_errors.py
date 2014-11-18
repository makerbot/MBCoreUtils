""" This file was automatically generated, do not edit it! """

error = {
	{{#toolhead_errors}}
		u'{{name}}': {{id}},
	{{/toolhead_errors}}
}

error_to_string = {
	{{#toolhead_errors}}
		{{id}}: u'{{name}}',
	{{/toolhead_errors}}
}
