#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<cstring>
#include<iomanip>

using namespace std;

class HOTEL
{
	private:
	  int room_no;                // to store room no
	  char name[30];              // to store name of Customer
	  char address[50];           // to store Address of Customer
	  char phone[15];             // to store Contatc no of customer
	  long days;                  // to store no of days of stay
	  long cost;                  // to store cost of stay
	  char rtype[30];             // to store room type 
	  long pay;                   // to store cost of food
	  void breakfast(int);        // to assign price of breakfast
	  void lunch(int);            // to assign price of lunch
	  void dinner(int);           // to assign price of dinner

	public:
	  void main_menu();	 	  //to dispay the main menu
	  void add();			  //to book a room
	  void display(); 		  //to display the specific customer information
	  void rooms();			  //to display alloted rooms
	  void edit();			  //to edit the customer by calling modify or delete
	  int check(int);		  //to check room status
	  void modify();		  //to modify the customer information
	  void delete_rec();              //to check out the customer
	  void restaurant();	          //to order food from restaurant
	  void modify_name(int);          //to modify name of guest
	  void modify_address(int);       //to modify address of guest
	  void modify_phone(int);         //to modify phone number of guest
	  void modify_days(int);          //to modify days of stay of guest
}h;

void HOTEL::main_menu()
{
	int choice;
	while(true)
	{
		system("clear");
		cout<<"\n\t\t\t\t *************";
		cout<<"\n\t\t\t\t *THE HOTEL*";
		cout<<"\n\t\t\t\t *************";
		cout<<"\n\t\t\t\t * MAIN MENU *";
		cout<<"\n\t\t\t\t *************";
		cout<<"\n\n\n\t\t\t\t1. Book A Room";
		cout<<"\n\t\t\t\t2. Customer Information";
		cout<<"\n\t\t\t\t3. Rooms Allotted";
		cout<<"\n\t\t\t\t4. Edit Customer Details";
		cout<<"\n\t\t\t\t5. Order Food from Restaurant";
		cout<<"\n\t\t\t\t6. Check Out from Room";
		cout<<"\n\t\t\t\t7. Exit";
		cout<<"\n\n\t\t\t\tEnter Your Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:	add();
				break;
			case 2: display();
				break;
			case 3: rooms();
				break;
			case 4:	edit();
				break;
			case 5: restaurant();
				break;
			case 6 :
			    delete_rec();
			    break;
			case 7: return;
			default:
				{
					cout<<"\n\n\t\t\tWrong choice.";
					cout<<"\n\t\t\tPress any key to continue.";
					getchar();
				}
		}
	}
}

void HOTEL::add()
{
	system("clear");
	int r,flag;
	ofstream fout("Record.DAT",ios::app|ios::binary);
	cout<<"\n\t\t\t +-----------------------+";
	cout<<"\n\t\t\t | Rooms  |   Room Type  |";
	cout<<"\n\t\t\t +-----------------------+";
	cout<<"\n\t\t\t |   1-50 |    Deluxe    |";
	cout<<"\n\t\t\t |  51-80 |   Executive  |";
	cout<<"\n\t\t\t | 81-100 | Presidential |";
	cout<<"\n\t\t\t +-----------------------+";
	cout<<"\n\n ENTER CUSTOMER DETAILS";
	cout<<"\n ----------------------";
	cout<<"\n\n Room Number: ";
	cin>>r;
	flag=check(r);
	if(flag==1)
		cout<<"\n Sorry, Room is already booked.\n";
	else
	{
	   if(flag==2)
		   cout<<"\n Sorry, Room does not exist.\n";
	   else
	   {
		   room_no=r;
		   cout<<" Name: ";
		   cin>>name;
		   cout<<" Address: ";
		   cin>>address;
		   cout<<" Phone Number: ";
		   cin>>phone;
		   cout<<" Number of Days: ";
		   cin>>days;
		   if(room_no>=1&&room_no<=50)
		   {
		      strcpy(rtype,"Deluxe");
		      cost=days*10000;
		   }
		   else
		   {
		      if(room_no>=51&&room_no<=80)
		      {
			 strcpy(rtype,"Executive");
			 cost=days*12500;
		      }
		      else
		      {
			 if(room_no>=81&&room_no<=100)
			 {
			    strcpy(rtype,"Presidential");
			    cost=days*15000;
			 }
		      }
		   }
		   fout.write((char*)this, sizeof(HOTEL));
		   cout<<"\n Room has been booked.";
	   }
	}
	cout<<"\n Press any key to continue.";
	getchar();
	getchar();
	fout.close();
}


