#pragma once
#include <iostream>
#include "Citizen.h"
#include <algorithm>
#include <vector>


using namespace std;
class DistrictsList;

namespace elc {

	class CitizensList
	{
	private:
		vector<Citizen*> list;
	
	public:
		CitizensList ()  {}
		~CitizensList()  
		{
			for (auto itr : list)
				delete itr;
		}
		CitizensList(const CitizensList& other) { list = other.list; }

		void setCitizen(Citizen*);
		void setCitizen(const string name, int id, int yob, const District& district);

		Citizen* const getCitizenPtr(int id) const;
	//	const Citizen&  getCitizen(int id) const;
		const vector<Citizen*> getList() const;

		//bool removeCitizen(const Citizen&);

		friend void swap(CitizensList& first, CitizensList& second);
		CitizensList& operator=(CitizensList other);
		friend std::ostream& operator<<(std::ostream& out, const CitizensList& other);

		void save(ofstream& out) const;
		void load(ifstream& in, const DistrictsList& _list);
	};
}