// gcc Project.c -o Project.exe
// Project.exe

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 20
#define MAX_SLOTS 5 // 5 SLOTS = 5 Slots of Patient Reservation Time / MAX 5 Slots 
#define PASSWORD 1234 // This is the passowrd for ADMIN only
// -1 = Not found
// Patient structure
typedef struct {
    char name[25]; // [25] = %24s and at the end 0\ // %24s= 24 character or letter
    int age;
    char gender[10];
    int id;
} Patient;

// Global arrays
Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Slots array (0 = free, else = patient ID)--> Array to track appointment slots
int slots[MAX_SLOTS] = {0, 0, 0, 0, 0};
char *slotTimes[MAX_SLOTS] = {
    "2:00pm --> 2:30pm",
    "2:30pm --> 3:00pm",
    "3:00pm --> 3:30pm",
    "4:00pm --> 4:30pm",
    "4:30pm --> 5:00pm"
};

// ---- Safe integer input (numbers only) ----
int ReadIntOnly(const char *prompt)
 {
    int value;
    while(1) // loop untill type correct int
	{
	if (prompt)
		printf("%s", prompt);
	if (scanf("%d",&value) ==1)
	{ 
	while(getchar() != '\n'); // Remove any leftover input or Additional letters untill sew /n or (Enter)
	return value;
	}
	else 
	{
		printf("Error: numbers only. try agian. \n");
		while(getchar() != '\n');
	}
  }
 }

// Function to check for Patient untill find or (Exists)
int findPatientIndex(int id) {
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            return i;
        }
    }
    return -1; // Not found
}

//*** Admin functions ***
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Database is full!\n");
        return;
    }

    Patient newPatient; // newpatient has name and age and IDS
    newPatient.id = ReadIntOnly("Enter patient ID: "); // Must write Num (int) only

    if (findPatientIndex(newPatient.id) != -1) {  
        printf("Error: ID already exists!\n");// if the ADMIN Write any char(letter)
        return;
    }

    printf("Enter patient name: ");
    scanf("%24s", newPatient.name); // scan patient name and put it's name in new patient
   while (getchar() != '\n');

    newPatient.age = ReadIntOnly("Enter patient age: ");

    int genderChoice;
    do {
        genderChoice = ReadIntOnly("Choose Gender (1 = Male, 2 = Female): ");
        if (genderChoice == 1) {
            strcpy(newPatient.gender, "Male");
        } else if (genderChoice == 2) {
            strcpy(newPatient.gender, "Female");
        } else {
            printf("Invalid choice, please choose (1) for Male or (2) for Female.\n");
        }
    } while (genderChoice != 1 && genderChoice != 2);

    patients[patientCount++] = newPatient; // Add new patient to the array, then increase count
    printf("Patient added successfully!\n");
}

void editPatient() {
    int id = ReadIntOnly("Enter patient ID to edit: ");

    int index = findPatientIndex(id);
    if (index == -1) // if ID not found in Hestory
	{
        printf("Error: ID not found!\n");
        return;
    }

    printf("Enter new name: ");
    scanf("%24s", patients[index].name);
	while(getchar() != '\n'); // Remove any leftover input or Additional letters untill sew /n or (Enter)

    patients[index].age = ReadIntOnly("Enter new age: ");

    int genderChoice;
    do // check the loop first if it did it's condition 
	{
        genderChoice = ReadIntOnly("Choose Gender (1 = Male, 2 = Female): ");
        if (genderChoice == 1) {
            strcpy(patients[index].gender, "Male");
        } else if (genderChoice == 2) {
            strcpy(patients[index].gender, "Female");
        } else {
            printf("Invalid choice, please choose (1) for Male or (2) for Female.\n");
        }
    } while (genderChoice != 1 && genderChoice != 2);// if the condition checked the again from first of do loop

    printf("Patient updated successfully!\n");
}

void reserveSlot() {
    int id = ReadIntOnly("Enter patient ID: "); // check for it's INT only

    if (findPatientIndex(id) == -1) // if in not INT
	{
        printf("Error: ID not found!\n");
        return;
    }

    // check if this ID already has a reservation
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i] == id) {
            printf("This ID already has a reservation at: %s\n", slotTimes[i]);
            return; // stop, no new reservation--> comes out of the function
        }
    }

    printf("Available slots:\n"); // it became see the free slots
    int hasFree = 0;
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i] == 0) {
            printf("%d. %s\n", i + 1, slotTimes[i]);
            hasFree = 1;
        }
    }
	
    if (!hasFree) // checking
	{
        printf("No available slots!\n");
        return;
    }

    int slotChoice = ReadIntOnly("Choose a slot number: ");

    if (slotChoice < 1 || slotChoice > MAX_SLOTS || slots[slotChoice - 1] != 0) // checking
	{
        printf("Error: Invalid or already reserved slot!\n");
        return;
    }

    slots[slotChoice - 1] = id;
    printf("Slot reserved successfully!\n");
}


