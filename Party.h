#pragma once

#include <iostream>
#include "Citizen.h"
#include <vector>
#include "Representative.h"
#include "CitizenList.h"

using namespace std;

namespace elc {
class CitizensList;

	
	class Party {
	private:
		string partyName;
		int partyID;
		const Citizen* boss; //citizen&
		vector<vector<Representative>> RepsList;

	public:


		Party() = default;
		Party(string _partyName, const Citizen& _boss, int _id)
			: partyName(_partyName), partyID(_id), boss(&_boss), RepsList() {}

		Party(const Party& o) : partyName(o.partyName), partyID(o.partyID), boss(o.boss)
		{
			RepsList = o.RepsList;
		}

		virtual ~Party(){}
		
		//--Getters--//
		string getPartyName() const				{ return partyName; };
		const Citizen& getBoss() const			{ return *boss; };
		int getpartyID() const					{ return partyID; };

		const vector<Representative>& getRepsFromDist(const int distID) const { return RepsList[distID]; }
		const vector<vector<Representative>>& getRepsList() const { return RepsList; }

		//--Setters--//
		void setPartyName(string _n)			{ partyName = _n; };
		void setBoss(const Citizen& b)			{ boss = &b; };
		void setpartyID(int n)				{ partyID = n; };

		//work of shabat 21:00
		void updateRepsList(unsigned int districtsAmount);
		void addRepresentative(const Citizen& rep, int distID);


		//--https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
		friend void swap(Party& first, Party& second);

		friend std::ostream& operator<<(std::ostream& out, Party& other);

		Party& operator=(Party other);

		void printNameAndId() const;

		void save(ofstream& out) const;
		void load(ifstream& in, const CitizensList& _list);

	};

};

