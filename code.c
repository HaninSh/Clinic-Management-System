#include <stdio.h>
#include <stdlib.h>
#include "Std_types.h"

//patient list
typedef struct patientNode{
	uint32_t ID;
	char name[50];
	uint16_t age;
	char gender ;
	struct patientNode * nextPatientPtr;
	
}patient;

//reservations list
typedef struct slotsNode{
	uint32_t ID ;
	float slot;
	struct slotsNode* nextSlotPtr;
}reservation;


//protoTypes
void WelcomeMsgs (void);
void mainMenu(void);
void separateLine (void);
void adminMode (void);
void userMode (void);
void copy (char * arr, char * newArr);
void defaultSlots (void);
void NewSlot(float slotValue, reservation** temp);


//declaration
uint16_t mode,U_mode,A_mode;


//initialization
patient* headPTR = NULL;
reservation *slotsHeadPTR = NULL;


int main (void){

defaultSlots();
WelcomeMsgs();
mainMenu();




return 0;
}

void WelcomeMsgs (void){
printf("\n\n\t\t\t\t\t##############################################################################################\n\n\n");
printf("\t\t\t\t\t\t\t\t\tWELCOME TO CLINIC MANAGEMENT SYSTEM\n\n\n");
printf("\t\t\t\t\t##############################################################################################\n");
	
}

void mainMenu(void){
	printf("\n\n###############################################################################\n");
    printf("################################  MAIN  MENU  #################################");
	printf("\n###############################################################################\n\n");
	printf("-> For Admin mode press '1'\n");
    printf("-> For User mode press '2'\n");
    printf("-> To exist press '3'\n\n");
    separateLine ();
	
	do {
    printf("The chosen mode is: ");
    scanf("%hu",&mode);	
	
	//ADMIN MODE
    if (mode == 1){
	    adminMode();
		break;
		
    } 
    //USER MODE
	else if (mode == 2){
	    userMode();
		break;
		
    }
	//EXIT
	else if (mode == 3) break;
    //unvalid option
	else printf("\nPlease, Enter a valid option: \n");
	

} while (1);
}

