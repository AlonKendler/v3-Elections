
#include "Citizen.h"
#include "district.h"
#include "DistrictsList.h"



namespace elc {

	 void swap(Citizen& first, Citizen& second)
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.name, second.name);
		swap(first.ID, second.ID);
		swap(first.YOB, second.YOB);
		swap(first.dist, second.dist);
		swap(first.hasVoted, second.hasVoted);
	}

	 Citizen& Citizen::operator=(Citizen other)
	 {
		 swap(*this, other); // (2)
		 return *this;
	 }
	std::ostream& operator<<(std::ostream& out, const Citizen& other)
	{
		std::cout
			<< "name: " << other.name << " , "
			<< "ID: " << other.ID << " , "
			<< "born in: " << other.YOB << " , "
			<< "district: " << other.dist->getDistName() << ".";
		return out;
	}


	/**************************serialiazion***************************/
	void Citizen::save(std::ofstream& out) const
	{
		int distID = dist->getDistID();
		int len = name.size();
		out.write(rcastcc(&len), sizeof(len));									 // name length
		out.write(rcastcc(name.c_str()), len);									 // len+1 for the '\0'
		out.write(rcastcc(&ID), sizeof(ID));									 // int ID
		out.write(rcastcc(&YOB), sizeof(YOB));									 // int - yob
		out.write(rcastcc(&hasVoted), sizeof(hasVoted));
		out.write(rcastcc(&distID), sizeof(distID));
	
	}
	void Citizen::load(std::ifstream& in, const DistrictsList& _list) //districts
	{
		int len, distID;
		in.read(rcastc(&len), sizeof(len));
		char* _name = new char[len + 1];
		in.read(_name, len);
		_name[len] = '\0';  //notice, we assign string to char*
		name = _name;		 //then, assign it to the string name
		delete[] _name; 	 //at last, delete the temporary char* 
		in.read(rcastc(&ID), sizeof(ID));
		in.read(rcastc(&YOB), sizeof(YOB));
		in.read(rcastc(&hasVoted), sizeof(hasVoted));
		in.read(rcastc(&distID), sizeof(distID));
	
		dist = &(_list.getDistrict(distID));
	}
}



