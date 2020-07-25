#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<process.h>

//******************************* CLASSES *****************************//                             

//-------------------CLASS TO STORE USER DETAILS IN A FILE------------------//
class users
{
	char name[20],pass[20];
	public:
	void getuser(char n[20],char p[20])                            //Function to input details
	{      strcpy(name,n);
	        strcpy(pass,p);
	}
	int checkpass(char p[20])                                             //Function to check password
	{           if(strcmp(p,pass)==0)
		return 1;
		return 0;
	}
             int checkname(char n[20]) //Function to check username
             {      if (strcmp(n,name)==0)
	        return 1;
	        return 0;
	 }
};
//--------------CLASS TO STORE QUESTIONS AND THEIR ANSWERS IN A FILE-------------//
class qna
{      int serial; //Serial no. of the current question
       int count;  //Serial no. of the answer of the question
       char ques[80],ans[5][80];
       public:
       qna()
       {    serial=0;
            count=0;
            strcpy(ques,"\0");
            strcpy(ans[0],"\0");
            strcpy(ans[1],"\0");
            strcpy(ans[2],"\0");
            strcpy(ans[3],"\0");
            strcpy(ans[4],"\0");
}
void showques()                                                 //Function to displays question
{     cout<<endl<<"Question "<<serial<<":"<<ques<<endl;
}
void showans()                                                    //Function to display it's answers
{	showques();
	cout<<endl;
	if (count==0)
	{        cout<<"NO ANSWERS AVAILABLE"<<endl;
	}
	else
	for (int i=0;i<count;i++)
	cout<<"Answer "<<i+1<<":"<<ans[i]<<endl;
 }
 void getques(int serial1)                                              //Function to ask for a question
 {	cout<<endl<<"Enter your question " <<endl;
	gets(ques);
	serial=serial1;
 }
 void getans()                                                                  //Function to ask for an answer
  {	cout<<endl<<"Enter your answer "<<endl;
	gets(ans[count++]);
}
int getserial()                                                                  //Function to return the value of serial no.
{    return serial;
}
int getcount()
{     return count;
}
void removeanswer(int serial)                                        //Function to remove answers as admin
{      for(int i=serial-1;i<count;i++)
       {	strcpy(ans[i],ans[i+1]);
       }
         count--;
      }
      void decreaseserial()                                //Function to maintain the serial order of answers
      {    serial--;
      }
};
//********************* THANK YOU AND WELCOME SCREENS *******************//

void welcome()
{       gotoxy(0,0);
        cout<<"////////////////////////////////////////////////////////////////"<<endl;
cout<<"/                                                                                                                 /"<<endl;
cout<<"/                                                                                                                 /"<<endl;
cout<<"/                          _________________________                                /"<<endl;
cout<<"/                         | WELCOME TO Q-n-A PORTAL |                              /"<<endl;
cout<<"/                         |_________________________|                             /"<<endl;
cout<<"/                     ___________________________________               /"<<endl;
cout<<"/                    | A FORUM FOR QUESTIONS AND ANSWERS |           /"<<endl;
cout<<"/                    |___________________________________|            /"<<endl;
cout<<"/                                                                                                                 /"<<endl;
cout<<"/                                                                                                                 /"<<endl;
cout<<"////////////////////////////////////////////////////////////////////"<<endl;
getch();
}