void adminMode (void){
	int pass,count = 0;
	
	printf("To enter admin mode please enter the password \n");
	
	do {
		
		printf("Password: ");
		scanf("%d",&pass);
		if (pass == 1234){
			printf("CORRECT PASSWORD!");
			printf("\n\n###############################################################################\n");
            printf("###########################  WELCOME TO ADMIN MODE  ###########################");
	        printf("\n###############################################################################\n\n");
			
			do {
			    printf("-> To add new patient press '1'\n");
	            printf("-> To edit patient record press '2'\n");
			    printf("-> To reserve with a doctor press '3'\n");
			    printf("-> To delete a reservation press '4'\n");
	            printf("-> To return to main menu press '5'\n\n");
				separateLine();
				
	            printf("Your choice: ");
                scanf("%hu",&A_mode);	
                //add new patient	
	            if (A_mode == 1){
					
				    uint16_t id;
	                char Name[50];
	                uint16_t Age;
	                char Gender ;
					
					printf("Please enter the following data: \n");
					printf("Patient's ID: ");
					scanf("%hu",&id);
					printf("Patient's name: ");
					scanf("%s",Name);
					printf("Patient's age: ");
					scanf("%hu",&Age);
					printf("For female press 'F' for male press 'M' \n");
					printf("Patient gender: ");
					scanf(" %c",&Gender);
					
                    patient* createdPatientNode =(patient*)calloc(1,sizeof(patient));
					if (createdPatientNode != NULL){
						createdPatientNode -> ID = id;
						copy(Name , createdPatientNode -> name);
						createdPatientNode -> age = Age;
						createdPatientNode -> gender = Gender;	
						
					}
					patient* temp = headPTR;
					if (headPTR == NULL){
		                headPTR = createdPatientNode;
		                printf("New patient added successfully!\n");
	                }
					else 
					{
						uint16_t flag = 1;
	                    while (temp -> nextPatientPtr != NULL){
		   
							 if(temp -> ID == id){
								 printf("\nID already exist\nCan't add new patient"); 
								 flag =0;
								 break;						 
							 }
							 temp = temp -> nextPatientPtr;
	                    }
						if (flag == 1){
						     temp -> nextPatientPtr = createdPatientNode;
                             printf("New patient added successfully!\n");	
						}
                        					
	                }
					
					separateLine();
					
		
	            }
	            //edit patient record
	            else if (A_mode == 2){
					 uint16_t tempID;
					 patient* temp = headPTR;
					
					 printf("enter patient ID: ");
			         scanf("%hu",&tempID);
				     while (temp -> ID != tempID)
				         {
                             if (temp -> nextPatientPtr == NULL){
						     printf("ID NOT FOUND \n\n"); break;
						     separateLine();		  
					         }
		                     temp = temp -> nextPatientPtr;
					   
			             }
				    if (temp -> ID == tempID){
						printf("\nEnter the new data: \n\n");
						
						uint16_t id;
	                    char Name[50];
	                    uint16_t Age;
	                    char Gender ;
					
					    printf("Please enter the following data: \n");
					    printf("Patient's ID: ");
					    scanf("%hu",&id);
					    printf("Patient's name: ");
					    scanf("%s",Name);
					    printf("Patient's age: ");
					    scanf("%hu",&Age);
					    printf("For female press 'F' for male press 'M' \n");
					    printf("Patient gender: ");
					    scanf(" %c",&Gender);
				
						temp -> ID = id;
						copy(Name , temp -> name);
						temp -> age = Age;
						temp -> gender = Gender;	
						
						printf("Data updates successfully\n\n");
						separateLine();
					
					
		
		
	            }
				}
				//reserve with a doctor
				else if (A_mode == 3){
					
					float desiredSlot;uint16_t id; uint16_t flag =1;uint16_t askPatientID =1;
					
			        printf ("Todays available reservation slots are: \n");
					
					reservation* temp = slotsHeadPTR;
					
					while (temp -> nextSlotPtr != NULL){
						
						if (temp -> ID == 0){
							printf("%.2f pm \n", temp -> slot);
						}
						temp = temp -> nextSlotPtr; 
					}
					if (temp -> ID == 0){printf("%.2f pm \n\n", temp -> slot);}
					
					printf("enter the desired slot: ");
					scanf("%f",&desiredSlot);
					temp = slotsHeadPTR;
					while(temp -> slot != desiredSlot){
						 if (temp -> nextSlotPtr == NULL){
						     printf("The slot you choose is unavailable \n\n");
						     separateLine(); askPatientID =0; break;	  
					         }
		                     temp = temp -> nextSlotPtr;
					}
					if (askPatientID == 1){
						 printf("Enter patient ID: ");
					     scanf("%hu",&id);
					     patient* patientTemp = headPTR;
						 reservation* SlotTemp = slotsHeadPTR;
					     while (patientTemp -> ID != id)
				         {
                             if (patientTemp -> nextPatientPtr == NULL){
						     printf("ID NOT FOUND \nFailed to reserve a slot\n\n"); flag = 0;  
						     separateLine(); break;		  
					         }
		                     patientTemp = patientTemp -> nextPatientPtr;
					   
			             }
						 while(SlotTemp -> nextSlotPtr != NULL ){
							 if(SlotTemp -> ID == id){
								 printf("This ID is already reserved\n"); flag =0;
								 separateLine(); break;
							 }
							 SlotTemp = SlotTemp -> nextSlotPtr;
						 }
				         if (flag == 1){
						    temp -> ID = id;
						    printf("Slot reserved successfully!\n\n");
						    separateLine();
					     } 
					}
					
				
				}
				//delete reservation
				else if (A_mode == 4){
					uint16_t tempID; reservation *temp = slotsHeadPTR; uint16_t flag=1;
					printf("Patient ID: ");
					scanf("%hu",&tempID);
					while (temp -> ID != tempID)
				         {
                             if (temp -> nextSlotPtr == NULL){
						     printf("ID NOT FOUND \n\n");   
						     separateLine(); flag =0; break;		  
					         }
		                     temp = temp -> nextSlotPtr;
			             }
						 if(flag ==1){
							 temp -> ID = 0;
						     printf("Reservation deleted successfully \n\n");
						     separateLine();
						 }
						 
					
				}
	            //return to main menu
	            else if (A_mode == 5){
		        mainMenu();
		        break;
	            } 
	            else printf("Please, enter a valid option\n");
	        }// sec do while
			while (1);
			break;
			
		
		} //if 
		else {
			printf("WRONG PASSWORD\n");
			count++;
		}
        
	} // main do while
	while (count != 3);
	if (count == 3) printf("Try again later");
	
}//admin mode

