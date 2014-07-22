#ifndef ERROR_QSTRINGS_HH
#define ERROR_QSTRINGS_HH

#include <QString>
#include "bwcoreutils/all_errors.hh"

namespace bwcoreutils {

/*
 * This class takes an error code integer and provides details for UI
 * error handling, including Qt translatable strings.
 * Requires Qt
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

    BotError(int errorCode) :
        m_type(0),
        m_action(0) {
        init(errorCode);
    }

    ~BotError() {}

    QString message() const {
        return m_message;
    }

    // Used to determine what thumbnail to display to the user
    TYPE type() const {
        return m_type;
    }

    ACTION action() const {
        return m_action;
    }

    QString title() const {
        return m_title;
    }

private:

    void init(int errorCode) {
        // TODO(jacksonh) - fix this string duplication
        switch(static_cast<Error>(errorCode)) {
            {{#toolhead_errors}}
            case {{name}}:
                m_title = QObject::tr("{{title}}");
                m_message = QObject::tr("{{message}}");
                m_type = {{error_type}};
                m_action = {{error_action}};
                break;
            {{/toolhead_errors}}
            {{#machine_errors}}
            case {{name}}:
                m_title = QObject::tr("{{title}}");
                m_message = QObject::tr("{{message}}");
                m_type = {{error_type}};
                m_action = {{error_action}};
                break;
            {{/machine_errors}}
            default:
                m_title = QObject::tr("System Error");
                m_message = QObject::tr("Oops, we have a problem. Please update your firmware using MakerBot Desktop.");
                break;
        }
    }

    QString m_message;
    TYPE m_type;
    ACTION m_action;
    QString m_title;

};

} // namespace

#endif // ERROR_QSTRINGS_HH
