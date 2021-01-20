#pragma once

#include <iostream>
#include "Citizen.h"
#include <vector>
#include "Representative.h"
#include "CitizenList.h"

using namespace std;
class CitizensList;

namespace elc {

	
	class Party {
	private:
		string partyName;
		int partyID;
		const Citizen* boss; //citizen&
		vector<vector<Representative>> RepsList;

	public:

		Party(string _partyName, const Citizen& _boss, int _id)
			: partyName(_partyName), partyID(_id), boss(&_boss), RepsList() {}

		Party(const Party& o) : partyName(o.partyName), partyID(o.partyID), boss(o.boss)
		{
			RepsList = o.RepsList;
		}

		virtual ~Party(){}
		
		//--Getters--//
		string getPartyName() const				{ return partyName; };
		const Citizen& getBoss() const			{ return *boss; };
		int getpartyID() const					{ return partyID; };

		const vector<Representative>& getRepsFromDist(const int distID) const { return RepsList[distID]; }

		//--Setters--//
		void setPartyName(string _n)			{ partyName = _n; };
		void setBoss(const Citizen& b)			{ boss = &b; };
		void setpartyID(int n)				{ partyID = n; };

		//work of shabat 21:00
		void updateRepsList(unsigned int districtsAmount);
		void addRepresentative(const Citizen& rep, int distID);


		//--https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
		friend void swap(Party& first, Party& second);

		friend std::ostream& operator<<(std::ostream& out, Party& other);

		Party& operator=(Party other);

		void printNameAndId() const;

		void save(ofstream& out) const;
		

		//Shemesh, try to pass this to party.cpp, its fucking anoying
		void load(ifstream& in, const CitizensList& _list)
		{
			int len, id;
			in.read(rcastc(&len), sizeof(len));
			char* _name;
			try {
				_name = new char[len + 1];
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl; exit(1);
			}
			in.read(_name, len);
			_name[len] = '\0';		 //notice, we assign string to char*
			partyName = _name;		 //then, assign it to the string name
			delete[] _name; 		 //at last, delete the temporary char* 

			in.read(rcastc(&partyID), sizeof(partyID));
			in.read(rcastc(&id), sizeof(id)); //reads boss id;


			//BUGGED!
			//boss = (_list.getCitizen(id));
			boss = &_list.getCitizen(id);

			//	in.read(rcastc(&elec_size), sizeof(elec_size));
			//	in.read(rcastc(&elec_length), sizeof(elec_length));
			//
			//	electors = new Elector[elec_size];
			//	for (int i = 0; i < elec_length; i++)
			//		electors[i].load(in, _list);
		}
	};

};

