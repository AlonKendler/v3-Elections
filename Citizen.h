#pragma once
#include <exception>
#include <iostream>
#include <fstream>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

namespace elc {

	class District;
	class DistrictsList;

	class Citizen {
	protected:
		string name;
		int ID;
		int YOB;
		const District* dist;
		bool hasVoted;

	public:

		Citizen() : ID(0), YOB(0), hasVoted(false), dist(nullptr) {}
		Citizen(string _name, int id, const District& _dist, int year)
			: name(_name), ID(id), dist(&_dist), YOB(year), hasVoted(false) 
		{
			if (YOB < 0 || YOB > 2020) throw invalid_argument("invalid year of birth");
			if (dist == nullptr) throw invalid_argument("distirct pointer of citizen is nullptr");
		}

		Citizen(const Citizen& o) : name(o.name), ID(o.ID), 
			dist(o.dist), YOB(o.YOB), hasVoted(o.hasVoted)  { };

		virtual ~Citizen() {};

		//--Getters
		std::string getName() const					{ return name; };
		int getID() const							{ return ID; };
		int getYOB() const							{ return YOB; };
		const District& getDistrict()const			{ return *dist; };
		bool getVote() const						{ return hasVoted; }

		//--Setters

		void setName(const std::string n)			{ name = n; };
		void setID(int id)							{ ID = id; };
		void setYOB(int year)						{ YOB = year; };
		void setDistrict(const District& _dist)     { dist = &_dist; };
		void setVote(bool val)						{ hasVoted = val; }


		//--https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
		friend void swap(Citizen& first, Citizen& second);

		Citizen& operator=(Citizen other);
	
		friend std::ostream& operator<<(std::ostream& out, const Citizen& other);

	    void save(std::ofstream& out) const;
	    void load(std::ifstream& in, const DistrictsList& _list);
	};
};

