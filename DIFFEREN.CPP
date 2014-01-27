/*
DIFFERENTIATOR DEVELOPED BY M.S.ADITYAN

THE FOLLOWING PROGRAM DIFFERENTIATES EXPRESSIONS WITH RESPECT TO 'x' ONLY.
*/

#include<graphics.h>
#include<dos.h>
#include<string.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<process.h>
#include<stdlib.h>
#include<iomanip.h>
#include<fstream.h>
#include<ctype.h>

void exponential(char p[]);
void product_rule(char p[]);
void quotient_rule(char p[]);
void func_sumORdiff(char p[]);


fstream f1("master.dat",ios::in|ios::out);

int find_sumORdiff(char p[]) //checks if the input expression has two or more functions separated by +/- sign

{	int t=0;

	for(int i=0;p[i]!='\0';i++)
	{
		if(p[i]=='(')
		t++;
		if(p[i]==')')
		t--;
		if(t==0&&(p[i]=='+'||p[i]=='-'))
		return 1;

	}
	return 0;
}

void chain_rule(char p[],int r,int q) //applies chain rule for nested functions
{

	for(int i=r+q,k=0;p[i]!='\0';i++,k++)
		p[k]=p[i];        //modifies the original input expression by removing the other function and retaining the next functions

	p[k]='\0';

}

int find_x(char p[]) //finds the variable 'x'
{	for(int i=0;i<strlen(p);i++)
	if(p[i]=='x')
	return 1;
	return 0;

}

int check_bracket(char p[]) //function to check if the input expression is a valid expression
{     int flag=0,k[10];
		for(int i=0;i<strlen(p);i++)
		{
			if(p[i]=='(')
			{
				k[flag]=i;
				flag++;
			}
		else if(p[i]==')')
				flag--;

		}

		if(flag==0&&p[i-1]==')')
		{
			if(k[flag]==0)
				return 1;
			else
				return 0;
		}
		else
			return 0;

}

int search_brackets(char p[]) //counts remaining nested functions
{       int e=0;
	for(int i=0;p[i]!='\0';i++)
		if(p[i]==')')
			e++;

	return e;
}

void rectify_bracket_error(char p[])
{
start:
int e=0;
	for(int i=0;p[i]!='\0';i++)
	{
		if(p[i]=='(')
		e++;
		if(p[i]==')')
		e--;
	}

	if(e<0)
	{
		p[strlen(p)-1]='\0';
		goto start;
	}


}
void tan(char p[],int i)
{
	chain_rule(p,i,3);
	rectify_bracket_error(p);


	cout<<"(sec"<<p<<")"<<"^(2)";
	f1<<"(sec"<<p<<")"<<"^(2)";
}
void sin(char p[],int i)
{
	chain_rule(p,i,3);
	rectify_bracket_error(p);

	cout<<"(cos"<<p<<")";
	f1<<"(cos"<<p<<")";
}
void cos(char p[],int i)
{
	chain_rule(p,i,3);
	rectify_bracket_error(p);

	cout<<"(-sin"<<p<<")";
	f1<<"(-sin"<<p<<")";
	}
void cot(char p[],int i)
{
	chain_rule(p,i,3);
	rectify_bracket_error(p);

	cout<<"(-cosec^2"<<p<<")";
	f1<<"(-cosec"<<p<<")"<<"^(2)";
}
void cosec(char p[],int i)
{
	chain_rule(p,i,5);
	rectify_bracket_error(p);

	cout<<"(-cot"<<p<<")"<<"(cosec"<<p<<")";
	f1<<"(-cot"<<p<<")"<<"(cosec"<<p<<")";
}
void sec(char p[],int i)
{
	chain_rule(p,i,3);
	rectify_bracket_error(p);

	cout<<"(sec"<<p<<")"<<"(tan"<<p<<")";
	f1<<"(sec"<<p<<")"<<"(tan"<<p<<")";
}



