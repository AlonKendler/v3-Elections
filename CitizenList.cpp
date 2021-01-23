#include "CitizenList.h"

namespace elc
{

	void CitizensList::setCitizen(const string name, int id, int yob, const District& district)
	{
		Citizen* temp = new Citizen(name, id, district, yob);
		setCitizen(temp);
	}

	void CitizensList::setCitizen(Citizen* citizen)
	{
		//check if citizen exist
		if (getCitizenPtr(citizen->getID()) == nullptr) //meaning no citizen with that ID exist
			{
				list.push_back(citizen);
			}
		else
			throw(invalid_argument("Citizen ID alredy listed, Citizen was not added."));
	}


	
	Citizen* const CitizensList::getCitizenPtr(int id) const
	{
	
		//using find_if std fuction, because we need to find the citizen obj maching ID
		//using lambda fuction as learn on stack-overflow
		//https://stackoverflow.com/questions/15517991/search-a-vector-of-objects-by-object-attribute
	
		auto it = find_if(list.begin(), list.end(), [&id]( Citizen* obj) {return obj->getID() == id; });
	
		if (it != list.end())
		{
			return *it; //return the pointer of the element in terator?
		}
	
		return nullptr; //if citizen not found then,
	}

	const vector<Citizen*>  CitizensList::getList()const
	{
		return list;
	}

	void swap(CitizensList& first, CitizensList& second)
	{
		using std::swap;
		swap(first.list, second.list);
	}
	CitizensList& CitizensList::operator=(CitizensList other)
	{
		swap(*this, other);
		return *this;
	}

	std::ostream& operator<<(std::ostream& out, const CitizensList& other)
	{
		for (unsigned int i = 0; i < other.list.size(); i++)
		{
			cout << *other.list[i] << '\n';
		}
		return out;
	}


	/**************************serialiazion***************************/
	void CitizensList::save(ofstream& out) const
	{
		int size = list.size();
		out.write(rcastcc(&size), sizeof(size));
		for (auto itr : list)
		{
			itr->save(out);
		}
	}

	void CitizensList::load(ifstream& in, const DistrictsList& _list)
	{
		int size;
		in.read(rcastc(&size), sizeof(size));
		list =  vector<Citizen*>(size);
		for (int i = 0; i < size; i++)
		{
			list[i] = new Citizen();
			list[i]->load(in, _list);
		}
	}
}