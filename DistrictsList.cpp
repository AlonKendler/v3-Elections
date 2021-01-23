#include "DistrictsList.h"
#include <fstream>



namespace elc
{
	
	void DistrictsList::setDistrict(string _DistrictName, int numOfReps, int div)
	{
		District* temp;
		if (div == 0) { temp = new Divided(_DistrictName, numOfReps, list.size()); }
		else if( div == 1) { temp = new District(_DistrictName, numOfReps, list.size()); }
		else { throw(invalid_argument("invalid District-Type")); }

		setDistrict(temp);
	}

	void DistrictsList::setDistrict(District* _dist)
	{
		string name = _dist->getDistName();
		//needs to check if district name exist, handle errors
		auto it = find_if(list.begin(), list.end(),
			[&name](District* obj) {return obj->getDistName() == name; });
		if (it == list.end()) //means that we did not found a district with same name, good to add
		{
			list.push_back(_dist);
		}
		else { throw(invalid_argument("Existing district with the Same Name")); }
	}


	District* DistrictsList::getDistrictPtr(const int& distID) const
	{
		if (distID < 0 || distID >= static_cast<int> (list.size()))
		{
			throw(out_of_range("invalid District ID, choose ID from avilable."));
		}
		return (list[distID]);
	}

	const District& DistrictsList::getDistrict(const int& distID) const
	{
		return(*getDistrictPtr(distID));
	}


	bool DistrictsList::setCitizenInDist(const Citizen& resident, const District& dist)
	{
		//need to check if distID equals their index, should work
		list[dist.getDistID()]->setDistCitizenInList(resident);
		return true;
	}

	void swap(DistrictsList& first, DistrictsList& second)
	{
		using std::swap;
		swap(first.list, second.list);
	}

	DistrictsList& DistrictsList::operator=(DistrictsList other)
	{
		swap(*this, other);
		return *this;
	}

	void DistrictsList::PrintNameAndId() 
	{
		for (unsigned int i = 0; i < list.size(); i++)
			list[i]->printNameAndId();
	}

	std::ostream& operator<<(std::ostream& out, const DistrictsList& other)
	{
		for (unsigned int i = 0; i < other.list.size(); i++)
		{
			cout << *other.list[i] << '\n';
		}
		return out;
	}


	void DistrictsList::save(ofstream& out) const
	{
		bool type = false;
		int size = list.size();

		out.write(rcastcc(&size), sizeof(size));
		for (auto itr : list)
		{
			type = itr->isDivided();
			out.write(rcastcc(&type), sizeof(type));
			itr->save(out);
		}
	}

	void DistrictsList::load(ifstream& in)
	{
		bool type = false;
		int size;

		in.read(rcastc(&size), sizeof(size));
	
		list = vector<District*>(size);
		for (int i = 0; i < size; ++i)
		{
			in.read(rcastc(&type), sizeof(type));
			if (type) // ==1 meand divided
			{
				list[i] = new Divided();
			}
			else
			{
				list[i] = new District();
			}
			list[i]->load(in);
		}
	}
}