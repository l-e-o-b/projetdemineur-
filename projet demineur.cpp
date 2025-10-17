#include <iostream>
#include<ctime>



using namespace std;

const int facile = 9;
int NbMines = (facile * facile) * 0.15;  //calcule de 15% de mines

// initialiser le tableau pour le plateau de jeu
void print_tab(int tab[facile][facile], bool CaseVisible[facile][facile])
{
	for (int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if (tab[i][j] == -1 && CaseVisible[i][j] == true)
			{
				cout << "[*]";
			}
			else if(tab[i][j] != -1 && CaseVisible[i][j] == false)
			{
				cout << "[?]";
			}
			else
			{
				cout << "[ ]";
			}
		}
		cout << endl;
	}
}

void PlacerMine(int tab[facile][facile], bool CaseVisible[facile][facile])
{
	int Mine = 0;

	while (Mine < 12)
	{
		int ligne = rand() % 9;
		int colonne = rand() % 9;		//test coordonnées mines ou non  
		if (tab[ligne][colonne] != -1)
		{
			tab[ligne][colonne] = -1;
			Mine++;
		}

	}
}


bool ChoisirCase(int tab[facile][facile], bool CaseVisible[facile][facile])
{
	int i, j;
	cout << "donner la ligne de la case" << endl;
	cin >> i;
	cout << "donne la colonne de la case" << endl;
	cin >> j;
	if (i >= 0 && i < 9 && j >= 0 && j < 9)
	{
		CaseVisible[i][j] = true;
	}
	if (tab[i][j] == -1)
	{
		return 0;
	}
	return 1;
}

void CaseAutour(int tab[facile][facile])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{

		}
	}
}



int main()
{
	int tab[facile][facile];
	bool CaseVisible[facile][facile];
	bool gameover = false;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tab[i][j] = 0;
			CaseVisible[i][j] = false;
		}
	}
	srand(time(NULL)); // obligatoire pour aleatoire sans = le meme nombre a chaque tours 
	PlacerMine(tab,CaseVisible);
	while (gameover == false)
	{
		if (ChoisirCase(tab, CaseVisible) == 0)
		{
			gameover = true;
			cout << "GAMEOVER" << endl;
		}
		print_tab(tab, CaseVisible);
	}
	
}