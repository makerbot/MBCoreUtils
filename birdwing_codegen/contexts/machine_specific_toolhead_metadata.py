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
    base_toolhead_metadata_dict['machine_toolheads'].append(toolhead_metadata)


def generate_context(env, target, source):
    if 'MBCOREUTILS_BWMACHINE_SETTINGS' in env:
        with open(env['MBCOREUTILS_BWMACHINE_SETTINGS']) as f:
            machine_config = json.load(f)
            if 'Toolheads' in machine_config:
                for tool in machine_config['Toolheads']:
                    tool_dict = machine_config['Toolheads'][tool]
                    for tool_num in tool_dict['Locations']:
                        toolhead_metadata = {
                            "name": tool,
                            "index": tool_num,
                            "program_floc": tool_dict['Program'],
                            "toolhead_include": "{0}_toolhead_manager.hh"
                                                .format(tool.lower())
                        }
                        append_machine_toolhead(toolhead_metadata)

    return base_toolhead_metadata_dict
