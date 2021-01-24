#include "Elections.h"
#include <iostream>

using namespace std;
namespace elc {


	void Elections::addCitizen(string name, int id, const District& dist, int yob)
	{
		try {
			citizens.setCitizen(name, id, yob, dist);
		}
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			throw(invalid_argument("Citzen object not added, procced"));
		}
		districts.setCitizenInDist(*citizens.getList().back(), dist); //we just push_back a citizen to citizen list, so we get it.
	}

	void Elections::addParty(string name, const Citizen& boss)
	{
		try {
			parties.setParty(name, boss, districts.getList().size());
		}
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			throw(invalid_argument("Party object not added, procced"));
		}
	}
	void Elections::addDistrict(string name, int num, int div)
	{
		try {
			districts.setDistrict(name, num, div);
			std::cout << "all good, passed input" << endl;
		}
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			throw(invalid_argument("District object not added, procced"));
		}
	}

	void Elections::addPartyCandidate(const Citizen& rep, int partyID, int distID)
	{
		if (partyID < 0 || partyID >= getPartiesLength())
			throw(out_of_range("invalid Party"));
		if (distID < 0 || distID >= getDistrictsLength())
			throw(out_of_range("invalid District"));
		parties.updateRepsList(districts.getList().size()); 
		try {
			parties.addPartyCandidate(rep, partyID, distID);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
			throw(invalid_argument("Representative object not added, procced"));
		}
	}

	bool Elections::enoughReps()
	{
		int repsQuota;
		for (int i = 0; i < getDistrictsLength(); i++)
		{
			repsQuota = getDistrict(i).getDistReps();
			for (int j = 0; j < getPartiesLength(); j++)
			{
				if (repsQuota > getParty(j)->getRepsList().size())
					return false;
			}
		}
		return true;
	}

	void Elections::printCitizens() 
	{
		cout << citizens; 
	}
	void Elections::printParties() 
	{ 
		cout << parties; 
	}
	void Elections::printDistricts() 
	{ 
		if (roundType)
			cout << "No distrricts available" << endl;
		else
			cout << districts; 
	}
	void Elections::printPartiesNameAndID()
	{
		parties.PrintNameAndId();
	}
	void Elections::printDistrictsNameAndID() 
	{
		districts.PrintNameAndId();
	}

	/*********************** voting proccess *******************************/

	void Elections::StartVotingProccess()
	{
		int numOfDistricts = districts.getList().size();
		int numOfParties = parties.getList().size();
		voting = Votes(numOfParties, numOfDistricts);
	//	voting.setVotes_table(numOfDistricts, numOfParties);
	//	voting.setElectors_table(numOfDistricts, numOfParties);
	}

	void Elections::setVote(Citizen& voter, const int& partyID) 
	{ 
		if (partyID < 0 || partyID >= getPartiesLength())
			throw(out_of_range("invalid Party"));
		 voting.setVote(voter, partyID);
	}

	void Elections::setResults()
	{
		if (!voting.getAfterCalcs()) 
		{
			int numOfDistricts = districts.getList().size();
			int numOfParties = parties.getList().size();

			voting = Votes(numOfParties, numOfDistricts);
			voting.updateVotesTable();

			int partiesSize = getPartiesLength();
			for (int i = 0; i < getDistrictsLength(); i++)
			{
				districts.getDistrict(i, true).initRepsList(partiesSize);
				voting.setElectorsInDist(parties, districts.getDistrict(i, true));
			}
			voting.setAfterCalcs(true);
		}
	}

	/**************************serialiazion***************************/
		void Elections::save(ofstream& out) const
		{
			out.write(rcastcc(&roundType), sizeof(roundType));	 
				
				date.save(out);
				districts.save(out); 
				citizens.save(out);
				parties.save(out);
				voting.save(out);
		}

		void Elections::load(ifstream& in)
		{
			in.read(rcastc(&roundType), sizeof(roundType));

			date.load(in);
			districts.load(in);
			citizens.load(in, districts);
			fixLoadOfDistricts();			//handle districts, assings proper citizens
			parties.load(in, citizens);
			voting.load(in);
		}

		void Elections::fixLoadOfDistricts()
		{
			int idx = citizens.getList().size();
			int id;
			for (int i = 0; i < idx; i++)
			{
				id = citizens.getList()[i]->getDistrict().getDistID();
				districts.setCitizenInDist(*citizens.getList()[i], getDistrict(id));
			}
		}

	}