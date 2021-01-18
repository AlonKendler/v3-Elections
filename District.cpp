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

	void District::save(ofstream& out) const
	{
		int len = name.size();
		out.write(rcastcc(&len), sizeof(len));				 // name length
		out.write(rcastcc(name.c_str()), len);
		out.write(rcastcc(&distID), sizeof(distID));				 // int ID
		out.write(rcastcc(&voters_precentage), sizeof(voters_precentage));				 // int - yob


		//we used to save reps size
		//out.write(rcastcc(&reps_size), sizeof(reps_size));
		//out.write(rcastcc(&reps_lentgh), sizeof(reps_lentgh));
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
		in.read(rcastc(&voters_precentage), sizeof(voters_precentage));

		//we used to load reps_size and length
		//in.read(rcastc(&reps_size), sizeof(reps_size));
		//in.read(rcastc(&reps_lentgh), sizeof(reps_lentgh));
		//RepsList = new Representatives[reps_size];

	}


}