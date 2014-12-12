// adapter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;
using namespace System;


ref class IIntranetPhoneList
{
public:
	virtual String^ GetPhoneList() = NULL;
};

ref class PersonnelSystem
{
public:
	array<array<String^>^>^  GetEmployees()
    {
		array<array<String^>^>^  employees= gcnew array<array<String^>^>(4);
        employees[0] =  gcnew array<String^> { "1201", "Jim", "Team Leader" };
        employees[1] =  gcnew array<String^> { "1202", "Bob", "Developer" };
        employees[2] =  gcnew array<String^> { "1203", "Sue", "Developer" };
        employees[3] =  gcnew array<String^> { "1204", "Dan", "Tester" };
        return employees;
    }
};

ref class Intranet {

private:
	IIntranetPhoneList^ _phoneListSource;
 
public:
	Intranet(IIntranetPhoneList^ phoneListSource)
    {
        _phoneListSource = phoneListSource;
    }
 
    void ShowPhoneList()
    {
        String^ phoneNumbers = _phoneListSource->GetPhoneList();
        Console::WriteLine(phoneNumbers);
    }
};


ref class PhoneListAdapter : IIntranetPhoneList
{
private:
	PersonnelSystem^ _personnel;
public: 
    PhoneListAdapter(PersonnelSystem^ personnel)
    {
        _personnel = personnel;
    }
 
    virtual  String^ GetPhoneList() override
    {
        array<array<String^>^>^ employees = _personnel->GetEmployees();
		Text::StringBuilder^ sb = gcnew Text::StringBuilder;
		for(int ii=0; ii<4; ii++)
		{
			sb->Append(employees[ii][1]);
			sb->Append(", ");
			sb->Append(employees[ii][2]);
			sb->Append(", ");
			sb->Append(employees[ii][0]);
			sb->Append("\n");
		}
        return sb->ToString();
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	PersonnelSystem^ personnel = gcnew PersonnelSystem();
    PhoneListAdapter^ adapter = gcnew PhoneListAdapter(personnel);
    Intranet^ intranet = gcnew Intranet(adapter);
    intranet->ShowPhoneList();
	Console::ReadLine();
	return 0;
}

