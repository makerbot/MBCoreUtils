# This context is used mostly for the toolhead initialization implementation

base_toolhead_metadata_dict = {
    "machine_toolheads": [
        # Elements are entirely machine-specific and are generated below. Ex:
        # {
        #     "name": "Bronx",
        #     "index": 0,
        #     "program_floc": "/usr/firmware/Bronx.hex",
        #     "toolhead_include": "bronx_toolhead_manager.hh"
        # },
    ]
}

import json


def append_machine_toolhead(toolhead_metadata):
    indices = map(lambda t: t['index'],
                  base_toolhead_metadata_dict['machine_toolheads'])
    if toolhead_metadata['index'] not in indices:
        base_toolhead_metadata_dict['machine_toolheads']\
            .append(toolhead_metadata)


def generate_context(**kwargs):
    if 'BWMACHINE_SETTINGS' in kwargs:
        with open(kwargs['BWMACHINE_SETTINGS']) as f:
            machine_config = json.load(f)
            if 'toolheads' in machine_config:
                for tool in machine_config['toolheads']:
                    tool_dict = machine_config['toolheads'][tool]
                    for tool_num in tool_dict['locations']:
                        toolhead_metadata = {
                            "name": ''.join([x.title()
                                             for x in tool.split('_')]),
                            "index": tool_num,
                            "program_floc": tool_dict['program'],
                            "toolhead_include": "{0}_toolhead_manager.hh"
                                                .format(tool.lower())
                        }
                        append_machine_toolhead(toolhead_metadata)

    return base_toolhead_metadata_dict
