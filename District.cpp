#pragma once
#include "district.h"
#include "Citizen.h"

namespace elc
{

	bool District::setVotersPercentage(int& allCitizens)
	{
		voters_precentage = citizens.size() / float(allCitizens);
		return true;
	}

	bool District::setVotersPersentage(const float& num)
	{
		this->voters_precentage = num;
		return true;
	}
	void District::setDistCitizenInList(const Citizen&_citizen)
	{
		//using citizen* list, this should not copy the data
		citizens.push_back(const_cast<Citizen*>(&_citizen));
	}

	void District::addPartyRepToList(const int& partyID, const Representative& rep)
	{
		RepsList[partyID].push_back(rep);
	}

	void District::addPartyRepToList(const int& partyID, const Citizen& rep)
	{
		addPartyRepToList(partyID, Representative(rep, partyID));
	}

	bool District::initRepsList(const int& size)
	{

		for (int i = 0; i < size; i++)
		{
			RepsList.push_back(vector<Representative>());
		}
		return true;
	}


	void District::printNameAndId()
	{
		cout << "(" << this->distID << " - " << this->name << ")";
	}

	void District::printPartyRepsNames(const int& partyID) const
	{
		int i = 1;
		for (auto itr = RepsList[partyID].begin(); itr != RepsList[partyID].end(); ++itr)
		{
			cout << i++<<") "<<itr->getRep().getName() << endl;
		}
		cout << endl;
	}

	std::ostream& operator<<(std::ostream& out, const District& other)
	{
		return other.print(out);
	}


	 std::ostream& District::print(std::ostream& out) const
	{	
		out <<  "district number: " << distID << " , "
			<< "name: " << name << " , "
			<< "number of Representatives: " << numOfReps;
		std::cout << " , type: Unified.";
		return out;
	}

	 std::ostream& Divided::print(std::ostream& out) const
	 {
		 out << "district number: " << distID << " , "
			 << "name: " << name << " , "
			 << "number of Representatives: " << numOfReps;
		 std::cout << " , type: Divided.";
		 return out;
	 }

	bool District::isDivided()
	{
		if (typeid(*this) == typeid(Divided))
			return true;
		else
			return false;
	}

	void District::save(ofstream& out) const
	{
		int len = name.size();
		out.write(rcastcc(&len), sizeof(len));			
		out.write(rcastcc(name.c_str()), len);
		out.write(rcastcc(&distID), sizeof(distID));	
		out.write(rcastcc(&numOfReps), sizeof(numOfReps));	
		out.write(rcastcc(&voters_precentage), sizeof(voters_precentage));			
	}

	void District::load(ifstream& in)
	{
		int len;
		in.read(rcastc(&len), sizeof(len));
		char* _name;
		try {
			_name = new char[len + 1];
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl; exit(1);
		}
		in.read(_name, len);
		_name[len] = '\0';  //notice, we assign string to char*
		name = _name;		 //then, assign it to the string name
		delete[] _name; 	 //at last, delete the temporary char* 

		in.read(rcastc(&distID), sizeof(distID));
		in.read(rcastc(&numOfReps), sizeof(numOfReps));
		in.read(rcastc(&voters_precentage), sizeof(voters_precentage));
	}


}