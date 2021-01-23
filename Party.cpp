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
		//why rep with distID???????
		//possible future bugs
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
			<< "Party boss-> " << other.getBoss().getName() << endl;
		
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
	

		//seralization of repsList

		int rowsSize = RepsList.size();
		int colsSize;

		out.write(rcastcc(&rowsSize), sizeof(rowsSize));

		for (auto itrI : RepsList)
		{
			colsSize = itrI.size();
			out.write(rcastcc(&colsSize), sizeof(colsSize));

			for (auto itrJ : itrI)
			{
				itrJ.save(out);
			}
		}	
	}
	
	void Party::load(ifstream& in, const CitizensList& _list)
	{
		int len, id;
		in.read(rcastc(&len), sizeof(len));
		char* _name;
		try {
			_name = new char[len + 1];
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl; exit(1);
		}
		in.read(_name, len);
		_name[len] = '\0';		 //notice, we assign string to char*
		partyName = _name;		 //then, assign it to the string name
		delete[] _name; 		 //at last, delete the temporary char* 

		in.read(rcastc(&partyID), sizeof(partyID));
		in.read(rcastc(&id), sizeof(id)); //reads boss id;
		boss = _list.getCitizenPtr(id);

		//seralization of repsList
		int rowsSize, colsSize;
		Representative temp;
		in.read(rcastc(&rowsSize), sizeof(rowsSize));
		
		RepsList = vector<vector<Representative>>(rowsSize);

		for (int i=0; i< rowsSize; i++)
		{
			in.read(rcastc(&colsSize), sizeof(colsSize));
			for (int j = 0; j < colsSize; j++)
			{
				temp.load(in, _list); //load one represative
				RepsList[i].push_back(temp); //push temp elemnt and (copy it).
			}
		}
	}
}
