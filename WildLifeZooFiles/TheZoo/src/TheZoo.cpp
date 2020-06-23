#include <iostream>
#include <jni.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}
vector<string> ZooVector; //creates global empty vector for user to populate

void AddAnimal() //function to add animal data to vector
{

	string userInput;

	cout << "Enter Animal Data (Tracking Number, Name, Type, Sub-Type, Egg count, and Nursing status): " << endl;
	getline(cin, userInput);

	ZooVector.push_back(userInput);

	cout << "Animal successfully added" << endl;
	cout << endl;

}


void RemoveAnimal() //function to remove animal from vector
{

     int userIndex;
     cout << "Select index of animal to be removed: 1-" << ZooVector.size() << endl;

     cin >> userIndex;
     if (userIndex == 1) {
    	 ZooVector.erase(ZooVector.begin());
     }
     else {
    	 ZooVector.erase(ZooVector.begin() + userIndex);
     }
     cout << "Animal successfully deleted" << endl;
     cout << endl;
}

void LoadDataFromFile() //function to load data from txt file into vector
{
	string dataLine;
	vector<string> DataArray;
	ifstream zoofile("zoodata.txt");
	unsigned int i;

	if(!zoofile) {
		cout << "Error opening file" << endl;
		system("pause");

	}
	while(getline(zoofile, dataLine)) {
		DataArray.push_back(dataLine);
	}
	for(i = 0; i < DataArray.size(); ++i) {
		cout << DataArray.at(i) << endl;
	}
	cout << endl;
}

void SaveDataToFile() //function to save data to txt file
{
     ofstream outFile("zoodata.txt");
     for (const auto &e : ZooVector) outFile << e << "\n";
     cout << "Save successfully completed" << endl;
     cout << endl;

}

void DisplayData() //function to display vector data
{

	for(const auto& item : ZooVector) {
			   cout << item << "\n";
			}
	cout << endl;
}

void DisplayMenu() //function to display user menu
{
     cout << "---------------------------------" << endl;
     cout << "==== Please Make a Selection ====" << endl;
     cout << "---------------------------------" << endl;
     cout << "(1) Load Animal Data" << endl;
     cout << "(2) Generate Data" <<  endl;
     cout << "(3) Display Animal Data" << endl;
     cout << "(4) Add Record" << endl;
     cout << "(5) Delete Record" << endl;
     cout << "(6) Save Animal Data" << endl;
     cout << "(7) Exit Program" << endl;
}



int main()
{

char rpt;

	do {
	int userMenuChoice;
	DisplayMenu();
	cin >> userMenuChoice;
	cin.ignore(80, '\n'); //collects user menu input choice

	switch (userMenuChoice) { //switch to call functions based on user choice
	case 1:
		LoadDataFromFile();
		break;
	case 2:
		GenerateData();
		break;
	case 3:
		DisplayData();
		break;
	case 4:
		AddAnimal();
		break;
	case 5:
		RemoveAnimal();
		break;
	case 6:
		SaveDataToFile();
		break;
	case 7:
		cout << "Exiting Program" << endl;
		break;

	}
	cout << "Would you like to make another selection?" << endl;
	cout << "Type Y to make another selection or N to exit." << endl;
	cin >> rpt;
	} while (rpt == 'Y'); //returns user to main menu and gives option for additional selection



	return 0;
}
