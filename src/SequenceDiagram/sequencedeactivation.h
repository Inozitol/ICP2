// Autor: xmurga01

#pragma once

#include <memory>

#include "sequenceevent.h"
#include "sequencelifeline.h"

///
/// \brief Class for representing a lifeline deactivation event in the sequence diagram.
///
class SequenceDeactivation : public SequenceEvent
{
public:
    /// \brief Class constructor without lifeline specification.
    SequenceDeactivation();
    /// \brief Class constructor with lifeline specification.
    /// \param lifeline shared pointer to the lifeline, which is to be deactivated.
    SequenceDeactivation(std::shared_ptr<SequenceLifeline> lifeline);
    /// \brief Method for obtaining the shared pointer to the lifeline.
    /// \return shared pointer to a lifeline, which is to be deactivated.
    std::shared_ptr<SequenceLifeline> GetLifeline();
    /// \brief Method for setting the lifeline, which is to be deactivated.
    /// \param lifeline shared pointer to the lifeline, which is to be deactivated.
    void SetLifeline(std::shared_ptr<SequenceLifeline> lifeline);
private:
    /// \brief Shared pointer to the lifeline.
    std::shared_ptr<SequenceLifeline> _lifeline;
};

