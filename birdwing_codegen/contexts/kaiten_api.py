import json
import os
import subprocess

api_dict = {'kaiten_api': []}


def add_metadata(api):
    for fidx, func in enumerate(api):
        # both api func params & api funcs have a 'name' key, making it
        # impossible to reference the parent api func while parsing its
        # parameters. create a unique 'fn_name' key that codegen templates can
        # use to insert the parent rpc func name while iterating the params.
        api[fidx]['fn_name'] = func['name']
        for pidx, param in enumerate(func['parameters']):
            if 'default' in param:
                # params are marked as being optional by the presence of a
                # 'default' key. the 'default' key is often set to null,
                # indicating the param is optional. this causes issues, as
                # mustache evaluates both the absense of keys and keys set to
                # null as False.  A null key vs an absent key has different
                # semantics, so create a bool for params that explicitly
                # indicates whether its optional.
                api[fidx]['parameters'][pidx]['optional'] = True
                # below flag is used to test if func has optional params w/out
                # iterating through params. if true, an extra func can be
                # generated in templates that only takes required params and a
                # callback (for convenience - opt params are often unused):
                api[fidx]['optional_params'] = True
    return api


def locate_apigen(path, depth=2):
    if os.path.isfile(path):
        return path
    elif depth:
        return locate_apigen(os.path.join(os.pardir, path), depth - 1)


def generate_context(env, target, source):
    # todo(jacksonh): check for env variable pointing to api_docgen.py
    apigen_path = locate_apigen(os.path.join(os.pardir, 'Birdwing-Software',
                                'firmware', 'kaiten', 'api_docgen.py'))
    if apigen_path:
        api = json.loads(subprocess.check_output(
                         ['python3', apigen_path, '-l 3']))
        api_dict['kaiten_api'] = add_metadata(api)
    elif 'BW_TOOLCHAIN_BUILD' in env:
        raise Exception('Unable to locate %s, required for birdwing builds!'
                        % apigen_path)
    return api_dict
