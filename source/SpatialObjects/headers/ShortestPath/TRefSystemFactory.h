/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//  TRefSystemFactory.h

/*! A singleton class listing reference surface, reference frame and reference frame transformation.
	A "server" of these systems. 
  
    Patterns: a flyweight factory of reference systems
  
*/
//////////////////////////////////////////////////////////////////////



#ifndef SU_REF_SYS_FACTORY
#define SU_REF_SYS_FACTORY


#if _MSC_VER >= 1000
#pragma once
#pragma warning (disable:4786)
#endif // _MSC_VER >= 1000


////////////////////////////////////////////////////////////////
// Forward declarations
//
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include <stddef.h>

class TAGeoidModel;
class TReferenceEllipsoid;
class TAReferenceFrame;
class TGeodeticRefFrame;
class TTerrestrialReferenceFrame;
class TModifiedLocalAstronomicalRF;
class TModifiedLocalGeodeticRF;
class THelmertRefFrameTransform;
class TCernGridGeoid;
class TARefFrameTransformation;
class TSpatialPosition;
class TScaleFactor;

#include <TLocalSystemOrigin.h>
//
//
////////////////////////////////////////////////////////////////

/*!\ingroup spatialobjects
	@{*/

//#define PHIP0 LITERAL(51.3692);

//! Singleton class: produce one unique instance listing ref. surfaces, ref.frames and transformations
class TRefSystemFactory
{
public:

	//!@name Constants
	//@{
		/*! Enumerator for ellipsoids implemented in the factory */
		enum  ERefEll {kGRS80, kWGSEll, kInternationalEll, kSphere, kNoEllipsoid, kBessel1841};
		/*! Enumerator for geoids implemented in the factory */
		enum  EGeoid {kCG2000, kCG2000Machine, kCG2000topo, kCG1985, 
			          kCG1985Machine, kNoGeoid, kCGSphere};
		/*! Enumerator for Reference Frames implemented in the factory */
		enum  ERefFrame {
			kCCS                 =  0, 
			kLAp0                =  1,
			kLGp0                =  2, 
			kCGRF                =  3, 
			kITRF97              =  4, 
			kWGS84_G2139         =  5, 
			kETRF93              =  7,
			kCH1903plus          =  8, /*!< Swiss coordinate system */
			kCGRF_new            =  9,
			kCCS_new             = 10,
			kLAp0_new            = 11,
			kLGp0_new            = 12,
			kITRFin              = 13,
			kITRFout			 = 14,
			kETRFin              = 15,
			kETRFout			 = 16,
			// Projections:
			kCernXYHe            = 100, 
			kCernX0Y0He          = 101, 
			kCernXYHg00          = 102, 
			kCernXYHg00Topo      = 103, 
			kCernXYHg00Machine   = 104, 
			kCernXYHg85          = 105, 
			kCernXYHg85Machine   = 106, 
			kCERNXYHsSphereSPS   = 107, 
			kCGRFSphere          = 108,
			kCGRFMercator_eh	 = 115,
#ifdef USE_SWISSTOPO
            kSwissLV95_eh        = 109,
            kSwissLV03_eh        = 110,
			kSwissLV95_lhn95	 = 111,
			kSwissLV03_ln02	 = 112,
			kSwissLV95_ln02		 = 113,
			kSwissLV03_lhn95	 = 114,
#endif
			//Franch system
			kFrenchRGF93_CC46_eh = 205,
			kFrenchRGF93_CC46_ign69 = 206,
			kLambert93_eh		 = 207,
			kLambert93_ign69		 = 208,			
			kRGF93               = 209,

			kCHTRF95             = 210,
			// Local Reference Frames:
			kMLA1985Machine      = 1000,
			kMLA2000Machine      = 1001,
			kMLASphere           = 1002,
			kMLA2000Topo         = 1003,
			kMLA2000H0           = 1004,
			kMLA1985H0           = 1005,

			kLA1985Machine       = 1010,
			kLA2000Machine       = 1011,
			kLASphere            = 1012,
			kLA2000Topo          = 1013,
			kLA2000H0            = 1014,
			kLA1985H0            = 1015,

