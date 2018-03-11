#include <iostream>
#include <queue>
#include<stdlib.h>
#include<unistd.h>
#include<sstream>

using namespace std;

class DFA
{
public:

  string dfa_name, i_name[40], name, state = "nf";
  int N_O_input, N_O_state, arr[90][40];
};

class state_name:public DFA
{
public:
  DFA obj[90];

  void init ();
  void create ();
  bool Replace (string);
  void inserVal ();
  bool Isvalid (string);
  int interpret (string);
  int select_two ();

};


class stropr
{
private:
  string n1, n2, n;

public:
  stropr (string s, string s1, string s2)
  {
    n = s;
    n1 = s1;
    n2 = s2;
  }
  string str ()
  {
    return n;
  }

  string str1 ()
  {
    return n1;
  }

  string str2 ()
  {
    return n2;
  }

};

state_name D[90];
int coun = 0, counU = 0;
string adi[50];

bool
Isper (string temp)
{
  for (int i = 0; i < counU; i++)
    {
      if (adi[i] == temp)
	return false;
    }
  return true;
}

void
Intersection (int na1, int na2)
{
  for (int i = 0; i < D[na1].N_O_state; i++)
    {
      for (int j = 0; j < D[na2].N_O_state; j++)
	{
	  if (D[na1].obj[i].state == "f" && D[na2].obj[j].state == "f")
	    {
	      //cout<<D[na1].obj[i].name + D[na2].obj[j].name<<"   ";
	      string temp = D[na1].obj[i].name + D[na2].obj[j].name;
	      int ch = D[coun].interpret (temp);
	      if (ch != -1)
		D[coun].obj[ch].state = "f";
	    }
	}
    }
  int c = 0;
  cout << "\n\t\tWant to save this whole DFA (if (0/1))";
  cin >> c;
  if (c == 1)
    {
      D[coun].dfa_name += "_Intersection";
      coun++;
    }
}

void
Minus (int na1, int na2)
{
  for (int i = 0; i < D[na1].N_O_state; i++)
    {
      for (int j = 0; j < D[na2].N_O_state; j++)
	{
	  if (D[na1].obj[i].state == "f" && D[na2].obj[j].state == "nf")
	    {
	      //cout<<D[na1].obj[i].name + D[na2].obj[j].name<<"   ";
	      string temp = D[na1].obj[i].name + D[na2].obj[j].name;
	      int ch = D[coun].interpret (temp);
	      if (ch != -1)
		D[coun].obj[ch].state = "f";
	    }
	}
    }
  int c = 0;
  cout << "\n\t\tWant to save this whole DFA (if (0/1))";
  cin >> c;
  if (c == 1)
    {
      D[coun].dfa_name += "_Minus";
      coun++;
    }
}

void
Union (int na1, int na2)
{
  for (int i = 0; i < D[na1].N_O_state; i++)
    {
      for (int j = 0; j < D[na2].N_O_state; j++)
	{
	  if ((D[na1].obj[i].state == "f" && D[na2].obj[j].state == "nf")
	      || (D[na1].obj[i].state == "nf" && D[na2].obj[j].state == "f"))
	    {
	      //cout<<D[na1].obj[i].name + D[na2].obj[j].name<<"   ";
	      string temp = D[na1].obj[i].name + D[na2].obj[j].name;
	      int ch = D[coun].interpret (temp);
	      if (ch != -1)
		D[coun].obj[ch].state = "f";
	    }
	}
    }
  int c = 0;
  cout << "\n\t\tWant to save this whole DFA (if (0/1))";
  cin >> c;
  if (c == 1)
    {
      D[coun].dfa_name += "_Union";
      coun++;
    }
}

void
sub_menu (int na1, int na2)
{
  int ch;
  cout << "\n\t\tenter your choice ....\n";
  cout << "\n\t\t1. " << D[na1].dfa_name << " U " << D[na2].
    dfa_name << " (0/1) :- ";
  cin >> ch;
  if (ch == 1)
    Union (na1, na2);
  cout << "\n\t\t2. " << D[na1].dfa_name << " - " << D[na2].
    dfa_name << " (0/1) :- ";
  cin >> ch;
  if (ch == 1)
    Minus (na1, na2);
  cout << "\n\t\t3. " << D[na1].dfa_name << " INTERSECTION " << D[na2].
    dfa_name << "  (0/1) :- ";
  cin >> ch;
  if (ch == 1)
    Intersection (na1, na2);


}

