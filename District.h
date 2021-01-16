#pragma once
#include <iostream>
#include "Party.h"
#include "Representative.h"
#include <list>
#include <vector>

using namespace std;

namespace elc
{
	class Citizen; //fW declaration
 
	//---------------District---------------//
	//------------------------------------//

	class District 
	{
	protected:
		string name;
		int distID;
		int numOfReps; //Total number of representatives in the district
		float voters_precentage;
		vector<Citizen*> citizens; 
		vector<vector<Representative>> RepsList;

	public:

		//District() : distID(0), numOfReps(0),
		//	citizens(), RepsList(), voters_precentage(0) {};


		District(string _name, int _numOfReps, int _id) :name(_name), distID(_id), numOfReps(_numOfReps),
			citizens(), RepsList(), voters_precentage(0) {
			cout << "Dist ctor:" << name << endl;
		};

		District(const District& o) :name(o.name), distID(o.distID), numOfReps(o.numOfReps),
			voters_precentage(o.voters_precentage)
		{ 
			citizens = o.citizens;
			RepsList = o.RepsList;
			//*this = o;
		}

		virtual ~District() { cout << "Dist dtor:" << name << endl; }

		//--Setters--//
		void  setDistName(const string _n)			{ name = _n; }
		void setDistID(const int& _id)				{ distID = _id; }
		void setnumOfReps(const int& _t)			{ numOfReps = _t; }
		bool setVotersPercentage(int& allCitizens);
		bool setVotersPersentage(const float& num);
		void setDistCitizenInList(Citizen&);

		//seters of repsList

		//--Getters--//


		const string getDistName() const			 { return name; }
		const int& getDistID() const				 { return distID; }
		int getDistReps() const						 { return numOfReps; }
		const float& getVotersPercentage() const	 { return voters_precentage; }


		const vector<Citizen*>& GetDistCitizens() const { return citizens; }
		const vector<Representative>& getRepsFromParty(const int partyID) const { return RepsList[partyID]; }



		//-----------------------------------------------------------------------------
		//--https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
		//-----------------------------------------------------------------------------
		friend void swap(District& first, District& second) // nothrow
		{
			// enable ADL (not necessary in our case, but good practice)
			using std::swap;

			// by swapping the members of two objects,
			// the two objects are effectively swapped
			swap(first.name, second.name);
			swap(first.distID, second.distID);
			swap(first.numOfReps, second.numOfReps);
			swap(first.voters_precentage, second.voters_precentage);
			swap(first.citizens, second.citizens);
			swap(first.RepsList, second.RepsList);
		}

		District& operator=(District other) // (1)
		{
			swap(*this, other); // (2)
			return *this;
		}

		bool initRepsList(const int& size/*, Party* list*/);

		friend std::ostream& operator<<(std::ostream& out, const District& other);

		virtual std::ostream& print(std::ostream& out) const;
	
		
		void printNameAndId();

		//void operator=(const District&);
		bool isDivided();

		void save(ofstream& out) const;
		void load(ifstream& in);
	};



	//---------------Divided---------------//
	//------------------------------------//
	class Divided : public District
	{
	private:

	public:
		//Divided() : District() {}
		Divided(string _name, int _numOfReps, int id) : District(_name, _numOfReps, id) {}
		Divided(const Divided& o) : District(o) {}
		virtual ~Divided() {};

		const Divided& operator=(const Divided& o)
		{
			District::operator=(o);
			return *this;
		}

		virtual std::ostream& print(std::ostream& out) const override;

	};
}