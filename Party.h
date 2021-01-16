#pragma once

#include <iostream>
#include "Citizen.h"
#include <vector>
#include "Representative.h"

using namespace std;
namespace elc {

	
	class Party {
	private:
		string partyName;
		int partyID;
		const Citizen* boss; //citizen&
		vector<vector<Representative>> RepsList;

	public:

		Party(string _partyName, const Citizen& _boss, int _id)
			: partyName(_partyName), partyID(_id), boss(&_boss), RepsList() {}

		Party(const Party& o) : partyName(o.partyName), partyID(o.partyID), boss(o.boss)
		{
			RepsList = o.RepsList;
		}

		~Party(){}
		
		//--Getters--//
		string getPartyName() const				{ return partyName; };
		const Citizen& getBoss() const			{ return *boss; };
		int getpartyID() const					{ return partyID; };

		const vector<Representative>& getRepsFromDist(const int distID) const { return RepsList[distID]; }

		//--Setters--//
		void setPartyName(string _n)			{ partyName = _n; };
		void setBoss(const Citizen& b)			{ boss = &b; };
		void setpartyID(int n)				{ partyID = n; };


		//--https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
		friend void swap(Party& first, Party& second);

		friend std::ostream& operator<<(std::ostream& out, Party& other);

		Party& operator=(Party other) // (1)
		{
			swap(*this, other); // (2)
			return *this;
		}
		void printNameAndId() const;

	//	void save(ofstream& out) const;
	//	void load(ifstream& in, const CitizensList& _list);

	};

};