void thanks()
{   clrscr();
     cout<<"///////////////////////////////////////////////////////////////////"<<endl;
     cout<<"/                                                                                                             /"<<endl;
     cout<<"/                     -----------------------------------                                        /"<<endl;
     cout<<"/                    |    THANK YOU FOR VISITING    |                              /"<<endl;
     cout<<"/                     -----------------------------------                                        /"<<endl;
     cout<<"/                                                                                                             /"<<endl;
     cout<<"/                                                                                                             /"<<endl;
     cout<<"//////////////////////////////////////////////////////////////////"<<endl;
}
//*************************** ADMIN FUNCTIONS **************************//	                                 
//------------------FUNCTION TO ASK ADMIN PASSWORD FROM USER------------------//
void pass()
{	int i,k=3;
	char n[20];
	attempt:                                   //For giving multiple tries to enter password
	i=0;
	cout<<endl<<"NO. OF ATTEMPTS LEFT: "<<k<<endl;
	cout<<endl<<"ENTER PASSWORD: ";
	do
	{        n[i]=getch();
	          cout<<"*";
	          if (n[i]==13 ||n[i]==27)
                       break; i++;
	} while(1);
	n[i]='\0';
	if (strcmp(n,"passwordqwert")==0)
	{ 	cout<<endl<<"VALID"<<endl;
		getch();
		clrscr();
	}
	else
	{      k--;
	       cout<<endl<<"INVALID"<<endl;
	       if(k)
	       {	cout<<endl<<"PRESS ANY KEY TO TRY AGAIN"<<endl;
		getch();
		clrscr();
		goto attempt;
	       }
	       clrscr();
	       cout<<endl<<"NO. OF ATTEMPTS LEFT: 0"<<endl;
	       cout<<endl<<"UNAUTHORISED ENTRY"<<endl;
	       getch();
	       exit(0);
         }
}
//-------------------FUNCTION TO REMOVE QUESTIONS AS ADMIN--------------------//
void remove(int cat, int serial)
{   qna s;
     ifstream f1("Sci.dat", ios::binary );
     ifstream f2("Art.dat", ios::binary );
     ifstream f3("Soc.dat", ios::binary );
     ofstream t1("Sci2.dat", ios::binary| ios::app );
     ofstream t2("Art2.dat", ios::binary| ios::app );
     ofstream t3("Soc2.dat", ios::binary| ios::app );
     if (cat==1)
     {	while(f1.read((char*)&s,sizeof(qna)))
	{	if(!(s.getserial()==serial))
		{	if(s.getserial()>serial)
			s.decreaseserial();
			t1.write((char*)&s,sizeof(qna));
		}
	}
	f1.close();
	t1.close();
	remove("Sci.dat");
	rename("Sci2.dat","Sci.dat");
     }
     if (cat==2)
     {    while(f2.read((char*)&s,sizeof(qna)))
          {  	if(!(s.getserial()==serial))
		{	if(s.getserial()>serial)
			s.decreaseserial();
			t2.write((char*)&s,sizeof(qna));
		}
	}
	f2.close();
	t2.close();
	remove("Art.dat");
	rename("Art2.dat","Art.dat");
     }
     if (cat==3)
     {	while(f3.read((char*)&s,sizeof(qna)))
	{	if(!(s.getserial()==serial))
		{	if(s.getserial()>serial)
			s.decreaseserial();
			t3.write((char*)&s,sizeof(qna));
		}
	}
	f3.close();
	t3.close();
	remove("Soc.dat");
	rename("Soc2.dat","Soc.dat");
     }
}
//--------------------FUNCTION TO REMOVE ANSWERS AS ADMIN-------------------//
void remove(int cat, int serial1, int serial2)
{   qna s;
    ifstream f1("Sci.dat", ios::binary );
    ifstream f2("Art.dat", ios::binary );
    ifstream f3("Soc.dat", ios::binary );
   ofstream t1("Sci2.dat", ios::binary );
   ofstream t2("Art2.dat", ios::binary );
   ofstream t3("Soc2.dat", ios::binary );
   if (cat==1)
   {	while(f1.read((char*)&s,sizeof(qna)))
	{            if(s.getserial()==serial1)
		{  s.removeanswer(serial2);
		}
		t1.write((char*)&s,sizeof(qna));
	}
	f1.close();
	t1.close();
	remove("Sci.dat");
	rename("Sci2.dat","Sci.dat");
   }
   if (cat==2)
   {    while(f2.read((char*)&s,sizeof(qna)))
        {	if(s.getserial()==serial1)
	{ s.removeanswer(serial2);
	}
	t2.write((char*)&s,sizeof(qna));
        }
        f2.close();
        t2.close();
        remove("Art.dat");
        rename("Art2.dat","Art.dat");
   }
   if (cat==3)
   {    while(f3.read((char*)&s,sizeof(qna)))
        {	if(s.getserial()==serial1)
	{    s.removeanswer(serial2);
	}
	t3.write((char*)&s,sizeof(qna));
        }
        f3.close();
        t3.close();
        remove("Soc.dat");
        rename("Soc2.dat","Soc.dat");
   }
}
//------------------FUNCTION TO WORK AS ADMIN------------------//
void admincategory(int a,int cat)
{    int c=0;
     int serial1,serial2;                                      //Serial no of questions and answers respectively
     char head[10][30];                                    //For Heading
     strcpy(head[0],"SCIENCE AND TECHNOLOGY");
     strcpy(head[1],"ARTS");
     strcpy(head[2],"SOCIETY AND RELATIONSHIPS");
     qna s;
     ifstream f1("Sci.dat", ios::binary);
     ifstream f2("Art.dat", ios::binary);
     ifstream f3("Soc.dat", ios::binary);
     gotoxy(30,5);
     cout<<head[cat-1]<<endl;
     if (cat==1)
     while(f1.read((char*)&s,sizeof(qna)))
     {	s.showques();
             c++;
     }
     if (cat==2)
     while(f2.read((char*)&s,sizeof(qna)))
     {       s.showques();
             c++;
     }
     if (cat==3)
     while(f3.read((char*)&s,sizeof(qna)))
     {	s.showques();
             c++;
     }
     f1.close();
     f2.close();
     f3.close();
     if (c==0)
     {	cout<<endl<<"NO QUESTIONS AVAILABLE"<<endl;
	getch();
             clrscr();
     }
     if (a==1 && c>0)
     {	cout<<endl<<"Enter serial no. of question to be removed: ";
	cin>>serial1;
	remove(cat,serial1);
	clrscr();
	cout<<endl<<"Question succesfully removed"<<endl;
	getch();
             clrscr();
     }
     if (a==2 && c>0)
     {	f1.open("Sci.dat", ios::binary);
	f2.open("Art.dat", ios::binary);
	f3.open("Soc.dat", ios::binary);
	int count;
	cout<<endl<<"Choose question to delete answer from: ";
	cin>>serial1;
	clrscr();
	if (cat==1)
	{   while(f1.read((char*)&s,sizeof(qna)))
	     if (s.getserial()==serial1)
	     {	s.showans();
		count=s.getcount();
	     }
	}
	if (cat==2)
	{    f2.seekg(0);
	      while(f2.read((char*)&s,sizeof(qna)))
	      if (s.getserial()==serial1)
	      { 	s.showans();
		count=s.getcount();
	      }
	}
	if (cat==3)
	{    f3.seekg(0);
	     while(f3.read((char*)&s,sizeof(qna)))
	      if(s.getserial()==serial1)
	      {	s.showans();
		count=s.getcount();
                    }
	}
	if (count>0)
	{	cout<<endl<<"Enter serial no. of answer to be removed: ";
		cin>>serial2;
		remove(cat,serial1,serial2);clrscr();
		cout<<endl<<"Answer succesfully removed"<<endl;
		getch();
                          clrscr();
	}
	else
	{	getch();
                           clrscr();
	}
	f1.close();
	f2.close();
	f3.close();
     }
}
//----------------------FUNCTION TO LOGIN AS AN ADMIN-----------------------//
void admin()
{     pass();                                                    //Checking for admin password
      int ch,ch1;
      do
      {	gotoxy(30,5);
	cout<<"ADMIN MENU";
	gotoxy(28,7);
	cout<<"CHOOSE ACTION"<<endl;
	cout<<endl<<"1. REMOVE QUESTIONS"<<endl;
	cout<<endl<<"2. REMOVE ANSWERS"<<endl;
	cout<<endl<<"3. EXIT"<<endl;
	cout<<endl<<"ENTER YOUR CHOICE: ";
	cin>>ch;
	switch(ch)
	{  case 1: {   clrscr();
		        cout<<endl<<"CHOOSE CATEGORY TO REMOVE QUESTION:"<<endl;
		        cout<<endl<<"1.SCIENCE AND TECHNOLOGY"<<endl;
		        cout<<endl<<"2.ARTS"<<endl;
		        cout<<endl<<"3.SOCIETY AND RELATIONSHIPS"<<endl;
		        cout<<endl<<"ENTER YOUR CHOICE: ";
		        cin>>ch1;
		        clrscr();
		        admincategory(1,ch1);
		        break;          }
	    case 2: {   clrscr();
		        cout<<endl<<"CHOOSE CATEGORY TO REMOVE ANSWER:"<<endl;
		        cout<<endl<<"1.SCIENCE AND TECHNOLOGY"<<endl;
		        cout<<endl<<"2.ARTS"<<endl;
		        cout<<endl<<"3.SOCIETY AND RELATIONSHIPS"<<endl;
		        cout<<endl<<"ENTER YOUR CHOICE: ";
		        cin>>ch1;
		        clrscr();
		        admincategory(2,ch1);
		        break;          }
	    case 3: {   clrscr();
                                   break;          }
	    default:    cout<<endl<<"INVALID CHOICE"<<endl;break;
	}
      } while(ch!=3);
}
//*************************** USER FUNCTIONS ***************************//