void HOTEL::display()
{
	system("clear");
	ifstream fin("Record.DAT",ios::in|ios::binary);
	int r,flag;
	cout<<"\n Enter Room Number: ";
	cin>>r;
	while(fin.read((char*)this,sizeof(HOTEL)))
	{
		if(room_no==r)
		{
			system("clear");
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room Number: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone Number: "<<phone;
			cout<<"\n Staying for "<<days<<" days.";
			cout<<"\n Room Type: "<<rtype;
			cout<<"\n Total cost of stay: "<<cost;
			flag=1;
			break;
		}
	}
	if(flag==0)
		cout<<"\n Room is Vacant.";
	cout<<"\n\n Press any key to continue.";
	getchar();
	getchar();
	fin.close();

}


void HOTEL::rooms()
{
	system("clear");
	const char separator=' ';
	const int NoWidth=8;
	const int GuestWidth=17;
	const int AddressWidth=16;
	const int RoomWidth=13;
	const int ContactNoWidth=13;
	ifstream fin("Record.DAT",ios::in|ios::binary);
	cout<<"\n\t\t\t    LIST OF ROOMS ALLOTED";
	cout<<"\n\t\t\t   -----------------------";
	cout<<"\n\n +---------+------------------+-----------------+--------------+--------------+";
	cout<<"\n | Room No.|    Guest Name    |      Address    |   Room Type  |  Contact No. |";
	cout<<"\n +---------+------------------+-----------------+--------------+--------------+";
	while(fin.read((char*)this,sizeof(HOTEL)))
	{
		cout<<"\n |"<<setw(NoWidth)<<setfill(separator)<<room_no<<" |";
		cout<<setw(GuestWidth)<<setfill(separator)<<name<<" |";
		cout<<setw(AddressWidth)<<setfill(separator)<<address<<" |";
		cout<<setw(RoomWidth)<<setfill(separator)<<rtype<<" |";
		cout<<setw(ContactNoWidth)<<setfill(separator)<<phone<<" |";
	}
	cout<<"\n +---------+------------------+-----------------+--------------+--------------+";
	cout<<"\n\n\n\t\t\tPress any key to continue.";
	getchar();
	getchar();
	fin.close();
}

void HOTEL::edit() 
{
    system("clear"); // Clear the console screen
    int choice, r; 
    cout << "\n EDIT MENU"; 
    cout << "\n ---------"; 
    cout << "\n\n 1. Modify Customer Information."; // Option to modify customer info
    cout << "\n Enter your choice: "; // Prompt for menu choice
    cin >> choice; // Read user's choice
    system("clear"); // Clear the console screen

    switch (choice) 
    {
        case 1: modify(); 
            break;
        default: cout << "\n Wrong Choice."; \
            break;
    }
    cout << "\n Press any key to continue."; // Prompt to continue
    getchar(); 
    getchar(); 
}

int HOTEL::check(int r) 
{
    int flag = 0; // Flag to indicate room status
    ifstream fin("Record.DAT", ios::in | ios::binary); // Open file for reading in binary mode

    // Loop to read records from the file
    while (fin.read((char*)this, sizeof(HOTEL))) // Continue until end of file
    {
        if (room_no == r) // If room number matches the input
        {
            flag = 1; // Set flag to indicate room is occupied
            break; // Exit the loop
        }
        else
        {
            if (r > 100) // If room number is invalid (greater than 100)
            {
                flag = 2; // Set flag to indicate invalid room number
                break; // Exit the loop
            }
        }
    }
    fin.close(); // Close the file
    return (flag); // Return flag indicating room status
}

