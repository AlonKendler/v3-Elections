#pragma once

#include <iostream>
#include <typeinfo>
#include <vector>
#include <utility>
#include "CitizenList.h"
#include "PartyList.h"
#include "DistrictsList.h"


using namespace std;
namespace elc
{
	class Votes
	{
	private:
		bool after_calcs;
		int numOfParties;
		int numOfDistricts;
		vector<vector<int>> votes_table; //holds in each cell the number of votes
		vector<vector<int>> electors;	//holds in each cell the number of electors from each party

	public:
		Votes() :votes_table(), electors(),after_calcs(false), numOfParties(0), numOfDistricts(0) {}
		Votes(int _numOfParties, int _numOfDistricts);
		Votes(const Votes& o) : after_calcs(o.after_calcs), numOfParties(o.numOfParties), 
			numOfDistricts(o.numOfDistricts), votes_table(o.votes_table), electors(o.electors) { }
		
		~Votes() {}

		void setnumOfParties(const int& num) { numOfParties = num; }
		void setnumOfDistricts(const int& num) { numOfDistricts = num; }
		void setVotes_table(const unsigned int& numOfDistricts, const unsigned int& numOfParties);
		void setElectors_table(const unsigned int& numOfDistricts, const unsigned int& numOfParties);
		bool setVote(Citizen&, int PartyID);
		void setAfterCalcs(bool exp) { after_calcs = exp; }

		const bool getAfterCalcs()		 { return after_calcs; }
		const int& getnumOfParties()	 { return numOfParties;	}
		const int& getnumOfDistricts()	 { return numOfDistricts; }
		const int getTotalPartyVotes(const int& partyID)const;
		const int getTotalVotesInDistrict(const int& DistID)const;
		const int getPartyVotesInDist(const int& PartyID, const int& distID)const;
		const float& getPartyVotesPrecentageInDist(const int& PartyID, const int& distID)const;
		const float& getTotalVotesPrecentage(const CitizensList& list)const;
		const float& getDistVotesPrecantage(const District& dist)const;
		const vector<pair<Party&,int>> getSortedElectorResults(const PartyList& parties)const;
		//int** getPartiesWinningOrder()const;

		//calculates the number of electors won for each Party in the district,
		//then adds the newly chosen senators under their party ID to the district representatives.
		void setElectorsInDist(PartyList& parties, District& dist);
		const int getElectorsforPartyInDist(const int& partyID, const int& distID) const;
		const int getTotalPartyElectors(const int& partyID)const;
		const int getWinnerIDInDist(const int& distID) const;
		const int getWinnerIDInDist(District* const dist) const;
		//const int getWinner() const;
		//const int& getWinner(const DistrictsList& D_list) const;


		friend void swap(Votes& first, Votes& second) // nothrow
		{
			// enable ADL (not necessary in our case, but good practice) 
			using std::swap;

			// by swapping the members of two objects,
			// the two objects are effectively swapped
			swap(first.after_calcs, second.after_calcs);
			swap(first.numOfParties, second.numOfParties);
			swap(first.numOfDistricts, second.numOfDistricts);
			swap(first.votes_table, second.votes_table);
			swap(first.electors, second.electors);
		}

		Votes& operator=(Votes other) // (1)
		{
			swap(*this, other); // (2)
			return *this;
		}

		void save(ofstream& out) const;
		void load(ifstream& in);

	};






}