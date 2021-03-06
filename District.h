#pragma once
#include <iostream>
#include "Party.h"
#include "Representative.h"
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
		DynamicArray<Citizen*> citizens;
		vector<vector<Representative>> RepsList;

	public:

		District() : distID(0), numOfReps(0),
			citizens(), RepsList(), voters_precentage(0) {};

		District(string _name, int _numOfReps, int _id) :name(_name), distID(_id), numOfReps(_numOfReps),
			citizens(), RepsList(), voters_precentage(0) {
			cout << "Dist ctor:" << name << endl;
		};

		District(const District& o) :name(o.name), distID(o.distID), numOfReps(o.numOfReps),
			voters_precentage(o.voters_precentage)
		{ 
			citizens = o.citizens;
			RepsList = o.RepsList;
		}

		virtual ~District() {}

		//--Setters--//
		void setDistName(const string _n)			{ name = _n; }
		void setDistID(const int& _id)				{ distID = _id; }
		void setnumOfReps(const int& _t)			{ numOfReps = _t; }
		bool setVotersPercentage(int& allCitizens);
		bool setVotersPersentage(const float& num);
		void setDistCitizenInList(const Citizen&);

		//seters of repsList
		void addPartyRepToList(const int& partyID, const Representative& rep);
		void addPartyRepToList(const int& partyID, const Citizen& rep);

		//--Getters--//


		const string getDistName() const			 { return name; }
		const int& getDistID() const				 { return distID; }
		int getDistReps() const						 { return numOfReps; }
		const float& getVotersPercentage() const	 { return voters_precentage; }


		const DynamicArray<Citizen*>& GetDistCitizens() const { return citizens; }
		const vector<Representative>& getRepsFromParty(const int partyID) const { return RepsList[partyID]; }
		void printPartyRepsNames(const int& partyID)const;

		//--https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
		friend void swap(District& first, District& second);

		District& operator=(District other);

		void initRepsList(const int& size);

		friend std::ostream& operator<<(std::ostream& out, const District& other);

		virtual std::ostream& print(std::ostream& out) const;
	
		
		void printNameAndId();

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
		Divided() : District() {} 
		Divided(string _name, int _numOfReps, int id) : District(_name, _numOfReps, id) {}
		Divided(const Divided& o) : District(o) {}
		virtual ~Divided() {}; //no need, Dtor of district handles itself

		const Divided& operator=(const Divided& o)
		{
			District::operator=(o);
			return *this;
		}

		virtual std::ostream& print(std::ostream& out) const override;
	};
}