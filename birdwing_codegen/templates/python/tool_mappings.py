""" This file was automatically generated, do not edit it! """

class Tool(object):
    """
    Do not instantiate directly, use Tool.from_name() or Tool.from_id()
    """
    def __init__(self, id, type, name, pretty_name):
        self._id = id
        self._type = type
        self._name = name
        self._pretty_name = pretty_name

    # Use properties to make it harder to accidentally change these values
    @property
    def id(self): return self._id
    @property
    def type(self): return self._type
    @property
    def name(self): return self._name
    @property
    def pretty_name(self): return self._pretty_name

    def valid(self):
        return self is not invalid_tool

    @staticmethod
    def from_name(name):
        return _name_map.get(name, invalid_tool)

    @staticmethod
    def from_id(id):
        return _id_map.get(id, invalid_tool)

_id_map = {
    {{#tools}}
        {{id}}: Tool({{id}}, u'{{type}}', u'{{name}}', u'{{pretty_name}}'),
    {{/tools}}
}

_name_map = {
    {{#tools}}
        u'{{name}}': _id_map[{{id}}],
    {{/tools}}
}

invalid_tool = _name_map['invalid_id']

valid_ids = sorted(set(t.id for t in _id_map.values() if t.valid()))
valid_tools = [Tool.from_id(i) for i in valid_ids]
