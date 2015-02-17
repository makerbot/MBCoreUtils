#ifndef PROCESS_ENUMS_HH
#define PROCESS_ENUMS_HH

namespace bwcoreutils {

enum ProcessType {
    kNoProcess,
    {{#process_types}}
    {{name}},
    {{/process_types}}
};

inline ProcessType ProcessTypeFromStr(const std::string &str) {
    const static std::unordered_map<std::string, ProcessType> strmap = {
        {{#process_types}}
        {"{{str}}", ProcessType::{{name}}},
        {{/process_types}}
    };
    try {
        return strmap.at(str);
    } catch (std::out_of_range &) {
        return ProcessType::kNoProcess;
    }
}

enum ProcessStep {
    kNoProcessStep,
    {{#process_steps}}
    {{name}},
    {{/process_steps}}
};

inline ProcessStep ProcessStepFromStr(const std::string &str) {
    const static std::unordered_map<std::string, ProcessStep> strmap = {
        {{#process_steps}}
        {"{{str}}", ProcessStep::{{name}}},
        {{/process_steps}}
    };
    try {
        return strmap.at(str);
    } catch (std::out_of_range &) {
        return ProcessStep::kNoProcessStep;
    }
}

}

#endif // PROCESS_ENUMS_HH