void differentiate(char p[])
{
int k=0,m=0,y[100];
while (check_bracket(p)==1)
	{
	chain_rule(p,0,1);
	p[strlen(p)-1]='\0';
	}

for(int i=0;p[i]!='\0';i++)
	{
		if(p[i]=='l'&&p[i+1]=='o'&&p[i+2]=='g')
		{
			chain_rule(p,i,3);
			rectify_bracket_error(p);

			cout<<"1/";
			cout<<"("<<p<<")";
			f1<<"1/("<<p<<")";
			break;
		}

		else if(p[i]=='x'&&p[i+1]=='^')
		{
			rectify_bracket_error(p);

			if(m==0)
			m=1;

			i=i+2;
			int u[7],z=0;
			k=0;
				for(;;i++)
				{
					if(p[i]>=48&&p[i]<58)
					{
						u[k]=p[i]-48;
						k++;
					}
					else
						break;
				}
			k--;

				for(int r=0;k>=0;k--,r++)

				     z=z+(u[k]*pow(10,r));


			cout<<m*z<<"x^"<<z-1;
			f1<<m*z<<"x^"<<z-1;

			chain_rule(p,0,strlen(p));
			break;
			}

			else if(p[i]>=48&&p[i]<60)
			{
			y[k++]=p[i]-48;

			if((p[i+1]<48)||p[i+1]>57)
			{       k--;
				for(int r=0;k>=0;k--,r++)
				m+=(y[k]*pow(10,r));

			}



			if(p[i+1]!='x')
			cout<<"("<<m<<")";
			f1<<"("<<m<<")";


			}
			else if(p[i]=='x')
			{         if(m==0)
			m=1;
			p[i]='\0';
			cout<<"("<<1*m<<")";
			f1<<"("<<1*m<<")";

			break;
			}

		else if(p[i]=='s'&&p[i+1]=='i'&&p[i+2]=='n')
		{
			sin(p,i);
			break;
		}

		else if(p[i]=='c'&&p[i+1]=='o'&&p[i+2]=='s'&&p[i+3]=='e'&&p[i+4]=='c')
		{
			cosec(p,i);
			break;
		}

		else if(p[i]=='c'&&p[i+1]=='o'&&p[i+2]=='s')
		{
			cos(p,i);
			break;
		}

		else if(p[i]=='t'&&p[i+1]=='a'&&p[i+2]=='n')
		{
			tan(p,i);
			break;
		}

		else if(p[i]=='c'&&p[i+1]=='o'&&p[i+2]=='t')
		{
			cot(p,i);
			break;
		}

		else if(p[i]=='s'&&p[i+1]=='e'&&p[i+2]=='c')
		{
			sec(p,i);
			break;
		}

		else if(p[i]=='+'||p[i]=='-')
		{	continue;
		}

	}


}


void identify_method(char p[])

{

	while (check_bracket(p)==1)

	{
		chain_rule(p,0,1);
		p[strlen(p)-1]='\0';
	}

int e=0,flag=0;

	for(int i=0;i<strlen(p);i++)
	{
		if(p[i]=='(')
		e++;
		if(p[i]==')')
		e--;

		if((p[i-1]==')'&&p[i]=='^')&&e==0)
		{	flag=1;
			break;

		}
		if(p[i]=='*'&&e==0)
		{	flag=2;
			break;
		}
		if(p[i]=='/'&&e==0)
		{	flag=3;
			break;
		}


	}

	 if(flag==1)
	 exponential(p);

	 else  if(flag==2)
	 product_rule(p);

	 else if(flag==3)
	 quotient_rule(p);

	 else  if(flag==0)

	while(1)
	{


		if(find_x(p)==1)
				{

					if(find_sumORdiff(p)==1)
					func_sumORdiff(p);

					else
					{
					e=search_brackets(p);
					differentiate(p);
					while(check_bracket(p)==1)
						{
						     p[strlen(p)-1]='\0';
						     chain_rule(p,0,1);
						 }

					}
				}
		else
				{
					cout<<"Sorry I cannot differentiate that function!";
					e=0;
					f1<<0;
					getch();
					break;
				}

		if(e==0)
		break;
	}
}


