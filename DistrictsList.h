#pragma once
#include <iostream>
#include "district.h"
#include <vector>
#include "DynamicArray.h"


using namespace std;

namespace  elc {

	class DistrictsList
	{
	private:
		DynamicArray<District*> list; //hold pointers vecause have base-inheritance disttricts

	public:
		DistrictsList()  {}
		DistrictsList(const DistrictsList& other) { list = other.list;  }
		~DistrictsList() 
		{
			for (auto itr : list)
				delete itr;
		}

		
		void setDistrict(string _DistrictName, int numOfReps, int div);
		void setDistrict(District* _dist);

		bool setCitizenInDist(const  Citizen&, const District& dist);

		District* getDistrictPtr(const int& distID) const;
		const District& getDistrict(const int& distID) const;


		District& getDistrict(int distID, bool flag) const { return *(list[distID]); }
		DynamicArray<District*> const getList() const { return list; }

	//	const int& getTotalRepsInDist(const int& distID) const { return list[distID]->getDistReps(); }
		void PrintNameAndId();


		friend void swap(DistrictsList& first, DistrictsList& second);
		DistrictsList& operator=(DistrictsList other);
		friend std::ostream& operator<<(std::ostream& out, const DistrictsList& other);

		void save(ofstream& out) const;
		void load(ifstream& in);

	};



}