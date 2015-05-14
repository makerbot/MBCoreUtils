base_enums_dict = {
    "enums": [
        {
            "name": "leveling_states",
            "values": [
                {"name": "too_high", "value": 1},
                {"name": "too_low", "value": 0},
                {"name": "wrong_way", "value": 3},
                {"name": "just_right", "value": 2}
            ]
        },
        {
            "name": "leveling_knobs",
            "values": [
                # These names are capitalized here because the python bindings
                # specifically need them to be, while every other enum name for
                # python is formatted like "enum_name".
                {"name": "Knob1", "value": 1},
                {"name": "Fixed", "value": 0},
                {"name": "Knob2", "value": 2}
            ]
        },
        {
            "name": "power_monitor_rail",
            "values": [
                {"name": "5v", "value": 0},
                {"name": "12v", "value": 1}
            ]
        },
        {
            "name": "power_monitor_value",
            "values": [
                # Same deal here as leveling_knobs
                {"name": "Current", "value": 0},
                {"name": "Voltage", "value": 1}
            ]
        },
        {
            "name": "constants",
            "values": [
                {"name": "axis_count", "value": 4},
                {"name": "warning_threshold", "value": 500},
                {"name": "toolhead_warning_threshold", "value": 128},
                {"name": "pru_buffer_size", "value": 1170},
                {"name": "machine_error_threshold", "value": 2000},
                {"name": "toolhead_version_bytes", "value": 2},
                {"name": "process_error_threshold", "value": 1000},
                # Machine-specific constants will be appended here.
                # (currently only expected_toolhead_count)
            ]
        }
    ]
}

import json


def append_constant_once(c):
    for enum in base_enums_dict['enums']:
        if enum['name'] == 'constants':
            if c['name'] not in [n['name'] for n in enum['values']]:
                enum['values'].append(c)


def generate_context(**kwargs):
    if 'BWMACHINE_SETTINGS' in kwargs:
        with open(kwargs['BWMACHINE_SETTINGS']) as f:
            machine_settings_config = json.load(f)
            tool_count = 0
            if "toolheads" in machine_settings_config:
                for tool in machine_settings_config['toolheads']:
                    tool_count += len(
                        machine_settings_config["toolheads"][tool]["locations"]
                    )
            expected_toolhead_count_constant = {
                "name": "expected_toolhead_count",
                "value": tool_count
            }
            append_constant_once(expected_toolhead_count_constant)

    return base_enums_dict
