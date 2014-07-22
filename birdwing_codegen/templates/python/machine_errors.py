""" This file was automatically generated, do not edit it! """

error = {
	{{#machine_errors}}
		u'{{name}}': {{id}},
	{{/machine_errors}}
}

error_to_string = {
	{{#machine_errors}}
		{{id}}: u'{{name}}',
	{{/machine_errors}}
}
