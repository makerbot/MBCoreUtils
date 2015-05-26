base_structs_dict = {
    "structs": [
        {
            "name": "toolhead",
            "inherits": False,
            "fields": [
                {"name": "tool_id", "type": "uint8"},
                {"name": "error", "type": "uint8"},
                {"name": "preheating", "type": "uint8"},
                {"name": "target_temperature", "type": "int16"},
                {"name": "current_temperature", "type": "int16"}
            ]
        },
        {
            "name": "bronx_toolhead",
            "inherits": "toolhead",
            "fields": [
                {"name": "filament_fan_running", "type": "bool"},
                {"name": "encoder_adc", "type": "uint16"},
                {"name": "filament_presence", "type": "bool"},
                {"name": "extrusion_percent", "type": "uint8"},
                {"name": "filament_jam", "type": "bool"}
            ]
        },
        {
            "name": "chamber_toolhead",
            "inherits": "toolhead",
            "fields": [
                {"name": "door_open", "type": "bool"},
                {"name": "fan_duty", "type": "uint8"},
                {"name": "heater_duty", "type": "uint8"},
                {"name": "otp_triggered", "type": "bool"},
                {"name": "heater_temp", "type": "uint16"},
                {"name": "fan_setpoint_hz", "type": "uint8"},
                {"name": "heater_setpoint_c", "type": "uint8"},
                {"name": "fan_speed_hz", "type": "uint8"},
                {"name": "control_regime", "type": "uint8"}
            ]
        },
        {
            "name": "u1extruder_toolhead",
            "inherits": "toolhead",
            "fields": [
                {"name": "extrusion_percent", "type": "uint8"},
                {"name": "filament_presence", "type": "bool"},
                {"name": "filament_jam", "type": "bool"},
                {"name": "current_mag", "type": "int32"},
                {"name": "filament_fan_running", "type": "bool"},
                {"name": "encoder_adc", "type": "uint16"},
            ]
        },
        {
            "name": "u1chamber_toolhead",
            "inherits": "toolhead",
            "fields": [
                {"name": "fan", "type": "bool"},
                {"name": "w200_heater", "type": "bool"},
                {"name": "w400_heater", "type": "bool"},
                {"name": "w200_heater_temp", "type": "uint16"},
                {"name": "w400_heater_temp", "type": "uint16"},
                {"name": "fan_setpoint_pc", "type": "uint8"},
                {"name": "w200_heater_setpoint_c", "type": "uint8"},
                {"name": "w400_heater_setpoint_c", "type": "uint8"},
                {"name": "control_regime", "type": "uint8"}
            ]
        },
        {
            "name": "machine_response",
            "inherits": False,
            "fields": [
                {"name": "preheat_percent", "type": "uint8"},
                {"name": "move_buffer_available_space", "type": "uint8"},
                {"name": "machine_error", "type": "uint16"}
                # Machine-specific toolhead struct fields will be appended here
            ]
        }
    ],
    "utility": [
        {
            "name": "tool_usage",
            "fields": [
                {"name": "retract_count", "type": "uint32", "default": "0"},
                {"name": "extrusion_time_s", "type": "uint32", "default": "0"},
                {"name": "extrusion_distance_mm", "type": "uint32",
                 "default": "0"},
                {"name": "refurb_count", "type": "uint8", "default": "0"}
            ]
        }
    ]
}

import json


def append_machine_response_field(field):
    for struct in base_structs_dict['structs']:
        if struct['name'] == 'machine_response':
            if field['name'] not in map(lambda f: f['name'], struct['fields']):
                struct['fields'].append(field)


def generate_context(**kwargs):
    if 'BWMACHINE_SETTINGS' in kwargs:
        with open(kwargs['BWMACHINE_SETTINGS']) as f:
            machine_settings_config = json.load(f)
            if 'toolheads' in machine_settings_config:
                for tool in machine_settings_config['toolheads']:
                    tool_dict = machine_settings_config['toolheads'][tool]
                    for tool_num in tool_dict['locations']:
                        struct_field = {
                            "name": "toolhead_{0}_status".format(tool_num),
                            "type": "{0}_toolhead".format(tool.lower())
                        }
                        append_machine_response_field(struct_field)

    return base_structs_dict
