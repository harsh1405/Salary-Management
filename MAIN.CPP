#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<dos.h> //for delay function
/************************************************************************************************************
*                             CLASS CONISITING OF MEMBERS FOR Salfile.DAT                                   *
*************************************************************************************************************/

class sal_manage
{
private:
    int sal_no;//Employee Number for Salfile.DAT
    char sal_name[20];//Employee Name for Salfile.DAT
    char sal_desig[20];//Employee's Designation for Salfile.DAT
    int days_worked;
    long sal_basic;//Employee's basic Salary for Salfile.DAT
    long DA;//Dearness Allowance
    long HRA;//House Rent Allowance
    long gross_sal;
public:
    //The Following Function Adds an Employee to Salfile.DAT by also calling the constructor
    void add_sal(int empnoc,char emp_namec[20],char emp_desigc[20],float basicc);
    //The Following Function Removes an Employee from Salfile.DAT
    void remove_sal(int empnoc);
    //The Following Function Modifies the Designation of an Employee in Salfile.DAT
    void moddesig_sal(int empnoc,char emp_desigc[20]);
    //The Following Function Modifies the Basic Salary of an Employee in Salfile.DAT
    void modbasic_sal(int empnoc,float basicc);
    /*The Following Function Updates Salfile.DAT in Respect to the Gross Salary Calculation for an Employee
    and also calls generate_slip()(if Required) and get_sal()*/
    void update_sal();
    //The Following Function Updates the Memebers Required to Calculate The Gross Salary Of An Employee
    void get_sal();
    //The Following Function Generates Payslip for an Employee
    void generate_slip();
    //The Following Function Helps us to Directly Generate Payslip In the Main Menu and calls generate_slip()
    void generate_main();
}empmain;
/************************************************************************************************************
*                                ADDITION OF EMPLOYEES TO Salfile.DAT                                       *
*************************************************************************************************************/
void sal_manage::add_sal(int empnoc,char emp_namec[20],char emp_desigc[20],float basicc)
{
    ofstream fout("Salfile.DAT",ios::app);
    empmain.sal_no=empnoc;
    strcpy(empmain.sal_name,emp_namec);
    strcpy(empmain.sal_desig,emp_desigc);
    empmain.sal_basic=basicc;
    empmain.days_worked=30;
    empmain.DA=0.5*(empmain.sal_basic);
    empmain.HRA=0.4*(empmain.sal_basic);
    empmain.gross_sal=(empmain.DA+empmain.HRA);
    fout.write((char*)&empmain,sizeof(empmain));
    fout.close();
}
/************************************************************************************************************
*                                REMOVAL OF EMPLOYEES FROM Salfile.DAT                                      *
*************************************************************************************************************/
void sal_manage::remove_sal(int enoc)
{
    ofstream fout("Temp.DAT",ios::app|ios::binary);
    ifstream fin("Salfile.DAT",ios::in);
    fin.seekg(ios::beg);
    fin.read((char*)&empmain,sizeof(empmain));
    while(!fin.eof())
    {
        if(sal_no!=enoc)
            fout.write((char*)&empmain,sizeof(empmain));
        fin.read((char*)&empmain,sizeof(empmain));
    }
    fin.close();
    fout.close();
    remove("Salfile.DAT");
    rename("Temp.DAT","Salfile.DAT");
}
/************************************************************************************************************
*                           MODIFICATION OF EMPLOYEE'S DESIGNATION IN Salfile.DAT                           *
*************************************************************************************************************/
void sal_manage::moddesig_sal(int empnoc,char emp_desigc[20])
{
    int pos;
    fstream fin("Salfile.DAT",ios::in|ios::out);
    if(!fin)
        cout<<"\nNo Such File Exists";
    fin.seekg(ios::beg);
    while(fin.read((char*)&empmain,sizeof(empmain)))
    {
        pos=fin.tellg();
	    if(empmain.sal_no==empnoc)
	    {
	        strcpy(empmain.sal_desig,emp_desigc);
		    fin.seekg(pos-sizeof(empmain));
		    fin.write((char*)&empmain,sizeof(empmain));
		    break;
	    }
    }
    fin.close();
}
/************************************************************************************************************
*                           MODIFICATION OF EMPLOYEE'S BASIC SALARY IN Salfile.DAT                           *
*************************************************************************************************************/
void sal_manage::modbasic_sal(int empnoc, float basicc)
{
    int pos;
    fstream fin("Salfile.DAT",ios::in|ios::out);
    if(!fin)
       cout<<"\nNo Such File Exists";
    fin.seekg(ios::beg);
    while(fin.read((char*)&empmain,sizeof(empmain)))
    {
	pos=fin.tellg();
	    if(empmain.sal_no==empnoc)
	    {
		empmain.sal_basic=basicc;
		empmain.DA=0.5*(empmain.sal_basic);
		empmain.HRA=0.4*(empmain.sal_basic);
		empmain.gross_sal=empmain.DA+empmain.HRA;
		fin.seekg(pos-sizeof(empmain));
		fin.write((char*)&empmain,sizeof(empmain));
		break;
	    }
    }
    fin.close();
}
/************************************************************************************************************
*                           UPDATION OF Salfile.DAT FOR GROSS SALARY CALACULATION                           *
*************************************************************************************************************/
void sal_manage::update_sal()
{
    int empno,pos;
    char found='n';
    clrscr();
    cout<<"\t\t\t\tUPDATION OF SALARY FILE";
    cout<<"\nEnter the Employee Number Whose Salary File has to be Updated: ";
    cin>>empno;
    fstream fin("Salfile.DAT",ios::in|ios::out);
    if(!fin)
	cout<<"\nError In Opening File!!";
    fin.seekg(ios::beg);
    while(fin.read((char*)&empmain,sizeof(empmain)))
    {
	pos=fin.tellg();
	if(sal_no==empno)
	    {
		found='y';
		get_sal();
		fin.seekg(pos-sizeof(empmain));
		fin.write((char*)&empmain,sizeof(empmain));
	    }
    }
    fin.close();
    if(found=='n')
    {
	cout<<"\nEmployee Not Found.";
	getch();
    }
}
/************************************************************************************************************
*                          UPDATION OF VALUES OF MEMBERS OF CONSTRUCTORS IN Salfile.DAT                    *
*************************************************************************************************************/
void sal_manage::get_sal()
{
    float x;
    char ch;
    cout<<"Name Of Employee: ";
    puts(sal_name);
    cout<<"\nEnter the No. of Days Worked: ";
    cin>>days_worked;
    cout<<"\nThe Basic Salary of the Employee is: Rs."<<sal_basic;
    DA=0.5*(sal_basic);
    HRA=0.4*(sal_basic);
    x=DA+HRA;
    gross_sal=(x/30)*(days_worked);
    delay(500);
    cout<<"\n\nDearness Allowance(DA) for the Employee is: Rs."<<DA;
    delay(500);
    cout<<"\n\nHouse Rent Allowance(HRA) for the Employee is: Rs."<<HRA;
    delay(500);
    cout<<"\n\nThe Net Salary for the Employee Comes out to be: Rs."<<gross_sal;
    cout<<"\n\nWant to Generate Pay Slip?(Y/N): ";
    cin>>ch;
    if(ch=='Y'||ch=='y')
	generate_slip();
    else
    {
	cout<<"\n\nSalary File Updated Successfully.";
	delay(900);
    }
}
/************************************************************************************************************
*                                            GENERATE PAY SLIP                                              *
*************************************************************************************************************/
void sal_manage::generate_slip()
{
    int day,mon,year,mon1,days_wo_pay,x;
    char month[10];
    clrscr();
    cout<<"\nEnter the Current Date:- ";
    cout<<"\nDate: ";
    cin>>day;
    cout<<"\nMonth: ";
    cin>>mon;
    cout<<"\nYear: ";
    cin>>year;
    cout<<"\nEnter the Month For Which The Payslip is to be Generated(1-12): ";
    cin>>mon1;
    switch(mon1)
    {
    case 1:
	strcpy(month,"January");
	    break;
    case 2:
	strcpy(month,"February");
	    break;
    case 3:
	strcpy(month,"March");
	break;
    case 4:
	strcpy(month,"April");
	break;
    case 5:
	strcpy(month,"May");
	break;
    case 6:
	strcpy(month,"June");
	break;
    case 7:
	strcpy(month,"July");
	break;
    case 8:
	strcpy(month,"August");
	break;
    case 9:
	strcpy(month,"September");
	break;
    case 10:
	strcpy(month,"October");
	break;
    case 11:
	strcpy(month,"November");
	break;
    case 12:
	strcpy(month,"December");
	break;
    }
    if(mon1==1||mon1==3||mon1==5||mon1==7||mon1==8||mon1==10||mon1==12)
	x=31;
    else if(mon1==2)
    {
	if((year%4)==0)
		x=29;
	    else
		x=28;
    }
    else
	x=30;
    days_wo_pay=x-days_worked;
    clrscr();
    cout<<"\t\t\t\tPEPSI";
    cout<<"\n--------------------------------------------------------------------------------";
    cout<<"\n\nPayslip For the Month: ";
    puts(month);
    cout<<"Date: "<<day<<"/"<<mon<<"/"<<year;
    cout<<"\n\nEmployee Name: ";
    puts(empmain.sal_name);
    cout<<"\nEmployee's Designation: ";
    puts(empmain.sal_desig);
    cout<<"\nDays Worked: "<<empmain.days_worked;
    cout<<"\t\t\t\t\t\t\tDays On Leave: "<<days_wo_pay;
    cout<<"\nBasic Salary"<<"\t\t\t\t\t: Rs."<<empmain.sal_basic;
    cout<<"\nDearness Allowance(DA)"<<"\t\t\t\t: Rs."<<empmain.DA;
    cout<<"\nHouse Rent Allowance(HRA)"<<"\t\t\t: Rs."<<empmain.HRA;
    cout<<"\n\t\t\t\t\t\t-------------";
    cout<<"\n\nGROSS SALARY"<<"\t\t\t\t\t= Rs."<<empmain.gross_sal;
    cout<<"\n\t\t\t\t\t\t-------------";
    cout<<"\n\n\n\nAUTHORISED SIGINATORY";
    getch();
}
/************************************************************************************************************
*                                   PAY SLIP GENRATION OPTION IN MAIN MENU                                 *
*************************************************************************************************************/
void sal_manage::generate_main()
{
    int empno;
    char found='n',choice;
    do
    {
	clrscr();
	cout<<"\t\t\t\tPAY SLIP";
	cout<<"\nEnter the Employee Number Whose Payslip is to be Generated: ";
	cin>>empno;
	ifstream fin("Salfile.DAT",ios::in);
	if(!fin)
	   cout<<"Error In Opening File.";
	while(fin.read((char*)&empmain,sizeof(empmain)))
	{
	    if(empmain.sal_no==empno)
	    {
		 found='y';
		 empmain.generate_slip();
	    }
	    }
	    fin.close();
	    if(found=='n')
	    {
		cout<<"\nEmployee Not Found.";
		getch();
	    }
	    cout<<"\nWant to Generate Pay Slip For Any other Employee?(Y/N): ";
	    cin>>choice;
    }while(choice=='y'||choice=='Y');
}
/************************************************************************************************************
*                             CLASS CONISITING OF MEMBERS FOR Employee.DAT                                  *
*************************************************************************************************************/
class empdata:public sal_manage
{
private:
    int empno;//Employee Number For Employee.DAT
    char emp_name[20];//Employee's Name For Employee.DAT
    char emp_desig[20];//Employee's Designation For Employee.DAT
    int hs;//Employee's House No
    int ss;//Employee's Street No
    char city[20];
    char state[20];
    char mobno[10];//Employee's Mobile Number
    int day;//Date of Joining
    int month;//Date of Joining
    int year;//Date of Joining
    long emp_basic;//Employee's basic Salary For Employee.DAT
public:
    //The Following Function Gets Information for an Employee from the User
    void get_emp();
    //The Following Function Shows Information for an Employee
    void show_emp();
    //The Following Function Adds an Employee to Employee.DAT
    void add_emp();
    //The Following Function Removes an Employee from Employee.DAT
    void rem_emp();
    //The Following Function Modifies Information for an Employee in Employee.DAT and Salfile.DAT(by calling moddesig_sal() and modbasic_sal())
    void mod_emp();
    //The Following Function Searches for an Employee in Employee.DAT
    void search_emp();
}emp_derive;
/************************************************************************************************************
*                                     GETS INFORMATION FOR AN EMPLOYEE                                      *
*************************************************************************************************************/
void empdata::get_emp()
{
    cout<<"\nEnter the Employee's Name: ";
    gets(emp_name);
    cout<<"\nEnter the Employee's Designation: ";
    gets(emp_desig);
    cout<<"\nEnter Employee's Address:- ";
    cout<<"\nHouse No.: ";
    cin>>hs;
    cout<<"\nStreet No.: ";
    cin>>ss;
    cout<<"\nCity: ";
    gets(city);
    cout<<"\nState: ";
    gets(state);
    cout<<"\nEnter Employee's Contact Details: ";
    gets(mobno);
    cout<<"\nEnter the date of Joining of Employee:- ";
    cout<<"\nDate: ";
    cin>>day;
    cout<<"\nMonth: ";
    cin>>month;
    cout<<"\nYear: ";
    cin>>year;
    cout<<"\nEnter the Basic Salary(in Rs.): ";
    cin>>emp_basic;
}
/************************************************************************************************************
*                                    SHOWS INFORMATION FOR AN EMPLOYEE                                      *
*************************************************************************************************************/
void empdata::show_emp()
{
    cout<<"\nEmployee Number: "<<empno;
    cout<<"\nEmployee's Name: ";
    puts(emp_name);
    cout<<"\nEmployee's Designation: ";
    puts(emp_desig);
    cout<<"\nEmployee's Address:- ";
    cout<<"\nHouse No.: "<<hs;
    cout<<"\nStreet No.: "<<ss;
    cout<<"\nCity: ";
    puts(city);
    cout<<"\nSate: ";
    puts(state);
    cout<<"\nEmployee's Contact Details: ";
    puts(mobno);
    cout<<"\nDate of Joining(dd/mm/yyyy): "<<day<<"/"<<month<<"/"<<year;
    cout<<"\nBasic Salary OF Employee: Rs. "<<emp_basic;
}
/************************************************************************************************************
*                                   ADDITION OF EMPLOYEES IN Employee.DAT                                   *
*************************************************************************************************************/
void empdata::add_emp()
{
    clrscr();
    char ch;
    k:
    do
    {
	clrscr();
	int eno;
	char found='n';
	cout<<"\t\t\tREGISTRATION OF NEW EMPLOYEES";
	fstream file("Employee.DAT",ios::in|ios::binary);
	cout<<"\n";
	cout<<"\nEnter the Employee Number: ";
	cin>>eno;
	//The following Loop Checks Whether A Employee With the Same Employee Number Exists Already
	while(file.read((char*)&emp_derive,sizeof(emp_derive)))
	{
	    if(emp_derive.empno==eno)
	    {
		found='y';
		cout<<"\nEmployee Already Exists.Please Enter Again.";
		getch();
		goto k;
	    }
	}
	file.close();
	if(found=='n')
	{
	    ofstream fout("Employee.DAT",ios::app|ios::binary);
	    emp_derive.empno=eno;
	    get_emp();
	    fout.write((char*)&emp_derive,sizeof(emp_derive));
	    fout.close();
	    add_sal(empno,emp_name,emp_desig,emp_basic);
	    cout<<"\n\nEmployee Added Successfully.";
	    cout<<"\nWant To Add More Employees?(Y/N): ";
	    cin>>ch;
	}
    }while(ch=='Y'||ch=='y');
}
/************************************************************************************************************
*                                  REMOVAL OF EMPLOYEES FROM Employee.DAT                                   *
*************************************************************************************************************/
void empdata::rem_emp()
{
    int eno;
    char ch,confirm='y',found='n';
    do
    {
	clrscr();
	cout<<"\t\t\t\tDELETION OF EMPLOYEES";
	cout<<"\nEnter the Employee No. Whose Information is to be Removed: ";
	cin>>eno;
	ofstream fout("Temp.DAT",ios::app|ios::binary);
	ifstream fin("Employee.DAT",ios::in);
	if(!fin)
	    cout<<"\nNo Such File Exists";
	fin.seekg(ios::beg);
	while(fin.read((char*)&emp_derive,sizeof(emp_derive)))
	{
	    if(empno==eno)
	    {
		found='y';
		show_emp();
		cout<<"\n\n";
		cout<<"Confirm Delete?(Y/N): ";
		cin>>confirm;
		if(confirm=='n'||confirm=='N')
		    fout.write((char*)&emp_derive,sizeof(emp_derive));
		else
		    cout<<"\nEmployee Deleted Successfully.";
	    }
	    else
		fout.write((char*)&emp_derive,sizeof(emp_derive));
	}
	fout.close();
	fin.close();
	remove("Employee.DAT");
	rename("Temp.DAT","Employee.DAT");
	remove_sal(eno);
	if(found=='n')
	{
	    cout<<"\nEmployee Not Found.";
	    delay(500);
	}
	cout<<"\nWant to Remove More Employees?(Y/N): ";
	cin>>ch;
    }while(ch=='Y'||ch=='y');
}
/************************************************************************************************************
*                              MODIFICATION OF EMPLOYEE'S DATA IN Employee.DAT                              *
*************************************************************************************************************/
void empdata::mod_emp()
{
    int eno,choice,pos;
    char found='n',x[10];
    do
    {
	clrscr();
	cout<<"\t\t\t\t\tMODIFY MENU";
	cout<<"\n1.Change Designation";
	cout<<"\n2.Change Address";
	cout<<"\n3.Change Contact Details";
	cout<<"\n4.Change Basic Salary";
	cout<<"\n5.Exit Modify Menu";
	cout<<"\nEnter your Choice: ";
	cin>>choice;
	if(choice!=5)
	{
	    cout<<"\nEnter the Employee Number Whose Information is To Be Modified: ";
	    cin>>eno;
	    fstream fin("Employee.DAT",ios::in|ios::out);
	    if(!fin)
		cout<<"No Such File Exists";
	    fin.seekg(ios::beg);
	    while(fin.read((char*)&emp_derive,sizeof(emp_derive)))
	    {
		pos=fin.tellg();
		if(emp_derive.empno==eno)
		{
		    found='y';
		    switch(choice)
		    {
		    case 1:
			cout<<"\nEnter New Designation: ";
			gets(x);
			cout<<"\nModifications Being Done...";
			delay(700);
			cout<<"\nModifications Done.";
			getch();
			strcpy(emp_derive.emp_desig,x);
			fin.seekg(pos-sizeof(emp_derive));
			fin.write((char*)&emp_derive,sizeof(emp_derive));
			moddesig_sal(eno,emp_desig);
			break;
		    case 2:
			cout<<"\nEnter New Address:- ";
			cout<<"\nHouse No.";
			cin>>hs;
			cout<<"\nStreet No.: ";
			cin>>ss;
			cout<<"\nCity: ";
			gets(city);
			cout<<"\nState: ";
			gets(state);
			cout<<"\nModifications Being Done...";
			delay(700);
			cout<<"\nModifications Done.";
			getch();
			fin.seekg(pos-sizeof(emp_derive));
			fin.write((char*)&emp_derive,sizeof(emp_derive));
			break;
		    case 3:
			cout<<"\nEnter New Contact Details: ";
			gets(mobno);
			cout<<"\nModifications Being Done...";
			delay(700);
			cout<<"\nModifications Done.";
			getch();
			fin.seekg(pos-sizeof(emp_derive));
			fin.write((char*)&emp_derive,sizeof(emp_derive));
			break;
		    case 4:
			cout<<"\nEnter New Basic Salary: ";
			cin>>emp_basic;
			cout<<"\nModifications Being Done...";
			delay(700);
			cout<<"\nModifications Done.";
			getch();
			fin.seekg(pos-sizeof(emp_derive));
			fin.write((char*)&emp_derive,sizeof(emp_derive));
			modbasic_sal(eno,emp_basic);
			break;
		    }
			    }
		    }
		    fin.close();
		    if(found=='n')
		    {
			cout<<"\nEmployee Not Found.";
			getch();
		    }
	    }
    }while(choice!=5);
    cout<<"\nModify Session Ended.";
    delay(700);
}
/************************************************************************************************************
*                                 SEARCHING OF AN EMPLOYEE IN Employee.DAT                                  *
*************************************************************************************************************/
void empdata::search_emp()
{
    int eno,choice;
    char ename[20],found='n';
    do
    {
	clrscr();
	cout<<"\t\t\t\tSEARCH MENU";
	cout<<"\n1.Search By Employee No.";
	cout<<"\n2.Search By Employee Name: ";
	cout<<"\n3.Exit Search Menu";
	cout<<"\nEnter Your Choice: ";
	cin>>choice;
	if(choice!=3)
	{
	    switch(choice)
	    {
	    case 1:
		cout<<"\nEnter the Employee No.: ";
		cin>>eno;
		ifstream fin("Employee.DAT",ios::in);
		if(!fin)
		    cout<<"No Such File Exists";
		fin.seekg(ios::beg);
		fin.read((char*)&emp_derive,sizeof(emp_derive));
		while(!fin.eof())
		{
		    if(empno==eno)
		    {
			found='y';
			show_emp();
			getch();
		    }
		    fin.read((char*)&emp_derive,sizeof(emp_derive));
		}
		fin.close();
		break;
	    case 2:
		cout<<"\nEnter the Employee Name: ";
		gets(ename);
		ifstream fin1("Employee.DAT",ios::in);
		if(!fin1)
		    cout<<"No Such File Exists";
		fin1.seekg(ios::beg);
		fin1.read((char*)&emp_derive,sizeof(emp_derive));
		while(!fin1.eof())
		{
		    if(strcmpi(emp_name,ename)==0)
		    {
			found='y';
			show_emp();
			getch();
		    }
		    fin1.read((char*)&emp_derive,sizeof(emp_derive));
		}
		fin1.close();
		break;
	    }
	    if(found=='n')
	    {
		cout<<"Employee Not Found.";
		getch();
	    }
	}
    }while(choice!=3);
    cout<<"\n\n\nSearch Session Ended.";
    delay(700);
}
/************************************************************************************************************
*                                             WELCOME SCREEN                                                *
*************************************************************************************************************/
int welc_screen()
{
   cout<<"       	                                                             \n";delay(500);
   cout<<"         							        	\n";delay(500);
   cout<<"         			     .__.                                      \n";delay(500);
   cout<<" 	        		     !--!                                   \n";delay(500);
   cout<<"         			    !    !                                      \n";delay(500);
   cout<<"         			   !      !                               \n";delay(500);
   cout<<" 	        		  !        !                                         \n";delay(500);
   cout<<"         			 !          !                                                   \n";delay(500);
   cout<<"         			 !          !                                                   \n";delay(500);
   cout<<" 	         		 !   PEPSI  !                                                   \n";delay(500);
   cout<<"         			  !--------!                                                   \n";delay(500);
   cout<<" 	        		  !--------!                                                   \n";delay(500);
   cout<<"         			 !          !                                                   \n";delay(500);
   cout<<"         			 !          !                                                   \n";delay(500);
   cout<<" 	         		 !          !                                                   \n";delay(500);
   cout<<"         			  !________!                                                   \n"; delay(500);
   cout<<"         									               \n";delay(900);
   cout<<"\n";delay(500);
   cout<<"                   _______           _______   _______              _______ \n";delay(500);
   cout<<" \\              / |         |       |         |       |  |\\    /|  |        \n";delay(500);
   cout<<"  \\            /  |         |       |         |       |  | \\  / |  |        \n";delay(500);
   cout<<"   \\    /\\    /   |-------  |       |         |       |  |  \\/  |  |------- \n";delay(500);
   cout<<"    \\  /  \\  /    |         |       |         |       |  |      |  |       \n";delay(500);
   cout<<"     \\/    \\/     |_______  |______ |_______  |_______|  |      |  |_______ \n";delay(500);
   cout<<"\n\n\n";delay(500);
   cout<<"                                 ________   ________  \n";delay(500);
   cout<<"                                     |     |        |  \n";delay(500);
   cout<<"                                     |     |        |   \n";delay(500);
   cout<<"                                     |     |        |   \n";delay(500);
   cout<<"                                     |     |        |   \n";delay(500);
   cout<<"                                     |     |________|   \n";delay(500);
   cout<<"\n\n\n";delay(500);
   cout<<"                     _______    ________   _______   ________   *    \n";delay(500);
   cout<<"                    |       |  |          |       | |           |  \n";delay(500);
   cout<<"                    |       |  |          |       | |           |  \n";delay(500);
   cout<<"                    |_______|  |________  |_______| |________   |  \n";delay(500);
   cout<<"                    |          |          |                  |  |\n";delay(500);
   cout<<"                    |          |          |                  |  |\n";delay(500);
   cout<<"                    |          |________  |         _________|  |\n";delay(500);
   cout<<"\n";delay(500);
   cout<<"\n";delay(500);
   cout<<"\n";delay(500);
   cout<<"\n";delay(500);
   cout<<"\n";delay(500);
   gotoxy(60,25);
   cout<<"PROJECT DEVELOPED BY:";
   gotoxy(61,25);
   cout<<"HARSH GUPTA(9158246)";
   gotoxy(59,25);
   cout<<"MAYANK SHARMA(9158255)";
   delay(1000);
   return 0;
}
/************************************************************************************************************
*                                               LOGIN PAGE                                                  *
*************************************************************************************************************/
int pass()
{
    char name[5],pass[6],name1[5];
    cout<<"\n\nEnter your Name: ";
    gets(name);
    strcpy(name1,name);
    if(strcmp("harsh",name)==0)
    {
	cout<<"\nEnter Password: ";
	gets(pass);
	if(strcmp("hm1323",pass)==0)
	{
	    cout<<"\n\nAccess Granted.";
	    delay(500);
	    clrscr();
	    cout<<"\t\t\t\t\tMAIN MENU";
	    cout<<"\nWelcome ";
	    puts(name1);
	    return 1;
	}
	else
	{
	    cout<<"\nWrong Password";
	    return -1;
	}
    }
    else
    {
	cout<<"\nWrong Username";
	return -1;
    }
}
/************************************************************************************************************
*                                              MAIN FUNCTION                                                *
*************************************************************************************************************/
void main() //Consists of Main Menu and calls welc_screen() and pass()
{
    clrscr();
    int pw,ch;
    welc_screen();
    clrscr();
    cout<<"\t\t\t\t\tLOGIN PAGE";
    p:
    pw=pass();
    if(pw==1)
    {
	do
	{
	    cout<<"\n1.Register a New Employee";
	    cout<<"\n2.Remove an Employee";
	    cout<<"\n3.Modify Information About an Employee";
	    cout<<"\n4.Search For Information About an Employee";
	    cout<<"\n5.Update Salary File";
	    cout<<"\n6.Generate Pay Slip";
	    cout<<"\n7.Exit";
	    cout<<"\nEnter your Choice: ";
	    cin>>ch;
	    switch(ch)
	    {
	    case 1:
		emp_derive.add_emp();
		clrscr();
		cout<<"\t\t\t\t\tMAIN MENU";
		break;
	    case 2:
		emp_derive.rem_emp();
		clrscr();
		cout<<"\t\t\t\t\tMAIN MENU";
		break;
	    case 3:
		emp_derive.mod_emp();
		clrscr();
		cout<<"\t\t\t\t\tMAIN MENU";
		break;
	    case 4:
		emp_derive.search_emp();
		clrscr();
		cout<<"\t\t\t\t\tMAIN MENU";
		break;
	    case 5:
		empmain.update_sal();
		clrscr();
		cout<<"\t\t\t\t\tMAIN MENU";
		break;
	    case 6:
		empmain.generate_main();
		clrscr();
		cout<<"\t\t\t\t\tMAIN MENU";
		break;
	    case 7:
		clrscr();
		cout<<"\n\nYou Ended the Session.";
		delay(700);
		cout<<"\n\n\n\n\n\t\t\t\tTHANK YOU";
		delay(700);
		break;
	    }
	}while(ch!=7);
    }
    else if(pw==-1)
	goto p;
    getch();
}