void
Special_Interpret (string * sp_a, int na1, int na2)
{
  int Crt1 = coun + 1;
  int Crt2 = coun + 2;
  int cc = 0, c = 0;
  for (int i = 0; i < D[coun].N_O_state; i++)
    {
      for (int j = 0; j < D[coun].N_O_input; j++)
	{
	  D[coun].arr[i][j] = D[coun].interpret (sp_a[cc]);

	  D[Crt1].arr[i][j] = D[coun].interpret (sp_a[cc]);

	  D[Crt2].arr[i][j] = D[coun].interpret (sp_a[cc]);

	  cc++;
	}
    }

  sub_menu (na1, na2);
}

void
Combine (int h, int p)
{
  int Crt1 = coun + 1;
  int Crt2 = coun + 2;
  queue < stropr > str;

  string s = D[h].obj[0].name + D[p].obj[0].name;

  string s1 = D[h].obj[0].name;

  string s2 = D[p].obj[0].name;

  str.push (stropr (s, s1, s2));

  int co = 0;
  counU = 0;
  adi[counU] = s;
  counU++;
  int coun_no_of_states = 0, temp_coun = 0;
  string sp_arr[30];

  cout << "\n\t\t<<<here we go..............>>>\n\n";

  D[coun].dfa_name = D[h].dfa_name + D[p].dfa_name;

  while (!str.empty ())
    {
      coun_no_of_states++;
      string s1 = str.front ().str1 ();
      string s2 = str.front ().str2 ();

      int si1 = D[h].interpret (s1);
      int si2 = D[p].interpret (s2);

      for (int i = 0; i < D[h].N_O_input; i++)
	{
	  string temp = D[h].obj[D[h].arr[si1][i]].name;
	  string temp1 = D[p].obj[D[p].arr[si2][i]].name;
	  string tsum = temp + temp1;

	  if (Isper (tsum))
	    {
	      //cout<<endl<<tsum<<endl;
	      adi[counU] = tsum;
	      counU++;
	      str.push (stropr (tsum, temp, temp1));
	    }


	  cout << "\t\t" << str.front ().str () << "  " << D[h].
	    i_name[i] << " ---> " << tsum << endl << endl;
	  sp_arr[temp_coun] = tsum;
	  temp_coun++;
	}
      D[coun].obj[coun_no_of_states - 1].name = str.front ().str ();
      D[coun + 1].obj[coun_no_of_states - 1].name = str.front ().str ();
      D[coun + 2].obj[coun_no_of_states - 1].name = str.front ().str ();
      cout << endl << endl;
      str.pop ();
    }

  D[coun].N_O_state = coun_no_of_states;
  D[coun].N_O_input = D[h].N_O_input;

  D[Crt1].N_O_state = coun_no_of_states;
  D[Crt1].N_O_input = D[h].N_O_input;

  D[Crt2].N_O_state = coun_no_of_states;
  D[Crt2].N_O_input = D[h].N_O_input;

  for (int i = 0; i < D[coun].N_O_input; i++)
    {
      D[coun].i_name[i] = D[h].i_name[i];
    }

  for (int i = 0; i < D[coun].N_O_input; i++)
    {
      D[Crt1].i_name[i] = D[h].i_name[i];
    }

  for (int i = 0; i < D[coun].N_O_input; i++)
    {
      D[Crt2].i_name[i] = D[h].i_name[i];
    }


  cout << "\n\t\tok\n";
  char r;
  cin >> r;
  while (r != 27)
    {
      cin >> r;
    }
  system ("clear");

  Special_Interpret (sp_arr, h, p);

}


int
Search (string n1)
{
  for (int i = 0; i < coun; i++)
    {
      if (D[i].dfa_name == n1)
	return i;
    }
  return -1;
}

bool
state_name::Replace (string temp)
{
  for (int i = 0; i < N_O_state; i++)
    {
      if (obj[i].name == temp)
	{
	  obj[i].state = "f";
	  return true;
	}
    }
  return false;
}

