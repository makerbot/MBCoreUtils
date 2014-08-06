# Birdwing Code Generation using Mustache
=========================================

We do some of our code generation utilizing a templating system called [Mustache](http://mustache.github.io), specifically the [python implementation (Pystache)](https://github.com/defunkt/pystache).  To avoid additional dependencies, a copy of Pystache is included directly in the MBCoreUtils source tree, under *[site_scons/lib/pystache](../site_scons/lib/pystache)*.

The [mustache demo](http://mustache.github.io/#demo) provides a good introduction to Mustache's syntax and capabilities.

Mustache has some limitations that make multi-language code generation tricky, so additional logic ([transformations](#transformations_brief)) has been implemented on top of Pystache to make it easier.


## Overview
-----------
The code generation system consists of four primary components:

- <a name="contexts_brief"></a>[**Contexts**](#contexts)
  - Contexts are located in *[birdwing_codegen/contexts/\<context file\>](contexts)*. They contain the data model that is processed using transformations, and then substituted into templates to render the final codegen output.  They can be .json or .py files (see below for more info).
- <a name="transformations_brief"></a>[**Transformations**](#transformations)
  - Transformations are defined in *[birdwing_codegen/transformations.json](transformations.json)*.  They are used by the build system to create a context specific to the language of the template being rendered by mutating the values associated with specific keys in the original context.
- [**Templates**](#templates)
  - Templates are located in *[birdwing_codegen/templates/\<language\>/\<template file\>](templates)*.  The transformed context data is substituted into them to produce the final code generation output.  See the [Mustache manual](http://mustache.github.io/mustache.5.html) for more details on template syntax.
- [**Build System**](#build_system)
  - The build system is implemented primarily in the *[SConscript](../SConscript)* and *[site_scons/mustache_based_codegen.py](../site_scons/mustache_based_codegen.py)*. These tie it all together: they contain the logic to integrate pystache with our build system, and implement transformations (since that is not a feature of Mustache/Pystache).  It should hopefully only be necessary to modify **Contexts**, **Templates**, and **Transformations** when adding code generation, **NOT** the build system.

See [here](codegen_flow.png) for an ugly diagram that illustrates how these components connect together.


### <a name="contexts"></a>Contexts

Located in *[birdwing_codegen/contexts/\<context file\>](contexts)*, context files can exist in two forms: 

  - As a json dict (e.g. [errors.json](contexts/errors.json))
  - <a name="python_contexts"></a>As a python file that defines a ***generate_context(env, target, source)*** method that returns a dict (e.g. [machine_specific_toolhead_metadata.py](contexts/machine_specific_toolhead_metadata.py))
    - The *env*, *target*, and *source* parameters to *generate_context* are the same as what is passed into the codegen scons builder.
    - If a machine-specific printer_settings.json file is available, the key ***'MBCOREUTILS_BWMACHINE_SETTINGS'*** will be present in *env* and will be set to the absolute path to the printer_settings.json file.


Best practices and things to note when creating contexts:

- **All strings should be lowercase_and_delimited_by_underscores whenever possible**.  Keeping strings in a consistent format makes it easier to apply transformations.
- **Don't use the same top-level key in multiple contexts**.  All context dicts are merged into a central context dictionary in memory.  This is not a recursive merge (it's just done using python's dict.update()), so the same top-level key used in multiple context files will overwrite itself without warning.
- Pay special attention to keys that have transformations applied to them.  Any key that is listed in a *[REPLACE_MATCHING_VALS_IN_KEYS](#rmvik)* field in *[birdwing_codegen/transformations.json](transformations.json)* will have it's value mutated globally in the applicable language's transformed context.  Thus, that same key shouldn't be used for multiple values that are unrelated to one-another.

### <a name="transformations"></a>Transformations

Located in *[birdwing_codegen/transformations.json](transformations.json)*, transformations are metadata used to mutate the values associated with specific keys in the context before passing it to the Pystache renderer.  This notion of 'transformations' is not part of the Mustache specification or Pystache.  Instead, the supporting logic is primarily implemented in *[site_scons/mustache_based_codegen.py](../site_scons/mustache_based_codegen.py)*.  Preprocessing the context dictionary like this makes it easier to use the same context data for generating code in many languages, since each language represents things like types differently (e.g. *uint16* in cpp vs *ctypes.c_uint16* in python).


Each language that templates are implemented in can have it's own transformations.  Every folder inside *[birdwing_codegen/templates/](templates)* that contains template files is considered to be a distinct implementation language.  In *[birdwing_codegen/transformations.json](transformations.json)*, there should be top-level keys (containing a dict) for each language that requires transformations.  For example, if one had templates in *birdwing_codegen/templates/cpp/)* and *birdwing_codegen/templates/python)*, transformations.json would look something like:

```
{
  "cpp": <cpp transformation dictionary>,
  "python": <python transformation dictionary>
}
```

To select specific keys in the context whose values we want to transform, there are two types of special keys used in transformation dictionaries: **[\<key\>\_MAPPINGS](#_mappings)** and **[\<key\>\_TRANSFORM](#_transform)**, where \<key\> is the key in the context dictionary being selected.  These special selector keys are scoped: Their location within the transformation dictionary determines what section of the context they're applied to.

For example, let's say there's a context dictionary like this:

```
{
  "structs": [
    {
      "name": "test_struct_one",
      "fields": [
        {"name": "variable1", "type": "uint32"},
        {"name": "variable2", "type": "bool"}
      ]
    }
  ],
  "enums": [
    {
      "name": "enum_one",
      "values": [
        {"name": "thing_one", "value": 5},
        {"name": "thing_two", "value": 42}
      ]
    }
  ],
  "random_variables": [
    {"name": "this_is_hacky", "type": "bool"},
    {"name": "struct_instance", "type": "test_struct_one"}
  ]
}
```
And there are the following requirements for a specific implementation language:

- Every structs' name value must be transformed to match the format "kTestStructOne".
- Struct's names can be used as a value for the "type" key in other locations (so must also be transformed there).
- Every enum's name value must be transformed to match the format "ENUM_ONE".
- Every enum value's name must be transformed to look like "Thing_One".
- Each value of "type" keys must be globally replaced with "BoOl" if they are set to "bool".


To transform the context with those rules, the following transformation dictionary (under the appropriate language key) could be created:

```
{
  "type_MAPPINGS": {
    "bool": "BoOl"
  },
  "structs": {
    "name_TRANSFORM": {
      "LAMBDA": "lambda s: 'k' + s.title().replace('_', '')",
      "REPLACE_MATCHING_VALS_IN_KEYS": ["type"]
    }
  },
  "enums": {
    "name_TRANSFORM": {
      "LAMBDA": "lambda s: s.upper()"
    },
    "values": {
      "name_TRANSFORM": {
        "LAMBDA": "lambda s: s.title()"
      }
    }
  }
}
```

With those transformation rules in place, the transformed context would then look like:

```
{
  "structs": [
    {
      "name": "kTestStructOne",
      "fields": [
        {"name": "variable1", "type": "uint32"},
        {"name": "variable2", "type": "BoOl"}
      ]
    }
  ],
  "enums": [
    {
      "name": "ENUM_ONE",
      "values": [
        {"name": "Thing_One", "value": 5},
        {"name": "Thing_Two", "value": 42}
      ]
    }
  ],
  "random_variables": [
    {"name": "this_is_hacky", "type": "BoOl"},
    {"name": "struct_instance", "type": "kTestStructOne"}
  ]
}
```


#### <a name="_mappings"></a>***\<key\>_MAPPINGS***
Mappings are used in transformations to replace specific values contained within a specific key.  A mapping is a dict, where each key-value pair is structured like:
*\<original value\> : \<new value\>*.  

##### Example
A mapping to replace values for all "type" keys within a context with ones that will work for a python implementation would look like:
 
```
"type_MAPPINGS": {
  "bool": "ctypes.c_bool",
  "int16": "ctypes.c_int16",
  "int32": "ctypes.c_int32",
  "int64": "ctypes.c_int64",
  "int8": "ctypes.c_int8",
  "uint16": "ctypes.c_uint16",
  "uint32": "ctypes.c_uint32",
  "uint64": "ctypes.c_uint64",
  "uint8": "ctypes.c_uint8"
}
```

##### Scoping
A mapping's position in the translation dict determines how broadly it is applied to the context (i.e. a mapping located in the root of the translation dict will be applied to all matching keys in the context, a mapping nested under a specific key in the translation dict will apply to all children of that key in the context).  If a key in a context falls under the scope of multiple mappings, the closest mapping will be used.

##### Caveats
Mappings are applied before key-specific transforms, so any key that has both a \_MAPPING and \_TRANSFORM associated with it will end up having the mapped value transformed by the \_TRANSFORM's [LAMBDA](#lambda), which could cause unintended results.

Mappings will only be applied to keys who's direct values are not lists or dicts.


#### <a name="_transform"></a>***\<key\>_TRANSFORM***
Value transforms are used in transformations to mutate the values of specific keys in a context.  A transform is a dict, with two specific elements:

- <a name="lambda"> </a>***LAMBDA***
  - This key **must be present** in all \_TRANSFORMs.  Its value should be string containing a python lambda that accepts one argument (the value of the key being transformed for the context).  This python lambda is responsible for mutating the supplied value and returning the new version.
- <a name="rmvik"> </a>***REPLACE_MATCHING_VALS_IN_KEYS***
  - This key is **optional**.  Setting it to false will also have the same effect as not specifying it.
  - If specified, its value should be a list of context keys.  If any keys contained in this list match a key **anywhere** in the context dictionary, and the value of that context dictionary element matches the original value of any key that was transformed by the LAMBDA, then that value in the context dictionary will be replaced by the transformed version.


##### Example
A transform that will convert all "name" values to uppercase, and then replace occurances of those original values with the transformed version in elements with the key "type" would look like:

```
"name_TRANSFORM": {
  "LAMBDA": "lambda s: s.upper()",
  "REPLACE_MATCHING_VALS_IN_KEYS": ["type""]
}
```

##### Scoping
The scope of transforms is different from the scope of mappings: Rather than applying to all children of the key they're located in, they will only be applied to keys in the context that directly match their location.  For example, given the following context:

```
{
  "structs": [
    {
      "name": "struct_one",
      "fields": [
        {"name": "field_one", "type": "char"}
      ]
    }
  ]
}
```

And the following transformation dictionary:

```
{
  "structs": {
    "name_TRANSFORM": {
      "LAMBDA": "lambda s: s.upper()"
    }
  }
}
```

The output would be:

```
{
  "structs": [
    {
      "name": "STRUCT_ONE",
      "fields": [
        {"name": "field_one", "type": "char"}
      ]
    }
  ]
}
```

Note how the "name" key under "fields" is not transformed, despite being contained within a child of "structs".

If a transform has keys specified for the ***REPLACE_MATCHING_VALS_IN_KEYS*** field, then any of those keys **anywhere** in the context dictionary will be replaced assuming their value matches one that was transformed.

##### Caveats

Transforms are applied after mappings, so any key that has both a \_MAPPING and \_TRANSFORM associated with it will end up having the mapped value transformed, which could cause unintended results.  Transforms will only be applied to keys who's direct values are not lists or dicts.


### <a name="templates"></a>Templates

Located in *[birdwing_codegen/templates/\<language\>/\<template\>](templates)*, templates are what the transformed context data is substituted into to produce the final code generation output.  An explanation of template syntax can be found on the [Mustache manpages](http://mustache.github.io/mustache.5.html).

The primary things to note when creating a template are:

- Directory structure
  - The parent directory of templates is used to represent implementation language for transformations and determine rendered file output location.  For example, a template written in python may reside under a directory called "python".  To apply a transformation dict to a context being passed to this template, the dict must then be created under a root key called "python" in *[transformations.json](transformations.json)*.
  - Templates must reside in a direct subfolder of *[birdwing_codegen/templates](templates)*.
- File name
  - Template file name can be anything, but will be used verbatim as the output file name.



A possible input directory structure could look like:

```
birdwing_codegen/
  templates/
    cpp/
      fileone.hh
      filetwo.cc
    python/
      fileone.py
      filetwo.py
    docs/
      fileone.md
      filetwo.md
```

And the output like:

```
obj/
  birdwing/
    cpp/
      fileone.hh
      filetwo.cc
    python/
      fileone.py
      filetwo.py
    docs/
      fileone.md
      filetwo.md
  include/
    bwcoreutils/
      fileone.hh
```

Note how the cpp header files were specifically copied to *obj/include/bwcoreutils*.  This is part of a [hardcoded hack](#include_hack) in to avoid changing the existing build system for a bunch of projects.

For an example template, see anything in *[birdwing_codegen/templates](templates)* or the [Mustache Docs](http://mustache.github.io/mustache.5.html).


### <a name="build_system"></a>Build System
The scripts responsible for producing the code-generated output from the supplied contexts, transformations, and templates are primarily:


- <a name="machine_settings_builder"></a>*[site_scons/machine_specific_settings.py](../site_scons/machine_specific_settings.py)*
  - Part of a [hack to enable machine-specific code generation](#machine_specific_hack), this SCons builder will generate a machine-specific printer_settings.json file in the same manner that Birdwing-Software/firmware/settings/SConscript does.
- *[site_scons/mustache_based_codegen.py](../site_scons/mustache_based_codegen.py)*
	- Given a set of input files containing templates, contexts, and transformations, and a list of output locations matching the supplied template names, this SCons builder will render and save the code generated output.
- *[SConscript](../SConscript)*
	- Contains the logic to generate input and output files for codegen, and executes the machine_specific_settings builder, the mustache_based_codegen builder, and the [cpp include hack](#include_hack).


It should not be necessary to modify the build system to add additional code generation.



## Hacks / Technical Debt
-------------------------
Unfortunately, a few hacky things needed to be implemented to get this code generation working with all our projects without requiring extensive refactors:

### <a name="include_hack"></a>CPP Output Copy Hack
Many projects (Prototype, machine driver, others) expect the cpp header output for birdwing in MBCoreUtils to be in obj/include/bwcoreutils.  Codegen currently outputs all files in obj/birdwing/\<language\>/\<file\>.  Rather than refactoring a bunch of projects to change the location they're looking for cpp headers in, or refactoring much of codegen, the quickest solution seemed to be to add a hack to the [MBCoreUtils SConscript](../SConscript) to copy the output in obj/birdwing/cpp/* to obj/include/bwcoreutils/.

Maybe this can be fixed in the future by allowing a custom output location to be specified on a per-file or per-language basis in a config file somewhere.

### <a name="machine_specific_hack"></a>Machine-Specific Code Generation
The code-generation that was being done previous to this system changed its output depending on which machine the Birdwing stack was being built for. Thus, several components of the stack are heavily dependent on this machine-specific output (machine driver).  It would be a lot of effort to refactor them to change this, so machine-specific code generation was hacked on by allowing [Contexts](#contexts_brief) to be dynamically generated.

There are two primary components to the machine-specific dynamic context generation:

- A [builder that is run prior to code generation](#machine_settings_builder) that creates a machine-specific printer_settings.json file local to MBCoreUtils.  This builder uses the same logic as *Birdwing-Software/firmware/settings/SConscript* to generate this file, and uses the printer_settings.json files in *Birdwing-Software/firmware/settings/* as its input.  If this builder is run the environment variable "MBCOREUTILS_BWMACHINE_SETTINGS" will be set to the path to the local printer_settings.json for dynamic contexts to use.
- [Dynamic python contexts](#python_contexts) that can load this printer_settings.json file and return a machine-specific dict.

### Transformations

Mustache has a nice templating syntax, but has limitations that make it difficult to generate code in a variety of languages from the same data.  Variations in keywords, syntax, and style means the same data often needs to be represented in slightly different ways for each implementation.  This is achieved by pre-processing the context dictionary for each implementation language using "[Transformations](#transformations_brief)".