void cancelReservation() {
    int id = ReadIntOnly("Enter patient ID to cancel reservation: ");

    int found = 0;
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i] == id) {
            slots[i] = 0;
            found = 1;
            printf("Reservation cancelled successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Error: No reservation found for this ID!\n");
    }
}

// ** User functions  **
void viewPatientRecord() {
    int id = ReadIntOnly("Enter patient ID: ");

    int index = findPatientIndex(id);
    if (index == -1) {
        printf("Error: ID not found!\n");
        return;
    }

    printf("\nPatient Info:\n");
    printf("Name: %s\n", patients[index].name);
    printf("Age: %d\n", patients[index].age);
    printf("Gender: %s\n", patients[index].gender);
    printf("ID: %d\n", patients[index].id);

    // check if the patient has a reservation
    int hasReservation = 0;
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i] == id) {
            printf("Reservation: %s\n", slotTimes[i]);
            hasReservation = 1;
            break;
        }
    }
    if (!hasReservation) {
        printf("This patient has no reservation.\n");
    }
}

void viewReservations() {
    printf("Today's Reservations:\n");
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i] == 0) {
            printf("%s --> Free\n", slotTimes[i]);
        } else {
            printf("%s --> Reserved by ID %d\n", slotTimes[i], slots[i]);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ******  Main function interface  ******
int main() 
{
    while (1) // unlimited Loop ---------->until Admin or user Close it
	{
        int mode;
        printf("\n*** Main Menu ***\n");// Main Menu Screen
        printf("1. Admin Mode\n");
        printf("2. User Mode\n");
        mode = ReadIntOnly("Choose mode: "); // The Admin or user Chose  1 or 2 

        if (mode == 1)  //if choose num 1 >> the go to ADMIN interface staring in PASSWORD
		{
            int attempts = 0; // itialize the passowrd
            while (attempts < 3) // while it try 3 times it will close the Program
			{
                int pass = ReadIntOnly("Enter password: "); // PASSWORD = 1234 
                if (pass == PASSWORD)// if it write correct
				{
                    printf("Login successful!\n");

                    int choice; // The Admin Choise go to the ADMIN interface
                    do {
                        printf("\n--- Admin Menu ---\n");
                        printf("1. Add new patient\n");
                        printf("2. Edit patient record\n");
                        printf("3. Reserve a slot\n");
                        printf("4. Cancel reservation\n");
                        printf("5. Return to Main Menu\n");
                        choice = ReadIntOnly("Enter choice: ");

                        switch (choice)
						{
                            case 1: addPatient(); break;
                            case 2: editPatient(); break;
                            case 3: reserveSlot(); break;
                            case 4: cancelReservation(); break;
                            case 5: printf("Returning to Main Menu...\n"); break;
                            default: printf("Invalid choice!\n");// if choose wrong answer not from 1 to 5
                        }
                    } while (choice != 5);

                    break; // back to main menu
                } else {
                    attempts++; // Decrease the number of try
                    printf("Wrong password! Attempts left: %d\n", 3 - attempts);
                }
            }
            if (attempts == 3) // untill 3 tries 
			{
                printf("Too many wrong attempts. System closing...\n");
                return 0; // and it will close
            }
        }

        else if (mode == 2) //if choose num 2 >> the go to User interface
			{
            int choice;// The User Choise go to the ADMIN interface
            do// it did the first try of code untill and again while >>while loop the condition correct
			{
                printf("\n--- User Menu ---\n");
                printf("1. View patient record\n");
                printf("2. View today's reservations\n");
                printf("3. Return to Main Menu\n");
                choice = ReadIntOnly("Enter choice: ");

                switch (choice)
				{
                    case 1: viewPatientRecord(); break;
                    case 2: viewReservations(); break;
                    case 3: printf("Returning to Main Menu...\n"); break;
                    default: printf("Invalid choice!\n");
                }
            } while (choice != 3); // if If he did something wrong that equal 3 it will get him out of the loop
        }

        else // if any thing did from above it will>>>
		{
            printf("Invalid mode selected!\n");
        }
    }// and the infinity loop again
    return 0;
}