			kMLGGRS80            = 2000,
			kMLGSphere           = 2001,
			kLGGRS80             = 2010,
			kLGSphere            = 2011,

			// Local RF with transformation matrix
			kLocalRFin = 3001,
			kLocalRFout = 3002,

			// Reserved value:
			kNotInGraph			 = -1,
			kLocalRefFrame       = -2 /*!< This was present in the TDataParameters variant. Referenced in LGC in few places */
      };

		/*! Enumerator for transformations between Ref.Frames implemented in the factory */
		enum  ERefFrameTransform {
			kCCS2CGRF, kLAp02LGp0, kLGp02CGRF, kLAp02CCS,
			kXYHe2CCS, kX0Y0He2XYHe,
			kXYHg2XYHe, kXYHg2XYHe00Topo, kXYHg2XYHe00Machine,
			kXYHg2XYHe85, kXYHg2XYHe85Machine, kXYHsSphereSPS2CCS,
			kCCS2CGRFSphere, kCGRF2CGRFMercator,
			kCGRF2CCS, kLGp02LAp0, kCGRF2LGp0, kCCS2LAp0,
			kCCS2XYHe, kXYHe2X0Y0He,
			kXYHe2XYHg, kXYHe00Topo2XYHg, kXYHe00Machine2XYHg,
			kXYHe852XYHg, kXYHe85Machine2XYHg, kCCS2XYHsSphereSPS,
			kCGRFSphere2CCS, kCGRFMercator2CGRF, kITRF972CGRF, kCGRF2ITRF97,
			kETRF932CH1903plus, kCH1903plus2ETRF93,
#ifdef USE_SWISSTOPO
			kCH1903plus2SwissLV95eh, kSwissLV95eh2CH1903plus, kCH1903plus2SwissLV95lhn95, kSwissLV95lhn952CH1903plus, 
			kSwissLV95eh2SwissLV03eh, kSwissLV03eh2SwissLV95eh,kSwissLV95eh2SwissLV03ln02, kSwissLV03ln022SwissLV95eh,
			kSwissLV95eh2SwissLV03lhn95, kSwissLV03lhn952SwissLV95eh, kCH1903plus2SwissLV95ln02, kSwissLV95ln022CH1903plus,
#endif
			kCC46eh2RGF93, kRGF932CC46eh, kCC46raf2RGF93, kRGF932CC46ign69, 
			kRGF932Lambert93eh, kLambert93eh2RGF93, kRGF932Lambert93ign69, kLambert93ign692RGF93,
			
			//new
			kCCS2CGRF2, kITRF972CGRF2,
			kCGRF22CCS, kCGRF22ITRF97,

			//Transformation between ITRF and ETRF
			kITRFin2ETRFout, kITRFin2ITRFout, kETRFin2ETRFout, kETRFin2ITRFout,
			kITRF972ETRF93, kETRF932ITRF97,
			kITRF972ETRFout, kETRFin2ITRF97,
			kITRFin2ITRF97, kITRF972ITRFout,
			kITRF972RGF93, kRGF932ITRF97,
			kITRF972CHTRF95, kCHTRF952ITRF97,
			kITRF972WGS84, kWGS842ITRF97,

			//Transformation between CAD systems and CCS
			kLocalRFin2CCS,
			kCCS2LocalRFout
		};
	//@}
	

	/*!@name Member Functions */
	//@{
		/*! Instance method to obtain a pointer to the TRefSystemFactory instance */
		static TRefSystemFactory* getRefSystemFactory();	
		
		/*! Return a pointer to the geoid asked for 
		\param geoidId an element of the existing geoid enumeration */
		TAGeoidModel* getGeoid(const EGeoid geoidId);

		/*! Return a pointer to the reference ellipsoid asked for 
		\param ellId an element of the existing ellipsoid enumeration */
		TReferenceEllipsoid* getEllipsoid(const ERefEll ellId);
		
		/*! Return a pointer to the reference frame asked for 
		\param refFrameId an element of the existing Ref. Frame enumeration */
		TAReferenceFrame* getRefFrame(const ERefFrame refFrameId);

