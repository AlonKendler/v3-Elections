#pragma once
#include <iostream>
#include "Citizen.h"
#include <algorithm>
#include <vector>
#include "DynamicArray.h"


using namespace std;
class DistrictsList;

namespace elc {

	class CitizensList
	{
	private:
		DynamicArray<Citizen*> list;
	
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
		const DynamicArray<Citizen*> getList() const;

		friend void swap(CitizensList& first, CitizensList& second);
		CitizensList& operator=(CitizensList other);
		friend std::ostream& operator<<(std::ostream& out, const CitizensList& other);

		void save(ofstream& out) const;
		void load(ifstream& in, const DistrictsList& _list);
	};
}