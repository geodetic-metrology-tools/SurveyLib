/*
© Copyright CERN 2000-2019. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef TVADJUSTABLE_OBJECT
#define TVADJUSTABLE_OBJECT

#include <string>
#include <vector>
#include "Quad.h"
#include "TSparseMatrix.h"
#include "TStatusObject.h"

#ifndef isnotanumber
#define isnotanumber(x) ((x)!=(x))
#endif

#define assert3D(x) assert((x) >= 0 && (x) < 3)
#define assert4D(x) assert((x) >= 0 && (x) < 4)

/*! 
	\ingroup AdjustableObjects
	\brief A pure virtual class which is an interface for all the adjustable objects.
*/
class TVAdjustableObject : public TStatusObject
{
	public:

		/// This virtual base class destructor does nothing since this is an interface.
		~TVAdjustableObject() {}

		/// Tells if this object is totally fixed, i.e. introduces no unknowns.
		virtual bool isFixed() const = 0;	

		/// Some adjustables can be forward declared, they are uninitialized in this case until they are overwritten by the definition.
		virtual bool isInitialized() const = 0;

		/*!
			\brief Returns The number of unknowns of this object.

			Calculates the number of unknowns that are added to the adjustment by this object.
			This number varies from zero to N unknowns, e.g. three for points.
			
		*/
		virtual int   getNumUnkn() const = 0;		

		/*! 
			This is part 1/2 to assign unknown indices for the matrix entries to  this object.
			A starting index is given and incremented for each variable component.

			Example: If point a point p0 is variable in Y and Z and this function is called with the integer '5',
			the Y component is adjusted in the 5th and the Z component in the 6th matrix row.

			\see getLastUidx is part 2/2.

			\throws Throws a logic_error if no component of the object is variable, i.e. it is fixed.
		*/
		virtual void  setFirstUidx(int idx) = 0;

		/*! 
			This is part 2/2 to assign unknown indices for the matrix entries to unknowns.
			It \returns the last unknown index that is assigned to this object. According to the example
			in \ref setFirstUidx this method \returns '6'.

			An application of the method is to iterate over a vector of adjustable objects and assign matrix indices using
			calls like currentPoint->setFirstUidx(previousPoint->getLastUidx()+1).

			\note This function only \returns useful results after a preceding call to \ref setFirstUidx .

			\see setFirstUidx is part 1/2.

			\throws Throws a logic_error if no component of the object is variable, i.e. it is fixed point.
		*/
		virtual int   getLastUidx() const = 0;
		
		/*!
			Provides read acces to the value that was set in \ref setFirstUidx.
		*/
		virtual int   getFirstUidx() const = 0;

		// return relative unknown indices associated with the free variables
		virtual const std::vector<int> getRelativeUnknIndices() const = 0;

		// getting the estimated vector with all variables
		virtual Eigen::VectorXd getEstVector() const = 0;
		/// getting the estimated value corresponding to the index
		virtual TReal getValue(int idx) const = 0;
		/// setting the estimated value corresponding to the index
		virtual void setValue(int idx, TReal value) = 0;
		/// Updates the value (oldValue+correction), a parameter of this object that is accesed by the unknown index specified by \ref setFirstUidx.
		virtual void setCorrection(int idx, TReal correction) { setValue(idx, getValue(idx) + correction); };

		/// Returns the name (which serves as an ID in most cases) of the adjustable object. This can be a name of: point, line, plane, scalar, angle or HelmertTransformation.
		virtual const std::string& getName() const = 0;

#if USE_SERIALIZER
		// Inherited via Serializable
		virtual void serialize(ObjectSerializer &obj) const override
		{
			TStatusObject::serialize(obj);
		}
#endif

};

#endif //TVADJUSTABLE_OBJECT
