error_dict = {
    "machine_errors": [
        {"use_base": "tool_critical", "name": "toolhead_no_response", "pretty_name": "Toolhead No Response", "id": 263},
        {"use_base": "tool_critical", "name": "toolhead_malformed_packet", "pretty_name": "Toolhead Malformed Packet", "id": 270},
        {"use_base": "tool_critical", "name": "toolhead_mismatch_api_version", "pretty_name": "Toolhead Mismatch Api Version", "id": 262},
        {"use_base": "tool_critical", "name": "could_not_send_toolhead_command", "pretty_name": "Could Not Send Toolhead Command", "id": 1038},
        {"use_base": "tool_critical", "name": "toolhead_not_initialized", "pretty_name": "Toolhead Not Initialized", "id": 272},
        {"use_base": "tool_critical", "name": "toolhead_feeder_sleep_interrupted", "pretty_name": "Toolhead Feeder Sleep Interrupted", "id": 1037},
        {"use_base": "tool_critical", "name": "eeprom_update_failed", "pretty_name": "Smart Extruder Update Failed", "id": 1045},
        {"use_base": "homing_problem", "name": "homing_not_completed", "pretty_name": "Homing Not Completed", "id": 1016},
        {"use_base": "homing_problem", "name": "unknown_homing_method", "pretty_name": "Unknown Homing Method", "id": 1025},
        {"use_base": "homing_problem", "name": "no_hes_log", "pretty_name": "No Hes Log", "id": 1023},
        {"use_base": "homing_problem", "name": "homing_timed_out", "pretty_name": "Homing Timed Out", "id": 1013},
        {"use_base": "homing_problem_stuck", "name": "hes_rebase_failed", "pretty_name": "Hes Rebase Failed", "id": 1022},
        {"use_base": "homing_problem_stuck", "name": "hes_log_overflow", "pretty_name": "Hes Log Overflow", "id": 1033},
        {"use_base": "homing_problem_stuck", "name": "bad_hes_waveforms", "pretty_name": "Bad Hes Waveforms", "id": 1032},
        {"use_base": "homing_problem_stuck", "name": "binary_search_out_of_range", "pretty_name": "Binary Search Out Of Range", "id": 1021},
        {"use_base": "homing_problem_stuck", "name": "no_valid_hes_slope", "pretty_name": "No Valid Hes Slope", "id": 1020},
        {"use_base": "print_file_error", "name": "json_toolpath_nothing_parsed", "pretty_name": "Json Toolpath Nothing Parsed", "id": 264},
        {"use_base": "print_file_error", "name": "json_toolpath_parse_error", "pretty_name": "Json Toolpath Parse Error", "id": 1011},
        {"use_base": "fw_fundamentally_broken", "name": "default_config_not_found", "pretty_name": "Default Config Not Found", "id": 1003},
        {"use_base": "fw_fundamentally_broken", "name": "default_config_missing_value", "pretty_name": "Default Config Missing Value", "id": 1005},
        {"use_base": "fw_fundamentally_broken", "name": "invalid_eeprom_filepath", "pretty_name": "Invalid Eeprom Filepath", "id": 1015},
        {"use_base": "fw_fundamentally_broken", "name": "default_config_parse_failure", "pretty_name": "Default Config Parse Failure", "id": 1004},
        {"use_base": "kaiten_error", "name": "critical_kaiten_error", "pretty_name": "Critical System Error", "id": 1500},
        {"use_base": "kaiten_error", "name": "kaiten_error", "pretty_name": "System Error", "id": 500},
        {"use_base": "misc_error", "name": "pru_initialization_failed", "pretty_name": "Pru Initialization Failed", "id": 1006},
        {"use_base": "misc_error", "name": "user_config_missing_value", "pretty_name": "User Config Missing Value", "id": 259},
        {"use_base": "misc_error", "name": "heat_zero_temperature", "pretty_name": "Heat Zero Temperature", "id": 267},
        {"use_base": "misc_error", "name": "suspend_no_valid_last_move", "pretty_name": "Suspend No Valid Last Move", "id": 1019},
        {"use_base": "misc_error", "name": "no_mac_address_set", "pretty_name": "No Mac Address Set", "id": 1036},
        {"use_base": "misc_error", "name": "heater_add_failure", "pretty_name": "Heater Add Failure", "id": 269},
        {"use_base": "misc_error", "name": "knob_not_tightened", "pretty_name": "Knob Not Tightened", "id": 1034},
        {"use_base": "misc_error", "name": "invalid_active_tool_setting", "pretty_name": "Invalid Active Tool Setting", "id": 278},
        {"use_base": "misc_error", "name": "unsupported_eeprom_version", "pretty_name": "Upload candidate EEPROM map is unsupported by the current tool", "id": 1044},
        {"use_base": "misc_error", "name": "toolhead_spi_config_error", "pretty_name": "Toolhead Spi Config Error", "id": 1017},
        {"use_base": "misc_error", "name": "heater_not_heating", "pretty_name": "Heater Not Heating", "id": 504},
        {"use_base": "misc_error", "name": "toolhead_command_tx_failure", "pretty_name": "Toolhead Command Tx Failure", "id": 1008},
        {"use_base": "misc_error", "name": "stop_iteration", "pretty_name": "Stop Iteration", "id": 287},
        {"use_base": "misc_error", "name": "invalid_file_type", "pretty_name": "Invalid File Type", "id": 1498},
        {"use_base": "misc_error", "name": "user_config_parse_failure", "pretty_name": "User Config Parse Failure", "id": 258},
        {"use_base": "misc_error", "name": "no_toolheads_detected", "pretty_name": "No Toolheads Detected", "id": 260},
        {"use_base": "misc_error", "name": "corrupted_firmware_file", "pretty_name": "Corrupted Firmware File", "id": 1031},
        {"use_base": "misc_error", "name": "z_pause_value_not_found", "pretty_name": "Z Pause Value Not Found", "id": 275},
        {"use_base": "misc_error", "name": "diagnostics_test_failed", "pretty_name": "Diagnostics Test Failed", "id": 297},
        {"use_base": "misc_error", "name": "invalid_acceleration_buffer_size", "pretty_name": "Invalid Acceleration Buffer Size", "id": 261},
        {"use_base": "misc_error", "name": "user_config_not_found", "pretty_name": "User Config Not Found", "id": 257},
        {"use_base": "misc_error", "name": "file_already_open", "pretty_name": "File Already Open", "id": 1499},
        {"use_base": "misc_error", "name": "buffer_full", "pretty_name": "Buffer Full", "id": 281},
        {"use_base": "misc_error", "name": "extrusion_distance_missing", "pretty_name": "Extrusion Distance Missing", "id": 277},
        {"use_base": "misc_error", "name": "parse_more", "pretty_name": "Parse More", "id": 280},
        {"use_base": "misc_error", "name": "invalid_tool_requested", "pretty_name": "Invalid Tool Requested", "id": 279},
        {"use_base": "misc_error", "name": "bad_tool_count_config", "pretty_name": "Bad Tool Count Config", "id": 299},
        {"use_base": "misc_error", "name": "resume_complete", "pretty_name": "Resume Complete", "id": 301},
        {"use_base": "misc_error", "name": "suspend_index_not_found", "pretty_name": "Suspend Index Not Found", "id": 1018},
        {"use_base": "misc_error", "name": "diagnostics_unknown_state_error", "pretty_name": "Diagnostics Unknown State Error", "id": 296},
        {"use_base": "misc_error", "name": "invalid_axis", "pretty_name": "Invalid Axis", "id": 265},
        {"use_base": "misc_error", "name": "ok", "pretty_name": "Ok", "id": 256},
        {"use_base": "misc_error", "name": "diagnostis_uknown_test_error", "pretty_name": "Diagnostis Uknown Test Error", "id": 298},
        {"use_base": "misc_error", "name": "invalid_heater_index", "pretty_name": "Invalid Heater Index", "id": 268},
        {"use_base": "misc_error", "name": "zero_length_move", "pretty_name": "Zero Length Move", "id": 271},
        {"use_base": "misc_error", "name": "file_transfer_timeout", "pretty_name": "File Transfer Timeout", "id": 1030},
        {"use_base": "misc_error", "name": "machine_driver_closed", "pretty_name": "Machine Driver Closed", "id": 274},
        {"use_base": "misc_error", "name": "not_implemented", "pretty_name": "Not Implemented", "id": 300},
        {"use_base": "misc_error", "name": "not_ready", "pretty_name": "Not Ready", "id": 266},
        {"use_base": "misc_error", "name": "machine_driver_failure", "pretty_name": "Machine Driver Failure", "id": 1501},
        {"use_base": "misc_error", "name": "invalid_endstop_type", "pretty_name": "Invalid Endstop Type", "id": 1035},
        {"use_base": "misc_error", "name": "file_not_found", "pretty_name": "File Not Found", "id": 1012},
        {"use_base": "misc_error", "name": "interface_led_comms_error", "pretty_name": "Interface Led Comms Error", "id": 288},
        {"use_base": "misc_error", "name": "power_monitor_i2c_failure", "pretty_name": "Power Monitor I2C Failure", "id": 295},
        {
            "use_base": False,
            "name": "tool_not_calibrated",
            "pretty_name": "Smart Extruder Not Calibrated",
            "title": "Run Calibration",
            "message": "Please run Z-Calibration before printing with this Smart Extruder",
            "error_type": "tool_error",
            "error_action": "calibrate_z",
            "id": 1046
        },
        {
            "use_base": False,
            "name": "no_build_plate",
            "pretty_name": "No Build Plate",
            "title": "No Build Plate",
            "message": "Please ensure your build plate is properly attached (Warning %d).",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1029
        },
        {
            "use_base": False,
            "name": "carriage_program_failure",
            "pretty_name": "Carriage Program Failure",
            "title": "Carriage Program Failed",
            "message": "The extruder carriage cannot be programmed (Error %d). Please visit our Support page at Makerbot.com/support.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1009
        },
        {
            "use_base": False,
            "name": "no_hes_change",
            "pretty_name": "No Hes Change",
            "title": "Homing Error",
            "message": "Homing failed (Error %d). Your Smart Extruder is not communicating. Please try again.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1024
        },
        {
            "use_base": False,
            "name": "both_sides_too_high",
            "pretty_name": "Both Sides Too High",
            "title": "Leveling Error",
            "message": "Leveling failed (Error %d). Your extruder nozzle may be stuck. Please try again.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1027
        },
        {
            "use_base": False,
            "name": "leveling_with_filament",
            "pretty_name": "Leveling With Filament",
            "title": "Clear Filament",
            "message": "Please remove filament from the Smart Extruder before proceeding (Warning %d).",
            "error_type": "none",
            "error_action": "unload_filament",
            "id": 1028
        },
        {
            "use_base": False,
            "name": "print_tool_connect_failed",
            "pretty_name": "Print Tool Connect Failed",
            "title": "Extruder Error",
            "message": "Smart Extruder Connect Failed (Error %d).  Please disconnect your Smart Extruder and try again.",
            "error_type": "tool_error",
            "error_action": "acknowledge",
            "id": 1014
        },
        {
            "use_base": False,
            "name": "chamber_program_failure",
            "pretty_name": "Chamber Program Failure",
            "title": "Chamber Program Failed",
            "message": "The build chamber heater controller cannot be programmed (Error %d). Please visit our Support page at Makerbot.com/support.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1010
        },
        {
            "use_base": False,
            "name": "z_pause",
            "pretty_name": "Z Pause",
            "title": "Print Paused",
            "message": "Paused your print. (TODO-This probably shouldn't be an error? #checkoutmysushitho %d)",
            "error_type": "zpause",
            "error_action": "zpaused",
            "id": 501
        },
        {
            "use_base": False,
            "name": "move_command_outside_axis_bounds",
            "pretty_name": "Move Command Outside Axis Bounds",
            "title": "File Error",
            "message": "Error %d: Please make sure that your .makerbot file is prepared for the correct printer type.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1039
        },
        {
            "use_base": False,
            "name": "toolhead_not_heating",
            "pretty_name": "Toolhead Not Heating",
            "title": "Heating Error",
            "message": "DO NOT touch the extruder as it may be very hot (Error %d). Please visit our Support page at Makerbot.com/support.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1001
        },
        {
            "use_base": False,
            "name": "out_of_filament",
            "pretty_name": "Out of Filament",
            "title": "Out of Filament",
            "message": "Please wait while your Smart Extruder unloads any leftover filament. (Warning %d)",
            "error_type": "filament_error",
            "error_action": "change_filament",
            "id": 1041
        },
        {
            "use_base": False,
            "name": "no_filament_loaded",
            "pretty_name": "No Filament",
            "title": "No Filament",
            "message": "Please load filament before starting your print. (Warning %d)",
            "error_type": "filament_error",
            "error_action": "change_filament",
            "id": 1040
        },
        {
            "use_base": False,
            "name": "printing_network_error",
            "pretty_name": "Network Error",
            "title": "Network Error",
            "message": "There was a problem communicating with MakerBot Cloud Services. Please try your print again later. (Warning %d)",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1042
        },
        {
            "use_base": False,
            "name": "cloud_slicing_error",
            "pretty_name": "Slicing Error",
            "title": "Slicing Error",
            "message": "Failed to slice your layout for printing. Please try again later. (Warning %d)",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1043
        },
        {
            "use_base": False,
            "name": "operation_timed_out",
            "pretty_name": "Internal Timeout",
            "message": "Internal operation timed out. Please contact Support.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 1100
        }
    ],

    "toolhead_errors": [
        {"use_base": "tool_problem", "name": "thermocouple_out_of_range", "pretty_name": "Thermocouple Out Of Range", "id": 66},
        {"use_base": "tool_problem", "name": "thermocouple_unplugged", "pretty_name": "Thermocouple Unplugged", "id": 67},
        {"use_base": "tool_problem", "name": "thermocouple_too_hot", "pretty_name": "Thermocouple Too Hot", "id": 68},
        {"use_base": "tool_problem", "name": "thermocouple_communication_failure", "pretty_name": "Thermocouple Communication Failure", "id": 65},
        {"use_base": "tool_problem", "name": "thermocouple_data_unchanging", "pretty_name": "Thermocouple Data Not Changing", "id": 75},
        {"use_base": "tool_problem", "name": "thermocouple_data_invalid", "pretty_name": "Thermocouple Data Invalid", "id": 69},
        {"use_base": "tool_critical", "name": "heater_short", "pretty_name": "Heater Short", "id": 50},
        {"use_base": "tool_critical", "name": "filament_fan_short", "pretty_name": "Filament Fan Short", "id": 52},
        {"use_base": "tool_critical", "name": "filament_fan_open", "pretty_name": "Filament Fan Open", "id": 73},
        {"use_base": "tool_critical", "name": "heater_temperature_overrun_triggered", "pretty_name": "Heater Temperature Overrun Triggered", "id": 58},
        {"use_base": "tool_critical", "name": "tool_short", "pretty_name": "Tool Short", "id": 49},
        {"use_base": "tool_critical", "name": "unsupported_tool", "pretty_name": "Unsupported Tool", "id": 85},
        {"use_base": "tool_critical", "name": "tool_fan_short", "pretty_name": "Tool Fan Short", "id": 51},
        {"use_base": "tool_critical", "name": "heater_temperature_sag_triggered", "pretty_name": "Heater Temperature Sag Triggered", "id": 57},
        {"use_base": "tool_critical", "name": "tool_fan_open", "pretty_name": "Tool Fan Open", "id": 72},
        {"use_base": "tool_critical", "name": "heater_rise_watchdog_triggered", "pretty_name": "Heater Rise Watchdog Triggered", "id": 55},
        {"use_base": "tool_critical", "name": "watchdog_triggered", "pretty_name": "Watchdog Triggered", "id": 11},
        {"use_base": "tool_critical", "name": "motor_over_current", "pretty_name": "Motor Over Current", "id": 53},
        {"use_base": "tool_critical", "name": "tool_checksum_fail", "pretty_name": "Tool Checksum Fail", "id": 87},
        {"use_base": "tool_critical", "name": "tool_read_error", "pretty_name": "Tool Read Error", "id": 86},
        {"use_base": "tool_critical", "name": "tool_open", "pretty_name": "Tool Open", "id": 70},
        {"use_base": "tool_critical", "name": "eeprom_checksum_failure", "pretty_name": "Eeprom Checksum Failure", "id": 95},
        {"use_base": "fw_fundamentally_broken", "name": "mismatch_api_version", "pretty_name": "Mismatch Api Version", "id": 130},
        {"use_base": "chamber_problem", "name": "chamber_heater_failure", "pretty_name": "Chamber Heater Failure", "id": 98},
        {"use_base": "chamber_problem", "name": "chamber_fan_failure", "pretty_name": "Chamber Fan Failure", "id": 99},
        {"use_base": "chamber_problem", "name": "chamber_heater_disconnected", "pretty_name": "Chamber Heater Disconnected", "id": 97},
        {"use_base": "chamber_problem", "name": "chamber_thermistor_disconnected", "pretty_name": "Chamber Thermistor Disconnected", "id": 96},
        {"use_base": "chamber_problem", "name": "heater_over_temp", "pretty_name": "Heater Over Temp", "id": 74},
        {"use_base": "chamber_problem", "name": "chamber_temperature_overrun", "pretty_name": "Chamber Temperature Overrun", "id": 100},
        {"use_base": "misc_error", "name": "heater_open", "pretty_name": "Heater Open", "id": 71},
        {"use_base": "misc_error", "name": "invalid_response", "pretty_name": "Invalid Response", "id": 12},
        {"use_base": "misc_error", "name": "eeprom_slave_missed_value", "pretty_name": "Eeprom Slave Missed Value", "id": 133},
        {"use_base": "misc_error", "name": "eeprom_fatal_internal_error", "pretty_name": "Eeprom Fatal Internal Error", "id": 136},
        {"use_base": "misc_error", "name": "invalid_encoder_resolution", "pretty_name": "Invalid Encoder Resolution", "id": 88},
        {"use_base": "misc_error", "name": "eeprom_start_failure", "pretty_name": "Eeprom Start Failure", "id": 132},
        {"use_base": "misc_error", "name": "eeprom_out_of_date", "pretty_name": "Eeprom Out Of Date", "id": 137},
        {"use_base": "misc_error", "name": "none", "pretty_name": "None", "id": 0},
        {"use_base": "misc_error", "name": "thermocouple_adc_busy", "pretty_name": "Thermocouple Adc Busy", "id": 129},
        {"use_base": "misc_error", "name": "eeprom_unknown_version", "pretty_name": "Eeprom Unknown Version", "id": 135},
        {"use_base": "misc_error", "name": "eeprom_id_verify_fail", "pretty_name": "Eeprom Id Verify Fail", "id": 134},
        {"use_base": "misc_error", "name": "command_index_mismatch", "pretty_name": "Command Index Mismatch", "id": 14},
        {"use_base": "misc_error", "name": "eeprom_no_slave_ack", "pretty_name": "Eeprom No Slave Ack", "id": 131},
        {"use_base": "misc_error", "name": "ac_power_disconnected", "pretty_name": "AC Power Disconnected", "id": 47},
        {"use_base": "misc_error", "name": "busy", "pretty_name": "Busy", "id": 138},
        {"use_base": "misc_error", "name": "empty_eeprom_cache", "pretty_name": "Empty EEPROM Cache", "id": 139},
        {"use_base": "misc_error", "name": "eeprom_write_failure", "pretty_name": "EEPROM Write Failure", "id": 140},
        {"use_base": "misc_error", "name": "eeprom_verify_failure", "pretty_name": "EEPROM Verify Failure", "id": 141},
        {
            "use_base": False,
            "name": "no_filament",
            "pretty_name": "No Filament",
            "title": "Out of Filament",
            "message": "This process requires filament to proceed. (Warning %d)",
            "error_type": "filament_error",
            "error_action": "change_filament",
            "id": 80
        },
        {
            "use_base": False,
            "name": "door_interlock_triggered",
            "pretty_name": "Door Interlock Triggered",
            "title": "Chamber Open",
            "message": "The heated build chamber is open (Warning %d). Please close the door to continue.",
            "error_type": "chamber_error",
            "error_action": "acknowledge",
            "id": 48
        },
        {
            "use_base": False,
            "name": "heater_hold_watchdog_triggered",
            "pretty_name": "Heater Hold Watchdog Triggered",
            "title": "Extruder Cooling",
            "message": "Your extruder cools down if the printer stays idle for a few minutes.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 56
        },
        {
            "use_base": False,
            "name": "filament_slip",
            "pretty_name": "Filament Slip",
            "title": "Filament Jam",
            "message": "Your filament seems to be jammed (Error %d). Please unload your remaining filament, and then reload it to continue printing.",
            "error_type": "filament_error",
            "error_action": "change_filament",
            "id": 81
        },
        {
            "use_base": False,
            "name": "no_tool_connected",
            "pretty_name": "No Tool Connected",
            "title": "Extruder Error",
            "message": "Your Smart Extruder is not connected (Error %d). Please reconnect your Smart Extruder.",
            "error_type": "tool_error",
            "error_action": "attach_tool",
            "id": 54
        },
        {
            "use_base": False,
            "name": "bad_tool_connected",
            "pretty_name": "Bad Tool Connected",
            "title": "Extruder Error",
            "message": "Your Smart Extruder has been corrupted (Error %d). Please visit our Support page at Makerbot.com/support.",
            "error_type": "tool_error",
            "error_action": "acknowledge",
            "id": 46
        },
        {
            "use_base": False,
            "name": "not_connected",
            "pretty_name": "Toolhead Not Connected",
            "title": "Toolhead Disconnect",
            "message": "Toolhead disconnected (Error %d). Please visit our Support page at Makerbot.com/support.",
            "error_type": "none",
            "error_action": "acknowledge",
            "id": 13,
            "alt_ids": [{"id": 15}, {"id": 16}],
            "per_source": [
                {
                    "source_type": "chamber",
                    "pretty_name": "Chamber Not Connected",
                    "title": "Chamber Heater Disconnect",
                    "message": "The build chamber heater controller is disconnected (Error %d). Please visit our Support page at Makerbot.com/support."
                },
                {
                    "source_type": "extruder",
                    "pretty_name": "Carriage Not Connected",
                    "title": "Carriage Disconnected",
                    "message": "The extruder carriage is disconnected from the machine (Error %d). Please visit our Support page at Makerbot.com/support."
                }
            ]
        }
    ],

    "error_bases": [
        {
            "name": "tool_problem",
            "title": "Extruder Error",
            "message": "Oops, we have a problem with your Smart Extruder (Error %d: %s). Please disconnect and reconnect your Smart Extruder.",
            "error_type": "tool_error",
            "error_action": "acknowledge"
        },
        {
            "name": "tool_critical",
            "title": "Extruder Error",
            "message": "Oops, we have a problem with your Smart Extruder (Error %d: %s). Please visit our Support page at Makerbot.com/support.",
            "error_type": "tool_error",
            "error_action": "acknowledge"
        },
        {
            "name": "homing_problem",
            "title": "Homing Error",
            "message": "Homing failed (Error %d: %s). Please try again.",
            "error_type": "none",
            "error_action": "acknowledge"
        },
        {
            "name": "homing_problem_stuck",
            "title": "Homing Error",
            "message": "Homing failed (Error %d: %s). Your extruder nozzle may be stuck. Please try again.",
            "error_type": "none",
            "error_action": "acknowledge"
        },
        {
            "name": "print_file_error",
            "title": "Print Error",
            "message": "Invalid print file (Error %d: %s). Please try to prepare again in MakerBot Desktop.",
            "error_type": "none",
            "error_action": "acknowledge"
        },
        {
            "name": "fw_fundamentally_broken",
            "title": "System Error",
            "message": "Oops, we have a problem (Error %d: %s). Please update your firmware using MakerBot Desktop.",
            "error_type": "none",
            "error_action": "acknowledge"
        },
        {
            "name": "kaiten_error",
            "title": "System Error",
            "message": "Oops, we have a problem (Error %d: %s).",
            "error_type": "none",
            "error_action": "acknowledge"
        },
        {
            "name": "chamber_problem",
            "title": "Chamber Error",
            "message": "There is a problem with your chamber heater (Error %d: %s). Please visit our Support page at Makerbot.com/support.",
            "error_type": "none",
            "error_action": "acknowledge"
        },
        {
            "name": "misc_error",
            "title": "System Error",
            "message": "Oops, we have a problem (Error %d: %s).",
            "error_type": "none",
            "error_action": "acknowledge"
        }
    ],

    "error_type_enum": [
        {"name": "none", "value": 0},
        {"name": "tool_error", "value": 1},
        {"name": "filament_error", "value": 2},
        {"name": "general_error", "value": 3},
        {"name": "zpause", "value": 4},
        {"name": "sad_bot", "value": 5},
        {"name": "chamber_error", "value": 6}
    ],

    "error_action_enum": [
        {"name": "acknowledge", "value": 0},
        {"name": "change_filament", "value": 1},
        {"name": "preheat_timeout", "value": 2},
        {"name": "zpaused", "value": 3},
        {"name": "unload_filament", "value": 4},
        {"name": "attach_tool", "value": 5},
        {"name": "calibrate_z", "value": 6}
    ]
}


