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
		int partyID;
		Citizen* rep;

	public:
		Representative() : partyID(0), rep(nullptr)
		{
			cout << "ctor representative" << endl;
		}

		Representative(Citizen& other, int id) : rep(&other), partyID(id) {};
		virtual ~Representative() {};

		void setpartyID(const int& _id) { partyID = _id; }
		void setRep(Citizen& r) { rep = &r; }

		const int& getPartyID() { return partyID; }
		const Citizen& getRep() { return *rep; }


		const Representative& operator=(const Representative& o)
		{
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& out, Representative& other)
		{
			out <<
				"Represenataitve from party:" << other.partyID <<
				*other.rep << endl;
		}
	};
}