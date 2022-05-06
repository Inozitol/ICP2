#pragma once

#include <QObject>
#include <iostream>
#include <memory>

///
/// \brief Class for representing an generic event in the sequence diagram.
///
/// Class maintains the type, status and error message of the event.
///
class SequenceEvent
{
public:
    /// \brief Enumeration for the different types of events.
    enum Type{
        Activation = 0,
        Deactivation,
        Message,
        Return,
        Nop
    };

    /// \brief Class constructor.
    /// \param type type of event.
    SequenceEvent(Type type);
    /// \brief Method for obtaining the type of the event.
    /// \return the type of the event.
    Type GetType();
    /// \brief Method for obtaining the status of the event.
    /// \return the status of the event.
    bool GetStatus();
    /// \brief Method for setting the status of the event.
    /// \param stat status of the event.
    void SetStatus(bool stat);
    /// \brief Method for obtaining the error message of the event.
    /// \return the error message of the event.
    std::string GetErrorMsg();
    /// \brief Method for setting the error message of the event.
    /// \param msg new error message.
    void SetErrorMsg(std::string msg);
private:
    /// \brief Type of the event.
    Type _type;
    /// \brief Status of the event.
    bool _status = true;
    /// \brief Error message of the event.
    std::string _errorMsg = "";
};

/// Make SequenceEvent pointer compatible with QVariant.
Q_DECLARE_METATYPE(std::shared_ptr<SequenceEvent>);
