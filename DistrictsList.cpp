#include "DistrictsList.h"
#include <fstream>



namespace elc
{
	
	void DistrictsList::setDistrict(string _DistrictName, int numOfReps, bool div)
	{
		District* temp;
		(div) ? temp = new Divided(_DistrictName, numOfReps, list.size()) :
		temp = new District(_DistrictName, numOfReps, list.size());
		//important to delete Memory at the end.
		//important to delete Memory at the end.
		//important to delete Memory at the end.
		setDistrict(temp);
	}

	void DistrictsList::setDistrict(District* _dist)
	{
		//needs to check if district name exist, handle errors
		list.push_back(_dist);
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
		int capacity = list.capacity();

		out.write(rcastcc(&capacity), sizeof(capacity));
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
		int capacity;
		in.read(rcastc(&capacity), sizeof(capacity));
		in.read(rcastc(&size), sizeof(size));
	
		list = vector<District*>(capacity);
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