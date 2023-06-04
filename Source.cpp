/*
Name: Srinivas Vardhan Dintakurthi

Class Name: CS-1337.503 Computer Programming-1

Due Date:10/27/2022

Description:The 911 service is developing an application to help the 
dispatcher attending emergency calls, to find the nearest/closest service to 
the place where the emergency occurred.This program will contact  
a POLICE_DEPARTMENT, a HOSPITAL or FIRE_STATION depending on the event. After
entering the location it will display a menu and find out the nearest selected
service.

*/

#include<iostream> //Header file for cin and cout
#include<fstream>//To save sorted array to file
#include<iomanip>//To manipulate output
#include<cmath>//To calculate distance
using namespace std;

enum servType { POLICE_DEPARTMENT = 0, HOSPITAL = 1, FIRE_STATION = 2 };

//Structure to store all the data of one service
struct servData{
	
	int serv_id;
	double x_cor, y_cor;
	servType type;
	char* city_name=new char[26];
	int calls;

};


//Required function prototypes
int getNumberOfRecords(char*);
bool readInputFiles(servData* , int,char*);
servData* getNearestService(servData*, int, double, double);
servData* getNearestPoliceDepartment(servData*, int, double,double);
servData* getNearestHospital(servData*, int, double, double);
servData* getNearestFireStation(servData*, int, double, double);
void sort(servData*, int);
void menu(servData* , int , double , double );

char ch;
double x, y;





int main() {

	//c-string to store filename
	//char filename[200]= "C:\\Users\\dvard\\OneDrive\\Desktop\\Fall-2022\\CS-1337\\Assignment-3\\Assignment-3\\ServiceInfo.txt";
	char filename[200] = "ServiceInfo.txt";
	int size = getNumberOfRecords(filename);

	if (size > 0) {
		//Dynamically allocating array
		servData* sd;
		sd = new servData[size];



		bool status = readInputFiles(sd, size, filename);

		if (status == true) {

			
			menu(sd,size,x,y);
		}
		else {
			cout << "Reading file failed\n";
			return -1;
		}

		sort(sd, size);
	}

	
	return 0;

}

//Declaring required functions

//Menu

bool go = true;
void menu(servData* sd,int size,double x,double y) {

	cout << "\nPlease make a selection\n";

	do{

		cout << "a) Enter your location (x,y)\n";
		if (!go) {
			cout<<
				"b) Find the nearest service\n" <<
				"c) Find the nearest POLICE DEPARTMENT\n" <<
				"d) Find the nearest HOSPITAL\n" <<
				"e) Find the nearest FIRE STATION\n";
		}
		cout<<"f) Exit\n";

		cin >> ch;

		if (ch == 'a')
			go = false;

		switch (ch) {

		case 'a': {
			cout << "Please enter the x and y coordinates\n";
			cin >> x >> y;

			
			menu(sd,size,x,y);
		}
				break;

		case 'b': {

			if (go) {
				cout << "Please enter coordinates by choosing option a)\n";

			}
			
			
	
			servData *ptr=getNearestService(sd,size,x,y);

			cout << "id-" << (*ptr).serv_id << " coordinates " << (*ptr).x_cor << "," << (*ptr).y_cor << " type is ";
				if ((*ptr).type == 0) {
					cout << "POLICE DEPARTMENT ";
				}
				else if ((*ptr).type == 1) {
					cout << "HOSPITAL ";
				}
				else if ((*ptr).type == 2) {
					cout << "FIRE STATION ";
				};
				cout<< "at " << (*ptr).city_name<<" no. of calls "<<(*ptr).calls<<"\n";
			
			menu(sd, size, x, y);
		}
				break;

		case'c': {
		    if (go) {
				cout << "Please enter coordinates by choosing option a)\n";

			}
			servData*polptr =getNearestPoliceDepartment(sd,size,x,y);

			cout << "id-" << (*polptr).serv_id << " coordinates " << (*polptr).x_cor << "," << (*polptr).y_cor << " type is ";
			if ((*polptr).type == 0) {
				cout << "POLICE DEPARTMENT ";
			}
			else if ((*polptr).type == 1) {
				cout << "HOSPITAL ";
			}
			else if ((*polptr).type == 2) {
				cout << "FIRE STATION ";
			};
			cout << "at " << (*polptr).city_name << " no. of calls " << (*polptr).calls << "\n";
			menu(sd, size, x, y);
		}
			   break;

		case'd': {
			if (go) {
				cout << "Please enter coordinates by choosing option a)\n";

			}
			servData*hosptr=getNearestHospital(sd,size,x,y);

			cout << "id-" << (*hosptr).serv_id << " coordinates " << (*hosptr).x_cor << "," << (*hosptr).y_cor << " type is ";
			if ((*hosptr).type == 0) {
				cout << "POLICE DEPARTMENT ";
			}
			else if ((*hosptr).type == 1) {
				cout << "HOSPITAL ";
			}
			else if ((*hosptr).type == 2) {
				cout << "FIRE STATION ";
			};
			cout << "at " << (*hosptr).city_name << " no. of calls " << (*hosptr).calls << "\n";
			menu(sd, size, x, y);
		}
			   break;

		case'e': {
			if (go) {
				cout << "Please enter coordinates by choosing option a)\n";

			}
			servData* fsptr=getNearestFireStation(sd,size,x,y);

			cout << "id-" << (*fsptr).serv_id << " coordinates " << (*fsptr).x_cor << "," << (*fsptr).y_cor << " type is ";
			if ((*fsptr).type == 0) {
				cout << "POLICE DEPARTMENT ";
			}
			else if ((*fsptr).type == 1) {
				cout << "HOSPITAL ";
			}
			else if ((*fsptr).type == 2) {
				cout << "FIRE STATION ";
			};
			cout << "at " << (*fsptr).city_name << " no. of calls " << (*fsptr).calls << "\n";
			menu(sd, size, x, y);
		}
			   break;

		
		case'f':return;
			break;

		default: {
			cout << "option is invalid";
		}
		}
	} while (go);
		


	
}

