#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
void phoneBook()//this function is only for console better look
{
	system("cls");
	cout << "\n\n\t\t\tPhone Book Application\n\n" << endl;
	cout << "----------------------------------------------------------------------------------------\n\n\n\n" << endl;
}
void PhoneBookFile(char fileName[])//this is for displaying current file open
{
	cout << fileName << " file is running: \n\n" << endl;
}
void concatCStr(char* arr1, char* arr2, int size1, int size2, bool toAddSpace)//this is for adding two cstrings 
{
	//heres 4th argument of bool data type is for specifying wether the function should add two strings by adding space between them or simple add them
	if (toAddSpace)
	{
		*(arr1 + size1) = ' ';
		size1++;
	}
	for (int x = 0; *(arr2 + x) != '\0'; x++)
	{
		*(arr1 + size1) = *(arr2 + x);
		size1++;
	}
	*(arr1 + size1) = '\0';
}
void toLowerCase(char* arr, int size)//this function will convert any uper-case cstring two lower case
{
	for (int x = 0; x < size; x++)
	{
		if (*(arr + x) >= 'A' && *(arr + x) <= 'Z')
		{
			*(arr + x) += 32;
		}
	}
}
bool isEqual(char arr1[], char arr2[], int size1, int size2)//this is for checking two cstrings are equal or not
{
	bool isequal = false;
	if (strlen(arr1) == strlen(arr2))
	{
		toLowerCase(arr1, strlen(arr1));
		toLowerCase(arr2, strlen(arr2));
		int counter = 0;
		for (int x = 0; x < strlen(arr1); x++)
		{
			if (arr1[x] == arr2[x])
			{
				counter++;
			}
		}
		if (counter == strlen(arr1))
		{
			isequal = true;
		}
	}
	return isequal;
}
void createFile(char fileName[])//this is for creating a new file 
{
	ofstream fout(fileName);
	fout.close();
	cout << "File created successfully." << endl;
}
bool CheckExistingFile(char fileName[])//this is check for existence of file it helped this application to work properly
{
	ifstream fin(fileName);
	if (!fin)
	{
		return false;
	}
	else
	{
		return true;
	}
	fin.close();
}
void firstLineOfFile(char fileName[])//this function is printing first two hardcoded lines in file
{
	ofstream fout(fileName, ios::app);
	fout << "Sr.No\t|\tName\t|\tPhone number" << endl;
	fout << "-----------------------------------------------------------------------------------" << endl;
	fout.close();
}
void copyFileData(char readfromfile[], char writetofile[])//this function is for copying data from one file to another
{
	char* tempArr = new char[500];
	ifstream fin(readfromfile);
	ofstream fout(writetofile);
	while (fin.getline(tempArr, 499, '\n'))
	{
		fout << tempArr << endl;
	}
	fin.close();
	fout.close();
}
void addRecord(char fileName[], int numOfRecords, int* srNo)//this is for adding new records in phone book
{
	int nameSize = 50;
	//here multiple arrays are dynamically allocating
	char* Name = new char[nameSize];
	int PhoneNoSize = 15;
	char* PhoneNo = new char[PhoneNoSize];
	//opening file in output mode
	ofstream fout(fileName, ios::app);
	{
		//this loop will run until the it takes input of all number of records entered by user
		for (int x = 1; x <= numOfRecords; x++)
		{
			cout << "Enter record " << x << " : " << endl;
			cout << "Enter Name: ";
			cin.ignore();
			cin.getline(Name, nameSize - 1);
			cout << "Enter Phone number of " << Name << " : ";
			cin >> PhoneNo;
			cout << endl;
			//adding records in file
			fout << (*srNo) + 1 << "\t|\t" << Name << "\t|\t" << PhoneNo << endl;
			(*srNo)++;
		}
	}
	fout.close();
	delete[] Name;
	delete[] PhoneNo;
}
void searchRecord(char fileName[], int* srNo)//this is for searching phone number by name
{
	ifstream fin(fileName);
	if (*srNo == 0)//if there is not serial number detects then the file is empty and there is nothing to be searched
	{
		//but file will be only present with only hardcoded data
		cout << "There are no records in the file to be searched." << endl;
	}
	else
	{
		char* SearchedName = new char[50];
		int SrNo;
		char* firstline = new char[500];
		char* Name = new char[50];
		char* lastName = new char[50];
		char* PhoneNo = new char[15];
		char del;
		bool found = false;
		cout << "Enter Name of the person of which phone number is to be searched: ";
		cin.ignore();
		//for first two lines are hardcoded 
		cin.getline(SearchedName, 49);
		fin.getline(firstline, 499, '\n');
		fin.getline(firstline, 499, '\n');
		//runs until it doesnt get any input to store in variables and arrays
		while (fin >> SrNo >> del >> Name >> lastName >> del >> PhoneNo)
		{
			//adding two cstring by adding space so it will become full name and the function is set to true for adding space and concat them
			concatCStr(Name, lastName, strlen(Name), strlen(lastName), true);
			//below function is for comapring two cstrings and tells wether they are equal or not
			//one cstring is user entered and other is name cstring which is in the file if they are equal than searching is done
			bool equal = isEqual(SearchedName, Name, strlen(SearchedName), strlen(Name));
			if (equal)
			{
				cout << endl;
				cout << "Name found in phone book: " << endl;
				cout << "SrNo: " << SrNo << endl;
				cout << "Name: " << Name << endl;
				cout << "Phone No: " << PhoneNo << endl;
				cout << endl;
				found = true;
				break;
			}
		}
		if (!found)
		{
			cout << "Name not found in Phone Book" << endl;
		}
		delete[] SearchedName;
		delete[] PhoneNo;
		delete[] firstline;
		delete[] Name;
		delete[] lastName;
	}

	fin.close();
	system("pause");
}
void modifyRecord(char fileName[], int* srNo)//this is for editing phone number by name
{
	//this also works similar like search function the difference only is that it is opening one temporary file in write or output mode 
	//and other file is opened in read mode or input mode which is main file
	char tempFile[] = "tempData.txt";
	ifstream fin(fileName);
	ofstream fout(tempFile);
	if (*srNo == 0)
	{
		cout << "There are no records in the file to be modified." << endl;
		fin.close();
		fout.close();
	}
	else
	{
		char* SearchedName = new char[50];
		int SrNo;
		char* firstline = new char[500];
		char* Name = new char[50];
		char* lastName = new char[50];
		char* PhoneNo = new char[15];
		char del;
		bool found = false;
		cout << "Enter the name of the person whose phone number you want to modify: ";
		cin.ignore();
		cin.getline(SearchedName, 49);
		fin.getline(firstline, 499, '\n');
		fout << firstline << endl;
		fin.getline(firstline, 499, '\n');
		fout << firstline << endl;
		while (fin >> SrNo >> del >> Name >> lastName >> del >> PhoneNo)
		{
			concatCStr(Name, lastName, strlen(Name), strlen(lastName), true);
			//now here when these two cstrings are equal than we can modify its phone number or contact number
			bool equal = isEqual(SearchedName, Name, strlen(SearchedName), strlen(Name));
			if (equal)
			{
				cout << endl;
				cout << "Name found in phone book: " << endl;
				cout << "SrNo: " << SrNo << endl;
				cout << "Name: " << Name << endl;
				cout << "Phone No: " << PhoneNo << endl;
				cout << endl;
				cout << "Enter the updated phone number: ";
				cin.getline(PhoneNo, 14);
				//after changing the contact number of the user en-tered person name it  update that PhoneNumber in file here
				//note that this is first saving updated data in temp file
				fout << SrNo << "\t|\t" << Name << "\t|\t" << PhoneNo << endl;
				found = true;
			}
			else
			{
				//it is for the other records which are not modfied
				fout << SrNo << "\t|\t" << Name << "\t|\t" << PhoneNo << endl;
			}
		}

		if (!found)
		{
			cout << "Name not found in Phone Book" << endl;
		}

		delete[] SearchedName;
		delete[] PhoneNo;
		delete[] firstline;
		delete[] Name;
		delete[] lastName;

		fin.close();
		fout.close();
		//now copying modfied data which was stored in temp file in or-ginal file 
		copyFileData(tempFile, fileName);
		if (found)
		{
			cout << "Your entered record modified successfully." << endl;
		}
	}
	system("pause");
}
void deleteRecord(char fileName[], int* srNo)//this is for deleting a rec-ord of the user entered name
{
	//this works almost similar like modify function
	char tempFile[] = "tempData.txt";
	ifstream fin(fileName);
	ofstream fout(tempFile);
	if (*srNo == 0)
	{
		cout << "There are no records in the file to be deleted." << endl;
		fin.close();
		fout.close();
	}
	else
	{
		char* SearchedName = new char[50];
		int SrNo;
		int updatedSrNo = 1;
		char* firstline = new char[500];
		char* Name = new char[50];
		char* lastName = new char[50];
		char* PhoneNo = new char[15];
		char del;
		bool found = false;
		cout << "Enter the name of the person whose phone number you want to delete record: ";
		cin.ignore();
		cin.getline(SearchedName, 49);

		fin.getline(firstline, 499, '\n');
		fout << firstline << endl;
		fin.getline(firstline, 499, '\n');
		fout << firstline << endl;
		while (fin >> SrNo >> del >> Name >> lastName >> del >> PhoneNo)
		{
			concatCStr(Name, lastName, strlen(Name), strlen(lastName), true);
			bool equal = isEqual(SearchedName, Name, strlen(SearchedName), strlen(Name));
			if (equal)
			{
				cout << endl;
				cout << "Name found in phone book: " << endl;
				cout << "Your entered record is below and is delet-ed successfully from Phone Book" << endl;
				cout << "SrNo: " << SrNo << endl;
				cout << "Name: " << Name << endl;
				cout << "Phone No: " << PhoneNo << endl;
				cout << endl;
				found = true;
				//it is not writing the record of the person user entered. it is only storing data which is writen in else condition in temp file
			}
			else
			{
				//writing only other records and updating SrNo of each
				fout << updatedSrNo << "\t|\t" << Name << "\t|\t" << PhoneNo << endl;
				updatedSrNo++;
			}
		}
		if (!found)
		{
			cout << "Name not found in Phone Book." << endl;
		}
		delete[] SearchedName;
		delete[] PhoneNo;
		delete[] firstline;
		delete[] Name;
		delete[] lastName;

		fin.close();
		fout.close();
		//again copying from temp file to original file
		copyFileData(tempFile, fileName);
	}
	system("pause");
}
void printFileOnConsole(char fileName[], int* srNo)//this function prints all data from file to console
{
	int tempArrSize = 500;
	char* tempArr = new char[tempArrSize];
	ifstream fin(fileName);
	cout << "Phone Book Data: \n" << endl;
	while (fin.getline(tempArr, 499, '\n'))
	{
		cout << tempArr << endl;
	}
	cout << endl;
	fin.close();
	ifstream fin1(fileName);
	fin1.getline(tempArr, 499, '\n');
	fin1.getline(tempArr, 499, '\n');
	while (fin1 >> *srNo && fin1.getline(tempArr, 499, '\n'))
	{
	}
	fin1.close();
	delete[] tempArr;
}