		/*! Return a pointer to the reference frame transformation asked for 
		\param transformId an element of the existing transformations enumeration */
		TARefFrameTransformation* getTransformation(const ERefFrameTransform transformId);

		/*! Return the transformation between two reference frames
			\return a vector of Reference Frame transformations */
		//vector<TARefFrameTransformation&> getTransform(const ERefFrame refFrameIdfrom, const ERefFrame refFrameIdto);
	
		/*! test if the reference frame is in graph or not 
		\param pointer to a Ref. Frame
		\return true if the ref. frame is in graph*/
		bool isInRFFactory( const TAReferenceFrame* );

		/*! Return a pointer to TGeodeticRefFrame
		\param reference frame id
		\return an error message (cerr) if the id is not cooresponding to a TGeodeticRefFrame*/
		TGeodeticRefFrame*	getGeoRefFrame(const ERefFrame refFrameId);

		//return a point to a Terrestrial Reference Frame
		TTerrestrialReferenceFrame* getTerrRefFrame (const ERefFrame refFrameId);

		// Update terrestrial reference frame with current epoch and solution
		void updateTerrestrialRefFrame(TReal epoch, std::string solution, ERefFrame frame);

		//return a pointer to a new Local ref Frame and put it in a list in order to be deleted
		TAReferenceFrame* getNewLocalRefFrame();

		//return a pointer to a new Modified Local Astronomic ref Frame and put it in a list in order to be deleted
		TAReferenceFrame* getNewLocalRefFrame(const TLocalSystemOrigin & LSO, EGeoid geoid, ERefFrame frame);

		// return a pointer to the CAD system with the path to the transformation matrix
		TAReferenceFrame* updatePathTotransformationMatrix(const std::string &pathToTransformationMatrix, ERefFrame frame);
	//@}


protected:

	/*!@name Constructors and Destructors */
	//@{
		/*! Default Constructor: build the unique instance of TRefSystemFactory */
		TRefSystemFactory();

		/*! Destructor */
		virtual  ~TRefSystemFactory();

private:

	/*! Copy constructor */
	TRefSystemFactory( const TRefSystemFactory& );
	//@}

	void	init();
	void initEllipsoidList();
	void initGeoidList();
	void addGeodeticRefFrames();
	void addGenericETRFandITRF();
	void addFrenchProjections();
	void addSwissProjections();
	void addTerrestrialRefFramesTransformations();
	void addFrenchTransformations();
	void addSwissTransformations();
	void addLocalRefFrameTransformations();

	TModifiedLocalGeodeticRF* createModifiedLocalGeodeticRF(TGeodeticRefFrame* refFrame, const std::string &frameName, const TAngle &phi_origine, const TAngle &lambda_origin, const TLength &h_origin);
	THelmertRefFrameTransform* createHelmertRefFrameTransform(TAReferenceFrame *from, TAReferenceFrame *to, const TAngle &rX, const TAngle &rY, const TAngle &rZ, const TLength &tX, const TLength &tY, const TLength &tZ, const TScaleFactor &scaleFactor);
	/*! Copy Assigment Operator */
	TRefSystemFactory& operator=( const TRefSystemFactory& );

	/*! Add an object to a list of unique pointers, forwarding the arguments to the constructor of the object */
	template<typename T, typename... Args>
	void addObject(std::vector<T*> &list, Args &&...args)
	{
		list.push_back(new T(std::forward<Args>(args)...));
	}

	/*! Create object, set Id and add to list*/
	template<typename T, typename ListT, typename IdT, typename... Args>
	void createObjectSetIdAndAddToList(IdT id, ListT &list, Args &&...args)
	{
		T *obj = new T(std::forward<Args>(args)...);
		setIdAndAddToList(obj, id, list);
	}

	/*! Set Id and add to the list */
	template<typename ListT, typename T, typename IdT>
	void setIdAndAddToList(T *obj, IdT id, ListT &list)
	{
		obj->setId(id);
		list.push_back(obj);
	}

