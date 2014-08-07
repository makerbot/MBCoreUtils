# Template Languages

Currently implemented template languages are:

- "[machine_cpp](machine_cpp)"
  -  These templates are written in CPP and their output is primarily used by the machine-driver and other low-level parts of the firmware.  The majority (all?) of machine-specific context generation is for these templates.
- "[shared_cpp](shared_cpp)"
  - These templates are written in CPP and their output is primarily used by UI clients.  The context data used to render these templates should hopefully be machine-agnostic.
- "[python](python)"
  - Primarily used by Kaiten, these templates are written in python and expose python-equivalent mappings and datastructures from what is implemented in machine_cpp and shared_cpp.