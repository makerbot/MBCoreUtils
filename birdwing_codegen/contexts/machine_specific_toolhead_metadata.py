# This context is used mostly for the toolhead initialization implementation

base_toolhead_metadata_dict = {
    "machine_toolheads": [
        # Elements are entirely machine-specific and will be generated below.  Example format:
        #{
        #    "name": "Bronx",
        #    "index": 0,
        #    "program_floc": "/usr/firmware/Bronx.hex",
        #    "toolhead_manager_include": "bronx_toolhead_manager"
        #},
    ]
}

import json

def append_machine_toolhead(toolhead_metadata):
    base_toolhead_metadata_dict['machine_toolheads'].append(toolhead_metadata)

def generate_context(env, target, source):
    if 'MBCOREUTILS_BWMACHINE_SETTINGS' in env:
        with open(env['MBCOREUTILS_BWMACHINE_SETTINGS']) as f:
            machine_settings_config = json.load(f)
            if 'Toolheads' in machine_settings_config:
                for tool in machine_settings_config['Toolheads']:
                    for tool_num in machine_settings_config['Toolheads'][tool]['Locations']:
                        toolhead_metadata = {
                            "name": tool,
                            "index": tool_num,
                            "program_floc": machine_settings_config['Toolheads'][tool]['Program'],
                            "toolhead_manager_include": "{0}_toolhead_manager.hh".format(tool.lower())
                        }
                        append_machine_toolhead(toolhead_metadata)

    return base_toolhead_metadata_dict