void product_rule(char p[])
{
int e,r=0,s=0,t=0;
char variable_term[10][20];
char constant_term[10][20];

	while (check_bracket(p)==1)
	{
		chain_rule(p,0,1);

		p[strlen(p)-1]='\0';

	}

	for(int i=0;i<strlen(p);i++)
	{
		if(p[i]=='(')
			 t++;
		if(p[i]==')')
			 t--;

		 if((p[i]=='*'||p[i]=='/')&&t==0)
			{
				if(p[i]=='/')
				goto label;


				variable_term[r][s]='\0';
				strcpy(constant_term[r],variable_term[r]);
				s=0;
				r++;

			}
		else

			{
				variable_term[r][s]=p[i];
				s++;
			}
	}


	variable_term[r][s]='\0';
	strcpy(constant_term[r],variable_term[r]);
	r++;
	e=r;

		for(i=0;i<e;i++)
		{
			cout<<"(";
			f1<<"(";
			identify_method(variable_term[i]);
			cout<<")";
			f1<<")";
				for(int j=0;j<e;j++)
				if(j!=i)
				{
					cout<<"*("<<constant_term[j]<<")";
					f1<<"*("<<constant_term[j]<<")";

				}
			 if(i!=e-1)
			 cout<<"+";
			 f1<<"+";
		}
label:
	if(p[i]=='/')
	quotient_rule(p);



}
void quotient_rule(char p[])
{       int e,k=0;
	char ch1[20],ch2[20],ch3[20],ch4[20];
	for(int i=strlen(p)-1;i>=0;i--)
	{	if(p[i]=='/')
		{	e=i;
			break;
		}
	}

		for(i=0;i<e;i++)
		ch1[i]=p[i];

	ch1[i]='\0';

		for(i=e+1;i<strlen(p);k++,i++)
		ch2[k]=p[i];

	ch2[k]='\0';

	strcpy(ch3,ch1);
	strcpy(ch4,ch2);

	if(find_x(ch1)==1)
	{
		cout<<"[(";
		f1<<"((";

		identify_method(ch1);

		cout<<"*("<<ch2<<"))-(";
		f1<<"*("<<ch2<<"))-(";

		identify_method(ch2);

		cout<<"*("<<ch3<<"))]/("<<ch4<<")^2";
		f1<<"*("<<ch3<<")))/("<<ch4<<")^2";
	}

	else if(find_x(ch1)==0)
	{
		cout<<"[0 -(";
		f1<<"0";

		identify_method(ch2);

		cout<<"*("<<ch3<<"))]/("<<ch4<<")^2";
		f1<<"*("<<ch3<<")))/("<<ch4<<")^2";
	}
}
void exponential(char p[])
{
int e,k=0;

while (check_bracket(p)==1)
{
	chain_rule(p,0,1);
	p[strlen(p)-1]='\0';

}


char ch1[20],ch2[20],ch3[20],ch4[20];


	for(int i=strlen(p)-1;i>=0;i--)
	{

		if(p[i-1]==')'&&p[i]=='^')
		{
			e=i;
			break;
		}
	}

	for(i=0;i<e;i++)
	ch1[i]=p[i];

	ch1[i]='\0';

	for(i=e+1;i<strlen(p);k++,i++)
	ch2[k]=p[i];

	ch2[k]='\0';
	strcpy(ch3,ch1);
	strcpy(ch4,ch2);

	cout<<"("<<p<<")*((";
	f1<<"("<<p<<")*((";

	identify_method(ch2);

	cout<<")*(log"<<ch1<<")+(";
	f1<<")*(log"<<ch1<<")+(";

	identify_method(ch1);

	cout<<"*"<<ch4<<")/"<<ch3<<"))";
	f1<<"*"<<ch4<<")/"<<ch3<<"))";
}
void func_sumORdiff(char p[])
{
char hold_func[20][20],hold_operator[10];
int q=0,u=0;

	while (check_bracket(p)==1)
	{
		chain_rule(p,0,1);

		p[strlen(p)-1]='\0';


	}


	for(int i=0,k=0;p[i]!='\0';i++)
	{
	     if(p[i]=='(')
		u++;
	     if(p[i]==')')
		u--;
	     if((p[i]=='+'||p[i]=='-')&&u==0)

		{

			hold_operator[q]=p[i];
			hold_func[q][k]='\0';
			q++;
			k=0;

		}
	     else
		{
			hold_func[q][k]=p[i];
			k++;
		}
	}


hold_func[q][k]='\0';
q++;

cout<<"(";
f1<<"(";

	for(i=0;i<q;i++)
	{
		identify_method(hold_func[i]);
			if(i!=q-1)
			{
				cout<<hold_operator[i];
				f1<<hold_operator[i];
			}
	}

cout<<")";
f1<<")";

}


void differentiator_startup()
{

   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   initgraph(&gdriver,&gmode,"C:\\TurboC++\\Disk\\TurboC3\\bgi");
   errorcode = graphresult();

   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

   midx = getmaxx() / 2;
   midy = getmaxy() / 2;

char msg[20]="DIFFERENTIATOR",msg1[50]="DEVELOPED BY M.S.ADITYAN";

setcolor(LIGHTRED);
settextstyle(0,0,5);
outtextxy(40,midy-50,msg);

setcolor(WHITE);
settextstyle(0,0,2);
outtextxy(midx-90,midy,msg1);

settextstyle(0,0,1);
outtextxy(midx-80,midy+70,"Press any key to continue...");

getch();
}

