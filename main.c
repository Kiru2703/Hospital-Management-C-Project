#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structs
typedef struct{
    char di_id[10];
    char di_user[50];
    char di_pass[20];
} Director;
typedef struct{
    char a_id[10];
    char a_name[50];
    char a_pass[20];
} Admin;
typedef struct{
    char do_id[10];
    char do_name[50];
    char do_specialty[50];
    char do_email[100];
    char do_pass[20];
} Doctor;
typedef struct{
    char n_id[10];
    char n_name[50];
    char n_ward[20];
    char n_email[100];
    char n_pass[20];
} Nurse;
typedef struct{
    char p_id[10];
    char p_name[50]; 
    int p_age;
    char p_gender[10];
    char p_email[50];
    char p_password[20];
} Patient;
typedef struct{
    char appID[10];
    char patientID[10];
    char doctorID[10];
    char date[20];
    char time[10];
    char period[5];
} Appointment;
typedef struct{
    char itemID[10];
    char itemName[50];
    char category[50];
    int quantity;
} Inventory;
typedef struct {
    char recordID[10];
    char patientID[10];
    char doctorID[10];
    char diagnosis[100];
    char prescription[100];
    char notes[200];
    char date[15];
} MedicalRecord;

// Function Prototypes
// Director
void directorLogin();
void directorMenu();
void addAdmin();
void viewAdmin();
void viewStaffReport();
void viewAppointmentTrend();
// Admin
void adminLogin();
void registerPatient();
void registerDoctor();
void registerNurse();
void viewPatients();
void searchPatient();
void viewInventory();
void searchInventory();
void adminMenu();
// Doctor
void doctorLogin();
void doctorMenu(char *loggedID);
void viewMyAppointments(char *loggedID);
void addMedicalRecord(char *loggedID);
void viewPatientHistory();
// Nurse
void nurseLogin();
void nurseMenu();
void viewDoctorSchedule();
void addInventory();
void viewInventory();
void searchInventory();
void generateReport();
// Patient
void patientLogin();
void patientMenu(char patientID[]);
void bookAppointment(char patientID[]);
void viewAppointments(char patientID[]);
void rescheduleAppointment(char patientID[]);
void cancelAppointment(char patientID[]);
void viewBilling(char patientID[]);
int Payment(char patientid[6], char appointmentid[10]);
int card(int amount, char patientid[6], char appointmentid[10]);
int onlinebanking(int amount, char patientid[6], char appointmentid[10]);
void generateAppointmentID(char newID[]);
int isFutureDate(char date[]);