	/*! Create and add a transformation and its inverse to the list, setting their Ids */
	template<typename TTransfomation, typename... Args>
	void addTransformationPair(ERefFrameTransform forwardId, ERefFrameTransform inverseId, Args &&...args)
	{
		auto *forwardTransformation = new TTransfomation(std::forward<Args>(args)...);
		setIdAndAddToList(forwardTransformation, forwardId, fTransformList);

		auto *inverseTransformation = forwardTransformation->inverse();
		setIdAndAddToList(inverseTransformation, inverseId, fTransformList);
	}

	/*! Add a transformation and its inverse to the list, setting their Ids */
	template<typename T, typename ListT, typename IdT>
	TARefFrameTransformation *addTransformationAndInverse(T *forward, IdT forwardId, IdT inverseId, ListT &list)
	{
		setIdAndAddToList(forward, forwardId, list);

		auto *inverse = forward->inverse();
		setIdAndAddToList(inverse, inverseId, list);

		return inverse;
	}

	/*! Matrix creation helper*/
	template<size_t R, size_t C>
	std::unique_ptr<TMatrix> makeMatrix(const std::array<std::array<TReal, C>, R> &src)
	{
		auto m = std::make_unique<TMatrix>(R, C);

		for (size_t i = 0; i < R; ++i)
			for (size_t j = 0; j < C; ++j)
				(*m)(static_cast<int>(i), static_cast<int>(j)) = src[i][j];

		return m;
	}

	/*! Geoid grid creation helper*/
	template<size_t R, size_t C>
	TCernGridGeoid *createCernGridGeoid(const std::string &name,
		const std::array<std::array<TReal, C>, R> &n,
		const std::array<std::array<TReal, C>, R> &eta,
		const std::array<std::array<TReal, C>, R> &xsi,
		const TPositionVector &dl,
		const TPositionVector &ur,
		const TRefSystemFactory::EGeoid geoidId)
	{
		auto N = makeMatrix(n);
		auto Eta = makeMatrix(eta);
		auto Xsi = makeMatrix(xsi);

		TCernGridGeoid *g = new TCernGridGeoid(name, geoidId, N.release(), Eta.release(), Xsi.release(), dl, ur, getRefFrame(TRefSystemFactory::kCGRF),
			getEllipsoid(TRefSystemFactory::kGRS80), getRefFrame(TRefSystemFactory::kCCS));

		return g;
	}

		template<typename T>
	T* getRefFrame(ERefFrame id)
	{
		TAReferenceFrame *base = getRefFrame(id); // existing function
		T *typed = dynamic_cast<T *>(base);

		if (!typed)
			throw std::bad_cast();

		return typed;
	}
	
private:
	static TRefSystemFactory* fRefSystemFactory; /*!< static member that contains a pointer to the unique instance of TRefSystemFactory */

	std::vector<TAGeoidModel*> fGeoidList;	/*!< list of pointers to the to-be-defined geoids */
	std::vector<TReferenceEllipsoid*> fRefEllList; /*!< list of pointers to the to-be-defined ellipsoids */
	std::vector<TAReferenceFrame*> fRefFrameList; /*!< list of pointers to the to-be-defined Ref.Frames */

	std::vector<TAReferenceFrame*> fLocalRefFrameList; /*!< list of pointers to the local Ref.Frames */

	std::vector<TARefFrameTransformation*> fTransformList; /*!< list of pointers to the to-be-defined Ref.Frame transformations */
	//il est important que ce soit une classe TA plutot que TV pour avoir acces au destructeur


	TGeodeticRefFrame *fCGRF = nullptr;
	TGeodeticRefFrame *fCGRFSphere = nullptr;
	TGeodeticRefFrame *fCGRF2 = nullptr;

	TTerrestrialReferenceFrame* fITRFin = nullptr;
	TTerrestrialReferenceFrame* fITRFout = nullptr;
	TTerrestrialReferenceFrame* fETRFin = nullptr;
	TTerrestrialReferenceFrame* fETRFout = nullptr;
};
/*@}*/

#endif // SU_REF_SYS_FACTORY