void instructions()
{

  /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   initgraph(&gdriver,&gmode,"C:\\TurboC++\\Disk\\TurboC3\\bgi");
   errorcode = graphresult();

   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }


  cout<<"\n\n\n\n\n\n\n\t> THIS PROGRAM DIFFERENTIATES FUNCTIONS WITH RESPECT TO 'X' ONLY.";
  cout<<"\n\t> INVERSE TRIGONOMETRIC FUNCTIONS ARE NOT DIFFERENTIATED.";
  cout<<"\n\t> PLEASE USE APPROPRIATE BRACKETS WHERE EVER REQUIRED \n\t  IN THE INPUT EXPRESSION.";
  cout<<"\n\t> PLEASE NOTE THAT A WRONG INPUT EXPRESSION MAY RESULT IN AN ERROR.";
  cout<<"\n\n  LIST OF MAIN ALGORITHMS USED IN THIS PROGRAM ARE...";
  cout<<"\n  1.CHAIN RULE TO DIFFERENTIATE NESTED FUNCTIONS.";
  cout<<"\n  2.PRODUCT RULE TO DIFFERENTIATE PRODUCT OF TWO OR MORE FUNCTIONS.";
  cout<<"\n  3.QUOTIENT RULE TO DIFFERENTIATE FUNCTION DIVIDED BY ANOTHER FUNCTION.";
  cout<<"\n  4.EXPONENTIAL ALGORITHM TO DIFFERENTIATE FUNCTION TO THE POWER OF FUNCTION.";
  cout<<"\n\n\tFOR EXAMPLE: IF THE USER ENTERED THE FOLLOWING FUNCTION...";
  cout<<"\n\tsin(tan(log(x^2)))";
  cout<<"\n\tTHE DIFFERENTIAL WOULD BE...";
  cout<<"\n\tcos(tan(log(x^2)*sec^2(log(x^2)*(1/(x^2))*(2x^1)";

  cout<<"\n\n\n\n\t\t\t\t\tPRESS ANY KEY TO CONTINUE...";
 settextstyle(0,0,4);
 setcolor(LIGHTRED);

 outtextxy((getmaxx()/2)-300, (getmaxy()/2)-170, "* DIFFERENTIATOR *");

 getch();

clearviewport();
cleardevice();

closegraph();

}

void loading()
{

  /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   initgraph(&gdriver,&gmode,"C:\\TurboC++\\Disk\\TurboC3\\bgi");
   errorcode = graphresult();

   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

 clearviewport();
 cleardevice();

 setfillstyle(SOLID_FILL,BLACK);
 setcolor(RED);

 int midx=0, midy=0,midx1=0,midx2=0,midx3=0,midy1=0,midy2=0,midy3=0;

	midx = (getmaxx()/ 2)-90;
	midy = (getmaxy()/ 2)-95;

	{
		settextstyle(0,0,3);
		outtextxy(midx-120,midy, "DIFFERENTIATING...");
	}



	midx = (getmaxx() / 2);
	midy = (getmaxy() / 2);

	 circle(midx, midy, 10);
		{
		 floodfill(midx,midy,RED);
		 delay(1000);
		}

	midx1 = (getmaxx() / 2)-20;
	midy1 = (getmaxy() / 2+20);

	 circle(midx1, midy1, 10);
		{
		 floodfill(midx1,midy1,RED);
		 delay(1000);
		}

	midx2 = (getmaxx() / 2);
	midy2 = (getmaxy() / 2)+40;

	 circle(midx2, midy2, 10);
		{
		 floodfill(midx2,midy2,RED);
		 delay(1000);
		}

	midx3 = (getmaxx() / 2)+20;
	midy3 = (getmaxy() / 2)+20;

	 circle(midx3, midy3, 10);
		{
		 floodfill(midx3,midy3,RED);
		 delay(1000);
		}

	settextstyle(0,0,1);
		outtextxy(midx-90,midy+70, "PRESS ENTER TO CONTINUE");

getch();

clearviewport();

closegraph();

}


void main()
{
	clrscr();
	differentiator_startup();
	instructions();
	char expression[50],choice;

	do
	{
		cout<<"\n\n Enter the expression you want me to differentiate ";
		cin>>expression;

		loading();

		cout<<"\n\n\tTHE DIFFERENTIAL OF THE EXPRESSION\n\t"<<expression<<" with respect to 'x' is...\n\n\t";

		identify_method(expression);

		f1<<".";

		cout<<"\n\n\n Do you want to differentiate again...? Y/N";
		cin>>choice;
		clrscr();
		f1.close();
	}while (choice=='y' || choice=='Y');

cout<<"\nBye bye!";
getch();
}

