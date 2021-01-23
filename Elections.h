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
		//char* date;
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

		int getPartiesLength() const				{ return parties.getList().size(); }
		int getCitizensLength() const				{ return citizens.getList().size(); }
		int getDistrictsLength() const				{ return districts.getList().size(); }

		const Date& getDate() const						{ return date; }
		const int& getRoundType() const				{ return roundType;  }

		Citizen* getCitizenPtr(int id)				   { return citizens.getCitizenPtr(id); }
		 District* getDistrictPtr(const int& distID) { return districts.getDistrictPtr(distID); }
		const District& getDistrict(const int& distID) { return districts.getDistrict(distID); }
		District& getDistrict(int distID, bool flag)   { return districts.getDistrict(distID, flag); }
		const DistrictsList& getDistList() const	   { return districts; }
		const CitizensList& getCitizensList() const    { return citizens; }
		const PartyList& getPartyList() const		{ return parties; }
    
		void setDate(const Date& _date)					{ date = _date; }
		void setRoundType(int _type)				{ roundType = _type; }

		Party* getParty(const int& partyID) { return (parties.getParty(partyID)); }
		//const Citizen& getCitizen(const int& id) { return *citizens.getCitizen(id); }

		void addCitizen(string name, int id, const District& dist, int yob);
		void addParty(string name, const Citizen& boss);
		void addDistrict(string name, int num, bool div);
		//void addPartyCandidate(int id, int partyID, int distID);
		void addPartyCandidate(const Citizen& rep, int partyID, int distID);

		//versions for simple round
		//void addCitizen(const char* name, int id, int yob);

		//void AddNewDistToParties(int);
		//bool isPartiesEmpty() { return parties.isEmpty(); }
		
		void printCitizens();
		void printParties();
		void printDistricts();
		void printDistrictsNameAndID(); 
		void printPartiesNameAndID();


		/*********************** voting proccess *******************************/

		//bool isEnoughRepsInDist(const int& distID, const int& partyID);

		void StartVotingProccess();
		bool setVote(Citizen& voter, const int& partyID) { return voting.setVote(voter, partyID); }
		const Votes& getVotes() { return voting; }

		void setResults();

		/**************************serialiazion***************************/
		void fixLoadOfDistricts();
		void save(ofstream& out) const;
		void load(ifstream& in) ;

	};



}