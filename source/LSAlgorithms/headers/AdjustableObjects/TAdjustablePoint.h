/*
© Copyright CERN 2000-2024. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef TADJUSTABLE_POINT
#define TADJUSTABLE_POINT

#include "TFreeVector.h"
#include "TPositionVector.h"
#include "TRefSystemFactory.h"
#include "TSpatialStatus.h"
#include "TVAdjustableObject.h"

/*!
	\ingroup AdjustableObjects
	\brief Adds adjustable information to a point represented by a TPositionVector class.
*/
class TAdjustablePoint : public TVAdjustableObject
{
public:
	/// comments (multi-line) above the point definition including line breaks
	std::string hdrcomment;
	/// DB comment after the point definition
	std::string eolcomment;
	/// the line of the point definition in the input file
	int line;

	/*!@name Constructors */
	//@{

	/*!
		\brief Constructs an AdjustmentPoint based on a position vector defined in one of the local object reference frames.

		Provisional value is represented in the coordinate system passed to the constructor, but estimated value is kept in k3DCartesian coordinate system, used in the adjustment process.

		\param[in] pos A reference to a position vector that will be adjusted. The point will be copied
					   so the poited-to object is no longer needed after construction.
		\param[in] isXfixed The X component of the point, fixed (not adjusted) if set to TRUE.
		\param[in] isYfixed The Y component of the point, fixed (not adjusted) if set to TRUE.
		\param[in] isZHfixed The Z component of the point, fixed (not adjusted) if set to TRUE.
		\param[in] name Name of the adjustable point.
		\param[in] referential Reference frame used (OLOC, RS2K, LEP, SPHE).
		\param[in] positionInTree iterator on the local object reference frame in which the point is defined.
	*/
	TAdjustablePoint(const TPositionVector &pos, bool isXfixed, bool isYfixed, bool isZHfixed, const std::string &name, TRefSystemFactory::ERefFrame referential);

	/// Copy constructor
	TAdjustablePoint(const TAdjustablePoint &pos);

	/// Create an unitialized point.
	static TAdjustablePoint createUninitialized(const std::string &name);

	/// Default constructor
	TAdjustablePoint();
	//@}

	/*!@name Access methods*/
	//@{
	/// Returns a constant reference on the provisional value of the position vector
	inline const TPositionVector &getProvisionalValue() const { return fProvisionalValue; }

	/// Returns a constant reference on the correction value of the point
	inline const TLength &getCorrection(int i) const { return fCorrection[i]; }

	/// Returns a constant reference on the estimated value of the point
	inline const TPositionVector &getEstimatedValue() const { return fEstimatedValue; }

	/// Returns a constant reference of the covariance matrix, not set-able
	inline const Eigen::Matrix3d &getCovarianceMatrix() const
	{
		ensureCovarIsSet();
		return fCovarianceMatrix;
	}

	// set and get for a-priori covariance matrix (generalizing the a-priodi standard deviations)
	// this matrix can very well contain NAN's - this will actually be the standard case for a free point: the apriori standard deviation is infinity
	inline const Eigen::Matrix3d &getAprioriCovarianceMatrix() const { return fAprioriCovarianceMatrix; }
	void setAprioriCovarianceMatrix(const Eigen::Matrix3d &apriCovar)
	{
		fAprioriCovarianceMatrix = apriCovar;
		fHasAprioriCovarianceMatrix = true;
	}

	/// Sets a constant reference on the provisional value of the position vector
	void setProvisionalValue(const TPositionVector &pointProv) { fProvisionalValue = pointProv; };

	/// Sets the covariance matrix
	void setCovarianceMatrix(const Eigen::Matrix3d &covar)
	{
		bool hasNan = (covar.array().isNaN()).any();
		if (hasNan)
			throw std::logic_error("Attempting to set invalid covariance matrix for point " + getName());
		fCovarianceMatrix = covar;
		fCovarianceMatrixIsSet = true;
	};

	/*!
		\brief Calculates and \returns the number of unknowns that are added to the adjustment by this point.
		This number varies from zero to three unknowns.
	*/
	virtual int getNumUnkn() const;

	/// Tells if at least one coordinate is unfixed (variable).
	bool hasVariable() const;

	/// Get the estimated euclidean distance with another adjustable point
	TLength getEstimatedEuclideanDistance(const TAdjustablePoint *ptOther) const;

