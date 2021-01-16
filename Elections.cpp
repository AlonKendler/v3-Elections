#include "Elections.h"
#include <iostream>

using namespace std;
namespace elc {

	bool Elections::setDate(char* _date)
	{
		int size = strlen(_date);
		if (date != nullptr)
			delete[] date;

		date = new char[size + 1];
		memcpy(date, _date, sizeof(char) * size);
		date[size] = '\0';
		return true;
	}

	bool Elections::setRoundType(int _type) { return this->roundType = _type; }

	void Elections::addCitizen(string name, int id, const District& dist, int yob)
	{
		citizens.setCitizen(name, id, yob, dist);
		districts.setCitizenInDist(citizens.getList().back(), dist); //we just push_back a citizen to citizen list, so we get it.
	}
	void Elections::addParty(string name, const Citizen& boss)
	{
		parties.setParty(name, boss, districts.getList().size());
	}
	void Elections::addDistrict(string name, int num, bool div)
	{
		districts.setDistrict(name, num, div);
	}

	void Elections::addPartyCandidate(const Citizen& rep, int partyID, int distID)
	{
		parties.updateRepsList(districts.getList().size());
		//checking repList
		cout << "now, lets check this thing" << endl;
		parties.addPartyCandidate(rep, partyID, distID);
	}

	//void Elections::addPartyCandidate(int id, int partyID, int distID)
	//{
	//	Citizen* temp = citizens.getCitizen(id);
	//	parties.addRepInParty(*temp, partyID, distID);
	//}
	//void Elections::addPartyCandidate(const Citizen& rep, int partyID, int distID)
	//{
	//	parties.addRepInParty(rep, partyID, distID);
	//}

	//void Elections::AddNewDistToParties(int distID)
	//{
	//	parties.AddNewDistToParties(distID);
	//}

	Citizen* Elections::findCitizen(int id)
	{
		//citizens.CitizenSort();
		return (citizens.getCitizen(id));
		//if ID doesn't exist in the database,
		//the return value will be nullptr
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
		{
			cout << "No distrricts available" << endl;
		}
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

	//bool Elections::isEnoughRepsInDist(const int& distID, const int& partyID)
	//{
	//	return (parties.getParty(partyID).getElectorInDist(distID).getNumOfSenators() > districts.getTotalRepsInDist(distID));
	//}

	void Elections::StartVotingProccess()
	{
		voting.setnumOfDistricts(districts.getList().size());
		voting.setnumOfParties(parties.getList().size());

		voting.setVotes_table();
		voting.setElectors_table();
	}

	//void Elections::setResults()
	//{
	//	if (voting.isCalcsDone())
	//		return;
	//
	//	bool flag = true;
	//	for (int i = 0; i < getDistrictsLength(); i++)
	//	{
	//		districts.getDistrict(i, flag).initRepsList(parties.getLength(), parties.getPartyList());
	//		voting.setElectorsInDist(parties, getDistrict(i, flag));
	//	}
	//	voting.finishCalcs();
	//}

	/**************************serialiazion***************************/
		void Elections::save(ofstream& out) const
		{
			int len = strlen(date); 
			out.write(rcastcc(&len), sizeof(len));                 //save len of date
			out.write(date, len);                                  //save date
			out.write(rcastcc(&roundType), sizeof(roundType));	   //save round type

				//districts.save(out);
				citizens.save(out);
				//parties.save(out);
				voting.save(out);

		}

		void Elections::load(ifstream& in)
		{
			int len;
			in.read(rcastc(&len), sizeof(len));
			date = new char[len + 1];

			in.read(date, len);
			date[len] = '\0';
			in.read(rcastc(&roundType), sizeof(roundType));

			//districts.load(in);
			citizens.load(in, districts);
			fixLoadOfDistricts();								//handle districts, assings proper citizens
			//parties.load(in, citizens);
			voting.load(in);
		}

		void Elections::fixLoadOfDistricts()
		{
			int idx = citizens.getList().size();
			int id;
			for (int i = 0; i < idx; i++)
			{
				id = citizens.getList()[i].getDistrict().getDistID();
				districts.setCitizenInDist(citizens.getList()[i], getDistrict(id));
			}
		}

	}