#pragma once
#include <fstream>
#include "CitizenList.h"
#include "PartyList.h"
#include "DistrictsList.h"
#include "Votes.h"
#include "Date.h"

using namespace std;



namespace elc {

	class Elections
	{
	private:
		int roundType; // 0 = normal, 1 = simple
		Date date;
		PartyList parties;
		CitizensList citizens;
		DistrictsList districts;
		Votes voting;
	public:

		Elections() : roundType(0) {};
		~Elections() {};
		Elections(ifstream& in)
		{
			load(in);
		}

		void handleSimpleRound(char* name, const int& reps)
		{	
			districts.setDistrict(name, reps, true);
		}

		int getPartiesLength() const				   { return parties.getList().size(); }
		int getCitizensLength() const				   { return citizens.getList().size(); }
		int getDistrictsLength() const				   { return districts.getList().size(); }

		const Date& getDate() const					   { return date; }
		const int& getRoundType() const				   { return roundType;  }

		bool isVotesEmpty()							   { return voting.isBufferEmpty(); }
		Party* getParty(const int& partyID)			   { return (parties.getParty(partyID)); }
		Citizen* getCitizenPtr(int id)				   { return citizens.getCitizenPtr(id); }
		 District* getDistrictPtr(const int& distID)   { return districts.getDistrictPtr(distID); }
		const District& getDistrict(const int& distID) { return districts.getDistrict(distID); }
		District& getDistrict(int distID, bool flag)   { return districts.getDistrict(distID, flag); }
		const DistrictsList& getDistList() const	   { return districts; }
		const CitizensList& getCitizensList() const    { return citizens; }
		const PartyList& getPartyList() const		{ return parties; }
    
		void setDate(const Date& _date)					{ date = _date; }
		void setRoundType(int _type)				{ roundType = _type; }

		void addCitizen(string name, int id, const District& dist, int yob);
		void addParty(string name, const Citizen& boss);
		void addDistrict(string name, int num, int div);
		void addPartyCandidate(const Citizen& rep, int partyID, int distID);
		
		void printCitizens();
		void printParties();
		void printDistricts();
		void printDistrictsNameAndID(); 
		void printPartiesNameAndID();


		/*********************** voting proccess ***************************/
		void StartVotingProccess();
		void setVote(Citizen& voter, const int& partyID);
		const Votes& getVotes() { return voting; }
		void setResults();

		/**************************serialiazion***************************/
		void fixLoadOfDistricts();
		void save(ofstream& out) const;
		void load(ifstream& in) ;

	};



}