	/// See \ref TVAdjustableObject::isFixed
	inline virtual bool isFixed() const { return fixedState[0] && fixedState[1] && fixedState[2]; }

	/*!
		\brief See \ref TVAdjustableObject::getFirstUidx

		\throws Throws a logic_error if no component of the point is variable, i.e. a fixed point.
	*/
	virtual int getFirstUidx() const;

	// returns vector of relative indices of free parameters
	const std::vector<int> getRelativeUnknIndices() const;

#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(ObjectSerializer &obj) const override;
#endif
	/*!
		\brief See \ref TVAdjustableObject::getLastUidx

		\throws Throws a logic_error if no component of the point is variable, i.e. a fixed point.
	*/
	virtual int getLastUidx() const;

	/// Returns name of the point */
	inline virtual const std::string &getName() const { return fName; }

	/// Returns the semi major axis of the error ellipsoid
	TLength getErrorEllMajorAxis() const;
	/// Returns the semi minor axis of the error ellipsoid
	TLength getErrorEllMinorAxis() const;
	/// Returns the gisement of the error ellipsoid
	TAngle getErrorEllGis() const;

	/// Returns the three axes of the error ellipsoid
#if USE_SERIALIZER
	struct ErrorEllipsoid : public Serializable
#else
	struct ErrorEllipsoid
#endif // USE_SERIALIZER
	{
		TReal vx[3]; // Direction (unit)vector of the x-semiaxis
		TReal vy[3]; // Direction (unit)vector of the y-semiaxis
		TReal vz[3]; // Direction (unit)vector of the z-semiaxis
		TReal lx; // Length of the x-semiaxis
		TReal ly; // Length of the y-semiaxis
		TReal lz; // Length of the z-semiaxis

		ErrorEllipsoid(TReal vx[3], TReal vy[3], TReal vz[3], TReal lx, TReal ly, TReal lz) :
			vx{vx[0], vx[1], vx[2]}, vy{vy[0], vy[1], vy[2]}, vz{vz[0], vz[1], vz[2]}, lx(lx), ly(ly), lz(lz)
		{
		}

#if USE_SERIALIZER
		// Inherited via Serializable
		virtual void serialize(ObjectSerializer &obj) const override;
#endif
	};
	ErrorEllipsoid getErrorEllipsoid() const;

	/*!
		\brief Returns the estimated coordinate of TAdjustablePoint.

		\param[in] idxCoordinate Allowed values are 0(X), 1(Y) and 2(Z) of the coordinate we want to access.
	*/
	inline TLength getEstValue(int idxCoordinate) const
	{
		assert3D(idxCoordinate);
		if (idxCoordinate == 0)
			return fEstimatedValue.getX();
		else if (idxCoordinate == 1)
			return fEstimatedValue.getY();
		else
			return fEstimatedValue.getZ();
	}
	// If these methods are needed, must be rewritten, because Estimated value and Provisional value can be in different reference systems (2DH and 3DCartesian)/

	/// Returns the estimated DX of TAdjustablePoint
	inline TLength getDXValue() const { return (fEstimatedValue.getX() - fProvisionalValue.getX()); }

	/// Returns the estimated DY of TAdjustablePoint
	inline TLength getDYValue() const { return (fEstimatedValue.getY() - fProvisionalValue.getY()); }

	/// Returns the estimated DZ of TAdjustablePoint
	inline TLength getDZValue() const { return (fEstimatedValue.getZ() - fProvisionalValue.getZ()); }

	/// Returns the estimated XY covariance in [m2]
	inline TReal getXYCovar() const
	{
		ensureCovarIsSet();
		return fCovarianceMatrix(0, 1);
	}

	/// Returns the estimated YZ covariance in [m2]
	inline TReal getYZCovar() const
	{
		ensureCovarIsSet();
		return fCovarianceMatrix(1, 2);
	}

	/// Returns the estimated XZ covariance in [m2]
	inline TReal getXZCovar() const
	{
		ensureCovarIsSet();
		return fCovarianceMatrix(0, 2);
	}

	/// Returns the estimated X estimated precision
	inline TLength getXEstPrecision() const
	{
		ensureCovarIsSet();
		return TLength(sqrt(fCovarianceMatrix(0, 0)));
	}

	/// Returns the estimated Y estimated precision
	inline TLength getYEstPrecision() const
	{
		ensureCovarIsSet();
		return TLength(sqrt(fCovarianceMatrix(1, 1)));
	}

