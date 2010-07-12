#ifndef CSGEOCORE_T_REF_FRAME_INFO_H_78d85635badc4fa08dd883eb60f912d4
#define CSGEOCORE_T_REF_FRAME_INFO_H_78d85635badc4fa08dd883eb60f912d4

#include <TCoordSysFactory.h>
#include <TRefSystemFactory.h>
#include <map>
#include <set>


/**
 *  Class for providing additional related information to the TRefSystemFactory::ERefFrame.
 *
 *  Each reference frame is being identified by a value from ERefFrame enum.
 *  However there is a need to associate some additional information
 *  with the enum values. For example:
 *     - Coordinate system  
 *     - User friendly name
 *
 *  In addition the class provides an easy way to iterate over the all 
 *  supported ERefFrame enum values.
 */
class TRefFrameInfo
{
private:
	/*! Constructor is private and has no definition. This class cannot be instantiated. */
	TRefFrameInfo();
    TRefFrameInfo(const TRefFrameInfo & other); // non construction-copyable
    const TRefFrameInfo & operator=(const TRefFrameInfo &); // non copyable

	struct TDetails
	{
		TDetails(const std::string & name, TCoordSysFactory::ECoordSys coordSys, bool local=false);
		const std::string fName;
        // @@@@ This will have to be changed! More than one system is allowed!!!
		const TCoordSysFactory::ECoordSys fDefaultCoordSys;
        const bool fLocal;
	};
	typedef std::map<TRefSystemFactory::ERefFrame, TDetails> MappingType;
	static const MappingType & getMapping();
public:
	typedef std::set<TRefSystemFactory::ERefFrame> RefFrameSet;

	/**
	 *  \return The set containing all the supported ERefFrame enum values.
	 */
	static const RefFrameSet & getRefFrameSet();

	/**
	 *  Check if the value can be converted into a registered
	 *  TRefSystemFactory::ERefFrame value.
     *
	 *  \param[in] frame Integer value corresponding to the ERefFrame enum value
	 */
	static bool isValidNumber(int frame);

	/**
	 *  Convert the value a registered TRefSystemFactory::ERefFrame value.
     *
	 *  \param[in] frame Integer value corresponding to the ERefFrame enum value
	 *	\return Corresponding TRefSystemFactory::ERefFrame value
	 *  \throw std::invalid_argument If the input parameter is not valid
	 */
	static TRefSystemFactory::ERefFrame fromNumber(int frame);

	/**
	 *  Retrieve a user friendly name of the ERefFrame.
	 *
	 *  \param[in] frame Integer value corresponding to the ERefFrame enum value
	 *  \return A user friendly name associated with the given reference frame
	 *  \throw std::invalid_argument If the input parameter is not valid
	 */
	static const std::string & getName(int frame);

	/**
	 *  Retrieve a default coordinate system for the ERefFrame.
	 *
	 *  \param[in] frame Integer value corresponding to the ERefFrame enum value
	 *  \return Default TCoordSysFactory::ECoordSys value for the given reference frame
	 *  \throw std::invalid_argument If the input parameter is not valid
	 */
	static TCoordSysFactory::ECoordSys getDefaultCoordSys(int frame);

    static bool isLocalRefFrame(int frame);

    static TAReferenceFrame * getReferenceFrame(int frame, const LocalSystemOrigin * lso = NULL);
};


#endif
