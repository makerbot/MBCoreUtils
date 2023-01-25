import os.path
from os import listdir
from os.path import isfile, join, splitext, basename
from pystache import Renderer
import json
from jackson_mustache_codegen import transform_context


def get_files_from_dir(directory: str, extension: str = '') -> list[str]:
    dir_files = [
        join(directory, ff) for ff in listdir(directory)
        if isfile(join(directory, ff))
    ]
    if extension:
        dir_files = [ff for ff in dir_files if splitext(ff)[-1] == extension]
    return dir_files


def generate_mustached_file(content_path: str, context: dict, output_path: str):
    with open(content_path, 'r') as ff:
        content = ff.read()
    renderer = Renderer()
    rendered = renderer.render(content, context)
    with open(output_path, 'w') as ff:
        ff.write(rendered)


def read_json(json_path: str) -> dict:
    with open(json_path, 'r') as ff:
        context = json.load(ff)
    return context


def mass_mustache_render(template_paths: list[str], context_paths: list[str], context_transform: dict = None,
                         output_dir: str = None) -> None:
    if output_dir is None:
        output_dir = os.getcwd()
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    contexts = [read_json(foo) for foo in context_paths]
    transformed_contexts = [transform_context(foo, context_transform) for foo in contexts]
    total_context = {}
    for tc in transformed_contexts:
        total_context.update(tc)
    for template_path in template_paths:
        filename = basename(template_path)
        outpath = join(output_dir, filename)
        generate_mustached_file(template_path, total_context, outpath)