void HOTEL::modify()
{
    system("clear"); 
    int ch, r; 
    cout << "\n MODIFY MENU"; 
    cout << "\n -----------"; 
    cout << "\n\n\n 1. Modify Name"; 
    cout << "\n 2. Modify Address"; 
    cout << "\n 3. Modify Phone Number"; 
    cout << "\n 4. Modify Number of Days of Stay"; 
    cout << "\n Enter Your Choice: "; 
    cin >> ch; 
    system("clear"); // Clear the console screen
    cout << "\n Enter Room Number: "; 
    cin >> r; 

    switch (ch) 
    {
        case 1: modify_name(r); 
            break;
        case 2: modify_address(r); 
            break;
        case 3: modify_phone(r); 
            break;
        case 4: modify_days(r);
            break;
        default: cout << "\n Wrong Choice"; 
                 getchar();
                 getchar(); 
                 break;
    }
}

void HOTEL::modify_name(int r) // Definition of modify_name function
{
    long pos, flag = 0; // Variables for file position and flag for success
    fstream file("Record.DAT", ios::in | ios::out | ios::binary); // Open file for reading and writing in binary mode

    // Loop to read records from the file
    while (!file.eof()) // Continue until end of file
    {
        pos = file.tellg(); // Store current position
        file.read((char*)this, sizeof(HOTEL)); // Read record into the current object

        if (room_no == r) // If room number matches the input
        {
            cout << "\n Enter New Name: "; // Prompt for new name
            cin >> name; // Read new name
            file.seekg(pos); // Move back to the current position
            file.write((char*)this, sizeof(HOTEL)); // Write updated record back to the file
            cout << "\n Customer Name has been modified."; // Display success message
            flag = 1; // Set flag to indicate successful operation
            break; // Exit the loop
        }
    }
    if (flag == 0) // If room number was not found
        cout << "\n Sorry, Room is vacant."; // Display message
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    file.close(); // Close the file
}

void HOTEL::modify_address(int r) // Definition of modify_address function
{
    long pos, flag = 0; // Variables for file position and flag for success
    fstream file("Record.DAT", ios::in | ios::out | ios::binary); // Open file for reading and writing in binary mode

    // Loop to read records from the file
    while (!file.eof()) // Continue until end of file
    {
        pos = file.tellg(); // Store current position
        file.read((char*)this, sizeof(HOTEL)); // Read record into the current object

        if (room_no == r) // If room number matches the input
        {
            cout << "\n Enter New Address: "; // Prompt for new address
            cin >> address; // Read new address
            file.seekg(pos); // Move back to the current position
            file.write((char*)this, sizeof(HOTEL)); // Write updated record back to the file
            cout << "\n Customer Address has been modified."; // Display success message
            flag = 1; // Set flag to indicate successful operation
            break; // Exit the loop
        }
    }
    if (flag == 0) // If room number was not found
        cout << "\n Sorry, Room is vacant."; // Display message
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    file.close(); // Close the file
}

void HOTEL::modify_phone(int r) // Definition of modify_phone function
{
    long pos, flag = 0; // Variables for file position and flag for success
    fstream file("Record.DAT", ios::in | ios::out | ios::binary); // Open file for reading and writing in binary mode

    // Loop to read records from the file
    while (!file.eof()) // Continue until end of file
    {
        pos = file.tellg(); // Store current position
        file.read((char*)this, sizeof(HOTEL)); // Read record into the current object

        if (room_no == r) // If room number matches the input
        {
            cout << "\n Enter New Phone Number: "; // Prompt for new phone number
            cin >> phone; // Read new phone number
            file.seekg(pos); // Move back to the current position
            file.write((char*)this, sizeof(HOTEL)); // Write updated record back to the file
            cout << "\n Customer Phone Number has been modified."; // Display success message
            flag = 1; // Set flag to indicate successful operation
            break; // Exit the loop
        }
    }
    if (flag == 0) // If room number was not found
        cout << "\n Sorry, Room is vacant."; // Display message
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    file.close(); // Close the file
}

