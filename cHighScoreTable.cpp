#include "cHighScoreTable.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>


cHighScoreTable::cHighScoreTable()
{
	this->userName = "";
}

cHighScoreTable::cHighScoreTable(int maxSize)
{
	this->MAX_SIZE = maxSize;
	this->userName = "";
}

bool cHighScoreTable::loadFromFile(string highScoreFile)
{
	ifstream file;
	string aName;
	int aScore;
	int item = 0;

	file.open(highScoreFile, ios::binary);
	if (!file.is_open())
	{ 
		cout << "Error opening file " << highScoreFile << endl;
		return false;
	}
	// Check if file is empty
	if (file.peek() == ifstream::traits_type::eof())
	{
		this->fileEmpty = true;
		cout << "File " << highScoreFile << " is empty!" << endl;
		return false;
	}
	
	Item aTableEntry;
	tableEntries.clear();

	while (!file.eof() && !this->fileEmpty)
	{
		tableEntries.push_back(new Item);
		file >> aName >> aScore;
		tableEntries[item]->Name = aName;
		tableEntries[item]->score = aScore;
		item++;
	}
	file.close();
	this->setTableSize(item);
	return true;
}

bool cHighScoreTable::saveToFile(string highScoreFile)
{
	ofstream file;
	file.open(highScoreFile, ios::binary | ios::out);

	if (!file.is_open())
	{ 
		cout << "Error opening file " << highScoreFile << " for saving to ..." << endl;
		return false;
	}

	for (int tblEntry = 0; tblEntry < (int)this->tableEntries.size(); tblEntry++)
	{
		file << tableEntries[tblEntry]->Name << " " << tableEntries[tblEntry]->score << endl;
	}

	file.close();
	return true;
}

int  cHighScoreTable::addItem(Item entry)
{
	int aRow = this->tableEntries.size();

	if (aRow == this->MAX_SIZE)
	{
		cout << "Table full" << endl;
		this->tableSize = aRow;
		return aRow;
	}
	else
	{
		int index = aRow;
		this->tableEntries.push_back(new Item);
		this->tableEntries[index]->Name = entry.Name;
		this->tableEntries[index]->score = entry.score;
		sort(this->tableEntries.begin(), this->tableEntries.end());
		return this->tableEntries.size();
	}
}

int  cHighScoreTable::addItem(string name, int score)
{
	int aRow = this->tableEntries.size();

	if (aRow == this->MAX_SIZE)
	{
		cout << "Table full" << endl;
		this->tableSize = aRow;
		return aRow;
	}
	else
	{
		int index = aRow;
		this->tableEntries.push_back(new Item);
		this->tableEntries[index]->Name = name;
		this->tableEntries[index]->score = score;
		sort(this->tableEntries.begin(), this->tableEntries.end());
		return this->tableEntries.size();
	}
}

cHighScoreTable::Item cHighScoreTable::getItem(int theRow)
{
	Item tblItem;
	tblItem.Name  = this->tableEntries[theRow]->Name;
	tblItem.score = this->tableEntries[theRow]->score;
	return tblItem;
}

void cHighScoreTable::clearTable()
{
	this->tableEntries.clear();
}

string cHighScoreTable::convertToString()
{
	string table = "";
	for (int tblEntry = 0; tblEntry < (int)this->tableEntries.size(); tblEntry++)
	{
		table += tableEntries[tblEntry]->Name + " " + std::to_string(tableEntries[tblEntry]->score) + "\n";
	}
	return table;
}

int cHighScoreTable::getTableSize()
{
	return this->tableSize;
}

void cHighScoreTable::setTableSize(int theSize)
{
	this->tableSize = theSize;
}

bool cHighScoreTable::getIsFileEmpty()
{
	return this->fileEmpty;
}

void cHighScoreTable::setIsFileEmpty(bool flag)
{
	this->fileEmpty = flag;
}


void cHighScoreTable::getUserName()
{

}

cHighScoreTable::~cHighScoreTable()
{
}