int getNumberOfRecords(char* p) {

	ifstream input;
	input.open(p);


	if (!input.is_open()) {
		cout << "Error opening the file" << endl;
		return -1;
	}

	

	char buffer[1000];
	int counter = 0;

	while (!input.eof()) {
		input.getline(buffer, 1000);
		counter++;
	}
	input.close();
	return counter;

}
// Function to read input file
bool readInputFiles(servData* s, int n,char* p) {
	ifstream input;
	input.open(p);

	int k;


	if (!input.is_open()) {
		cout << "Error opening the file" << endl;
		return -1;
	}

	char buffer[1000];
	int counter;

	for (counter = 0; !input.eof();counter++) {

		input >> s[counter].serv_id >> s[counter].x_cor >> s[counter].y_cor >> k;

		s[counter].type = static_cast<servType>(k);

		input >> s[counter].city_name >> s[counter].calls;
	}
	input.close();

	input.clear();
	input.seekg(0, ios::beg);

	return true;

}

//Function to get nearest service
servData* getNearestService(servData* sd, int size, double x_loc, double y_loc) {

	
	double min_dis=-1, d;
	 int min_ind=-1;

	for (int i = 0; i < size; i++) {


		d = sqrt((pow((sd[i].x_cor - x_loc), 2.0) + pow((sd[i].y_cor - y_loc), 2.0)));
		


		if (i == 1) {
			min_dis = d;
		}
		else if (min_dis > d) {
			min_dis = d;
			min_ind = i;
		}
	}

	if (min_ind != -1) {
		servData* ptr = &sd[min_ind];
		return ptr;
	}
	else return nullptr;

}

//function to get police station
servData* getNearestPoliceDepartment(servData* sd, int size, double x_loc, double y_loc) {

	double min_dis = -1, d;
	int min_ind=-1;
	int counter = 0;

	for (int i = 0; i < size; i++) {
		
		if (sd[i].type == 0) {
			
			d = sqrt((pow((sd[i].x_cor - x_loc), 2.0) + pow((sd[i].y_cor - y_loc), 2.0)));



			if (counter == 0) {
				min_dis = d;
			}
			else if (min_dis > d) {
				min_dis = d;
				min_ind = i;
				
			}

			counter++;
		}

	}

	
	if (min_ind != -1) {
		servData* ptr = &sd[min_ind];
		return ptr;
	}
	else return nullptr;
}

//function to get hospital
servData* getNearestHospital(servData* sd, int size, double x_loc, double y_loc) {
	double min_dis = -1, d;
	int min_ind = -1;
	int counter = 0;

	for (int i = 0; i < size; i++) {

		if (sd[i].type == 1) {

			d = sqrt((pow((sd[i].x_cor - x_loc), 2.0) + pow((sd[i].y_cor - y_loc), 2.0)));



			if (counter == 0) {
				min_dis = d;
			}
			else if (min_dis > d) {
				min_dis = d;
				min_ind = i;

			}

			counter++;
		}

	}


	if (min_ind != -1) {
		servData* ptr = &sd[min_ind];
		return ptr;
	}
	else return nullptr;
}

//function to get fire station
servData* getNearestFireStation(servData* sd, int size, double x_loc, double y_loc) {
	double min_dis = -1, d;
	int min_ind = -1;
	int counter = 0;

	for (int i = 0; i < size; i++) {

		if (sd[i].type == 2) {

			d = sqrt((pow((sd[i].x_cor - x_loc), 2.0) + pow((sd[i].y_cor - y_loc), 2.0)));



			if (counter == 0) {
				min_dis = d;
			}
			else if (min_dis > d) {
				min_dis = d;
				min_ind = i;

			}

			counter++;
		}

	}


	if (min_ind != -1) {
		servData* ptr = &sd[min_ind];
		return ptr;
	}
	else return nullptr;
}

//function to sort
void sort(servData* sd, int size) {

		bool swap;
		servData temp;
		
			 do
			 {
				 swap = false;
					for (int count = 0; count < (size-1); count++)
					{
						if (sd[count].type > sd[count + 1].type)
						{
							 temp = sd[count];
							 sd[count] = sd[count + 1];
							 sd[count + 1] = temp;
							 swap = true;
						}
					}
			 } while (swap);

			 ofstream output;
			 output.open("sortedServiceInfo.txt");

			 for (int i = 0; i < size; i++) {

				 output << left ;
				 
				 output << setw(6) << sd[i].serv_id << fixed << setprecision(1)
					 <<setw(10) << sd[i].x_cor<<
					 setw(10) << sd[i].y_cor << setw(6) << sd[i].type <<
				 setw(30) << sd[i].city_name
				     <<setw(6) << sd[i].calls << "\n";
			 }

			 output.close();
}