void HOTEL::modify_days(int r) // Definition of modify_days function
{
    long pos, flag = 0; // Variables for file position and flag for success
    fstream file("Record.DAT", ios::in | ios::out | ios::binary); // Open file for reading and writing in binary mode

    // Loop to read records from the file
    while (!file.eof()) // Continue until end of file
    {
        pos = file.tellg(); // Store current position
        file.read((char*)this, sizeof(HOTEL)); // Read record into the current object

        if (room_no == r) // If room number matches the input
        {
            cout << " Enter New Number of Days of Stay: "; // Prompt for new days of stay
            cin >> days; // Read new number of days
            // Determine room type and cost based on room number
            if (room_no >= 1 && room_no <= 50) // If room number is in Deluxe range
            {
                strcpy(rtype, "Deluxe"); // Set room type to Deluxe
                cost = days * 10000; // Calculate cost for Deluxe room
            }
            else if (room_no >= 51 && room_no <= 80) // If room number is in Executive range
            {
                strcpy(rtype, "Executive"); // Set room type to Executive
                cost = days * 12500; // Calculate cost for Executive room
            }
            else if (room_no >= 81 && room_no <= 100) // If room number is in Presidential range
            {
                strcpy(rtype, "Presidential"); // Set room type to Presidential
                cost = days * 15000; // Calculate cost for Presidential room
            }
            file.seekg(pos); // Move back to the current position
            file.write((char*)this, sizeof(HOTEL)); // Write updated record back to the file
            cout << "\n Customer information is modified."; // Display success message
            flag = 1; // Set flag to indicate successful operation
            break; // Exit the loop
        }
    }
    if (flag == 0) // If room number was not found
        cout << "\n Sorry, Room is Vacant."; // Display message
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    file.close(); // Close the file
}

void HOTEL::delete_rec()
{
    // Clear the console screen
    system("clear");
    
    int r, flag = 0; // 'r' will hold the room number to delete, 'flag' indicates if a customer was checked out
    char ch; // Variable to store user's choice for checking out the customer

    // Prompt the user to enter the room number
    cout << "\n Enter Room Number: ";
    cin >> r; // Read the room number from user input

    // Open the existing records file in binary read mode
    ifstream fin("Record.DAT", ios::in | ios::binary);
    // Create a temporary file to store records that are not deleted
    ofstream fout("temp.DAT", ios::out | ios::binary);
    
    // Read each record from the file until the end of the file is reached
    while (fin.read((char*)this, sizeof(HOTEL)))
    {
        // Check if the current record's room number matches the input room number
        if (room_no == r)
        {
            // Display customer details
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone Number: " << phone;
            cout << "\n Room Type: " << rtype;
            cout << "\n Your total bill is: Rs. " << cost;
            cout << "\n\n Do you want to check out this customer (y/n): ";
            cin >> ch; // Get user's choice for checking out
            
            // If the user chooses 'n', write the record to the temporary file
            if (ch == 'n')
                fout.write((char*)this, sizeof(HOTEL)); // Preserve the record in temp file
            else
            {
                // If the user chooses 'y', mark that a customer has checked out
                cout << "\n Customer Checked Out.";
                flag = 1; // Set flag to indicate a successful checkout
            }
        }
        else
        {
            // If the room number does not match, write the record to the temporary file
            fout.write((char*)this, sizeof(HOTEL)); // Preserve this record as well
        }
    }
    
    // Close both the input and output file streams
    fin.close();
    fout.close();
    
    // Check if a customer was checked out
    if (flag == 0)
        // If no customer was checked out, inform the user that the room is vacant
        cout << "\n Sorry, Room is Vacant.";
    else
    {
        // If a customer was checked out, remove the original records file
        remove("Record.DAT");
        // Rename the temporary file to replace the original records file
        rename("temp.DAT", "Record.DAT");
    }
    
    // Prompt the user to return to the main menu
    cout << "\n Press any key to return to the main menu.";
    getchar(); getchar(); // Wait for user input before returning to the main menu
}


