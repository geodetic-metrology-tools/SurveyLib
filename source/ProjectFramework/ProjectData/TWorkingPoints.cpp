// TWorkingPoints.cpp: implementation of the TWorkingPoints class.
//




#include "TWorkingPoints.h"
//ClassImp(TWorkingPoints)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TWorkingPoints::TWorkingPoints():fLastPtNbr(0)
{
	fBroadcaster = new TPtListBroadcaster();
}

TWorkingPoints::~TWorkingPoints()
{
	if( fBroadcaster != 0 )
	{
		delete fBroadcaster;
	}
}


/////////////////////////////////////////////////////////////
// Adding a Spatial point to the pointsSet member variable
/////////////////////////////////////////////////////////////
bool TWorkingPoints::addPoint(TSpatialPoint *sp){
	
	string empty("");
	bool insert_ok = false;

	// check that the point is not already in the list
	if (fWorkingPoints.find(sp->getName().getName()) == fWorkingPoints.end())
	{
		if (((sp->getName()).getName()) == empty){
			ostringstream oss;
			fLastPtNbr ++;
			oss << "SpPt" << fLastPtNbr;
			sp->setName(TSpatialPointName(oss.str()));
		}
		sp->setListener(this);
		fWorkingPoints[sp->getName().getName()] = pointsList.size();
		pointsList.push_back(*sp);
			
		insert_ok = true;
	}

	return insert_ok;
}

/////////////////////////////////////////////////////////////
// Adding a Spatial point to the pointsSet member variable
/////////////////////////////////////////////////////////////
bool TWorkingPoints::insertPoint(TSpatialPoint *sp, int pos){
	
	string empty("");
	bool insert_ok = false;
	int origNumPoints = fWorkingPoints.size();
	
	// check that the point is not already in the list
	if (fWorkingPoints.find(sp->getName().getName()) == fWorkingPoints.end())
	{

		if (((sp->getName()).getName()) == empty){
			ostringstream oss;
			fLastPtNbr ++;
			oss << "SpPt" << fLastPtNbr;
			sp->setName(TSpatialPointName(oss.str()));
		}

		sp->setListener(this);

		PointIterator iter = pointsList.begin();
		for (int i=0; i < pos; i++)
		{
				iter++;
		}
		fWorkingPoints[sp->getName().getName()] = pos;
		pointsList.insert(iter, *sp);

		while (iter != pointsList.end())
		{
			fWorkingPoints[iter->getName().getName()]++;
			iter++;
		}
			
		insert_ok = true;
	}

	/*FOR CHABA INTERFACE USE ONLY!!!*/
	//if time stamp happens to be the same if clicked in quick succesion
	else 
	{
	
		/*PUT HERE FOR NOW*/
		string name = sp->getName().getName(); 
		string s = name.substr(0,15);

		if (s == "Insert_New_Row_")
		{
			ostringstream oss;
			fLastPtNbr++;
			oss << name << fLastPtNbr;	
			sp->setDuplicatePtName(oss.str());
			sp->setListener(this);

			PointIterator iter = pointsList.begin();
			for (int i=0; i < pos; i++)
			{
					iter++;
			}
			fWorkingPoints[sp->getName().getName()] = pos;
			pointsList.insert(iter, *sp);

			while (iter != pointsList.end())
			{
				fWorkingPoints[iter->getName().getName()]++;
				iter++;
			}
				
			insert_ok = true;
		}


	}

	insert_ok = (fWorkingPoints.size() == (origNumPoints + 1));
	return insert_ok;
}


bool TWorkingPoints::deletePoint(PointIterator iter)
{
	bool delete_ok;
	int origNumPoints = fWorkingPoints.size();

	if (iter == pointsList.end())
	{
	 delete_ok = false;
	}
		
	else
	{
	fWorkingPoints.erase(iter->getName().getName());
		pointsList.erase(iter);
	 delete_ok = true;
	}
	
	delete_ok = (fWorkingPoints.size() == (origNumPoints - 1));
	return delete_ok;
}

/////////////////////////////////////////////////////////////////
// Returns the number of Spatial Points stored in the pointsSet
/////////////////////////////////////////////////////////////////

int TWorkingPoints::numberOfPoints() const{

	return fWorkingPoints.size();
}


/////////////////////////////////////////////////////////////////
// Returns an iterator on the first element of the fWorkingPoints
/////////////////////////////////////////////////////////////////
PointIterator TWorkingPoints::getPointsBeginIterator() {

	return pointsList.begin();
}

//////////////////////////////////////////////////////////////////////
// Returns a const iterator on the first element of the fWorkingPoints
//////////////////////////////////////////////////////////////////////
PointConstIter TWorkingPoints::getPointsBeginIterator() const{

	return pointsList.begin();
}

////////////////////////////////////////////////////////////////////
// returns an iterator on one element past the end of fWorkingPoints
////////////////////////////////////////////////////////////////////
PointIterator TWorkingPoints::getPointsEndIterator() {

	return pointsList.end();
}

/////////////////////////////////////////////////////////////////////////
// returns a const iterator on one element past the end of fWorkingPoints
/////////////////////////////////////////////////////////////////////////
PointConstIter TWorkingPoints::getPointsEndIterator() const{

	return pointsList.end();
}

///////////////////////////////////////////////////////////////////
// returns an iterator on a point, given its TSpatialPointName
///////////////////////////////////////////////////////////////////
PointIterator TWorkingPoints::getPoint(TSpatialPointName spn) {

	hash_map<string, int>::iterator i = fWorkingPoints.find(spn.getName());
	if (i == fWorkingPoints.end())
	{
		return pointsList.end();
	}
	return pointsList.begin() + i->second;
}

///////////////////////////////////////////////////////////////////
// returns a const iterator on a point, given its TSpatialPointName
///////////////////////////////////////////////////////////////////
PointConstIter TWorkingPoints::getPoint(TSpatialPointName spn) const{

	hash_map<string, int>::const_iterator i = fWorkingPoints.find(spn.getName());
	if (i == fWorkingPoints.end())
	{
		return pointsList.end();
	}
	return pointsList.begin() + i->second;
}

void TWorkingPoints::headerChanged(TSpatialPointName name)
{
	PointIterator iter = getPoint(name);
	fBroadcaster->headerChanged(iter);

}


void TWorkingPoints::ptNameChanged(TSpatialPointName name)
{
	PointIterator iter = getPoint(name);
	fBroadcaster->ptNameChanged(iter);
}

void TWorkingPoints::positionChanged(TSpatialPointName name)
{
	PointIterator iter = getPoint(name);
	fBroadcaster->positionChanged(iter);
}
	
void TWorkingPoints::distChanged(TSpatialPointName name)
{
	PointIterator iter = getPoint(name);
	fBroadcaster->distChanged(iter);
}
	
void TWorkingPoints::statusChanged(TSpatialPointName name)
{
	PointIterator iter = getPoint(name);
	fBroadcaster->statusChanged(iter);
}

void TWorkingPoints::addListener(TVPtListListener* listener)
{

	fBroadcaster->addListener(listener);
}

void TWorkingPoints::deleteListener(TVPtListListener* listener)
{

	fBroadcaster->deleteListener(listener);
}


