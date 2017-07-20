#ifndef T_STATUS_OBJECT_H
#define T_STATUS_OBJECT_H

//! Class that gives the object the activation status property and an interface to manage it.
/**
 * By default the activation status is true.
 */
class TStatusObject {

public:

    //! Default constructor, sets the activation status true
    TStatusObject() : active_(true) {}

    //! Parameterised constructor
    /**
     * Set the activation status to *active* while constructing the object
     */
    TStatusObject(bool active) : active_(active) {}

    //! Retrieve the activation status of the object
    virtual bool isActive() const { return active_; }

    //! Set the activation status of the object to *active*
    virtual void setActive(const bool &active) { active_ = active; }

private:

    bool active_;
};

#endif // T_STATUS_OBJECT_H