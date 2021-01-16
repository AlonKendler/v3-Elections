#pragma once
#include <iostream>
#include "Citizen.h"

using namespace std;

namespace elc
{
	class Citizen;
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
	};
}