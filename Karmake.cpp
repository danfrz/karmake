#include <iostream>
#include <math.h>
#include <cctype>
using namespace std;
char map[4][4];
char result[16];
int workingindex;

void solveKarnaugh_3();
void solveKarnaugh_4();
bool getRegion(int x1, int x2, int y1, int y2);

int main()
{
	int inputs;
	cout << "\nWelcome to Karmake!\n\n"
		 <<	"[3] to make 3-input karnaugh map\n"
		 << "[4] to make 4-input karnaugh map\n"
		 << "                              : ";
	cin >> inputs;
	while(inputs != 3 && inputs != 4)
	{
		cout << "You have enterred an incorrect number, please enter 3 or 4: ";
		cin >> inputs;
	}
	cout << "                                __          _ _\n";
	cout << "Note: If you see something like AB it means A*B\n";
	if(inputs == 3)
		solveKarnaugh_3();
	else if (inputs == 4)
		solveKarnaugh_4();

	return 0;
}

bool verifyBool(char x)
{
	switch(x)
	{
		case '0':
		case '1':
		case 'x':
		case 'X':
		case '_':
			return true;
		default:
			return false;
	}
}
bool isTrue(char x)
{
	switch(x)
	{
		case '1':
		case 'x':
		case 'X':
		case '_':
				return true;
		default:
				return false;
	}
}

void printWorkingKarnaugh_3()
{
	cout	<<"\n\nEnter the result of the truth table...\n"
			<< "Using 0, 1, or (_ or X)\n"
			<< "_ or X stand for Do Not Care inputs\n"
			<< "___________________\n"
			<< "|A: 0 0 0 0 1 1 1 1\n"
			<< "|B: 0 0 1 1 0 0 1 1\n"
			<< "|C: 0 1 0 1 0 1 0 1\n|\n"
			<< "|x: ";
	for(int i = 0; i < workingindex; i++)
		cout << result[i];
}


void printWorkingKarnaugh_4()
{
	cout	<<"\n\nEnter the result of the truth table...\n"
			<< "Using 0, 1, or (_ or X)\n"
			<< "_ or X stand for Do Not Care outputs\n"
			<< "____________________\n"
			<< "|A: 0000000011111111\n"
			<< "|B: 0000111100001111\n"
			<< "|C: 0011001100110011\n"
			<< "|D: 0101010101010101\n|\n"
			<< "|x: ";
	for(int i = 0; i < workingindex; i++)
		cout << result[i];
}


void solveKarnaugh_3()
{
	int entries = 8; //2 ^ 3

	cout	<< "\nEnter the result of the truth table...\n"
			<< "Using 0, 1, or (_ or X)\n"
			<< "_ or X stand for Do Not Care outputs\n"
			<< "____________\n"
			<< "|A: 0 0 0 0 1 1 1 1\n"
			<< "|B: 0 0 1 1 0 0 1 1\n"
			<< "|C: 0 1 0 1 0 1 0 1\n|\n"
			<< "|x: ";
	//get boolean truth table
	for(workingindex = 0; workingindex < entries; workingindex++)
	{
		cin >> result[workingindex];
		while(isspace(result[workingindex]))
			cin >> result[workingindex];
		while(!verifyBool(result[workingindex]))
		{
			cout << "Invalid input character '" << result[workingindex] << "'! R to start over, Q to quit.\n";
			printWorkingKarnaugh_3();
			cin >> result[workingindex];		
			if (result[workingindex] == 'Q' || result[workingindex] == 'q')
			{
				cout << "Exiting...\n";
				return;
			}
			else if (result[workingindex] == 'R' || result[workingindex] == 'r')
			{
				solveKarnaugh_3();
				return;
			}
		}
	}
	

	int half = entries/2;
	//map the booleans to array
	//convert standard progression to grey code
	int x, y;
	for(int i = 0; i < entries; i++)
	{
		int next = i+1;
		if (i >= half)
		{
			//flip y
			y = 2+ (7-i)/2;
		} else  y = i/2;
		x = 1-next%2;
		map[y][x] = result[i];
	}

	//output karnaugh map
	cout	<< "      _  \n"
			<< "      C C\n"
			<< " __ _____\n"
			<< "_AB |";
	cout << ' ' << map[0][0] << ' ' << map[0][1] << '\n';
	cout	<< "AB  |";
	cout << ' ' << map[1][0] << ' ' << map[1][1] << '\n';
	cout	<< "AB_ |";
	cout << ' ' << map[2][0] << ' ' << map[2][1] << '\n';
	cout	<< " AB |";
	cout << ' ' << map[3][0] << ' ' << map[3][1] << '\n';

	//check groups.
	
    bool A = getRegion(0,1,2,3);
    bool B = getRegion(0,1,1,2);
    bool C = getRegion(1,1,0,3);
    int sum = A+B+C;
    if(sum == 3)
    {
        cout << "A+B+C\n";
    }
    else if(sum > 0)
    {
        if(A) cout << "A + ";
        if(B) cout << "B + ";
        if(C) cout << "C + ";
        cout << "other terms...\n";
    }

}

