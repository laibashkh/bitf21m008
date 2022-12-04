#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void displayFormatted();
//function to add record of new patient
int addpatient(FILE *addptr);
//function to delete a record
int delpatient(FILE *delptr);
//function to display all records
int searchpatient (FILE *searchptr);
//function to search records
int updatepatient(FILE *updateptr);
//function to update records
void displaypatients(FILE* displayptr);
//patient record structure
struct patient_record
{
	int ID;
	char name[15];
	char CNIC[15];
	char phonenumber[15];
	char disease[15];
	char admit[15];
	char null;
}patient;
int main()
{
	int choice;
	printf("1.Add patient\n2.Delete patient\n3.Update patient\n4.Search patient\n5.Display all patients\nChoose an option :");
	scanf("%d", &choice);
	FILE* ptr = NULL;
	while (choice > 0 && choice<6)
	{		
		switch (choice)
		{
		case 1:
			//function is called to add a new patient
			addpatient(ptr);
			printf("\n\n1.Add patient\n2.Delete patient\n3.Update patient\n4.Search patient\n5.Display all patients\nChoose an option :");
			scanf("%d", &choice);
			break;
		case 2:
			//function is called to delete a patient
			delpatient(ptr);
			printf("\n\n1.Add patient\n2.Delete patient\n3.Update patient\n4.Search patient\n5.Display all patients\nChoose an option :");
			scanf("%d", &choice);
			break;
        case 3:
			//function is called to update a patient
			updatepatient(ptr);
			printf("\n\n1.Add patient\n2.Delete patient\n3.Update patient\n4.Search patient\n5.Display all patients\nChoose an option :");
			scanf("%d", &choice);
			break;    
        case 4:
			//function is called to search a patient
			searchpatient(ptr);
			printf("\n\n1.Add patient\n2.Delete patient\n3.Update patient\n4.Search patient\n5.Display all patients\nChoose an option :");
			scanf("%d", &choice);
			break;   
		case 5:
			//function is called to display record of all patients
			displaypatients(ptr);
			printf("\n\n1.Add patient\n2.Delete patient\n3.Update patient\n4.Search patient\n5.Display all patients\nChoose an option :");
			scanf("%d", &choice);
			break;
		}
	}
	return 0;
}
int addpatient(FILE *addptr)
{
	//id number which we want to add
	int id;
	int count=0;
	printf("\nEnter ID of patient :");
	scanf("%d",&id);
	fflush(stdin);
	addptr=fopen("assignment.txt", "r");
	//loop to check if the id we want to enter is already present in a record or it's a new one
	while((fread(&patient, sizeof(struct patient_record), 1, addptr)))
	{
		//condition to check if id user entered matches any of the id of record	
		if (patient.ID==id)
		{
			count++;
		}
    }
    //if id has matched
    if (count>0)
    {
    	printf("This ID already exists\n");
	}
	//if no such id exists
	else if(count==0)
    {
	
          	fclose(addptr);
          	//patient id becomes equal to id entered by the user
           	patient.ID=id;
			printf("Enter name of patient:");                                               
			scanf("%s", patient.name);
			fflush(stdin);
			printf("Enter CNIC number of patient : ");
			scanf("%s", patient.CNIC);
			fflush(stdin);
			printf("Enter Phone number of patient : ");
			scanf("%s", patient.phonenumber);
			fflush(stdin);
			printf("Enter patient's disease : ");
			scanf("%s", patient.disease);
			printf("Do you want to admit the patient or just take medicine: ");
			scanf("%s", patient.admit);
			//opening a file in append mode
			addptr=fopen("assignment.txt", "a");
			//writing the whole record into the file
			fwrite(&patient,sizeof(struct patient_record),1,addptr);
			fclose(addptr);
			void displayFormatted();
	}
}
int delpatient(FILE *delptr)
{
	//id number which we want to delete
	int id;
	int count=0;
	FILE *copyptr;
	printf("Enter ID of patient you want to delete : ");
	scanf("%d",&id);
	//opening the file in which the records are already present in read mode 
	delptr=fopen("assignment.txt", "r");
	//loop which reads record from file and compare it with id entered by the user
	while((fread(&patient, sizeof(struct patient_record), 1, delptr)))
	{	
		//if id entered by the user matches ID of record then increment in count and contiue
		if (patient.ID==id)
		{
			count++;
			break;
		}
	}
	fclose(delptr);
		//if ID don't matches record then copy that record to another file(copy.txt) which is opened in writing mode 
	delptr=fopen("assignment.txt", "r");
	copyptr=fopen("copy1.txt","w+");
	while((fread(&patient, sizeof(struct patient_record), 1, delptr)))
	{
	 	if(patient.ID!=id)
		{
			fwrite(&patient,sizeof(struct patient_record),1,copyptr);
		}
	}
	fclose(delptr);
	fclose(copyptr);
	//at the end of while loop all records are copied to file copy1.txt from the file assignment.txt except for that user wanted to delete 
	//count=0 means id entered by user is not present in any of the records 
	if(count==0)
	{
		printf("\n\tNO such ID exists\n");
		return 0;
	}
	//now overwrite the content of copy1.txt file to assignment.txt file by opening copy.txt file in read mode and assignment.txt file in writing mode	
	else if (count>0)
	{
		copyptr=fopen("copy1.txt","r");
		delptr=fopen("assignment.txt", "w+");
		while((fread(&patient, sizeof(struct patient_record), 1, copyptr)))
		{
			fwrite(&patient,sizeof(struct patient_record),1,delptr);
		}
	}	
	fclose(copyptr);
	fclose(delptr);
		
	//record deleted 
}