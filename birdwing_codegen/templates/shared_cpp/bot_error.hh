//  THIS FILE IS DEPRECATED!  Please use bot_error_noqt.hh instead.
//  This exists because we planned to use Qt's tr() for translation, but that never happened.

#ifndef ERROR_QSTRINGS_HH
#define ERROR_QSTRINGS_HH

#include <string>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  #include <QString>
  // The QStringLiteral macro is only available in Qt5+
  #ifndef QStringLiteral
    #define QStringLiteral(str) QString::fromUtf8(str)
  #endif
#else
  #include <QtCore/QString>
#endif

#include "bwcoreutils/all_errors.hh"

namespace bwcoreutils {

/*
 * This class takes an error code integer and provides details for UI
 * error handling, including Qt translatable strings.
 * Requires Qt and C++11
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
        m_type(static_cast<TYPE>(0)),
        m_action(static_cast<ACTION>(0)),
        m_error(errorCode),
        m_isFancy(false) {
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
        m_isFancy(false) {
        init();
    }

    // TODO(jacksonh): support custom error messages for toolhead-specific errors
    // BotError(Error errorCode, int toolhead_index, ToolheadType toolhead_type) {}

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

        ErrorDefaults(const QString& title, const std::string& message, TYPE type, ACTION action) :
        title(title),
        message(message),
        type(type),
        action(action) {}
	ErrorDefaults() {}
        ~ErrorDefaults() {}


        QString title;
        std::string message;
        TYPE type;
        ACTION action;

    };

    static ErrorDefaults get_base_defaults(ErrorBases b) {
        switch (b) {
            {{#error_bases}}
            case {{name}}:
                return ErrorDefaults(QStringLiteral("{{{title}}}"), "{{{message}}}", {{error_type}}, {{error_action}});
            {{/error_bases}}
        }
	return ErrorDefaults();
    }

    void init() {
	ErrorDefaults d;
    QString dummy;
        switch(m_error) {
            {{#toolhead_errors}}
            case {{name}}:
                {{#use_base}}
                d = get_base_defaults({{use_base}});
                {{^title}}
                m_title = d.title;
                {{/title}}
                {{^message}}
                m_message = dummy.sprintf(d.message.c_str(), static_cast<int>(m_error), "{{{pretty_name}}}");
                {{/message}}
                {{^error_type}}
                m_type = d.type;
                {{/error_type}}
                {{^error_action}}
                m_action = d.action;
                {{/error_action}}
                {{/use_base}}
                {{#title}}
                m_title = QStringLiteral("{{{title}}}");
                {{/title}}
                {{#message}}
                m_message = dummy.sprintf("{{{message}}}", static_cast<int>(m_error));
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
                m_message = dummy.sprintf(d.message.c_str(), static_cast<int>(m_error), "{{{pretty_name}}}");
                {{/message}}
                {{^error_type}}
                m_type = d.type;
                {{/error_type}}
                {{^error_action}}
                m_action = d.action;
                {{/error_action}}
           {{/use_base}}
                {{#title}}
                m_title = QStringLiteral("{{{title}}}");
                {{/title}}
                {{#message}}
                m_message = dummy.sprintf("{{{message}}}", static_cast<int>(m_error));
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
                m_title = QStringLiteral("System Error");
                m_message = QStringLiteral("Oops, we have a problem. Please update your firmware using MakerBot Desktop.");
                break;
        }
    }

    QString m_message;
    TYPE m_type;
    ACTION m_action;
    QString m_title;
    Error m_error;
    bool m_isFancy;

};

inline bool operator==(const BotError &lhs, const BotError &rhs) {return lhs.error() == rhs.error();}
inline bool operator==(const BotError &lhs, Error rhs) {return lhs.error() == rhs;}
inline bool operator==(Error lhs, const BotError &rhs) {return operator==(rhs, lhs);}
inline bool operator!=(const BotError &lhs, const BotError &rhs) {return !(lhs == rhs);}
inline bool operator!=(const BotError &lhs, Error rhs) {return !(lhs == rhs);}
inline bool operator!=(Error lhs, const BotError &rhs) {return !(lhs == rhs);}

} // namespace

#endif // ERROR_QSTRINGS_HH
