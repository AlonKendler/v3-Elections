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
		~PartyList() {}
		PartyList(const PartyList& other) { list = other.list;  }


		void setParty(string _partyName, const Citizen& boss, int numOfDistricts);
		void setParty(Party&);

		//Party* getParty(int partyID) ;
		//string const getPartyName(const int& partyID) const;
		vector<Party*> const getList() const { return list; }


		void PrintNameAndId();

		friend void swap(PartyList& first, PartyList& second);
		PartyList& operator=(PartyList other);
		friend std::ostream& operator<<(std::ostream& out, const PartyList& other);

		//void save(ofstream& out) const;
		//void load(ifstream& in, const CitizensList& _list);
	};
}