void HOTEL::restaurant() 
{
    system("clear"); 
    int r, ch, num; 
    cout << "\n RESTAURANT MENU:"; 
    cout << "\n --------------- "; 
    cout << "\n\n 1. Order Breakfast\n 2. Order Lunch\n 3. Order Dinner"; // Menu options
    cout << "\n\n Enter your choice: ";
    cin >> ch; 
    system("clear"); 
    cout << " Enter Room Number: "; 
    cin >> r; 
    switch(ch) 
    {
        case 1: breakfast(r); 
            break;

        case 2: lunch(r); 
            break;

        case 3: dinner(r); 
        break;
    }
    cout << "\n\n Press any key to continue."; 
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    return; 
}

void HOTEL::breakfast(int r) // Definition of breakfast function
{
    int num, flag = 0; // Variables for number of people and flag for booking status
    long pos; // Variable to store current position in file
    cout << " Enter number of people: "; // Prompt for number of people
    cin >> num; // Read number of people
    fstream file("Record.DAT", ios::in | ios::out | ios::binary); // Open file for reading and writing in binary mode

    // Loop to read records from the file
    while (!file.eof()) // Continue until end of file
    {
        pos = file.tellg(); // Store current position
        file.read((char*)this, sizeof(HOTEL)); // Read record into the current object

        if (room_no == r) // If room number matches the input
        {
            pay = 500 * num; // Calculate payment for breakfast
            cost = cost + pay; // Update total cost
            file.seekg(pos); // Move back to the current position
            file.write((char*)this, sizeof(HOTEL)); // Write updated record back to the file
            cout << "\n Amount added to the bill: Rs. " << pay; // Display amount added
            flag = 1; // Set flag to indicate successful operation
            break; // Exit the loop
        }
    }
    if (flag == 0) // If room number was not found
        cout << "\n Sorry, Room is Vacant."; // Display message
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    file.close(); // Close the file
}

void HOTEL::lunch(int r) // Definition of lunch function
{
    int num, flag = 0; // Variables for number of people and flag for booking status
    long pos; // Variable to store current position in file
    cout << " Enter number of people: "; // Prompt for number of people
    cin >> num; // Read number of people
    fstream file("Record.DAT", ios::in | ios::out | ios::binary); // Open file for reading and writing in binary mode

    // Loop to read records from the file
    while (!file.eof()) // Continue until end of file
    {
        pos = file.tellg(); // Store current position
        file.read((char*)this, sizeof(HOTEL)); // Read record into the current object

        if (room_no == r) // If room number matches the input
        {
            pay = 1000 * num; // Calculate payment for lunch
            cost = cost + pay; // Update total cost
            file.seekg(pos); // Move back to the current position
            file.write((char*)this, sizeof(HOTEL)); // Write updated record back to the file
            cout << "\n Amount added to the bill: Rs. " << pay; // Display amount added
            flag = 1; // Set flag to indicate successful operation
            break; // Exit the loop
        }
    }
    if (flag == 0) // If room number was not found
        cout << "\n Sorry, Room is vacant."; // Display message
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    file.close(); // Close the file
}

void HOTEL::dinner(int r) // Definition of dinner function
{
    int num, flag = 0; // Variables for number of people and flag for booking status
    long pos; // Variable to store current position in file
    cout << " Enter number of people: "; // Prompt for number of people
    cin >> num; // Read number of people
    fstream file("Record.DAT", ios::in | ios::out | ios::binary); // Open file for reading and writing in binary mode

    // Loop to read records from the file
    while (!file.eof()) // Continue until end of file
    {
        pos = file.tellg(); // Store current position
        file.read((char*)this, sizeof(HOTEL)); // Read record into the current object

        if (room_no == r) // If room number matches the input
        {
            pay = 1200 * num; // Calculate payment for dinner
            cost = cost + pay; // Update total cost
            file.seekg(pos); // Move back to the current position
            file.write((char*)this, sizeof(HOTEL)); // Write updated record back to the file
            cout << "\n Amount added to the bill: Rs. " << pay; // Display amount added
            flag = 1; // Set flag to indicate successful operation
            break; // Exit the loop
        }
    }
    if (flag == 0) // If room number was not found
        cout << "\n Sorry, Room is Vacant."; // Display message
    getchar(); // Wait for user input
    getchar(); // Wait for user input
    file.close(); // Close the file
}


int main()
{
	system("clear");
	h.main_menu();
	return 0;
}
