#ifndef BOT_ERROR_NOQT_HH
#define BOT_ERROR_NOQT_HH

#include <string>
#include <boost/format.hpp>
#include "bwcoreutils/all_errors.hh"

namespace bwcoreutils {

/*
 * This class takes an error code integer and provides details for UI
 * error handling.  Does not support string translation.  Requires C++11 and boost::format.
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

    explicit BotError(Error errorCode) :
        m_message("Oops, we have a problem. Please update your firmware using MakerBot Desktop."),
        m_type(static_cast<TYPE>(0)),
        m_action(static_cast<ACTION>(0)),
        m_title("System Error"),
        m_error(errorCode) {
        init();
    }

    // TODO(ted): Ideally we would do this with constructor delegation, like:
    // explicit BotError(int errorCode) : BotError(static_cast<Error>(errorCode)) {}
    // but MSVC 11 (2012) doesn't support that feature of c++11, so we'll have to
    // update this when we switch to a newer MSVC
    explicit BotError(Error errorCode) :
        m_message("Oops, we have a problem. Please update your firmware using MakerBot Desktop."),
        m_type(static_cast<TYPE>(0)),
        m_action(static_cast<ACTION>(0)),
        m_title("System Error"),
        m_error(static_cast<Error>(errorCode)) {
        init();
    }

    // TODO(jacksonh): support custom error messages for toolhead-specific errors
    // BotError(Error errorCode, int toolhead_index, ToolheadType toolhead_type) {}

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
    void init() {
        switch(m_error) {
            {{#toolhead_errors}}
            case {{name}}:
                {{#use_base}}
                {{^title}}
                m_title = {{{use_base}}}_TITLE;
                {{/title}}
                {{^message}}
                m_message = (boost::format({{{use_base}}}_MESSAGE) % static_cast<int>(m_error) % "{{{pretty_name}}}").str();
                {{/message}}
                {{^error_type}}
                m_type = {{{use_base}}}_TYPE;
                {{/error_type}}
                {{^error_action}}
                m_action = {{{use_base}}}_ACTION;
                {{/error_action}}
                {{/use_base}}
                {{#title}}
                m_title = "{{{title}}}";
                {{/title}}
                {{#message}}
                m_message = (boost::format("{{{message}}}") % static_cast<int>(m_error)).str();
                {{/message}}
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
                {{^title}}
                m_title = {{{use_base}}}_TITLE;
                {{/title}}
                {{^message}}
                m_message = (boost::format({{{use_base}}}_MESSAGE) % static_cast<int>(m_error) % "{{{pretty_name}}}").str();
                {{/message}}
                {{^error_type}}
                m_type = {{{use_base}}}_TYPE;
                {{/error_type}}
                {{^error_action}}
                m_action = {{{use_base}}}_ACTION;
                {{/error_action}}
                {{/use_base}}
                {{#title}}
                m_title = "{{{title}}}";
                {{/title}}
                {{#message}}
                m_message = (boost::format("{{{message}}}") % static_cast<int>(m_error)).str();
                {{/message}}
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

    // Error base constants
    {{#error_bases}}
    static constexpr const char* {{{name}}}_TITLE = "{{{title}}}";
    static constexpr const char* {{{name}}}_MESSAGE = "{{{message}}}";
    static const TYPE {{{name}}}_TYPE = {{{error_type}}};
    static const ACTION {{{name}}}_ACTION = {{{error_action}}};
    {{/error_bases}}
};

inline bool operator==(const BotError &lhs, const BotError &rhs) {return lhs.error() == rhs.error();}
inline bool operator==(const BotError &lhs, Error rhs) {return lhs.error() == rhs;}
inline bool operator==(Error lhs, const BotError &rhs) {return operator==(rhs, lhs);}
inline bool operator!=(const BotError &lhs, const BotError &rhs) {return !(lhs == rhs);}
inline bool operator!=(const BotError &lhs, Error rhs) {return !(lhs == rhs);}
inline bool operator!=(Error lhs, const BotError &rhs) {return !(lhs == rhs);}

} // namespace

#endif /* BOT_ERROR_NOQT_HH */
