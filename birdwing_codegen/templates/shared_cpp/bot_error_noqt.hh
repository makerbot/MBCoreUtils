#ifndef BOT_ERROR_NOQT_HH
#define BOT_ERROR_NOQT_HH

#include <string>
#include <boost/format.hpp>
#include "bwcoreutils/all_errors.hh"

namespace bwcoreutils {

/*
 * This class takes an error code integer and provides details for UI
 * error handling.  Does not support string translation.
 * Requires C++11 and boost::format.
 */
class BotError {
public:
    typedef std::vector<std::string> MESSAGE_ARGS;
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

    explicit BotError(Error errorCode) :
        m_type(static_cast<TYPE>(0)),
        m_action(static_cast<ACTION>(0)),
        m_error(errorCode),
        m_messageArgs() {
        init();
    }

    // TODO(ted): Ideally we would do this with constructor delegation, like:
    // explicit BotError(int errorCode) : BotError(static_cast<Error>(errorCode)) {}
    // but MSVC 11 (2012) doesn't support that feature of c++11, so we'll have to
    // update this when we switch to a newer MSVC
    explicit BotError(int errorCode) :
        m_type(static_cast<TYPE>(0)),
        m_action(static_cast<ACTION>(0)),
        m_error(static_cast<Error>(errorCode)),
        m_messageArgs() {
        init();
    }

    // TODO(jacksonh): support custom error messages for toolhead-specific errors
    // BotError(Error errorCode, int toolhead_index, ToolheadType toolhead_type) {}

    ~BotError() {}

    std::string message() const {
        return m_message;
    }

    void setMessage(const std::string & newMessage) {
        m_message = newMessage;
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

    MESSAGE_ARGS messageArgs() const {
        return m_messageArgs;
    }

private:

    enum ErrorBases {
        {{#error_bases}}
        {{name}},
        {{/error_bases}}
    };

    struct ErrorDefaults {
        ErrorDefaults(const std::string& title, const std::string& message, TYPE type, ACTION action) :
        title(title),
        message(message),
        type(type),
        action(action) {}
        ErrorDefaults() {}
        ~ErrorDefaults() {}

        std::string title;
        std::string message;
        TYPE type;
        ACTION action;
    };

    static ErrorDefaults get_base_defaults(ErrorBases b) {
        switch (b) {
            {{#error_bases}}
            case {{name}}:
                return ErrorDefaults("{{{title}}}", "{{{message}}}", {{error_type}}, {{error_action}});
            {{/error_bases}}
        }
    return ErrorDefaults();
    }

    void init() {
        ErrorDefaults d;
        switch(m_error) {
            {{#toolhead_errors}}
            case {{name}}:
                {{#use_base}}
                d = get_base_defaults({{use_base}});
                {{^title}}
                m_title = d.title;
                {{/title}}
                {{^message}}
                m_message = (boost::format(d.message) % static_cast<int>(m_error) % "{{{pretty_name}}}").str();
                {{/message}}
                {{#message_args}}
                m_messageArgs.push_back("{{{arg}}}");
                {{/message_args}}
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
                {{^msg_no_errcode}}
                m_message = (boost::format("{{{message}}}") % static_cast<int>(m_error)).str();
                {{/msg_no_errcode}}
                {{#msg_no_errcode}}
                m_message = "{{{message}}}";
                {{/msg_no_errcode}}
                {{/message}}
                {{#message_args}}
                m_messageArgs.push_back("{{{arg}}}");
                {{/message_args}}
                {{#error_type}}
                m_type = {{{error_type}}};
                {{/error_type}}
                {{#error_action}}
                m_action = {{{error_action}}};
                {{/error_action}}
                break;
            {{/toolhead_errors}}
            {{#machine_errors}}
            case {{name}}:
                {{#use_base}}
                d = get_base_defaults({{use_base}});
                {{^title}}
                m_title = d.title;
                {{/title}}
                {{^message}}
                m_message = (boost::format(d.message) % static_cast<int>(m_error) % "{{{pretty_name}}}").str();
                {{/message}}
                {{#message_args}}
                m_messageArgs.push_back("{{{arg}}}");
                {{/message_args}}
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
                {{^message_noqt}}
                {{#message}}
                {{^msg_no_errcode}}
                m_message = (boost::format("{{{message}}}") % static_cast<int>(m_error)).str();
                {{/msg_no_errcode}}
                {{#msg_no_errcode}}
                m_message = "{{{message}}}";
                {{/msg_no_errcode}}
                {{/message}}
                {{/message_noqt}}
                {{#message_noqt}}
                m_message = "{{{message_noqt}}}";
                {{/message_noqt}}
                {{#message_args}}
                m_messageArgs.push_back("{{{arg}}}");
                {{/message_args}}
                {{#error_type}}
                m_type = {{{error_type}}};
                {{/error_type}}
                {{#error_action}}
                m_action = {{{error_action}}};
                {{/error_action}}
                break;
            {{/machine_errors}}
            default:
                break;
        }
    }

    std::string m_message;
    TYPE m_type;
    ACTION m_action;
    std::string m_title;
    Error m_error;
    MESSAGE_ARGS m_messageArgs;

};

inline bool operator==(const BotError &lhs, const BotError &rhs) {return lhs.error() == rhs.error();}
inline bool operator==(const BotError &lhs, Error rhs) {return lhs.error() == rhs;}
inline bool operator==(Error lhs, const BotError &rhs) {return operator==(rhs, lhs);}
inline bool operator!=(const BotError &lhs, const BotError &rhs) {return !(lhs == rhs);}
inline bool operator!=(const BotError &lhs, Error rhs) {return !(lhs == rhs);}
inline bool operator!=(Error lhs, const BotError &rhs) {return !(lhs == rhs);}

} // namespace

#endif /* BOT_ERROR_NOQT_HH */
