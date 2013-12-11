# Birdwing Metaparsing
This directory contains several files defined in a meta language (.json) that are converted into both C and Python code.  The converted .hh and .py files are then linked in to various projects int the makerware/birdwing stack.

## MachineErrors
Machine Error codes are returned by the machine whenever a function is called.  Kaiten then interprets these error codes to discern what happened inside the machine drive object.  The OK error code means the function executed successfully.  NOT_READY means kaiten must call this function again to fully execute.  All others are considered "errors".

There are 4 error categories, each with their own meaning:

    * 1 - 255: Toolhead errors.  These are defined in a different file in Birdwing-Software/firmware/meta.  TODO: This should probably be moved into here
    * 256 - 500: Warnings.  Warnings neither require user action nor cause processes to fail; they exist to conveyor information to kaiten.
    * 501 - 1000: User Warnings.  These errors trigger the machine/process to enter the "wait_for_acknowledge" state, requiring a connected client to acknowledge the warning
    * 1001 - 2000: Process Critical errors. These errors cause the process that called the function to cancel
    * > 2001: Machine critical errors.  These errors cause the machine to shutdown.
