#pragma once
#include <iostream>
#include "Citizen.h"
#include "CitizenList.h"

using namespace std;

namespace elc
{
	class Citizen;
	//class citizensList;
	class Representative
	{
	private:
		int ID; //partyID || DistrictID
		const Citizen* rep;

	public:
		Representative() : ID(0), rep(nullptr)
		{
			cout << "ctor representative" << endl;
		}

		Representative(const Citizen& other, int id) : rep(&other), ID(id) {};
		virtual ~Representative() {};

		void setID(const int& _id) { ID = _id; }
		void setRep(Citizen& r) { rep = &r; }

		const int& getID() { return ID; }
		const Citizen& getRep() { return *rep; }


		const Representative& operator=(const Representative& o)
		{
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& out, Representative& other)
		{
			out << *other.rep << endl;;
			return out;
		}

		void save(ofstream& out) const 
		{
			int citizenID = rep->getID();
			out.write(rcastcc(&ID), sizeof(ID));
			out.write(rcastcc(&citizenID), sizeof(citizenID));
		}


		void load(ifstream& in, const CitizensList& _list)
		{
			int citizenID;
			in.read(rcastc(&ID), sizeof(ID));
			in.read(rcastc(&citizenID), sizeof(citizenID));
			rep = _list.getCitizenPtr(citizenID);
		}
	};
}