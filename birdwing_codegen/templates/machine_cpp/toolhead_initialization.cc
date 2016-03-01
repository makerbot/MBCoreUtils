#include <cstring>
#include <ctime>
#include "machine.hh"
#include "heater_manager.hh"
#include <boost/log/trivial.hpp>
{{#machine_toolheads}}
#include "{{toolhead_include}}"
{{/machine_toolheads}}



void Machine::InitializeToolheads(){

    memset(&machine_status_,0, sizeof(machine::MachineResponseStatus));
    static time_t start;
    {{#machine_toolheads}}
    BOOST_LOG_TRIVIAL(info) << "Setting status struct for toolhead {{index}}";
    toolhead_[{{index}}]->SetStatusStruct(&machine_status_.toolhead_{{index}}_status);
    LoadToolhead({{index}});
    {{/machine_toolheads}}
}