void userMode (void){
	printf("\n\n###############################################################################\n");
    printf("###########################  WELCOME TO USER MODE  ############################");
	printf("\n###############################################################################\n\n");
	
	
	
	do {
		   printf("-> To view patient record press '1'\n");
	       printf("-> To view today's reservations press '2'\n");
	       printf("-> To return to main menu press '3'\n\n");
	
	       separateLine();
	
	       printf("Your choice: ");
           scanf("%hu",&U_mode);	
    
	      //view patient record	
	      if (U_mode == 1){
		     
			        
			 uint16_t tempID ;
			 patient* temp = headPTR;
			 
			 if (temp == NULL){
				 printf("No patients added yet\n\n");
				 separateLine(); 
			 }
			 else
			 {
				 
                 printf("enter patient ID: ");
			     scanf("%hu",&tempID);
				 while (temp -> ID != tempID)
				 {
					   if (temp -> nextPatientPtr == NULL){
						   printf("ID NOT FOUND \n\n"); break;
						   separateLine();		  
					   }
		               temp = temp -> nextPatientPtr;
					   
			     }
				 if (temp -> ID == tempID){
 
					printf("\nPatient record: \n\n");
			        printf("ID: %hu\n",temp -> ID);				
	                printf("Name: %s\n",temp -> name);
			        printf("Age: %hu\n",temp -> age);		
		            printf("Gender: %c\n",temp -> gender);	 
                    separateLine();				
			     }
				 
				  
	         }
			 
			     
			 
	         
			 
			 
	
			 
	      }
	
	      //view today's reservation
	      else if (U_mode == 2){
			  reservation*temp = slotsHeadPTR;
			  
			  printf("\nTodays reservations: \n");
			  while (temp -> nextSlotPtr != NULL){
						
						if (temp -> ID != 0){
							printf("Patient with ID: %hu has appointment at %.2f pm \n",temp -> ID ,temp -> slot);
						}
						temp = temp -> nextSlotPtr; 
					}
					if (temp -> ID != 0){printf("Patient with ID: %hu has appointment at %.2f pm \n",temp -> ID ,temp -> slot);} 
	                printf("\n");
					separateLine();
		  }
	      //return to main menu
	      else if (U_mode == 3){
		  mainMenu();
		  break;
	} 
	else printf("Please, enter a valid option\n");
	}while (1);
}
 
void separateLine (void){
	printf("############################################################################################\n\n");
}

void copy (char * arr, char * newArr){
	while (*arr != '\0'){
		*newArr = *arr;
		arr++; newArr++;
	}
}

void defaultSlots (void){
	
	NewSlot(2.00, &slotsHeadPTR);  // slot 2 from 2.30 pm to 3.00 pm
	NewSlot(2.30, &slotsHeadPTR);  // slot 2 from 2.30 pm to 3.00 pm
	NewSlot(3.00, &slotsHeadPTR);  // slot 3 from 3.00 pm to 3.30 pm
	NewSlot(4.00, &slotsHeadPTR);  // slot 4 from 4.00 pm to 4.30 pm 
	NewSlot(4.30, &slotsHeadPTR);  // slot 4 from 4.30 pm to 5.00 pm 
}

void NewSlot(float slotValue, reservation**slotsHeadPTR){
	reservation * createdSlot = NULL;
	createdSlot = (reservation*)calloc(1,sizeof(reservation));
	if (createdSlot != NULL){
		createdSlot -> slot = slotValue;
	}
	
	reservation* temp = *slotsHeadPTR;
	if (*slotsHeadPTR == NULL){
		*slotsHeadPTR = createdSlot;
	} 
	else {
		while (temp -> nextSlotPtr != NULL){
		        temp = temp -> nextSlotPtr;
	            }
            temp -> nextSlotPtr = createdSlot;	
	}

	
    }
	


