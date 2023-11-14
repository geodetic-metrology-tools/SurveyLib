/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef T_STATUS_OBJECT_H
#define T_STATUS_OBJECT_H

#if USE_SERIALIZER
#	include <Serializer.hpp>
#endif // USE_SERIALIZER

//! Class that gives the object the activation status property and an interface to manage it.
/**
 * By default the activation status is true.
 */
#if USE_SERIALIZER
class TStatusObject : public Serializable
#else
class TStatusObject
#endif // USE_SERIALIZER
{

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

#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(ObjectSerializer &obj) const override
	{
		obj.addProperty("active_", active_);
	}
#endif

private:

    bool active_;
};

#endif // T_STATUS_OBJECT_H