//---------------------FUNCTION TO VIEW ANSWERS----------------------//
void viewans(int a)
{      qna s;
        int serial;
        ifstream f1("Sci.dat", ios::binary);
        ifstream f2("Art.dat", ios::binary);
        ifstream f3("Soc.dat", ios::binary);
        cout<<endl<<"Enter serial no. of question: ";
        cin>>serial;
        clrscr();
        if (a==1)
        {	while(f1.read((char*)&s,sizeof(qna)))
	if (s.getserial()==serial)
	s.showans();
        }
        if (a==2)
        {	while(f2.read((char*)&s,sizeof(qna)))
	if(s.getserial()==serial)
	s.showans();
        }
        if (a==3)
        {	while(f3.read((char*)&s,sizeof(qna)))
	if(s.getserial()==serial)
	s.showans();
        }
        getch();  clrscr();
        f1.close();
        f2.close();
        f3.close();
}
//---------------------FUNCTION TO POST ANSWERS---------------------//
void postans(int a)
{     qna s,t;
       int serial;
       ifstream f1("Sci.dat", ios::binary);
       ifstream f2("Art.dat", ios::binary);
       ifstream f3("Soc.dat", ios::binary);
       cout<<endl<<"Enter serial no. of question: ";
      cin>>serial;
      if (a==1)
      {	while(f1.read((char*)&s,sizeof(qna)))
	if(s.getserial()==serial)
	t=s;
      }
      if (a==2)
      {	while(f2.read((char*)&s,sizeof(qna)))
	if(s.getserial()==serial)
	t=s;
      }
      if (a==3)
      {	while(f3.read((char*)&s,sizeof(qna)))
	if(s.getserial()==serial)
	t=s;
      }
      f1.close();
      f2.close();
      f3.close();
      ofstream t1("Sci.dat", ios::binary| ios::ate);
      ofstream t2("Art.dat", ios::binary| ios::ate);
      ofstream t3("Soc.dat", ios::binary| ios::ate);
      clrscr();
      t.getans();
      if (a==1)
      {	t1.seekp((serial-1)*sizeof(qna),ios::beg);
	t1.write((char*)&t,sizeof(qna));
      }
      if (a==2)
      {	t2.seekp((serial-1)*sizeof(qna),ios::beg);
	t2.write((char*)&t,sizeof(qna));
      }
      if(a==3)
      {	t3.seekp((serial-1)*sizeof(qna),ios::beg);
	t3.write((char*)&t,sizeof(qna));
      }
      clrscr();
      t1.close();
      t2.close();
      t3.close();
}
/------------------------FUNCTION TO VIEW QUESTIONS----------------------//
void viewques(int a)
{     qna s;
      int ch1,serial;
      char cat[10][30];                                                                    //For Heading
      strcpy(cat[0],"SCIENCE AND TECHNOLOGY");
      strcpy(cat[1],"ARTS");
      strcpy(cat[2],"SOCIETY AND RELATIONSHIPS");
      do
      {      int c=0;
	gotoxy(30,5);
	cout<<cat[a-1]<<endl;
	ifstream f1("Sci.dat", ios::binary);
	ifstream f2("Art.dat", ios::binary);
	ifstream f3("Soc.dat", ios::binary);
	if (a==1)
	while(f1.read((char*)&s,sizeof(qna)))
	{       s.showques();
                      c++;
	}
	if (a==2)
	while(f2.read((char*)&s,sizeof(qna)))
	{       s.showques();
                      c++;
	}
	if(a==3)
	while(f3.read((char*)&s,sizeof(qna)))
	{        s.showques();
                      c++;
	}
	f1.close();
	f2.close();
	f3.close();
	if(c==0)
	cout<<endl<<"NO QUESTIONS TO DISPLAY"<<endl;
	cout<<endl<<"1. ANSWER QUESTION";
	if(c==0)
	cout<<" (Unavailable) ";
	cout<<endl<<endl<<"2. VIEW EXISTING ANSWERS";
	if(c==0)
	cout<<" (Unavailable)";
	cout<<endl<<"3. RETURN TO MENU"<<endl;
	cout<<endl<<"ENTER CHOICE"<<endl;
	cin>>ch1;
	switch(ch1)
	{    case 1:    {    if(c==0)
		              {    clrscr();
                                              break;   }
		              postans(a);
                                        break;
                                   }
	      case 2:    {   if(c==0)
		             {     clrscr();
                                              break;   }
		             viewans(a);
                                        break;
	      case 3:    {   clrscr();
                                        break;    }
	      default:   {   clrscr();
                                         cout<<endl<<"INVALID CHOICE"<<endl;
                                         break;   }
	}
      } while(ch1!=3);
}
//---------------------FUNCTION TO CALCULATE  SERIAL NO.----------------------//
int calserial(int a)
{       qna s;
        int serial=1;
        ifstream f1("Sci.dat", ios::binary);
        ifstream f2("Art.dat", ios::binary);
        ifstream f3("Soc.dat", ios::binary);
        if (a==1)
        {      while(f1.read((char*)&s,sizeof(qna)))
                serial++;             }
        if (a==2)
        {      while(f2.read((char*)&s,sizeof(qna)))
                serial++;             }
        if(a==3)
        {      while(f3.read((char*)&s,sizeof(qna)))
                serial++;             }
        return serial;
}
//---------------------FUNCTION TO POST QUESTIONS-------------------- //
void postques(int a)
{       int serial;
        qna s;
        //Opening files to read/write questions/answers
        ofstream f1("Sci.dat", ios::binary | ios::app);
        ofstream f2("Art.dat", ios::binary | ios::app);
        ofstream f3("Soc.dat", ios::binary | ios::app);
        serial=calserial(a);
        if (serial==6)
        {      clrscr();
                cout<<endl<<"CATEGORY FULL. CAN'T ADD MORE QUESTIONS"<<endl;
                getch();
                clrscr();                }
        else
        {      s.getques(serial);
                if(a==1)
                f1.write((char*)&s,sizeof(qna));
                if(a==2)
                f2.write((char*)&s,sizeof(qna));
                if(a==3)
                f3.write((char*)&s,sizeof(qna));
                clrscr();
        }
        f1.close();
        f2.close();
        f3.close();
}
//-----------------------FUNCTION TO WORK AS USER-------------------------//
void category(int a)
{       char cat[10][30];  //For Heading
        strcpy(cat[0],"SCIENCE AND TECHNOLOGY");
        strcpy(cat[1],"ARTS");
        strcpy(cat[2],"SOCIETY AND RELATIONSHIPS");
        qna s;
        //Opening files to read/write questions/answers
        fstream f1("Sci.dat", ios::binary | ios::in | ios::out);
        fstream f2("Art.dat", ios::binary | ios::in | ios::out);
        fstream f3("Soc.dat", ios::binary | ios::in | ios::out);
        int ch;
        do
        {       gotoxy(30,5);
	   cout<<cat[a-1]<<endl;
	   cout<<endl<<"1.VIEW EXISTING QUESTIONS"<<endl;
	   cout<<endl<<"2.POST A QUESTION"<<endl;
	   cout<<endl<<"3.EXIT"<<endl;
	   cout<<endl<<"ENTER YOUR CHOICE: ";
	   cin>>ch;
	   clrscr();
	   gotoxy(30,5);
	   cout<<cat[a-1]<<endl;
	   switch(ch)
	   {    case 1:     {     viewques(a);
                                              break;     }
	        case 2:     {     postques(a);
                                             break;      }
	        case 3:     {      clrscr();
                                              break;     }
	        default:    {     clrscr();
	                                cout<<endl<<"INVALID CHOICE"<<endl;
                                             break;      }
                }
        } while(ch!=3);
        f1.close();
        f2.close();
        f3.close();
}
//---------------------FUNCTION TO LOGIN AS A USER----------------------//
void user()
{     ifstream f("Users.dat",ios::binary);                        //Opening file to match details of user
      users s;
      int ch,i=0,flag=0;
      char n[20],p[20];
      gotoxy(30,5);
      cout<<"USER MENU"<<endl;
      cout<<endl<<"ENTER USERNAME: ";
      gets(n);
      cout<<endl<<"ENTER PASSWORD: ";
      while(1)                                                                        //For asking password
       {	p[i]=getch();
	cout<<"*";
	if(p[i]==13 || p[i]==27)
	break;
	i++;
       }
       p[i]='\0';
       f.seekg(0);
       while(f.read((char*)&s,sizeof(users)))                                         //For checking user details
       {       if (s.checkname(n)==1 && s.checkpass(p)==1)
               flag=1;
       }
       if (flag==0)
      {	cout<<endl<<"INVALID LOGIN DETAILS";
	getch();
	clrscr();
      }
      else
      {	cout<<endl<<"SUCCESFULLY LOGGED IN";
	getch();
	clrscr();
	do
	{       gotoxy(30,5);
	        cout<<"USER MENU";
	        gotoxy(27,7);
	        cout<<"CHOOSE CATEGORY"<<endl;
                     cout<<endl<<"1.SCIENCE AND TECHNOLOGY"<<endl;
	        cout<<endl<<"2.ARTS"<<endl;
	        cout<<endl<<"3.SOCIETY AND RELATIONSHIPS"<<endl;
	        cout<<endl<<"4.EXIT"<<endl;
	        cout<<endl<<"ENTER YOUR CHOICE: ";
	        cin>>ch;
	        switch(ch)
	        {	case 1:   {    clrscr();
                                                category(1);
                                                break;     }
                           case 2:   {    clrscr();
                                                category(2);
                                                break;     }
                           case 3:   {    clrscr();
                                                category(3);
                                                break;     }
		case 4:   {    clrscr();
                                                break;     }
		default:  {    clrscr();
                                                cout<<endl<<"INVALID CHOICE"<<endl;
                                                break;     }
	        }
	} while(ch!=4);
      }

//********************* FUNCTIONS TO CREATE USER ID *******************//

//-------------------FUNCTION TO CHECK DUPLICATE USERNAME---------------------//
int check(char n[ ])
{	fstream f;
	f.open("Users.dat", ios::in|ios::binary);
	users s;
	f.seekg(0, ios::beg);
	while(f.read((char*)&s,sizeof(users))) //Checking for duplicates
	{    if (s.checkname(n)==1)
	     {	cout<<endl<<"Username already exists"<<endl;
		return 0;
	     }
	}
	return 1;
}
//-------------------------- FUNCTION TO REGISTER AS A USER----------------------//
void create()
{	fstream f;	                                        //Opening file to store the details
	users s;
	char n[20],p[20];                                    //Details asked from user
	retry:                                                         //To start again in case of duplicate
	f.open("Users.dat", ios::app|ios::binary);
	gotoxy(25,5);
	cout<<"REGISTER AS A USER:"<<endl;
	cout<<endl<<"ENTER USERNAME: ";
	gets(n);
	if (check(n)==1)
	{	cout<<endl<<"ENTER PASSWORD: ";
	             gets(p);
	             s.getuser(n,p);
	             f.write((char*)&s,sizeof(users));
	             cout<<endl<<"SUCCESFULLY REGISTERED"<<endl;
	             getch();
	}
	else
	{       f.close();
	        getch();  clrscr();
	        goto retry;
	}
             clrscr();
             f.close();
}

//***************************** MAIN MENU ***************************//
void main()
{      welcome();
        clrscr();
        int ch;
        do
        {	gotoxy(30,5);
	cout<<"Q-n-A PORTAL";
	gotoxy(31,7);
	cout<<"MAIN MENU"<<endl;
	cout<<endl<<"1.USER LOGIN"<<endl;
	cout<<endl<<"2.ADMIN LOGIN"<<endl;
	cout<<endl<<"3.CREATE USER ID"<<endl;
	cout<<endl<<"4.EXIT"<<endl;
	cout<<endl<<"ENTER YOUR CHOICE: ";
	cin>>ch;
	switch(ch)
	{           case 1:   {     clrscr();
			        user();
		        	        break;      }
                          case 2:   {     clrscr();
			        admin();
		        	        break;      }
		case 3:   {     clrscr();
			        create();
		        	        break;      }
		case 4:   {     clrscr();
		        	        break;      }
		default:  {    clrscr();
			        cout<<endl<<"INVALID CHOICE. RETRY."<<endl;
		        	        break;      }					  
	}
        } while(ch!=4);
        thanks();
        getch();
}
