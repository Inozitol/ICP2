// Autor: xhorac19, xmurga01

#pragma once

#include "sequenceevent.h"
#include "sequencelifeline.h"

///
/// \brief Class representing the return type of a sequence diagram event.
///
/// Class maintains origin, destination, message and return type of the event.
///
class SequenceReturn : public SequenceEvent
{
public:
    /// \brief Return type of the event.
    using DataType = std::string;

    /// \brief Class constructor.
    /// \param orig sender of the return event.
    /// \param dest recipient of the return event.
    /// \param msg contents of the return message.
    /// \param type return type of the return message.
    SequenceReturn(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest, std::string msg, DataType type);
    /// \brief Class constructor.
    SequenceReturn();
    /// \brief Method for obtaining the sender of the return event.
    /// \return shared pointer to the lifeline who sent the return message.
    std::shared_ptr<SequenceLifeline> GetOrigin();
    /// \brief Method for obtaining the recipient of the return event.
    /// \return shared pointer to the lifeline who received the return message.
    std::shared_ptr<SequenceLifeline> GetDestination();
    /// \brief Method for obtaining the contents of the return message.
    /// \return the contents of the return message.
    std::string GetMessage();
    /// \brief Method for obtaining the return type of the return message.
    /// \return the data type of the return message.
    DataType GetReturnType();
    /// \brief Method for setting the sender lifeline.
    /// \param lifeline the new sender lifeline.
    void SetOrigin(std::shared_ptr<SequenceLifeline> lifeline);
    /// \brief Method for setting the recipient lifeline.
    /// \param lifeline the new recipient lifeline.
    void SetDestination(std::shared_ptr<SequenceLifeline> lifeline);
    /// \brief Method for setting the contents of the message.
    /// \param lifeline the new message content.
    void SetMessage(std::string msg);
    /// \brief Method for setting the return type of the event.
    /// \param lifeline the new return type.
    void SetReturnType(DataType type);
private:
    /// \brief Sender lifeline.
    std::shared_ptr<SequenceLifeline> _origin;
    /// \brief Recipient lifeline.
    std::shared_ptr<SequenceLifeline> _destination;
    /// \brief Message content.
    std::string _msg;
    /// \brief Return type of the return message.
    DataType _return_type;
};
