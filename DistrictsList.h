#pragma once
#include <iostream>
#include "district.h"
#include <vector>


using namespace std;

namespace  elc {

	class DistrictsList
	{
	private:
		vector<District*> list; //hold pointers vecause have base-inheritance disttricts

	public:
		DistrictsList()  {}
		~DistrictsList() {}
		DistrictsList(const DistrictsList& other) { list = other.list;  }

		
		void setDistrict(string _DistrictName, int numOfReps, bool div);
		void setDistrict(District* _dist);

		bool setCitizenInDist(const  Citizen&, const District& dist);

		const District& getDistrict(const int& distID) const { return *(list[distID]); }
		District& getDistrict(int distID, bool flag) const { return *(list[distID]); }
		vector<District*> const getList() const { return list; }

	//	const int& getTotalRepsInDist(const int& distID) const { return list[distID]->getDistReps(); }
		void PrintNameAndId();


		friend void swap(DistrictsList& first, DistrictsList& second);
		DistrictsList& operator=(DistrictsList other);
		friend std::ostream& operator<<(std::ostream& out, const DistrictsList& other);

		//void save(ofstream& out) const;
		//void load(ifstream& in);

	};



}