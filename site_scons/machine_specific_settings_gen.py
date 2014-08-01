from collections import OrderedDict
import json

def _write_json(data, filename):
    with open(filename, 'w') as out:
        json.dump(data, out, indent=4, separators=(',', ': '))
        out.write('\n')

def _update(base, overrides):
    # update values in base with overrides
    # unlike dict's .update() method, this is recursive,
    # so handles updates in subdicts 
    for k, v in overrides.items():
        if isinstance(v, OrderedDict):
            base[k] = _update(base.get(k, {}), v)
        else:
            base[k] = v
    return base

def gen_machine_specific_settings(env, target, source):
    # sources should generally be [xx_settings.json, xx_settings.json.machine]
    # order matters for sources!
    # use ordered dict to keep key order
    # THIS SHOULD BE THE SAME LOGIC AS "generate_settings_action" in Birdwing-Software/firmware/settings/SConscript!
    settings = OrderedDict()
    for filename in source:
        with open(str(filename), 'r') as sf:
            overrides = json.loads(sf.read(), object_pairs_hook=OrderedDict)
            _update(settings, overrides)
    _write_json(settings, str(target[0]))
