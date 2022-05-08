// Autor: xhorac19, xmurga01

#pragma once

#include "sequenceevent.h"
#include "sequencelifeline.h"

#include <memory>

///
/// \brief Class representing the message type of a sequence diagram event.
///
/// Class maintains origin, destination and message of the event.
///
class SequenceMessage : public SequenceEvent
{
public:
    /// \brief Class constructor.
    /// \param orig sender of the message.
    /// \param dest recipient of the message.
    /// \param msg message content.
    SequenceMessage(std::shared_ptr<SequenceLifeline> orig, std::shared_ptr<SequenceLifeline> dest, std::string msg);
    /// \brief Class constructor.
    SequenceMessage();

    /// \brief Method for obtaining the sender of the message.
    /// \return shared pointer to the lifeline who sent the message.
    std::shared_ptr<SequenceLifeline> GetOrigin();
    /// \brief Method for obtaining the recipient of the message.
    /// \return shared pointer to the lifeline who received the message.
    std::shared_ptr<SequenceLifeline> GetDestination();
    /// \brief Method for obtaining the contents of the message.
    /// \return the contents of the message.
    std::string GetMessage();
    /// \brief Method for setting the sender of the message.
    /// \param lifeline shared pointer to the sender lifeline.
    void SetOrigin(std::shared_ptr<SequenceLifeline> lifeline);
    /// \brief Method for setting the recipient of the message.
    /// \param lifeline shared pointer to the recipient lifeline.
    void SetDestination(std::shared_ptr<SequenceLifeline> lifeline);
    /// \brief Method for setting the contents of the message.
    /// \param msg new message content.
    void SetMessage(std::string msg);
private:
    /// \brief Sender lifeline.
    std::shared_ptr<SequenceLifeline> _origin;
    /// \brief Recipient lifeline.
    std::shared_ptr<SequenceLifeline> _destination;
    /// \brief Message content.
    std::string _msg;
};