bool getRegion(int x1, int x2, int y1, int y2)
{
    bool term = true;
    while(y1 <= y2 && term)
    {
        for(int x = x1; x <= x2 && term; x++)
        {
            if(map[y1][x] != '1')
                term = false;
        }
        y1++;
    }

    return term;
}


void solveKarnaugh_4()
{
	cout	<< "\nEnter the result of the truth table...\n"
			<< "Using 0, 1, or X\n"
			<< "___________________\n"
			<< "A: 0000000011111111\n"
			<< "B: 0000111100001111\n"
			<< "C: 0011001100110011\n"
			<< "D: 0101010101010101\n\n"
			<< "x: ";
	int entries = 16; //2 ^ 4

	//get boolean truth table
	for(workingindex = 0; workingindex < entries; workingindex++)
	{
		cin >> result[workingindex];
		while(isspace(result[workingindex]))
			cin >> result[workingindex];
		while(!verifyBool(result[workingindex]))
		{
			cout << "Invalid input character '" << result[workingindex] << "'! R to start over, Q to quit.\n";
			printWorkingKarnaugh_4();
			cin >> result[workingindex];		
			if (result[workingindex] == 'Q' || result[workingindex] == 'q')
			{
				cout << "Exiting...\n";
				return;
			}
			else if (result[workingindex] == 'R' || result[workingindex] == 'r')
			{
				solveKarnaugh_4();
				return;
			}
		}
	}
	

	int half = entries/2;
	//map the booleans to array
	//convert standard progression to grey code
	int x, y;
	for(int i = 0; i < entries; i++)
	{
		int next = i+1;
		if (i >= half)
		{
			//flip y
			y = 2+ (15-i)/4;
		} else  y = i/4;
		int mod = i % 4;
		if (mod > 1)
		{
			if(mod == 2)
				x = 3;
			else x = 2;
		} else x = mod;

		//cout << "y=" << y << " x=" << x << '\n';
		map[y][x] = result[i];
	}

	//output karnaugh map
	cout	<< "      __ _      _\n"
			<< "      CD CD CD CD\n"
			<< " __ _____________\n"
			<< "_AB |";
	cout 	<< "  " << map[0][0] << "  " << map[0][1] << "  " << map[0][2] << "  " << map[0][3] << '\n';
	cout	<< "AB  |";
	cout 	<< "  " << map[1][0] << "  " << map[1][1] << "  " << map[1][2] << "  " << map[1][3] << '\n';
	cout	<< "AB_ |";
	cout 	<< "  " << map[2][0] << "  " << map[2][1] << "  " << map[2][2] << "  " << map[2][3] << '\n';
	cout	<< " AB |";
	cout 	<< "  " << map[3][0] << "  " << map[3][1] << "  " << map[3][2] << "  " << map[3][3] << "\n\n";

    bool A = getRegion(0,3,2,3);
    bool B = getRegion(0,3,1,3);
    bool C = getRegion(2,3,0,3);
    bool D = getRegion(1,2,0,3);

    int sum = A+B+C+D;
    if(sum == 4)
    {
        cout << "A+B+C+D\n";
    }
    else if(sum > 0)
    {
        if(A) cout << "A + ";
        if(B) cout << "B + ";
        if(C) cout << "C + ";
        if(D) cout << "D + ";
        cout << "other terms...\n";
    }


	bool corners = isTrue(map[0][0]) && isTrue(map[0][3]) && isTrue(map[3][3]) && isTrue(map[3][0]);
	bool center  = isTrue(map[1][1]) && isTrue(map[1][2]) && isTrue(map[2][1]) && isTrue(map[2][2]);
	if(corners)
	{
		if(center)
		{
			cout << "                    __\n";
			cout << "Corners and center: BD + BD = B XNOR D\n";
		}
		else
		{
			cout << "           " << "__\n";
			cout << "4 Corners: " << "BD +\n";
		}
	} else if (center)
	{
		cout << "           " << "\n";
		cout << "Center:    " << "BD +\n";
	}

}

