#include "PartyList.h"

namespace elc
{
	
	void PartyList::setParty(string _partyName, const Citizen& boss, int numOfDistricts)
	{
		Party* temp = new Party(_partyName, boss, list.size());
		//no use of numOfDistricts
		//handle errors here??
		setParty(temp);

	}

	void PartyList::setParty(Party* _party)
	{
		//check if pary name exist, handle error
		list.push_back(_party);
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

	void PartyList::updateRepsList(int districtsAmount)
	{
		//here we want to iterate and check each party if his repsList is updated
		// repsList (2s arrays, columns represent districtAmount)
		for (auto obj : list)
		{
			obj->updateRepsList(districtsAmount);
		}
	}

	void PartyList::addPartyCandidate(const Citizen& rep, int partyID, int distID)
	{
		//list.getParty(partyID).addRepresentatitve(rep, distID);
		list.at(partyID)->addRepresentative(rep, distID);
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
	void PartyList::PrintNameAndId()
	{
		for (unsigned int i = 0; i < list.size(); i++)
			list[i]->printNameAndId();
	}

	std::ostream& operator<<(std::ostream& out,  const PartyList& other)
	{
		for (unsigned int i = 0; i < other.list.size(); i++)
		{
			std::cout << *other.list[i] << '\n';
		}
		return out;
	}

	void PartyList::save(ofstream& out) const
	{
		int size = list.size();
		out.write(rcastcc(&size), sizeof(size));
		for(auto itr : list)
		{
			itr->save(out);
		}
	}
	
	void PartyList::load(ifstream& in, const CitizensList& _list)
	{
		int size;
		in.read(rcastc(&size), sizeof(size));
		list = vector<Party*>(size);
		for(auto itr : list)
		{
			itr->load(in, _list);
		}
	}
}