#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "clsString.h"
using namespace std;

class clsBook
{
private:
	enum enMode {
		eEmptyMode = 1, eUpdateMode = 2, eAddNewMode = 3
	};
	enMode _Mode;
	string _BookID;
	string _BookName;
	string _BookWriter;
	short  _BookPrice;
	bool _MarkedForDelete = false;
	bool _Available = true;

	static string _ConvertBookRecordToLine(clsBook BookRecord,string Separator = "#//#")
	{
		string BookDataLine = "";
		BookDataLine += BookRecord.BookID + Separator;
		BookDataLine += BookRecord.BookName + Separator;
		BookDataLine += BookRecord.BookWriter + Separator;
		BookDataLine += to_string(BookRecord.BookPrice) + Separator;
		BookDataLine += to_string(BookRecord.Available);
		return BookDataLine;
	}
	static clsBook _ConvertLineToBookRecord(string Line ,string Separator = "#//#")
	{
		vector <string> vBookData ;
		vBookData = clsString::Split(Line, Separator);
		return clsBook(enMode::eUpdateMode,vBookData[0], vBookData[1], vBookData[2], stod(vBookData[3]), stod(vBookData[4]));
	}
	static void _SaveBooksDataToFile(clsBook BookRecord)
	{
		fstream MyFile;
		MyFile.open("Books.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			string BookDataLine = _ConvertBookRecordToLine(BookRecord);
			MyFile << BookDataLine << endl;
			MyFile.close();
		}
	}
	static vector <clsBook> _LoadBookDataFromFile()
	{
		fstream MyFile;
		vector <clsBook> vBookData;
		MyFile.open("Books.txt", ios::in);
		if (MyFile.is_open())
		{
			string BookDataLine = "";
			
			while (getline(MyFile, BookDataLine))
			{
				clsBook BookRecord = _ConvertLineToBookRecord(BookDataLine);
				vBookData.push_back(BookRecord);
			}
			MyFile.close();
		}
		return vBookData;
	}
	static void _SaveBooksDataToFile(vector <clsBook> vBooks)
	{

		fstream MyFile;
		MyFile.open("Books.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBook U : vBooks)
			{
				if (U._MarkedForDelete == false)
				{
					DataLine = _ConvertBookRecordToLine(U);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}

	}
	static clsBook _GetEmptyBookObject()
	{
		return clsBook(enMode::eEmptyMode,"", "", "", 0,0);
	}
	static void _SaveBookDataToFile(clsBook BookRecord)
	{
		fstream MyFile;
		MyFile.open("Books.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			string Line = _ConvertBookRecordToLine(BookRecord);
			MyFile << Line << endl;
			MyFile.close();
		}
	} 
	void _Add()
	{
		_SaveBookDataToFile(*this);
	}
	void _Update()
	{
		vector <clsBook> _vBooks = _LoadBookDataFromFile();
		for (clsBook &B : _vBooks)
		{
			if (B.BookID == _BookID)
			{
				B = *this;
				break;
			}
		}
		_SaveBooksDataToFile(_vBooks);
	}

public:

	clsBook(enMode Mode,string BookID, string BookName, string BookWriter, short BookPrice , bool Available = 1 )
	{
		_Mode = Mode;
		_BookID = BookID;
		_BookName = BookName;
		_BookWriter = BookWriter;
		_BookPrice = BookPrice;
		_Available = Available;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::eEmptyMode);
	}
	static bool IsBookExist(string BookID)
	{
		clsBook BookRecord = clsBook::Find(BookID);
		return (!BookRecord.IsEmpty());
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string GetBookID()
	{
		return _BookID;
	}
	void SetBookID(string BookID)
	{
		_BookID = BookID;
	}
	__declspec(property(get = GetBookID, put = SetBookID)) string BookID;
	string GetBookName()
	{
		return _BookName;
	}
	void SetBookName(string BookName)
	{
		_BookName = BookName;
	}
	__declspec(property(get = GetBookName, put = SetBookName)) string BookName;
	string GetBookWriter()
	{
		return _BookWriter;
	}
	void SetBookWriter(string BookWriter)
	{
		_BookWriter = BookWriter;
	}
	__declspec(property(get = GetBookWriter, put = SetBookWriter)) string BookWriter;
	short GetBookPrice()
	{
		return _BookPrice;
	}
	void SetBookPrice(short BookPrice)
	{
		_BookPrice = BookPrice;
	}
	__declspec(property(get = GetBookPrice, put = SetBookPrice)) short BookPrice;
	bool get_Available() const { return _Available; }
	void set_Available(bool value) { _Available = value; }
	__declspec(property(get = get_Available, put = set_Available)) bool Available;
	
	static void SaveBookRecordToFile(clsBook Book)
	{
		_SaveBooksDataToFile(Book);
	}
	
	static clsBook GetAddNewBookObj()
	{
		return clsBook(enMode::eAddNewMode, "", "", "", 0 );
	}

	static clsBook Find(string ID)
	{
		fstream MyFile;
		MyFile.open("Books.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsBook BookRecord = _ConvertLineToBookRecord(Line);
				if (BookRecord.BookID == ID)
				{
					MyFile.close();
					return BookRecord;
				}
			}
			MyFile.close();
		}
		return _GetEmptyBookObject();
	}
	static clsBook Find(string ID,string BookName)
	{
		fstream MyFile;
		MyFile.open("Books.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsBook BookRecord = _ConvertLineToBookRecord(Line);
				if (BookRecord.BookID == ID && BookRecord.BookName == BookName)
				{
					MyFile.close();
					return BookRecord;
				}
			}
			MyFile.close();
		}
		return _GetEmptyBookObject();
	}
	
	bool Delete()
	{
		vector <clsBook> vBooks = clsBook::_LoadBookDataFromFile();
		for (clsBook& B : vBooks)
		{
			if (B.BookID == _BookID)
			{
				B._MarkedForDelete = true;
				break;
			}
		}
		clsBook::_SaveBooksDataToFile(vBooks);
		*this = clsBook::_GetEmptyBookObject();
		return true;
	}

	enum enSave {
		eFailSavedEmptyObj = 1 , eSavedSuccessfuly = 2 , eFailSavedBookIDExist = 3
	};
	enSave Save()
	{
		switch (_Mode)
		{
		case enMode::eEmptyMode:
			return enSave::eFailSavedEmptyObj;
		case enMode::eAddNewMode:
			//_Add(); fonction resposable to add new book with new ID . (Check if Book ID not Exist).
			// In Case we find ID exist . we do  enSave::eFailSavedBookIDExist.
			//Later one.
			if (clsBook::IsBookExist(_BookID))
			{
				return enSave::eFailSavedBookIDExist;
			}
			else
			{
				_Add();
				_Mode = enMode::eUpdateMode;
				return enSave::eSavedSuccessfuly;
			}
			
		case enMode::eUpdateMode:
			//_Update(); Fonction Resposable to update old info to new info.
			if (clsBook::IsEmpty())
			{
				return enSave::eFailSavedEmptyObj;
			}
			else
			{
			_Update();
			return enSave::eSavedSuccessfuly;
			}
		}
	}

	static vector <clsBook> GetListBooks()
	{
		return _LoadBookDataFromFile();
	}

	 bool IsBookAvailable()
	{
		return _Available;
	}

};

