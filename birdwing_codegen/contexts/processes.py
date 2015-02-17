base_steps = [
    "running",
    "cancelling",
    "cleaning_up",
    "done",
]

print_steps = [
    "initializing",
    "initial_heating",
    "final_heating",
    "cooling",
    "homing",
    "position_found",
    "preheating_resuming",
    "calibrating",
    "printing",
    "end_sequence",
    "cancelling",
    "suspending",
    "suspended",
    "unsuspending",
    "preheating_loading",
    "preheating_unloading",
    "loading_filament",
    "unloading_filament",
    "stopping_filament",
    "cleaning_up",
    "clear_build_plate",
    "loading_print_tool",
]

filament_steps = [
    "preheating",
    "extrusion",
]

processes = [
    {"name": "AssistedLevelingProcess", "steps": [
        "preheating",
        "cooling",
        "initializing",
        "checking_first_point",
        "checking_front_level",
        "leveling_front",
        "leveling_front_inverse",
        "checking_side_level",
        "leveling_side",
        "leveling_side_inverse",
        "calibrating_z_offset",
        "finishing_level",
        "preheating_unloading",
        "unloading_filament",
    ]},
    {"name": "BronxUploadProcess"},
    {"name": "DiagnosticProcess"},
    {"name": "DRMPrintProcess", "steps": print_steps},
    {"name": "FirmwareBurningProcess", "steps": [
        "transfer",
        "verify_firmware",
        "writing",
    ]},
    {"name": "FirmwareCleanupProcess"},
    {"name": "HomingProcess"},
    {"name": "LibraryPrintProcess", "steps": print_steps + [
        "slice_queued",
        "slicing",
        "downloading",
    ]},
    {"name": "LoadFilamentProcess", "steps": filament_steps},
    {"name": "UnloadFilamentProcess", "steps": filament_steps},
    {"name": "ManualLevelingProcess", "steps": [
        "manual_steps",
        "traveling",
        "leveling_front",
        "leveling_side",
        "finishing_level",
    ]},
    {"name": "ParkProcess"},
    {"name": "PreheatProcess"},
    {"name": "PrintProcess", "steps": print_steps},
    {"name": "QueueProcess"},
    {"name": "ResetToFactoryProcess"},
    {"name": "YonkersUploadProcess"},
    {"name": "ZipLogsProcess"},
    {"name": "ZCalibrationProcess", "steps": [
        "initializing",
        "cooling",
        "preheating",
    ]},
]


def list_merge(*lists):
    return sorted(list(reduce(lambda a, b: a | b, map(set, lists))))


def generate_context(env, target, source):
    steps = list_merge(base_steps, *[p.get('steps', []) for p in processes])
    for process in processes:
        process['steps'] = list_merge(base_steps, process.get('steps', []))
        process['str'] = process['name']
    return {
        "process_types": processes,
        "process_steps": [{"name": s, "str": s} for s in steps],
    }
