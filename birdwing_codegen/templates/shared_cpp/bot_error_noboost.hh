#ifndef BOT_ERROR_NOBOOST_HH
#define BOT_ERROR_NOBOOST_HH

#include <string>
#include "bwcoreutils/all_errors.hh"
#include "bwcoreutils/process_enums.hh"
#include "bwcoreutils/toolheads.hh"

namespace bwcoreutils {

/*
 * This class takes an error code integer and provides details for UI
 * error handling.  Does not support string translation.  Requires C++11.
 */
class BotError {
public:

    enum TYPE {
        {{#error_type_enum}}
        {{name}} = {{value}},
        {{/error_type_enum}}
    };

    enum ACTION {
        {{#error_action_enum}}
        {{name}} = {{value}},
        {{/error_action_enum}}
    };

    explicit BotError(Error errorCode, int toolhead_index, ToolheadType toolhead_type,
                      ProcessType process_type, ProcessStep process_step) :
        m_message("Oops, we have a problem. Please update your firmware using MakerBot Desktop."),
        m_type(static_cast<TYPE>(0)),
        m_action(static_cast<ACTION>(0)),
        m_title("System Error"),
        m_error(errorCode),
        m_toolhead_idx(toolhead_index),
        m_toolhead_type(toolhead_type),
        m_process_type(process_type),
        m_process_step(process_step) {
        init();
    }

    explicit BotError(int errorCode, int toolhead_index, ToolheadType toolhead_type,
                      ProcessType process_type, ProcessStep process_step) :
        BotError(static_cast<Error>(errorCode), toolhead_index, toolhead_type,
                 process_type, process_step) {}

    explicit BotError(Error errorCode, int toolhead_index, ToolheadType toolhead_type) :
        BotError(errorCode, toolhead_index, toolhead_type,
                 ProcessType::kNoProcess, ProcessStep::kNoProcessStep) {}

    explicit BotError(int errorCode, int toolhead_index, ToolheadType toolhead_type) :
        BotError(static_cast<Error>(errorCode), toolhead_index, toolhead_type) {}

    explicit BotError(Error errorCode, ProcessType process_type, ProcessStep process_step) :
        BotError(errorCode, -1, ToolheadType::kUnknownToolheadType,
                 process_type, process_step) {}

    explicit BotError(int errorCode, ProcessType process_type, ProcessStep process_step) :
        BotError(static_cast<Error>(errorCode), process_type, process_step) {}

    explicit BotError(Error errorCode) :
        BotError(errorCode, -1, ToolheadType::kUnknownToolheadType) {}

    explicit BotError(int errorCode) :
        BotError(static_cast<Error>(errorCode)) {}

    ~BotError() {}

    std::string message() const {
        return m_message;
    }

    // Used to determine what thumbnail to display to the user
    TYPE type() const {
        return m_type;
    }

    ACTION action() const {
        return m_action;
    }

    std::string title() const {
        return m_title;
    }

    Error error() const {
        return m_error;
    }

private:

    enum ErrorBases {
        {{#error_bases}}
        {{name}},
        {{/error_bases}}
    };

    struct ErrorDefaults {
        ErrorDefaults(const std::string& title, TYPE type, ACTION action) :
        title(title),
        type(type),
        action(action) {}
        ErrorDefaults() {}
        ~ErrorDefaults() {}

        std::string title;
        TYPE type;
        ACTION action;
    };

    static ErrorDefaults get_base_defaults(ErrorBases b) {
        switch (b) {
            {{#error_bases}}
            case {{name}}:
                return ErrorDefaults("{{{title}}}", {{error_type}}, {{error_action}});
            {{/error_bases}}
        }
    return ErrorDefaults();
    }

    // Because of the way we do codegen this function has to be indented to
    // an absolutely ridiculous level, so this function gets indented to 2
    // characters per level.  Apologies to anyone who has to read this.
    void init() {
      ErrorDefaults d;
      switch(m_error) {
        {{#all_errors}}
        case {{name}}:
        {{#alt_ids}}
        case {{id}}:
        {{/alt_ids}}
          switch (m_toolhead_type) {
            {{#per_source}}
            {{#source_type}}
            case {{source_type}}:
            {{/source_type}}
            {{^source_type}}
            default:
            {{/source_type}}
              switch (m_process_type) {
                {{#per_process}}
                {{#process_type}}
                case {{process_type}}:
                {{/process_type}}
                {{^process_type}}
                default:
                {{/process_type}}
                  switch (m_process_step) {
                    {{#per_process_step}}
                    {{#process_step_type}}
                    case {{process_step_type}}:
                    {{/process_step_type}}
                    {{^process_step_type}}
                    default:
                    {{/process_step_type}}
                      {{#use_base}}
                      d = get_base_defaults({{use_base}});
                      {{^title}}
                      m_title = d.title;
                      {{/title}}
                      {{^message}}
                      m_message = "{{{base_message}}}";
                      {{/message}}
                      {{^error_type}}
                      m_type = d.type;
                      {{/error_type}}
                      {{^error_action}}
                      m_action = d.action;
                      {{/error_action}}
                      {{/use_base}}
                      {{#title}}
                      m_title = "{{{title}}}";
                      {{/title}}
                      {{#message}}
                      m_message = "{{{message}}}";
                      {{/message}}
                      {{#error_type}}
                      m_type = {{{error_type}}};
                      {{/error_type}}
                      {{#error_action}}
                      m_action = {{{error_action}}};
                      {{/error_action}}
                      break;
                    {{/per_process_step}}
                  }
                  break;
                {{/per_process}}
              }
              break;
            {{/per_source}}
          }
          break;
        {{/all_errors}}
        default:
          break;
      }
    }
    // End of 2 spaces per indent

    std::string m_message;
    TYPE m_type;
    ACTION m_action;
    std::string m_title;
    Error m_error;
    int m_toolhead_idx;
    ToolheadType m_toolhead_type;
    ProcessType m_process_type;
    ProcessStep m_process_step;

};

// TODO: Determine what if anything BotError equality should mean

} // namespace

#endif /* BOT_ERROR_NOBOOST_HH */