int main()
{
	char open = ' ';
	//we initialized open variable with space charcter and then we are taking input of open variable wether the user 
	//wants to open or close application
	cout << "Do you want to open Phone Book Application (Enter 'o' to open, 'c' to close): ";
	cin >> open;
	//this loop will run until open gets 'c' or 'o' value
	while (open != 'o' && open != 'c')
	{
		cout << "You entered other than 'o' and 'c' please enter again: " << endl;
		cout << "Do you want to open Phone Book Application (Enter 'o' to open, 'c' to close): ";
		cin >> open;
	}
	//this loop will run till the value of open is changed from 'o'.
	while (open == 'o')
	{
		phoneBook();
		char fileOpenOrCreate, operOnFileData;
		char fileName[50], filenameTxt[] = ".txt";
		int n_of_Records;
		bool flag1 = false;
		int fileLineSize = 300;
		int SrNo = 0;
		//this flag1 variable will get false value when file do not exist and true when file entered exist or created new file
		while (!flag1)
		{
			fileOpenOrCreate = ' ';
			operOnFileData = ' ';
			//this is for opening existing file or creating new one
			while (fileOpenOrCreate != 'e' && fileOpenOrCreate != 'c')
			{
				cout << "Enter ('e' to open existing file) or ('c' to create new file): ";
				cin >> fileOpenOrCreate;
				if (fileOpenOrCreate != 'e' && fileOpenOrCreate != 'c')
				{
					cout << "You entered wrong character other than op-tions. Please enter again: \n" << endl;
				}
			}
			switch (fileOpenOrCreate)
			{
			case 'e':
				cout << "Enter file name you want to open (existing file name): ";
				cin >> fileName;
				//concatCstr function is used for combining file name with .txt like file.txt
				concatCStr(fileName, filenameTxt, strlen(fileName), strlen(filenameTxt), false);
				//check existance of file
				if (CheckExistingFile(fileName))
				{
					cout << "File you entered exists and is open-ing now." << endl;
					flag1 = true;
				}
				else
				{
					cout << "File you entered do not exists." << endl;
					cout << "Please select options again  that you want to create or open existing file.\n" << endl;
					flag1 = false;
				}
				break;
			case 'c':
				cout << "Enter file name by which you want create file: ";
				cin >> fileName;
				concatCStr(fileName, filenameTxt, strlen(fileName), strlen(filenameTxt), false);
				//below two functions are used create new file and makinf frist two hardcoded lines in file
				createFile(fileName);
				firstLineOfFile(fileName);
				flag1 = true;
				break;
			}
		}
		phoneBook();
		PhoneBookFile(fileName);
		printFileOnConsole(fileName, &SrNo);
		//this loop will as operation until user enter correct caharct-er from the options below
		while (operOnFileData != 'a' && operOnFileData != 's' && operOnFileData != 'm' && operOnFileData != 'd')
		{
			cout << "Enter which operation you want to do with file data record('a' to add, 's' to search, 'm' to modify, 'd' to delete): ";
			cin >> operOnFileData;
			if (operOnFileData != 'a' && operOnFileData != 's' && operOnFileData != 'm' && operOnFileData != 'd')
			{
				cout << "You entered invalid character enter char-acter again in the given options: \n" << endl;
			}
		}
		phoneBook();
		PhoneBookFile(fileName);
		printFileOnConsole(fileName, &SrNo);
		switch (operOnFileData) {
		case 'a':
			//for performing add operation 
			cout << "\n\n\t\tAdd Record Mode\n\n" << endl;
			cout << "Enter number of records to add: ";
			cin >> n_of_Records;
			system("cls");
			addRecord(fileName, n_of_Records, &SrNo);
			break;
		case 's':
			//for performing search operation
			cout << "\n\n\t\tSearch Record Mode\n\n" << endl;
			searchRecord(fileName, &SrNo);
			break;
		case 'm':
			//for performing modify operation
			cout << "\n\n\t\tModify Record Mode\n\n" << endl;
			modifyRecord(fileName, &SrNo);
			break;
		case 'd':
			//for performing delete operation
			cout << "\n\n\t\tDelete Record Mode\n\n" << endl;
			deleteRecord(fileName, &SrNo);
			break;
		}
		PhoneBookFile(fileName);
		//now displaying updated file data
		cout << "\tupdated Phone Book Data: \n" << endl;
		printFileOnConsole(fileName, &SrNo);
		cout << "Do you want to keep open Phone Book Application (Enter 'o' to open, 'c' to close): ";
		cin >> open;
		//asks again for open or close application
		while (open != 'o' && open != 'c')
		{
			cout << "You entered other than 'o' and 'c' please enter again: " << endl;
			cout << "Do you want to keep open Phone Book Application (Enter 'o' to open, 'c' to close): ";
			cin >> open;
		}
	}
	if (open == 'c')//runs when application is turning off
	{
		system("cls");
		cout << "\n\n\n\t\t\tThanks For using Phone Book Application." << endl;
		cout << "\t\t\tApplication is closed successfully.\n\n\n" << endl;
	}
	return 0;
}
