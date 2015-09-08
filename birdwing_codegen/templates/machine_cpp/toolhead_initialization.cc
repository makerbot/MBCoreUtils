#include <cstring>
#include <ctime>
#include "machine.hh"
#include "heater_manager.hh"
{{#machine_toolheads}}
#include "{{toolhead_include}}"
{{/machine_toolheads}}



void Machine::InitializeToolheads(){

    memset(&machine_status_,0, sizeof(machine::MachineResponseStatus));
    static time_t start;
    {{#machine_toolheads}}

    toolhead_[{{index}}] = new {{name}}ToolheadManager({{index}});
    heater_manager_->AddHeater(toolhead_[{{index}}]);
    toolhead_[{{index}}]->SetStatusStruct(&machine_status_.toolhead_{{index}}_status);
    toolhead_[{{index}}]->SetFilepath("{{program_floc}}");
    toolhead_[{{index}}]->Power12V(false);
    toolhead_[{{index}}]->PowerData(false);
    start = time(NULL);
    while((time(NULL)-start)<1);
    LoadToolhead({{index}});
    {{/machine_toolheads}}
}