int
state_name::interpret (string temp)
{
  for (int i = 0; i < N_O_state; i++)
    {
      if (obj[i].name == temp)
	{
	  return i;
	}
    }
  return -1;
}

void
state_name::inserVal ()
{
  string temp;
  for (int i = 0; i < N_O_state; i++)
    {
      for (int j = 0; j < N_O_input; j++)
	{
	label:
	  cout << "\t\t" << obj[i].
	    name << " on input " << i_name[j] << " goes to --> ";
	  cin >> temp;
	  int ok = interpret (temp);
	  if (ok == -1)
	    {
	      cout << "\t\tplease check your spell buddy...\n";
	      cout << "\t\ttry again !!\n";
	      goto label;
	    }
	  arr[i][j] = ok;
	}
    }
}

bool
state_name::Isvalid (string ch)
{
  for (int i = 0; i < N_O_state; i++)
    {
      if (ch == obj[i].name)
	return false;
    }
  return true;
}

void
state_name::create ()
{
  for (int i = 0; i < N_O_state; i++)
    {
    label2:
      cout << "\t\tenter the name of state " << i + 1 << " :-";
      string temp;
      cin >> temp;
      if (Isvalid (temp))
	obj[i].name = temp;
      else
	{
	  cout <<
	    "\n\t\tDon't be over smart you are inserting a previously inserted state!!!\n try again \n";
	  goto label2;
	}
    }

  int temp;
label1:
  cout << "\t\tenter the number of final states " << " :-";
  cin >> temp;
  if (temp > N_O_state)
    {
      cout <<
	"\n\t\twhat is this you are inserting final states more than the states you have\n try again\n";
      goto label1;
    }

  string tt;

label:
  for (int i = 0; i < temp; i++)
    {
      cout << "\t\tenter the  final state(s) " << i + 1 << " :-";
      cin >> tt;
      bool chc = Replace (tt);
      if (!chc)
	{
	  cout << "\t\tplease check your spell buddy...\n";
	  cout << "\t\ttry again !!\n";
	  goto label;
	}
    }

  inserVal ();
}

void
state_name::init ()
{

  cout << "\t\tenter name of DFA  :- ";
  cin >> dfa_name;

  cout << "\t\tenter the number of states : ";
  cin >> N_O_state;

  cout << "\t\tenter the number of input_type : ";
  cin >> N_O_input;

  cout << "\t\tenter data for DFA >>>>>\n";

  for (int i = 0; i < N_O_input; i++)
    {
      cout << "\t\tenter the name of input " << i + 1 << " :-";
      cin >> i_name[i];
    }

  create ();
}

void
Par_print ()
{
  string nam;
  int ch;
label:
  cout << "\n\t\tEnter the Name of DFA you are interested to print ";
  cin >> nam;

  int ind = Search (nam);

  if (ind == -1)
    {
      cout <<
	"\n\t\tBuddy check your spell or go for the available DFA's option !!!\n";
      cout << "\n\t\tnwant to try or go to main menu (0/1)!!\n";
      cin >> ch;
      if (ch == 1)
	goto label;
      else
	return;
    }

  for (int i = 0; i < D[ind].N_O_state; i++)
    {
      for (int j = 0; j < D[ind].N_O_input; j++)
	{
	  cout << "\t\t( " << D[ind].obj[i].name << " , " << D[ind].
	    i_name[j] << " ) " << " ---> " << D[ind].obj[D[ind].arr[i][j]].
	    name << "  " << D[ind].obj[i].state << endl;
	}
    }

  cout << "\n\t\tok ? \n";
  char r;
  cin >> r;
  while (r != 27)
    {
      cin >> r;
    }
  system ("clear");
}

void
Avai_print ()
{
  if (coun == 0)
    cout << "\t\t\nnothing (no DFA is there!!!)\n";

  else
    {
      cout << "\n\t\t<<< here we go..... >>>\n";
      for (int i = 0; i < coun; i++)
	{
	  cout << "\n\t\t" << D[i].dfa_name << "  ";
	}
    }

  cout << "\n\t\tok ? \n";
  char r;
  cin >> r;
  while (r != 27)
    {
      cin >> r;
    }
  system ("clear");

}

