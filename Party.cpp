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
			<< "Party boss-> " << "boss name" << endl;
		
		vector< vector<Representative> >::iterator row;	//similar to i-j for loop
		vector<Representative>::iterator col;			//with iterators
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



	//================================seralization============================================
	void Party::save(ofstream& out) const
	{
		int len = partyName.size();
		int bs = boss->getID();
		out.write(rcastcc(&len), sizeof(len));
		out.write(rcastcc(partyName.c_str()), len);
	
		out.write(rcastcc(&partyID), sizeof(partyID));
		out.write(rcastcc(&bs), sizeof(bs));
	
		//add repsLisst save
		//add repsLisst save
		//add repsLisst save
		//add repsLisst save
		//add repsLisst save
		//add repsLisst save
	
	}
	
	//void elc::Party::load(std::ifstream& in, const CitizensList& _list)
	//{
	//	int len, id;
	//	in.read(rcastc(&len), sizeof(len));
	//	char* _name;
	//	try {
	//		_name = new char[len + 1];
	//	}
	//	catch (bad_alloc& ex) {
	//		cout << ex.what() << endl; exit(1);
	//	}
	//	in.read(_name, len);
	//	_name[len] = '\0';		 //notice, we assign string to char*
	//	partyName = _name;		 //then, assign it to the string name
	//	delete[] _name; 		 //at last, delete the temporary char* 
	//
	//	in.read(rcastc(&partyID), sizeof(partyID));
	//	in.read(rcastc(&id), sizeof(id)); //reads boss id;
	//
	//	//boss = (_list.getCitizen(id));
	//	boss =_list.getCitizen(id);
	//
	////	in.read(rcastc(&elec_size), sizeof(elec_size));
	////	in.read(rcastc(&elec_length), sizeof(elec_length));
	////
	////	electors = new Elector[elec_size];
	////	for (int i = 0; i < elec_length; i++)
	////		electors[i].load(in, _list);
	//}
}
