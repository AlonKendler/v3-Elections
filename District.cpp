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
	void District::setDistCitizenInList(Citizen&_citizen)
	{
		//notice, this copys the data
		//consider use of list<citizen*>
		citizens.push_back(&_citizen);

	}

	bool District::initRepsList(const int& size /*, Party* list*/)
	{
		////RepsList.reserve(size+1);
		//
		//
		//cout << "test" << endl;
		//for (int i = 0; i < size; i++)
		//{
		//	RepsList.a
		//}
		//for (auto obj : RepsList)
		//{
		//	RepsList.push_back()
		//}
		//	RepsList[i].set	//RepsList[i].setPartyID(list[i].getPartyNumber())
		//}
		//
		//
		//reps_size = size + 1;
		//reps_lentgh = size;
		//delete[] RepsList;
		//RepsList = temp;
		return true;
	}



	void District::printNameAndId()
	{
		cout << "(" << this->distID << " - " << this->name << ")";
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

}