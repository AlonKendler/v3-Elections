//#include "CitizenList.h"
#include "Party.h"
#include <iostream>
#include "Representative.h"

namespace elc {

	void Party::updateRepsList(unsigned int districtsAmount)
	{
		while (RepsList.size() < districtsAmount)
		{
			vector<Representative> temp;
			RepsList.push_back(temp);
		}
	}

	void Party::addRepresentative(const Citizen& rep, int distID)
	{

		RepsList.at(distID).push_back(Representative(rep, distID));
	}


	void swap(Party& first, Party& second)
	{
		using std::swap;

		swap(first.partyName, second.partyName);
		swap(first.partyID, second.partyID);
		swap(first.boss, second.boss);
		swap(first.RepsList, second.RepsList);
	}

	std::ostream& operator<<(std::ostream& out, Party& other)
	{
		out
			<< "Party name: " << other.partyName << " | "
			<< "party number: " << other.partyID << " | "
			<< "Party boss-> " << "NEEDS FIX! "<< endl;
		
		vector< vector<Representative> >::iterator row;
		vector<Representative>::iterator col;
		for (row = other.RepsList.begin(); row != other.RepsList.end(); row++)
		{
			cout << "Representatives from District ID: " << row->begin()->getID() << endl;
			for (col = row->begin(); col != row->end(); col++)
			{
				cout << *col;
			}
		}
		return out;
	}

	Party& Party::operator=(Party other) // (1)
	{
		swap(*this, other); // (2)
		return *this;
	}

	void Party::printNameAndId() const
	{
		std::cout << "(" << this->partyID << " - " << this->partyName << ")";
	}

}


	//================================seralization============================================
	//void Party::save(ofstream& out) const
	//{
	//	int len = partyName.size();
	//	int bs = boss.getID();
	//	out.write(rcastcc(&len), sizeof(len));
	//	out.write(rcastcc(partyName.c_str()), len);
	//
	//	out.write(rcastcc(&partyNumber), sizeof(partyNumber));
	//	out.write(rcastcc(&numberOfParty), sizeof(numberOfParty));
	//	out.write(rcastcc(&bs), sizeof(bs));
	//
	//	out.write(rcastcc(&elec_size), sizeof(elec_size));
	//	out.write(rcastcc(&elec_length), sizeof(elec_length));
	//	for (int i = 0; i < elec_length; i++)
	//	{
	//		electors[i].save(out);
	//	}
	//
	//}
	//
	//void Party::load(ifstream& in, const CitizensList& _list)
	//{
	//	int len, id;
	//	in.read(rcastc(&len), sizeof(len));
	//	char* temp = new char[len + 1];
	//	in.read(temp, len);
	//	temp[len] = '\0';
	//	partyName = temp;
	//	delete[] temp;
	//	in.read(rcastc(&partyNumber), sizeof(partyNumber));
	//	in.read(rcastc(&numberOfParty), sizeof(numberOfParty));
	//	in.read(rcastc(&id), sizeof(id)); //reads boss id;
	//
	//	boss = *(_list.getCitizen(id));
	//
	//	in.read(rcastc(&elec_size), sizeof(elec_size));
	//	in.read(rcastc(&elec_length), sizeof(elec_length));
	//
	//	electors = new Elector[elec_size];
	//	for (int i = 0; i < elec_length; i++)
	//		electors[i].load(in, _list);
	//}

	//void Elector::save(ofstream& out) const
	//{
	//	out.write(rcastcc(&numOfSenators), sizeof(numOfSenators));
	//	Senator* temp = head;
	//	int citzId;
	//	while (temp)
	//	{
	//		citzId = temp->candidate.getID();
	//		out.write(rcastcc(&citzId), sizeof(citzId));
	//		temp = temp->getNext();
	//	}
	//}
//	void Elector::load(ifstream& in, const CitizensList& _list)
//	{
//		Citizen* temp;
//		int citzId;
//		in.read(rcastc(&numOfSenators), sizeof(numOfSenators));
//		for (int i = 0; i < numOfSenators; i++)
//		{
//			in.read(rcastc(&citzId), sizeof(citzId));
//			temp = (_list.getCitizen(citzId));
//			Elector::addSenator(*temp);
//			numOfSenators--; //NOTICE! addSenator() increases numOfSenators, not needed while loading form file.
//		}
//
//	}
//
//}