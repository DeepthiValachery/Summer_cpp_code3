/*	Student Name	:	Deepthi Valachery
	Student ID		:	816035457
	Course Code		:	COMP 1602 (Summer)
	Assignment		:	3
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Student{
	string fName;
	int id;
	int amt;
	string pets[10];
};

Student s[20];

void print(Student s[], int num){
	cout << "No.\t   Name\tStudent ID\tAmt\tPets"<< endl;
	
	for (int i=0;i<num;i++){
		cout << "Student " << i+1 << ": " << s[i].fName << setw(8) << s[i].id << setw(11) << s[i].amt << setw(12) ;
		for (int j=0;j<s[i].amt;j++){
			cout << s[i].pets[j] << ", ";
		}
		cout << endl;
	}
}

int findName (Student s[], int num, string name){
	for (int i=0;i<num;i++){
		if (s[i].fName == name){
			return i;
		}
	}
	return -1;
}

int findPet (Student s[], int num, string name, string pet){
	int i = findName(s, num, name);
	
	if (i != -1){
		for (int j=0;j<s[i].amt;j++){
			if (s[i].pets[j] == pet){
				return -2;
			}
		}
	}
return i;
}

void add(Student s[], int num, string name, string pet){
	int search = findPet(s, num, name, pet);
	
	if (search == -1){
		cout << name << " does not exist." << endl;
	}else if (search == -2){
		cout << pet << " already exists for " << name << endl;
	}else{
		s[search].pets[s[search].amt++] = pet;
	}
}

void deleteData(Student s[], int num, string name, string pet){
	int i = findName(s, num, name);
	if (i == -1){
		cout << name << " does not exist.";
	}else{
		for (int j=0;j<s[i].amt;j++){
			if (s[i].pets[j] == pet){
				s[i].pets[j] = "DELETED";
				string temp = s[i].pets[s[i].amt-1];
				s[i].pets[s[i].amt-1] = s[i].pets[j];
				s[i].pets[j] = temp;
				s[i].amt--;
				break;
			}
		}
	}
}

int count(Student s[], int num, string pet){
	int count = 0;
	for(int i=0;i<num;i++){
		for(int j=0;j<s[i].amt;j++){
			if(s[i].pets[j] == pet)
				count++;
		}
	}
	return count;
}

void highest(Student s[], int num){
	int max = 0, maxLoc;
	for(int i=0;i<num;i++){
		if (s[i].amt>max){
			max = s[i].amt;
			maxLoc=i;
		}
	}
	cout << "Name\t\tStudent ID  Amount of pets\t\tPets"<< endl;
	cout << s[maxLoc].fName <<"\t\t" << s[maxLoc].id <<"\t\t"<< max <<"\t\t";
	for (int j=0;j<max;j++){
			cout << s[maxLoc].pets[j] << ", ";
		}
	cout << endl;
	
}

void sort(Student s[], int num){
	for (int i=0;i<num-1;i++) {
		int minLoc = i; 

		for (int j=i+1;j<=num-1;j++){
			if(s[j].fName < s[minLoc].fName) 	
				minLoc = j; 
		}
		Student temp = s[i];
		s[i] = s[minLoc];
		s[minLoc] = temp; 
	}
	
	for (int x=0;x<num;x++){
		int numPet = s[x].amt;
		for (int i=0;i<numPet-1;i++) {
			int minLoc = i; 

			for (int j=i+1;j<=numPet-1;j++){
				if(s[x].pets[j] < s[x].pets[minLoc]) 	
					minLoc = j; 
			}
			string temp = s[x].pets[i];
			s[x].pets[i] = s[x].pets[minLoc];
			s[x].pets[minLoc] = temp; 
		}
	}
}

void start(){
	ifstream in;
	in.open("student_pets.txt");
	
	if(!in.is_open()) {
		cout << "File cannot be opened. Aborting...";
		exit(1);
	}
	int num = 0;
	string name;
	int id, amt;
	string pets;
	
	in >> name;
	while (name!="ENDDATA"){
		in >> id;
		in >> amt;
		
		s[num].fName = name;
		s[num].id = id;
		s[num].amt = amt;
		
		for (int i=0;i<amt;i++){
			in >> pets;
			s[num].pets[i] = pets;
		}
		num++;
		in >> name;
	}
	//print(s, num); cout<<"\n==========================================================\n";	//Original Table of records
	
	string commands;
	in >> commands;
	
	while(commands != "ENDCOMMANDS"){
		
		if(commands == "ADD"){
			in>>name>>amt;
			for (int i=0;i<amt;i++){
				in>>pets;
				cout << "ADDING " << pets << " FOR " << name << "..." << endl;
				add(s, num, name, pets); }
				cout << endl << endl;
		}if (commands == "DELETE"){
			in>> name >> pets;
			cout << "DELETEING " << pets << " FROM " << name << "..." << endl;
			deleteData(s, num, name, pets);
			cout << endl << endl;
		}if(commands == "PRINT"){
			cout << "PRINTING..." << endl;
			print(s, num);
			cout << endl << endl;
		}if (commands == "COUNT"){
			in >> pets;
			cout << "COUNTING THE AMOUNT OF " << pets << " IN THE CLASSROOM..." << endl;
			int i = count(s, num, pets);
			cout << "There are " << i << " " << pets << " as pets in the classroom" << endl << endl;
		}if (commands == "HIGHEST"){
			cout << "CALCULATING THE HIGHEST NO. OF PETS..." << endl;
			highest(s, num);
			cout << endl << endl;
		}if (commands == "SORT"){
			cout << "SORTING..." << endl;
			sort(s, num);
			cout << endl << endl;
		}
		cout<<"==========================================================\n";
		
		in>>commands;
	}
	in.close();	
}

int main() {
	start();
return 0;
}
