## Machine Errors
Machine Error codes are returned by the machine whenever a function is called.  They are defined in errors.json under the "machine_errors" key.  Kaiten then interprets these error codes to discern what happened inside the machine drive object.  The OK error code means the function executed successfully.  NOT_READY means kaiten must call this function again to fully execute.  All others are considered "errors".

There are 4 error categories, each with their own meaning:

    * 1 - 255: Toolhead errors.  These are defined in errors.json under the "toolhead_errors" key.
    * 256 - 500: Warnings.  Warnings neither require user action nor cause processes to fail; they exist to conveyor information to kaiten.
    * 501 - 1000: User Warnings.  These errors trigger the machine/process to enter the "wait_for_acknowledge" state, requiring a connected client to acknowledge the warning
    * 1001 - 2000: Process Critical errors. These errors cause the process that called the function to cancel
    * > 2001: Machine critical errors.  These errors cause the machine to shutdown.

## Toolhead Errors
Toolhead errors are returned by the toolhead to the machine object.  Additionally, when kaiten calls Iterate on the machine drive object, toolhead errors for each attached toolhead are returned.  They are defined in errors.json under the "toolhead_errors" key.