void
IsstringValid ()
{
  string temp;
label:
  cout <<
    "\n\t\tEnter the Name of the DFA to check whether the string is valid for it :- ";
  cin >> temp;

  int ind = Search (temp);

  if (ind == -1)
    {
      cout << "\t\tplease check your spell buddy...\n";
      cout << "\t\ttry again !!\n";
      goto label;
    }

  int n;
  cout << "\n\t\tEnter the size of the string : ";
  cin >> n;

  char str[n];
  cout << "\n\t\tenter the string : ";
  cin >> str;

  string sss = D[ind].obj[0].name;

  int sssv1;

  int ccc = 0;

  int sciv1 = 0;

  while (ccc < n)
    {
      char te = str[ccc];

      sciv1 = int (te) - '0';

      sssv1 = D[ind].interpret (sss);

      sss = D[ind].obj[D[ind].arr[sssv1][sciv1]].name;

      ccc++;
    }

  sssv1 = D[ind].interpret (sss);

  if (D[ind].obj[sssv1].state == "f")
    cout << "\n\t\tValid string for " << D[ind].dfa_name << endl;

  else
    cout << "\n\t\tNot valid string for " << D[ind].dfa_name << endl;

  cout << "\n\t\tok ? \n";
  char r;
  cin >> r;
  while (r != 27)
    {
      cin >> r;
    }
  system ("clear");
}

int
main ()
{
  int ch;
  int o, p;
  string n1, n2;
  cout << "\nCREATED BY D . A . S\n";
  cout << "\nVersion 0.0.1\n";
  cout << "\nTOC Assignment (ALPHA COLLEGE OF ENGINEERING AND TECHNOLOGY)\n";
  cout << "\nFor more details E-mail us @ shalinsirwani@gmail.com\n";
  cout << "\nPress any number to start DFA Combiner\n";
  cin >> ch;
  system ("clear");
  while (1)
    {
      cout << "CREATED BY D . A . S";
      cout << "\nVersion 0.0.1\n";
      cout <<
	"\nTOC Assignment (ALPHA COLLEGE OF ENGINEERING AND TECHNOLOGY)";
      cout << "\nFor more details E-mail us @ shalinsirwani@gmail.com\n";

      cout <<
	"\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

      cout <<
	"\n$$$$$$$$$$$$$$$$$$$$$$$ enter your choice $$$$$$$$$$$$$$$$$$$$$$$$$$\n";

      cout <<
	"\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

      cout << "\n\t\t1. To Insert Values in DFA\n";

      cout << "\n\t\t2. To Print a Particular DFA\n";

      cout << "\n\t\t3. To Print the Available DFA'S\n";

      cout << "\n\t\t4. To Combine Two DFA's\n";

      cout << "\n\t\t5. To Check the String is Valid for a Particular DFA\n";

      cout << "\n\t\t6. Press to leave\n";

      int ch1;
      cin >> ch1;
      char j;
      system ("clear");

      switch (ch1)
	{
	case 1:
	  system ("clear");
	  D[coun++].init ();
	  cout << "\n\t\tok \n";
	  break;

	case 2:
	  system ("clear");
	  Par_print ();
	  cout << "\n\t\tok \n";
	  break;

	case 3:
	  system ("clear");
	  Avai_print ();
	  cout << "\n\n\t\tok \n";
	  break;

	case 4:
	  system ("clear");
	  if (coun <= 1)
	    cout <<
	      "\n\t\tnot possible to Combine them , as at least two DFA's are needed\n";

	  else
	    {
	      system ("clear");
	      cout << "\t\tenter the name of two DFA's :-  ";
	      cin >> n1 >> n2;
	      o = Search (n1);
	      p = Search (n2);
	      Combine (o, p);
	    }
	  char j;
	  cout <<
	    "\n\tpress esc and then hit enter so i gonna redirect you to main menu\n";
	  cin >> j;
	  cout << "\n\t\tok \n";
	  break;

	case 5:
	  system ("clear");
	  IsstringValid ();
	  break;

	case 6:
	  return 0;

	default:

	  cout << "\n\t\tWrong choice :: \n";
	  break;

	}

      system ("clear");
    }
  return 0;
}