def has_key(obj, key):
    if isinstance(obj, dict):
        return key in obj or any(has_key(v, key) for v in obj.itervalues())
    elif isinstance(obj, list):
        return any(has_key(o, key) for o in obj)
    else:
        return False


# Switch keys are used to specialize errors based on additional
# information.  To use a key <KEY> in a given error, a "per_<KEY>"
# field must be present and contain a list of dicts that contain
# a "<KEY>_type" field and one of more overrides for other error
# fields.  To use multiple keys, they must be nested in the
# following order:
SWITCH_KEYS = ('source', 'process', 'process_step')


def validate_error(error, loc_msg, switch_keys=SWITCH_KEYS):
    """
    Verify that switch keys are used correctly.  This also adds an empty
    dict to the end of every switch list to generate default cases.
    """
    def nest_error(key):
        raise Exception('In %s, %s improperly nested' % (loc_msg, key))
    top_key = 'per_'+switch_keys[0]
    if top_key in error:
        switch_list = error[top_key]
        del error[top_key]
        for key in ['per_'+s for s in switch_keys]:
            if has_key(error, key):
                nest_error(key)
        if not isinstance(switch_list, list):
            raise Exception('In %s, %s must be a list' % (loc_msg, top_key))
        type_name = switch_keys[0]+'_type'
        for sub_dict in switch_list:
            if type_name not in sub_dict:
                raise Exception('In %s, all %s entries must contain %s' %
                                (loc_msg, top_key, type_name))
            if has_key(sub_dict, top_key):
                nest_error(top_key)
            if len(switch_keys) > 1:
                validate_error(sub_dict, loc_msg, switch_keys[1:])
        switch_list.append({})
        error[top_key] = switch_list
    elif has_key(error, top_key):
        nest_error(top_key)
    elif len(switch_keys) > 1:
        validate_error(error, loc_msg, switch_keys[1:])


def err_id_fill(error, loc_msg, id=None):
    """ Fill in the error id at codegen time. """
    if id is None and 'id' in error:
        id = error['id']
    if 'message' in error and '%d' in error['message']:
        error['message'] = error['message'] % id
    for val in error.values():
        if isinstance(val, list):
            for sub_dict in val:
                err_id_fill(sub_dict, loc_msg, id)


def generate_context(env, target, source):
    for key in SWITCH_KEYS:
        error_dict['per_'+key] = True

    for error in error_dict['machine_errors']:
        if has_key(error, 'per_source'):
            raise Exception('Machine error %s cannot depend on toolhead source'
                            % error.get('name', repr(error)))

    all_errors = []
    for dname in ('machine_errors', 'toolhead_errors'):
        for error in error_dict[dname]:
            loc_msg = '%s in %s' % (error.get('name', repr(error)), dname)
            validate_error(error, loc_msg)
            err_id_fill(error, loc_msg)
            all_errors.append(error)
    error_dict['all_errors'] = all_errors

    return error_dict
