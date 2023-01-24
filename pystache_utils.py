import os.path
from os import listdir
from os.path import isfile, join, splitext, basename
from pystache import Renderer
import json


def get_files_from_dir(directory: str, extension: str ='') -> list[str]:
    dir_files = [
        join(directory, ff) for ff in listdir(directory)
        if isfile(join(directory, ff))
    ]
    if (extension):
        dir_files = [ff for ff in dir_files if splitext(ff)[-1] == extension]
    return dir_files

def apply_multi_contexts(content: str, contexts: list[dict]) -> str:
    renderer = Renderer()
    for context in contexts:
        content = renderer.render(content, context)
    return content


def generate_mustached_file(content_path: str, contexts: list[dir], output_path: str):
    with open(content_path, 'r') as ff:
        content = ff.read()
    rendered = apply_multi_contexts(content, contexts)
    with open(output_path, 'w') as ff:
        ff.write(rendered)
    

def load_all_contexts(context_dirs: list[str]) -> list[dict]:
    context_files = []
    for dir in context_dirs:
        context_files += get_files_from_dir(dir, extension='.json')
    contexts = []
    for file in context_files:
        with open(file, 'r') as ff:
            context = json.load(ff)
        contexts.append(context)
    return contexts


def mass_mustache_render(contents_dirs: list[str], context_dirs: list[str], output_dir: str) -> None:
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    contexts = load_all_contexts(context_dirs)
    for dir in contents_dirs:
        content_files = get_files_from_dir(dir)
        for content_file in content_files:
            filename = basename(content_file)
            outpath = join(output_dir, filename)
            generate_mustached_file(content_file, contexts, outpath)