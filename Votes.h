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
		//holds in each cell the number of votes
		vector<vector<int>> votes_table;

		//holds in each cell the number of electors from each party
		//in every district
		vector<vector<int>> electors;

		//table[districts][parties]

	public:
		Votes() :votes_table(), electors(),after_calcs(false) {}
		Votes(int _numOfParties, int _numOfDistricts);
		~Votes();

		//void setnumOfParties(const int& num);
		//void setnumOfDistricts(const int& num);
		void setVotes_table(const unsigned int& numOfDistricts, const unsigned int& numOfParties);
		void setElectors_table(const unsigned int& numOfDistricts, const unsigned int& numOfParties);
		bool setVote(Citizen&, int PartyID);
		void finishCalcs();

		const bool isCalcsDone();
		//const int& getnumOfParties();
		//const int& getnumOfDistricts();
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

		void save(ofstream& out) const;
		void load(ifstream& in);

	};






}