#pragma once
#include <iostream>
#include "Party.h"


using namespace std;

namespace  elc {



	class PartyList
	{
	protected :
		vector<Party*> list;
		

	public:
		PartyList()  {}
		PartyList(const PartyList& other) { list = other.list;  }
		~PartyList()
		{
			for (auto itr : list)
				delete itr;
		}


		void setParty(string _partyName, const Citizen& boss, int numOfDistricts);
		void setParty(Party*);

		Party* getParty(int partyID) ;
		//string const getPartyName(const int& partyID) const;
		const int& getSize() const { return list.size(); }
		vector<Party*> const getList() const { return list; }
		const Representative& getPartyRepInDist(const int& partyID, const int& DistID, const int& place) { return list[partyID]->getRepsFromDist(DistID).at(place); }

		void updateRepsList(int districtsAmount);
		void addPartyCandidate(const Citizen& rep, int partyID, int distID);


		void PrintNameAndId();

		friend void swap(PartyList& first, PartyList& second);
		PartyList& operator=(PartyList other);
		friend std::ostream& operator<<(std::ostream& out, const PartyList& other);

		void save(ofstream& out) const;
		void load(ifstream& in, const CitizensList& _list);
	};
}