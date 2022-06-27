#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>


using namespace std;
using std::cout;
using std::vector;


//function allows python functions to be called 
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}




//calls python function using a string parameter 
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}





//calls python functions with integer parameter
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}



/*function opens dat fileand puts file infromation into an array
then separates names of items from their quantity
function then prints histogram with data from file */

void printHistogram() {
	//declare variables 
	int index = 0;
	int arraySize = 40;

	//declares file 
	ifstream file;

	//opens file 
	file.open("frequency.dat");

	//validates that file is open 
	if (file.fail()) {
		cout << "Error: file did not open" << endl;
	}

	//declare array that holds file data 
	string itemArray[40];

	//loop to add file data to array 
	while (index < arraySize && file >> itemArray[index])
	{
		index++;
	}

	//declare vectors for sorting data 
	vector <string> nameVect;
	vector <int> quantityVect;

	//loop to add item names to name vector 
	for (int i = 0; i < 40; i += 2) {
		int n = 0;
		nameVect.push_back(itemArray[i]);
	}

	//loop adds quantities to quantity array 
	for (int i = 1; i < 40; i += 2) {
		int n = 0;
		int newQuantity = stoi(itemArray[i]);
		quantityVect.push_back(newQuantity);
	}

	//loop to print names of item and appropriate number of stars for items purchased
	for (int i = 0; i < nameVect.size(); ++i) {
		cout << nameVect.at(i);
		for (int j = 0; j < quantityVect.at(i); ++j) {
				cout << "*";
		}
		cout << endl;
	}

}





void main()
{
	//declare variables and initailize python 
	Py_Initialize();
	int option = 0;

	//menu loop
	while (option != 5) {
		cout << "1................All items purchased................" << endl;
		cout << "2......Number of purchases of a singular item......." << endl;
		cout << "3...........Most to least purchased items..........." << endl;
		cout << "4........Display product purchase histogram........." << endl;
		cout << "5......................Exit........................." << endl;
		cout << endl;

		//user input for menu selection 
		cin >> option;

		//switch statement to execute menu selection 
		switch (option) {
			
			//prints items purchased 
		case 1:
			CallProcedure("ItemsPurchased");
			cout << endl;
			break;

			//prints purchases of a specific item when entered
		case 2:
			CallProcedure("GetNumItemsSold");
			cout << endl;
			break;

			//sorts items by most purchased to least purchased 
		case 3:
			CallProcedure("MostPopularItems");
			cout << endl;
			break;

			//prints histogram 
		case 4:
			printHistogram();
			cout << endl;
			break;

			//exit menu 
		case 5:
			cout << "You have exited the menu" << endl;
			cout << "Goodbye" << endl;
			cout << endl;
			break;

			//default prompting user to input valid menu selection
		default:
			cout << "Please enter a valid selection: " << endl;
			cout << endl;
			break;
		}
	}

}