/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef TADJUSTABLE_LENGTH
#define TADJUSTABLE_LENGTH

#include "TLength.h"
#include "TVAdjustableObject.h"

/*!
	\ingroup AdjustableObjects
	\brief Class providing adjustable related information for a TLength class.
*/
class TAdjustableLength : public TVAdjustableObject
{
public:
	/*!@name Constructors */
	//@{
	/*!
		\brief Constructs an TAdjustableLength based on an existing TLength value.

		\param[in] lengthValue A reference to an length that will be adjusted. The length will be copied
							  so the pointed-to object is no longer needed after construction.
		\param[in] isFixed The length will be excluded from the adjustment if set to TRUE, i.e. fixed length.
		\param[in] name Name of the adjustable length.
	*/
	TAdjustableLength(const TLength &lengthValue, bool isFixed, const std::string &name);
	//@}
	/// Create an unitialized length, the length is by default fixed and has no NO_VALf inside.
	static TAdjustableLength createUninitialized(const std::string &name);

	/*!@name Access methods*/
	//@{
	/// Returns a constant reference on the provisional value of the length.
	inline const TLength &getProvisionalValue() const { return fProvisionalValue; }

	/// Returns a constant reference on the correction value.
	inline const TLength &getCorrection() const { return fCorrection; }

	/// Returns a constant reference on the estimated value of the length.
	inline const TLength &getEstimatedValue() const { return fEstimatedValue; }

	/// Returns a constant reference on the estimated precision of the length.
	inline const TLength &getEstimatedPrecision() const { return fEstimatedPrecision; }

	/*!
		\brief Returns The number of unknowns for this length.

		Number of unknowns that are added to the adjustment by this length.
		This number varies from zero to 1 unknowns.
	*/
	inline virtual int getNumUnkn() const { return (int)!ifFixed; }

	/// See \ref TVAdjustjustableObject::isFixed
	inline virtual bool isFixed() const { return ifFixed; }

	/*!
		See \ref TVAdjustableObject::getFirstUidx

		\throws Throws a logic_error if the length is fixed.
	*/
	inline virtual int getFirstUidx() const
	{
		if (!ifFixed)
			return uidx;
		throw std::logic_error("Trying to get unknown index from fixed length.");
	}

	/*!
		See \ref TVAdjustableObject::getLastUidx

		\throws Throws a logic_error if no component of the length is variable, i.e. a fixed length.
	*/
	inline virtual int getLastUidx() const
	{
		if (!ifFixed)
			return uidx;
		throw std::logic_error("Trying to get unknown index from fixed length.");
	}

	// returns vector of relative indices of free parameters
	const std::vector<int> getRelativeUnknIndices() const override
	{
		std::vector<int> activeIndices;
		if (!ifFixed)
			activeIndices.push_back(0);
		return activeIndices;
	};

	/// Returns the name of the length.
	inline virtual const std::string &getName() const { return fName; }

	/// Returns TRUE since the length is always initialized.
	inline virtual bool isInitialized() const { return true; }

	//@}

	/*!@name Settings */
	//@{
	/// Set the provisional value of the length from a constant reference
	void setProvisionalValue(const TLength &provisionalValue) { fProvisionalValue = provisionalValue; };

	/*! Set the fixed state of the length */
	void setFixed(bool fixed) { ifFixed = fixed; }

	/*!
		See \ref TVAdjustableObject::setFirstUidx

		\throws Throws a logic_error if the length is fixed.
	*/
	virtual void setFirstUidx(int idx);

	// getting the estimated vector with all variables
	virtual Eigen::VectorXd getEstVector() const override;
	// get value corresponding to unknown index
	virtual TReal getValue(int idx) const override;
	// set the value corresponding to an index
	virtual void setValue(int idx, TReal value) override;
	//set the estimated value
	void setEstValue(TReal value) { fEstimatedValue.setMetresValue(value); };

	/*! Sets the estimated precision after calculation in radians.*/
	void setEstimatedPrecision(int idx, TReal ep);

	/*!
		\brief Re-initialise the object

		Sets the estimated values to be the provisional values and for the precisions, correections and covariances zeros. Typically used for SIMULATION.
	*/
	void reInitialise();

	//@}

	bool operator==(const TAdjustableLength &other) const;

#if USE_SERIALIZER
	// Inherited via Serializable
	virtual void serialize(ObjectSerializer &obj) const override;
#endif

private:
	TLength fProvisionalValue; /*!< length provisional value. */
	TLength fCorrection; /*!< length correction after calculation.  */
	TLength fEstimatedValue; /*!< length estimated value after calculation. */
	TLength fEstimatedPrecision; /*!< length estimated precision after calculation. */

	bool ifFixed; /*!< Tells if the length is excluded from the adjustment, TRUE = fixed*/
	int uidx; /*!< Index of the length in LS input matrix (unknown) */

	std::string fName; /*!< Name of the adjustable length. */
};

#endif // TADJUSTABLE_length
