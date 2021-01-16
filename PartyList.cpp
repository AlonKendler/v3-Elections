#include "PartyList.h"

namespace elc
{
	
	void PartyList::setParty(string _partyName, const Citizen& boss, int numOfDistricts)
	{
		Party temp = Party(_partyName, boss, list.size());

		//handle errors here??
		setParty(temp);

	}

	void PartyList::setParty(Party& party)
	{
		list.push_back(&party);
	}

//	Party* PartyList::getParty(int partyID)  {
//		auto it = find_if(list.begin(), list.end(), [partyID](Party& obj) {return obj.getpartyID() == partyID; });
//
//		if (it != list.end())
//		{
//			return *it; //return the pointer of the element in terator?
//		}
//	}

	//const string const PartyList::getPartyName(const int& partyID) const
	//{
	//	return list[partyID]->getPartyName();
	//}


	void PartyList::PrintNameAndId()
	{
		for (unsigned int i = 0; i < list.size(); i++)
			list[i]->printNameAndId();
	}


	void swap(PartyList& first, PartyList& second)
	{
		using std::swap;
		swap(first.list, second.list);
	}

	PartyList& PartyList::operator=(PartyList other)
	{
		swap(*this, other);
		return *this;
	}

	std::ostream& operator<<(std::ostream& out,  const PartyList& other)
	{
		for (unsigned int i = 0; i < other.list.size(); i++)
		{
			std::cout << other.list[i] << '\n';
		}
		return out;
	}

	//void PartyList::save(ofstream& out) const
	//{
	//	int size = list.size();
	//	int capacity = list.capacity();
	//
	//	out.write(rcastcc(&capacity), sizeof(capacity));
	//	out.write(rcastcc(&size), sizeof(size));
	//	for (int i = 0; i < size; ++i)
	//	{
	//		list[i]->save(out);
	//	}
	//}
	//
	//void PartyList::load(ifstream& in, const CitizensList& _list)
	//{
	//	int size;
	//	int capacity;
	//	in.read(rcastc(&capacity), sizeof(capacity));
	//	in.read(rcastc(&size), sizeof(size));
	//
	//	list = vector<Party*>(capacity);
	//	for (int i = 0; i < size; i++)
	//	{
	//		list[i]->load(in, _list);
	//	}
	//}
}