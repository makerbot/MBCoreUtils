#include <cstring>
#include <ctime>
#include "machine.hh"
#include "pins.hh"
#include "heater_manager.hh"
{{#machine_toolheads}}
#include "{{toolhead_manager_include}}"
{{/machine_toolheads}}



void Machine::InitializeToolheads(){

    memset(&machine_status_,0, sizeof(machine::MachineResponseStatus));
    static time_t start;
    {{#machine_toolheads}}

    toolhead_[{{index}}] = new {{name}}ToolheadManager(pins::kToolheadInterrupt{{index}}, pins::kToolheadEnable{{index}}, pins::kToolheadCS{{index}}, pins::kToolheadBus{{index}}, pins::kToolheadPower12V{{index}}, pins::kToolheadPower5V{{index}});
    heater_manager_->AddHeater(toolhead_{{index}});
    heater_manager_->SetStatusStruct({{index}}, &machine_status_.toolhead_{{index}}_heating_status);
    toolhead_{{index}}->SetStatusStruct(&machine_status_.toolhead_{{index}}_status);
    toolhead_{{index}}->SetToolheadNumber({{index}});
    toolhead_{{index}}->SetFilepath("{{program_floc}}");
    toolhead_{{index}}->Power12V(false);
    toolhead_{{index}}->PowerData(false);
    start = time(NULL);
    while((time(NULL)-start)<1);
    LoadToolhead({{index}});
    {{/machine_toolheads}}
}