	/// Returns the estimated Z estimated precision
	inline TLength getZEstPrecision() const
	{
		ensureCovarIsSet();
		return TLength(sqrt(fCovarianceMatrix(2, 2)));
	}

	/*!
		\brief Returns The boolean result of the query.

		Checks if a component of the point is excluded from the adjustment.

		\param[in] d Allowed values are 0(X), 1(Y) and 2(Z).
	*/
	inline virtual bool isCoordinateFixed(int d) const
	{
		assert3D(d);
		return (fixedState[d]);
	}

	/*!
		\brief Returns index of an unknown point coordinate in a LS matrices.

		\param[in] d Allowed values are 0(X), 1(Y) and 2(Z).
	*/
	int getCoordinateUnknIndex(int d) const;

	/// Returns reference frame of the point
	inline TRefSystemFactory::ERefFrame getReferenceFrame() const { return fReferential; }

	/// \see TAdjustableObject::isInitialized
	inline virtual bool isInitialized() const { return !isnotanumber(fProvisionalValue.getX().getMetresValue()); }

	/// Returns the height estimated value
	TReal getHEstValue() const;

	/// Returns the spatial status
	inline TSpatialStatus::ESpatialStatus getSpatialStatus() const { return fSpatialStatus; }
	//@}

	/*!@name Settings */
	//@{
	/*!
		\brief See \ref TVAdjustableObject::setCorrection

		Sets correction for the current estimatedValue and updates it, if point has fixed H value transformation is made.

		\throws Throws a logic_error if the adjusted point does not contain required index.
	*/
	virtual void setCorrection(int idx, TReal value);

	/*!
		\brief See \ref TVAdjustableObject::setFirstUidx

		\throws Throws a logic_error if no component of the point is variable, i.e. a fixed point.
	*/
	virtual void setFirstUidx(int idx);

	/// Update the adjustment information of a point, used to set point coordinates fixed if ALLFIXED used
	void updateFixedState(bool lx, bool ly, bool lz);

	/*!
		\brief Re-initialise the object

		Sets the estimated values to be the provisional values and for the precisions, corrections and covariances zeros.
	*/
	void reInitialise();

	//@}

protected:
	TPositionVector fProvisionalValue; /*!< point's provisional value */
	TLength fCorrection[3]; /*!< point's correction after calculation  */
	TPositionVector fEstimatedValue; /*!< point's estimated value after calculation */
	Eigen::Matrix3d fCovarianceMatrix = Eigen::Matrix3d::Zero();
	bool fCovarianceMatrixIsSet{false};
	Eigen::Matrix3d fAprioriCovarianceMatrix = Eigen::Matrix3d::Constant(INFINITY);
	bool fHasAprioriCovarianceMatrix{false};

	TRefSystemFactory::ERefFrame fReferential; /*!< Reference frame of the point */

	std::string fName; /*!< Name of the adjustable point. */

	bool fixedState[3]; /*!< Tells which element of the point is FIXED or VARIABLE (TRUE means that point element is fixed).*/
	int uidx[3]; /*!< Indices of the point elements in LS input matrices (unknowns).*/

	void setDefaults(bool lx, bool ly, bool lz); /*!< Set default adjustment related values.*/

	bool fHfixed; /*!< TRUE if provisional value given in XYH coordinates and H set to be TRUE */

	// This two variables are needed for determinig whether all variable components of a point were set in particular LS calculation run.
	// We need to control it, because in a case that point was defined in 2D+H coordinates and H  with the height value fixed, we need to make transformation X1Y1Z1 ->
	// X1Y1H0 --> X1Y1Z0new, but only after all variable components of a point were updated in this LS run.
	bool fXValueSet; /*!< Tells whether X value was set in one particular LS calculation run, if X component is variable. */
	bool fYValueSet; /*!< Tells whether Y value was set in one particular LS calculation run, if Y component is variable. */

	// This method set an original H0 value to fEstimatedValue, transform it into XYZ coordinates
	void transformEstimatedValue();
	/*!
		\brief ensuring the covariance has been set
	*/
	void ensureCovarIsSet() const
	{
		if (!fCovarianceMatrixIsSet)
		{
			throw std::logic_error("Covariance of point" + getName() + " is not set.");
		}
	};

	/*!Private constructor for creating uninitialized object	*/
	TAdjustablePoint(const std::string &name);

	TSpatialStatus::ESpatialStatus fSpatialStatus;
};
#endif // TADJUSTABLE_POINT
