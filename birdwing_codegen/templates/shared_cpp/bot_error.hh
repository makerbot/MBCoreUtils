#ifndef ERROR_QSTRINGS_HH
#define ERROR_QSTRINGS_HH

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  #include <QString>
#else
  #include <QtCore/QString>
#endif

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
        m_type(static_cast<TYPE>(0)),
        m_action(static_cast<ACTION>(0)) {
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


    enum ErrorBases {
        {{#error_bases}}
        {{name}},
        {{/error_bases}}
    };

    struct ErrorDefaults {

        ErrorDefaults(const QString& title, const QString& message, TYPE type, ACTION action) :
        title(title),
        message(message),
        type(type),
        action(action) {}
	ErrorDefaults() {}
        ~ErrorDefaults() {}


        QString title;
        QString message;
        TYPE type;
        ACTION action;

    };

    static ErrorDefaults get_base_defaults(ErrorBases b) {
        switch (b) {
            {{#error_bases}}
            case {{name}}:
                return ErrorDefaults(QObject::tr("{{title}}"), QObject::tr("{{message}}"), {{error_type}}, {{error_action}});
            {{/error_bases}}
        }
	return ErrorDefaults();
    }

    void init(int errorCode) {
	ErrorDefaults d;
        switch(static_cast<Error>(errorCode)) {
            {{#toolhead_errors}}
            case {{name}}:
                {{#use_base}}
                d = get_base_defaults({{use_base}});
                {{^title}}
                m_title = d.title;
                {{/title}}
                {{^message}}
                m_message = d.message.arg(errorCode).arg(QObject::tr("{{pretty_name}}"));
                {{/message}}
                {{^error_type}}
                m_type = d.type;
                {{/error_type}}
                {{^error_action}}
                m_action = d.action;
                {{/error_action}}
                {{/use_base}}
                {{#title}}
                m_title = QObject::tr("{{title}}");
                {{/title}}
                {{#message}}
                m_message = QObject::tr("{{message}}").arg(errorCode);
                {{/message}}
                {{#error_type}}
                m_type = {{error_type}};
                {{/error_type}}
                {{#error_action}}
                m_action = {{error_action}};
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
                m_message = d.message.arg(errorCode).arg(QObject::tr("{{pretty_name}}"));
                {{/message}}
                {{^error_type}}
                m_type = d.type;
                {{/error_type}}
                {{^error_action}}
                m_action = d.action;
                {{/error_action}}
                {{/use_base}}
                {{#title}}
                m_title = QObject::tr("{{title}}");
                {{/title}}
                {{#message}}
                m_message = QObject::tr("{{message}}").arg(errorCode);
                {{/message}}
                {{#error_type}}
                m_type = {{error_type}};
                {{/error_type}}
                {{#error_action}}
                m_action = {{error_action}};
                {{/error_action}}
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