// Main Code
int main(){
    int choice;
    do{
        printf("\n====================================\n");
        printf("   HOSPITAL MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Director Login\n");
        printf("2. Administrator Login\n");
        printf("3. Patient Login\n");
        printf("4. Doctor Login\n");
        printf("5. Nurse Login\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                directorLogin();
                break;
            case 2:
                adminLogin();
                break;
            case 3:
                patientLogin();
                break;
            case 4:
                doctorLogin();
                break;
            case 5:
                nurseLogin();
                break;
            case 6:
                printf("\nExiting system...\n");
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } while(choice != 6);
    return 0;
}

// Functions
// Director
void directorLogin(){
    FILE *fp;
    Director d;
    char id[10], pass[50];
    int found = 0;
    fp = fopen("director.txt", "r");
    if(fp == NULL){
        printf("Error opening director file\n");
        return;
    }
    printf("\n=== DIRECTOR LOGIN ===\n");
    printf("Enter Director ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    scanf("%s", pass);
    while(fscanf(fp, "%s %s %s", d.di_id, d.di_user, d.di_pass) != EOF){
        if(strcmp(id, d.di_id) == 0 && strcmp(pass, d.di_pass) == 0){
            found = 1;
            break;
        }
    }
    fclose(fp);
    if(found){
        printf("\nLogin successful!\n");
        directorMenu();
    }
    else{
        printf("\nInvalid login.\n");
    }
}
// Director Menu
void directorMenu(){
    int choice;
    do{
        printf("\n===== DIRECTOR MENU =====\n");
        printf("1. Add Admin\n");
        printf("2. View Admins\n");
        printf("3. Staff Report\n");
        printf("4. Appointment Summary\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                addAdmin();
                break;
            case 2: 
                viewAdmin();
                break;
            case 3:
                viewStaffReport();
                break;
            case 4: 
                viewAppointmentTrend();
                break;
            case 5:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid option\n");
        }

    } while(choice != 5);
}
// Add Admin function
void addAdmin(){
    FILE *fp = fopen("admin.txt", "a");
    Admin a;
    if(fp == NULL){
        printf("File error\n");
        return;
    }
    printf("\nEnter Admin ID: ");
    scanf("%s", a.a_id);
    printf("Enter Username: ");
    scanf("%s", a.a_name);
    printf("Enter Password: ");
    scanf("%s", a.a_pass);
    fprintf(fp, "%s %s %s\n", a.a_id, a.a_name, a.a_pass);
    fclose(fp);
    printf("Admin added successfully\n");
}
// View Admin
void viewAdmin(){
    FILE *fp = fopen("admin.txt", "r");
    Admin a;
    if(fp == NULL){
        printf("No admin file\n");
        return;
    }
    printf("\n--- ADMIN LIST ---\n");
    while(fscanf(fp, "%s %s %s", a.a_id, a.a_name, a.a_pass) != EOF){
        printf("ID: %s | Name: %s\n", a.a_id, a.a_name);
    }
    fclose(fp);
}
// View Staff Report
void viewStaffReport(){
    FILE *fp1 = fopen("admin.txt", "r");
    FILE *fp2 = fopen("doctors.txt", "r");
    FILE *fp3 = fopen("nurses.txt", "r");
    Admin a;
    Doctor doc;
    Nurse n;
    printf("\nRole      ID         Name\n");
    printf("--------------------------\n");
    // Admin
    if(fp1 != NULL){
        while(fscanf(fp1, "%s %s %*s", a.a_id, a.a_name) != EOF){
            printf("Admin  %s  %s\n", a.a_id, a.a_name);
        }
        fclose(fp1);
    }
    // Doctor
    if(fp2 != NULL){
        while(fscanf(fp2, "%s %s %*s %*s %*s", doc.do_id, doc.do_name) != EOF){
            printf("Doctor %s  %s\n", doc.do_id, doc.do_name);
        }
        fclose(fp2);
    }
    // Nurse
    if(fp3 != NULL){
        while(fscanf(fp3, "%s %s %*s %*s %*s", n.n_id, n.n_name) != EOF){
            printf("Nurse  %s  %s\n", n.n_id, n.n_name);
        }
        fclose(fp3);
    }
}
// View Appointment Trend
void viewAppointmentTrend(){
    FILE *fp = fopen("appointments.txt", "r");
    Appointment ap;
    int total = 0;
    if(fp == NULL){
        printf("No appointment file\n");
        return;
    }
    while(fscanf(fp, "%s %s %s %s %s %s", ap.appID, ap.patientID, 
                ap.doctorID, ap.date, ap.time, ap.period) != EOF){
        total++;
    }
    fclose(fp);
    printf("\n--- APPOINTMENT SUMMARY ---\n");
    printf("Total Appointments: %d\n", total);
}

// Admin
// Login Function
int adminAuthenticate(char loggedAdminID[]){
    FILE *fp = fopen("admin.txt", "r");
    Admin a;
    char inputID[10];
    char inputPassword[20];
    printf("\n=== ADMIN LOGIN ===\n");
    printf("Enter Admin ID: ");
    scanf("%s", inputID);
    printf("Enter Password: ");
    scanf("%s", inputPassword);
    if(fp == NULL){
        printf("Error: admin.txt not found.\n");
        return 0;
    }
    while(fscanf(fp, "%s %s %s", a.a_id, a.a_name, a.a_pass) != EOF){
        if(strcmp(inputID, a.a_id) == 0 && strcmp(inputPassword, a.a_pass) == 0){
            strcpy(loggedAdminID, a.a_id);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
// Admin Login function
void adminLogin(){
    char loggedAdminID[10];
    if(adminAuthenticate(loggedAdminID)){
        printf("\nLogin successful. Welcome %s\n", loggedAdminID);
        adminMenu();
    }
    else{
        printf("\nInvalid Admin ID or Password.\n");
    }
}
// Admin Menu
void adminMenu(){
    int choice;
    do{
        printf("\n=================================\n");
        printf("        ADMINISTRATOR MENU      \n");
        printf("=================================\n");
        printf("1. Register Patient\n");
        printf("2. Register Doctor\n");
        printf("3. Register Nurse\n");
        printf("4. View All Patients\n");
        printf("5. Search Patient\n");
        printf("6. View Inventory\n");
        printf("7. Search Inventory\n");
        printf("8. Logout\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                registerPatient();
                break;
            case 2: 
                registerDoctor();
                break;
            case 3: 
                registerNurse();
                break;
            case 4:
                viewPatients();
                break;
            case 5:
                searchPatient();
                break;
            case 6:
                viewInventory();
                break;
            case 7:
                searchInventory();
                break;
            case 8:
                printf("\nLogging out...\n");
                break;
            default:
                printf("\nInvalid choice.\n");
        }

    } while(choice != 8);
}
// Helper Function
void toLowerCase(char str[]){
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
}
// Generate Patient ID function
void generatePatientID(char newID[]){
    FILE *fp = fopen("patients.txt", "r");
    Patient p;
    int lastNumber = 0;
    if(fp != NULL){
        while(fscanf(fp,"%s %s %d %s %s %s", p.p_id, p.p_name, &p.p_age, p.p_gender, p.p_email, p.p_password) != EOF){
            int num;
            sscanf(p.p_id,"P%d",&num);
            if(num > lastNumber)
                lastNumber = num;
        }
        fclose(fp);
    }
    sprintf(newID,"P%04d",lastNumber + 1);
}
// Register Patient Function
void registerPatient(){
    FILE *fp = fopen("patients.txt", "a");
    Patient p;
    generatePatientID(p.p_id);
    printf("\nGenerated ID: %s\n",p.p_id);
    printf("Enter Name: ");
    scanf("%s", p.p_name);
    printf("Enter Age: ");
    scanf("%d", &p.p_age);
    printf("Enter Gender: ");
    scanf("%s", p.p_gender);
    char temp[50];
    strcpy(temp,p.p_name);
    toLowerCase(temp);
    sprintf(p.p_email,"%s.hms@hospital.com",temp);
    printf("Generated Email: %s\n",p.p_email);
    printf("Enter Password: ");
    scanf("%s", p.p_password);
    fprintf(fp,"%s %s %d %s %s %s\n", p.p_id,p.p_name,
            p.p_age,p.p_gender,p.p_email,p.p_password);
    fclose(fp);
    printf("Patient registered successfully\n");
}
// Generate Doctor ID Function
void generateDoctorID(char newID[]){
    FILE *fp = fopen("doctors.txt","r");
    Doctor doc;
    int lastNumber = 0, num;
    if(fp == NULL){
        sprintf(newID,"D0001");
        return;
    }
    while(fscanf(fp,"%s %s %s %s %s",doc.do_id, doc.do_name, doc.do_specialty,
                doc.do_email, doc.do_pass) != EOF){
        sscanf(doc.do_id,"D%d",&num);
        if(num > lastNumber){
            lastNumber = num;
        }
    }
    fclose(fp);
    sprintf(newID,"D%04d",lastNumber + 1);
}
// Register Doctor Function
void registerDoctor(){
    FILE *fp = fopen("doctors.txt","a");
    Doctor doc;
    generateDoctorID(doc.do_id);
    printf("\nGenerated Doctor ID: %s\n",doc.do_id);
    printf("Enter Name: ");
    scanf("%s",doc.do_name);
    printf("Enter Specialism: ");
    scanf("%s",doc.do_specialty);
    char temp[50];
    strcpy(temp,doc.do_name);
    toLowerCase(temp);
    sprintf(doc.do_email,"%s.hms@hospital.com",temp);
    printf("Email: %s\n",doc.do_email);
    printf("Enter Password: ");
    scanf("%s",doc.do_pass);
    fprintf(fp,"%s %s %s %s %s\n", doc.do_id, doc.do_name, 
            doc.do_specialty, doc.do_email, doc.do_pass);
    fclose(fp);
    printf("Doctor registered\n");
}
// Generate Nurse ID function
void generateNurseID(char newID[]){
    FILE *fp = fopen("nurses.txt","r");
    Nurse n;
    int lastNumber = 0, num;
    if(fp == NULL){
        sprintf(newID,"N0001");
        return;
    }
    while(fscanf(fp,"%s %s %s %s %s", n.n_id, n.n_name, n.n_ward,
                n.n_email, n.n_pass) != EOF){
        sscanf(n.n_id,"N%d",&num);
        if(num > lastNumber)
            lastNumber = num;
    }
    fclose(fp);
    sprintf(newID,"N%04d",lastNumber + 1);
}
// Register Nurse Function
void registerNurse(){
    FILE *fp = fopen("nurses.txt","a");
    Nurse n;
    generateNurseID(n.n_id);
    printf("\nGenerated Nurse ID: %s\n",n.n_id);
    printf("Enter Name: ");
    scanf("%s",n.n_name);
    printf("Enter Ward: ");
    scanf("%s",n.n_ward);
    char temp[50];
    strcpy(temp,n.n_name);
    toLowerCase(temp);
    sprintf(n.n_email,"%s.hms@hospital.com",temp);
    printf("Email: %s\n",n.n_email);
    printf("Enter Password: ");
    scanf("%s",n.n_pass);
    fprintf(fp,"%s %s %s %s %s\n", n.n_id, n.n_name, n.n_ward, n.n_email, n.n_pass);
    fclose(fp);
    printf("Nurse registered\n");
}
// View Patient function
void viewPatients(){
    FILE *fp;
    Patient p;
    fp = fopen("patients.txt","r");
    while(fscanf(fp,"%s %s %d %s %s %s", p.p_id,p.p_name,&p.p_age,p.p_gender,p.p_email,p.p_password)!=EOF){
        printf("%s %s %d %s %s\n", p.p_id,p.p_name,p.p_age,p.p_gender,p.p_email);
    }
    fclose(fp);
}
// Search Patient function
void searchPatient(){
    FILE *fp = fopen("patients.txt","r");
    Patient p;
    char id[10];
    printf("Enter ID: ");
    scanf("%s",id);
    while(fscanf(fp,"%s %s %d %s %s %s", p.p_id, p.p_name, &p.p_age, p.p_gender, p.p_email, p.p_password)!=EOF){
        if(strcmp(id,p.p_id)==0){
            printf("Found: %s %s\n",p.p_id,p.p_name);
            break;
        }
    }
    fclose(fp);
}
// View Inventory function
void viewInventory(){
    FILE *fp = fopen("inventory.txt","r");
    Inventory i;
    while(fscanf(fp,"%s %s %s %d", i.itemID, i.itemName, i.category, &i.quantity)!=EOF){
        printf("%s %s %d\n", i.itemID, i.itemName, i.quantity);
    }
    fclose(fp);
}
// Search Inventory function
void searchInventory(){
    FILE *fp = fopen("inventory.txt","r");
    Inventory i;
    char key[50];
    int found = 0;
    printf("\n=== SEARCH INVENTORY ===\n");
    printf("Enter Item ID or Name: ");
    scanf("%s", key);
    if(fp == NULL)
    {
        printf("Inventory file not found.\n");
        return;
    }
    printf("\nResults:\n");
    while(fscanf(fp,"%s %s %s %d", i.itemID, i.itemName, i.category, &i.quantity) != EOF){
        if(strcmp(i.itemID, key) == 0 || strcmp(i.itemName, key) == 0){
            printf("\nItem ID   : %s\n", i.itemID);
            printf("Name      : %s\n", i.itemName);
            printf("Category  : %s\n", i.category);
            printf("Quantity  : %d\n", i.quantity);
            found = 1;
        }
    }
    if(found == 0){
        printf("\nItem not found.\n");
    }
    fclose(fp);
}

// Doctor
// Login function
void doctorLogin(){
    FILE *fp = fopen("doctors.txt", "r");
    if (fp == NULL){
        printf("Error: doctors.txt not found!\n");
        return;
    }
    char inputID[10];
    char inputPass[20];
    char loggedID[10];
    Doctor doc;
    int found = 0;
    printf("\n=== DOCTOR LOGIN ===\n");
    printf("Enter Doctor ID: ");
    scanf("%s", inputID);
    printf("Enter Password: ");
    scanf("%s", inputPass);
    while (fscanf(fp, "%s %s %s %s %s", doc.do_id, doc.do_name, doc.do_specialty, doc.do_email, doc.do_pass) != EOF){
        if (strcmp(inputID, doc.do_id) == 0 && strcmp(inputPass, doc.do_pass) == 0){
            strcpy(loggedID, doc.do_id);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (found){
        printf("\nLogin successful! Welcome Doctor %s\n", loggedID);
        doctorMenu(loggedID);
    }
    else{
        printf("\nInvalid login credentials.\n");
    }
}
// Doctor Menu
void doctorMenu(char *loggedID){
    int choice;
    do{
        printf("\n=================================\n");
        printf("           DOCTOR MENU           \n");
        printf("=================================\n");
        printf("1. View My Appointments\n");
        printf("2. Add Medical Record\n");
        printf("3. View Patient History\n");
        printf("4. Logout\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                viewMyAppointments(loggedID);
                break;
            case 2:
                addMedicalRecord(loggedID);
                break;
            case 3:
                viewPatientHistory();
                break;
            case 4:
                printf("\nLogging out...\n");
                break;
            default:
                printf("\nInvalid choice.\n");
        }
    } while(choice != 4);
}
// View Appointments
void viewMyAppointments(char *loggedID){
    FILE *fp = fopen("appointments.txt", "r");
    if (fp == NULL){
        printf("\nNo appointments found.\n");
        return;
    }
    Appointment a;
    printf("\n%-10s %-10s %-12s %-10s\n", "AppID", "PatientID", "Date", "Time");
    while (fscanf(fp, "%s %s %s %s %s %s", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period) != EOF){
        if (strcmp(a.doctorID, loggedID) == 0){
            printf("%-10s %-10s %-12s %s %s\n", a.appID, a.patientID, a.date, a.time, a.period);
        }
    }
    fclose(fp);
}
// Add Medical Record function
void addMedicalRecord(char *loggedID){
    FILE *fp = fopen("medical_records.txt", "a");
    if (fp == NULL){
        printf("Error opening file.\n");
        return;
    }
    MedicalRecord mr;
    printf("\n=== ADD MEDICAL RECORD ===\n");
    printf("Record ID: ");
    scanf("%s", mr.recordID);
    printf("Patient ID: ");
    scanf("%s", mr.patientID);
    getchar();
    printf("Diagnosis: ");
    fgets(mr.diagnosis, sizeof(mr.diagnosis), stdin);
    mr.diagnosis[strcspn(mr.diagnosis, "\n")] = 0;
    printf("Prescription: ");
    fgets(mr.prescription, sizeof(mr.prescription), stdin);
    mr.prescription[strcspn(mr.prescription, "\n")] = 0;
    printf("Notes: ");
    fgets(mr.notes, sizeof(mr.notes), stdin);
    mr.notes[strcspn(mr.notes, "\n")] = 0;
    printf("Date (DD/MM/YYYY): ");
    scanf("%s", mr.date);
    strcpy(mr.doctorID, loggedID);
    fprintf(fp,"%s %s %s %s %s %s %s\n", mr.recordID, mr.patientID, mr.doctorID, mr.diagnosis, mr.prescription, mr.notes, mr.date);
    fclose(fp);
    printf("\nMedical record added successfully.\n");
}
// View Patient History
void viewPatientHistory(){
    FILE *fp = fopen("medical_records.txt", "r");
    char searchID[10];
    printf("\nEnter Patient ID: ");
    scanf("%s", searchID);
    if (fp == NULL){
        printf("No records found.\n");
        return;
    }
    MedicalRecord mr;
    int found = 0;
    printf("\n====== PATIENT HISTORY ======\n");
    while (fscanf(fp,"%s %s %s %s %s %s %s", mr.recordID, mr.patientID, mr.doctorID, mr.diagnosis, mr.prescription, mr.notes, mr.date) != EOF){
        if (strcmp(mr.patientID, searchID) == 0){
            printf("\nRecord ID  : %s\n", mr.recordID);
            printf("Doctor ID    : %s\n", mr.doctorID);
            printf("Date Visited : %s\n", mr.date);
            printf("Diagnosis    : %s\n", mr.diagnosis);
            printf("Prescription : %s\n", mr.prescription);
            printf("Notes        : %s\n", mr.notes);
            found = 1;
        }
    }
    if(found == 0){
        printf("\nNo records found for this patient.\n");
    }
    fclose(fp);
}

// Nurse
// Nurse Login function
void nurseLogin(){
    FILE *fp = fopen("nurses.txt", "r");
    if(fp == NULL){
        printf("Error: nurses.txt not found.\n");
        return;
    }
    char inputID[10];
    char inputPass[20];
    char loggedID[10];
    Nurse n;
    int found = 0;
    printf("\n=== NURSE LOGIN ===\n");
    printf("Enter Nurse ID: ");
    scanf("%s", inputID);
    printf("Enter Password: ");
    scanf("%s", inputPass);
    while(fscanf(fp,"%s %s %s %s %s", n.n_id, n.n_name, n.n_ward, n.n_email, n.n_pass) != EOF){
        if(strcmp(inputID,n.n_id)==0 && strcmp(inputPass,n.n_pass)==0){
            strcpy(loggedID,n.n_id);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if(found){
        printf("\nLogin successful! Welcome %s (%s)\n",n.n_name,n.n_ward);
        nurseMenu();
    }
    else{
        printf("\nInvalid login.\n");
    }
}
// Nurse Menu
void nurseMenu(){
    int choice;
    do{
        printf("\n========== NURSE MENU ==========\n");
        printf("1. View Doctor Schedule\n");
        printf("2. Add Inventory\n");
        printf("3. View Inventory\n");
        printf("4. Search Inventory\n");
        printf("5. Low Stock Report\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                viewDoctorSchedule();
                break;
            case 2:
                addInventory(); 
                break;
            case 3:
                viewInventory();
                break;
            case 4:
                searchInventory();
                break;
            case 5:
                generateReport();
                break;
            case 6:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice\n");
        }

    } while(choice != 6);
}
// View Doctor Schedule
void viewDoctorSchedule(){
    FILE *fp = fopen("appointments.txt","r");
    if(fp == NULL){
        printf("No appointments found.\n");
        return;
    }
    Appointment a;
    printf("\n%-10s %-10s %-10s %-12s %-10s\n", "AppID", "Patient", "Doctor", "Date", "Time");
    while(fscanf(fp,"%s %s %s %s %s %s", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period) != EOF){
        printf("%-10s %-10s %-10s %-12s %s %s\n", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period);
    }
    fclose(fp);
}
// Add Inventory function
void addInventory(){
    FILE *fp = fopen("inventory.txt","a");
    Inventory i;
    if(fp == NULL) return;
    printf("\nEnter Item ID: ");
    scanf("%s",i.itemID);
    printf("Enter Name: ");
    scanf("%s",i.itemName);
    printf("Enter Category: ");
    scanf("%s",i.category);
    printf("Enter Quantity: ");
    scanf("%d",&i.quantity);
    fprintf(fp,"%s %s %s %d\n", i.itemID, i.itemName, i.category, i.quantity);
    fclose(fp);
    printf("Inventory added.\n");
}
// Generate Report function
void generateReport(){
    FILE *fp = fopen("inventory.txt","r");
    if(fp == NULL) return;
    Inventory i;
    printf("\n=== LOW STOCK (Below 10) ===\n");
    while(fscanf(fp,"%s %s %s %d", i.itemID, i.itemName, i.category, &i.quantity)!=EOF){
        if(i.quantity < 10){
            printf("%s (%s) Qty:%d\n", i.itemName, i.itemID, i.quantity);
        }
    }
    fclose(fp);
}

// Patient
// Patient Login Function
void patientLogin(){
    FILE *fp = fopen("patients.txt","r");
    Patient p;
    char inputEmail[50], inputPass[20];
    printf("\n=== PATIENT LOGIN ===\n");
    printf("Email: ");
    scanf("%s", inputEmail);
    printf("Password: ");
    scanf("%s", inputPass);
    while(fscanf(fp,"%s %s %d %s %s %s", p.p_id, p.p_name, &p.p_age, p.p_gender, p.p_email, p.p_password)!=EOF){
        if(strcmp(p.p_email,inputEmail)==0 && strcmp(p.p_password,inputPass)==0){
            printf("Login successful\n");
            patientMenu(p.p_id);
            return;
        }
    }
    printf("Invalid login\n");
    fclose(fp);
}
// Patient Menu
void patientMenu(char patientID[]){
    int ch;
    do{
        printf("\n===== PATIENT MENU =====\n");
        printf("1. Book Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Reschedule Appointment\n");
        printf("4. Cancel Appointment\n");
        printf("5. View Billing\n");
        printf("6. Logout\n");
        printf("Choice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                bookAppointment(patientID);
                break;
            case 2:
                viewAppointments(patientID);
                break;
            case 3:
                rescheduleAppointment(patientID);
                break;
            case 4:
                cancelAppointment(patientID);
                break;
            case 5:
                viewBilling(patientID);
                break;
            case 6:
                printf("Logging out......");
                break;
            default:
                printf("Enter a Valid Option...");
        }
    } while(ch!=6);
}
// Generate Appointment ID
void generateAppointmentID(char newID[]){
    FILE *fp = fopen("appointments.txt","r");
    Appointment a;
    int last=0,num;
    if(fp!=NULL){
        while(fscanf(fp,"%s %*s %*s %*s %*s %*s",a.appID)!=EOF){
            sscanf(a.appID,"A%d",&num);
            if(num>last) last=num;
        }
        fclose(fp);
    }
    sprintf(newID,"A%04d",last+1);
}
// Book Appointment
void bookAppointment(char patientID[]){
    FILE *fp = fopen("appointments.txt","a");
    FILE *check;
    Appointment a, temp;
    generateAppointmentID(a.appID);
    strcpy(a.patientID,patientID);
    // doctor list
    FILE *fdoc = fopen("doctors.txt","r");
    Doctor doc;
    printf("\n=== DOCTORS ===\n");
    while(fscanf(fdoc,"%s %s %s %*s %*s", doc.do_id, doc.do_name, doc.do_specialty)!=EOF){
        printf("%s - %s (%s)\n", doc.do_id, doc.do_name, doc.do_specialty);
    }
    fclose(fdoc);
    printf("Enter Doctor ID: ");
    scanf("%s",a.doctorID);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s",a.date);
    if(!isFutureDate(a.date)){
        printf("Invalid date\n");
        return;
    }
    // Time Slots
    printf("\nAvailable Time Slots:\n");
    printf("1. 09:00 AM\n");
    printf("2. 10:00 AM\n");
    printf("3. 11:00 AM\n");
    printf("4. 02:00 PM\n");
    printf("5. 03:00 PM\n");
    int slot;
    printf("Enter choice (1-5): ");
    scanf("%d",&slot);
    switch(slot){
        case 1:
            strcpy(a.time,"09:00");
            strcpy(a.period,"AM"); 
            break;
        case 2: 
            strcpy(a.time,"10:00"); 
            strcpy(a.period,"AM"); 
            break;
        case 3: 
            strcpy(a.time,"11:00"); 
            strcpy(a.period,"AM"); 
            break;
        case 4: 
            strcpy(a.time,"02:00"); 
            strcpy(a.period,"PM"); 
            break;
        case 5: 
            strcpy(a.time,"03:00"); 
            strcpy(a.period,"PM"); 
            break;
        default: 
            printf("Invalid slot\n"); 
            return;
    }
    // conflict check
    check = fopen("appointments.txt","r");
    if(check!=NULL){
        while(fscanf(check,"%s %s %s %s %s %s", temp.appID, temp.patientID, temp.doctorID, temp.date, temp.time, temp.period)!=EOF){
            if(strcmp(temp.doctorID,a.doctorID)==0 && strcmp(temp.date,a.date)==0 && strcmp(temp.time,a.time)==0 && strcmp(temp.period,a.period)==0){
                printf("Doctor not available\n");
                return;
            }
        }
        fclose(check);
    }
    fprintf(fp,"%s %s %s %s %s %s\n", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period);
    fclose(fp);
    // billing
    Payment(patientID, a.appID);
    printf("Appointment booked! ID: %s\n",a.appID);
}
// View Appointments
void viewAppointments(char patientID[]){
    FILE *fp = fopen("appointments.txt","r");
    Appointment a;
    while(fscanf(fp,"%s %s %s %s %s %s", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period)!=EOF){
        if(strcmp(a.patientID,patientID)==0){
            printf("%s | %s %s %s\n", a.appID,a.date,a.time,a.period);
        }
    }
    fclose(fp);
}
// Reschedule Appointments
void rescheduleAppointment(char patientID[]){
    FILE *fp=fopen("appointments.txt","r");
    FILE *temp=fopen("temp.txt","w");
    Appointment a;
    char id[10];
    printf("Enter Appointment ID: ");
    scanf("%s",id);
    while(fscanf(fp,"%s %s %s %s %s %s", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period)!=EOF){
        if(strcmp(a.appID,id)==0 && strcmp(a.patientID,patientID)==0){
            printf("New Date (DD/MM/YYYY): ");
            scanf("%s",a.date);
        printf("\nAvailable Time Slots:\n");
        printf("1. 09:00 AM\n");
        printf("2. 10:00 AM\n");
        printf("3. 11:00 AM\n");
        printf("4. 02:00 PM\n");
        printf("5. 03:00 PM\n");
        int slot;
        printf("Enter choice (1-5): ");
        scanf("%d",&slot);
        switch(slot){   
            case 1:
                strcpy(a.time,"09:00");
                strcpy(a.period,"AM");
                break;
            case 2:
                strcpy(a.time,"10:00");
                strcpy(a.period,"AM");
                break;
            case 3:
                strcpy(a.time,"11:00");
                strcpy(a.period,"AM"); 
                break;
            case 4:
                strcpy(a.time,"02:00");
                strcpy(a.period,"PM"); 
                break;
            case 5:
                strcpy(a.time,"03:00");
                strcpy(a.period,"PM"); 
                break;
            default:
                printf("Invalid slot\n"); 
                return;
        }
    fprintf(temp,"%s %s %s %s %s %s\n", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period);
    }
    }
    fclose(fp); fclose(temp);
    remove("appointments.txt");
    rename("temp.txt","appointments.txt");
    printf("Rescheduled\n");
}
// Cancel Appointments
void cancelAppointment(char patientID[]){
    FILE *fp=fopen("appointments.txt","r");
    FILE *temp=fopen("temp.txt","w");
    Appointment a;
    char id[10];
    printf("Enter Appointment ID: ");
    scanf("%s",id);
    while(fscanf(fp,"%s %s %s %s %s %s", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period)!=EOF){
        if(strcmp(a.appID,id)==0 && strcmp(a.patientID,patientID)==0){
            continue;
        }
        fprintf(temp,"%s %s %s %s %s %s\n", a.appID, a.patientID, a.doctorID, a.date, a.time, a.period);
    }
    fclose(fp); 
    fclose(temp);
    remove("appointments.txt");
    rename("temp.txt","appointments.txt");
    printf("Cancelled\n");
}
// View Billing
void viewBilling(char patientID[]){
    FILE *fp=fopen("billing.txt","r");
    char app[10], pid[10], pmethod[20];
    int amt;
    if(fp == NULL){
        printf("No billing records found.\n");
        return;
    }
    printf("\n=== BILLING ===\n");
    while(fscanf(fp,"%s %s RM%d %s", pid, pmethod, &amt, app)!=EOF){
        if(strcmp(pid,patientID)==0){
            printf("Paid By : %s | Payment Method : %s | Amount : RM %d | Appointment ID : %s \n", pid, pmethod, amt, app);
        }
    }
    fclose(fp);
}
// Payment
int Payment(char patientid[6], char appointmentid[10]){
    int paysuccess = 0;
    int amount = 100;
    printf("You need to Pay : RM %d \n", amount);
    for(int i = 0; i<3; i++){
        int pmoption;
        printf("Payment Methods \n1.Card \n2.Online Banking \nChoose Payment Method : ");
        scanf("%d", &pmoption);
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}           // Clear the Input Buffer
        switch(pmoption){
            case 1:
                paysuccess = card(amount, patientid, appointmentid);
                break;
            case 2:
                paysuccess = onlinebanking(amount, patientid, appointmentid);
                break;
            default:
                printf("Please Enter a Valid Option \n");          
        }
        if(i==2){
            printf("Too Many Failed Attempts, Please Try Again Later.");
        }
    }
    if(paysuccess == 1){
        viewBilling(patientid);
    }
    return paysuccess;
}
// Card (Payment)
int card(int amount, char patientid[6], char appointmentid[10]){
    int paysuccess = 0;
    char CNo[18];
    for(int j = 0; j<3; j++){
        printf("Enter Card Number : ");
        fgets(CNo, sizeof(CNo), stdin);
        CNo[strcspn(CNo, "\n")] = '\0';
        if(strlen(CNo) == 16){
            char CName[50];
            printf("Enter Name on Card : ");
            fgets(CName, sizeof(CName), stdin);
            CName[strcspn(CName, "\n")] = '\0';
            int CV;
            printf("Enter Card Valdity : ");
            scanf("%d", &CV);
            int CVV;
            printf("Enter CVV Code : ");
            scanf("%d", &CVV);
            int c;
            while ((c = getchar()) != '\n' && c != EOF){}           // Clear the Input Buffer
            char confo[9];
            printf("Type 'Pay Now' to confirm payment : ");
            fgets(confo, sizeof(confo), stdin);
            confo[strcspn(confo, "\n")] = '\0';
            if(strcmp(confo, "Pay Now") == 0){
                printf("Payment Success. \n");
                paysuccess = 1;
                FILE *pFile = fopen("billing.txt", "a");
                if(pFile == NULL){
                    printf("An Error Occured. \n");
                    return 1;
                }
                fprintf(pFile, "%s Card RM%d %s \n", patientid, amount, appointmentid);
                fclose(pFile);
                return paysuccess;
            }
            else{
                printf("Payment Failed. \n");
                paysuccess = 0;
                return paysuccess;
            }
        }
        else{
            printf("Invalid Card Number! Please Try Again \n");
        }
        if(j==2){
            printf("Too Many Failed Attempts, Please Try Again Later. \n");
            return paysuccess;
        }
    }
    return paysuccess;
}
// Online Banking (Payment)
int onlinebanking(int amount, char patientid[6], char appointmentid[10]){
    int paysuccess = 0;
    char OB[10];
    printf("Enter Bank Name : ");
    fgets(OB, sizeof(OB), stdin);
    OB[strcspn(OB, "\n")] = '\0';
    printf("Redirecting to Online Banking... \n");
    printf("Enter your banking details (We do not store your banking details.) \n");
    char un[30];
    printf("Enter Username : ");
    fgets(un, sizeof(un), stdin);
    un[strcspn(un, "\n")] = '\0';
    char pass[40];
    printf("Enter Password : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';
    char confo[9];
    printf("Type 'Pay Now' to confirm payment : ");
    fgets(confo, sizeof(confo), stdin);
    confo[strcspn(confo, "\n")] = '\0';
    if(strcmp(confo, "Pay Now") == 0){
        printf("Payment Success. \n");
        paysuccess = 1;
        FILE *pFile = fopen("billing.txt", "a");
        if(pFile == NULL){
            printf("An Error Occured. \n");
            return 1;
        }
        fprintf(pFile, "%s Online_Banking RM%d %s \n", patientid, amount, appointmentid);
        fclose(pFile);
        return paysuccess;
    }
    else{
        printf("Payment Failed. \n");
        return paysuccess;
    }
}
// Future Date
int isFutureDate(char input[]){
    int d,m,y;
    sscanf(input,"%d/%d/%d",&d,&m,&y);
    time_t t=time(NULL);
    struct tm *now=localtime(&t);
    if(y < now->tm_year+1900) return 0;
    if(y == now->tm_year+1900 && m < now->tm_mon+1) return 0;
    if(y == now->tm_year+1900 && m == now->tm_mon+1 && d < now->tm_mday) return 0;
    return 1;
}