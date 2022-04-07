// TDeciDegsFilter.h:
/*
© Copyright CERN 2000-2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/
/*!
Concrete Class of the TAngleFilter PABC.
Handles the IO of an TAngle object angles in a text stream with
decimal degrees units.

Patterns:
This class is a Singleton.
Works as a Strategy of a TTStreamFormatter object.
*/
//////////////////////////////////////////////////////////////////////

#ifndef SU_DECIDEGS_FILTER
#define SU_DECIDEGS_FILTER

#if _MSC_VER >= 1000
#	pragma once
#endif // _MSC_VER >= 1000

////////////////////////////////////////////////////////////////
// Forward declarations
//
//
class TAngle;
#include "TAStreamFormatter.h"
#include "TAngleFilter.h"
//
// typedefs
//
//
////////////////////////////////////////////////////////////////

/*!\ingroup FiltersAndFormats
@{*/

// Class definition
class TDeciDegsFilter : public TAngleFilter //: public TObject
{
public:
	/*!name Public Member Function*/
	//@!{
	/*!return the unique class component*/
	static TDeciDegsFilter *instance();

	/*!Get angle value from a TAStreamFormatter object
	and set the values in a TAngle object
	\param stream a TAStreamFormatter object
	\param ang a TAngle object*/
	virtual void input(TAStreamFormatter &, TAngle &) const;

	/*!Get the values from a TAngle object
	and put the values in a TAStreamFormatter object
	\param stream a TAStreamFormatter object
	\param ang a TAngle object*/
	virtual void output(TAStreamFormatter &, const TAngle &) const;

	static void deleteFilter()
	{
		if (fFilter != 0)
		{
			delete fFilter;
		}
		return;
	}
	//@}

protected:
	/*!name Constructors / Destructors*/
	//@!{
	/*!Constructors*/
	TDeciDegsFilter();

	/*!Destructors*/
	virtual ~TDeciDegsFilter();
	//@}

private:
	/*!static pointer to TGonsFilter*/
	static TDeciDegsFilter *fFilter;

	/*!copy constructor declaration*/
	TDeciDegsFilter(const TDeciDegsFilter &);

	// ClassDef(TGonsFilter, 1)
};

/*@}*/

#endif // SU_DECIDEGS_FILTER
