#include <iostream>
#include<ctime>



using namespace std;

const int facile = 9;
int NbMines = (facile * facile) * 0.15;  //calcule de 15% de mines

// initialiser le tableau pour le plateau de jeu
void print_tab(int tab[facile][facile], bool CaseVisible[facile][facile], bool caseFlag[facile][facile])
{
	for (int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if (CaseVisible[i][j] == true)
			{
				if (tab[i][j] == -1)
					cout << "[*]";
				else
				{
					cout << "[" << tab[i][j] << "]";
				}
			}
			else if (caseFlag[i][j] == true)
			{
				cout << "[F]";
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


bool ChoisirCase(int tab[facile][facile], bool CaseVisible[facile][facile], int& i, int& j)
{
	cout << "donner la ligne de la case" << endl;
	cin >> i;
	cout << "donne la colonne de la case" << endl;
	cin >> j;
	if (i < 0 || i >= 9 || j < 0 || j >= 9)
	{
		cout << "coordonnees invalides !" << endl;
		return 1;  
	}
	if (tab[i][j] == -1)
	{
		return 0; 
	}
	return 1;
}

void CaseAutour(int tab[facile][facile])
{
	int Boom = 0;
	int NbCase = 0;
	int ni = 0;
	int nj = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (tab[i][j] != -1)
			{
				Boom = 0;
				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (!(dx == 0 && dy == 0))
						{
							ni = i + dx;
							nj = j + dy;
							if (ni >= 0 && ni < 9 && nj < 9 && nj >= 0)
							{
								if (tab[ni][nj] == -1)
								{
									Boom++;
								}
							}
						}
					}
				}
				tab[i][j] = Boom;
			}
		}
	}
}



void ReveleCase(int tab[facile][facile], bool CaseVisible[facile][facile], int i, int j)
{
	if (i < 9 && i >= 0 && j < 9 && j >= 0)
	{
		if (CaseVisible[i][j] == false)
		{
			CaseVisible[i][j] = true;
			if (tab[i][j] == 0)
			{
				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (!(dx == 0 && dy == 0))
						{
							int ni = i + dx;
							int nj = j + dy;
							ReveleCase(tab, CaseVisible, ni, nj);
						}
					}
				}
			}
		}
	}
	else
	{

	}
}


void ReveleMines(int tab[facile][facile], bool CaseVisible[facile][facile])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (tab[i][j] == -1)
				CaseVisible[i][j] = true;
		}
	}
}



int main()
{
	int tab[facile][facile];
	bool CaseVisible[facile][facile];
	bool gameover = false;
	int i, j;
	bool caseFlag[facile][facile];
	int choix;


		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				tab[i][j] = 0;
				CaseVisible[i][j] = false;
				caseFlag[i][j] = false;
			}
		}
		srand(time(NULL)); // obligatoire pour aleatoire sans = le meme nombre a chaque tours 
		PlacerMine(tab,CaseVisible);
		CaseAutour(tab);
		while (gameover == false)
		{
			print_tab(tab, CaseVisible, caseFlag);
			cout << "vous souhaiter :" << endl;
			cout << "1.reveler une case" << endl;
			cout << "2. mettre/retirer un drapeau" << endl;

			cin >> choix;

			if (choix == 1)
			{
				if (ChoisirCase(tab, CaseVisible, i, j) == 0)
				{
					gameover = true;
					ReveleMines(tab, CaseVisible);
					print_tab(tab, CaseVisible, caseFlag);
					cout << "GAMEOVER" << endl << "vous avez toucher une mine a la case : " << "(" << i << "," << j << ")" << endl;

				}
				else
				{
					ReveleCase(tab, CaseVisible, i, j);
				}
			}
			else if (choix == 2)
			{
				cout << "donner la ligne de la case pour poser/enlever un drapeau" << endl;
				cin >> i;
				cout << "donner la colonne de la case pour poser/enlever un drapeau" << endl;
				cin >> j;
				if (i < 0 || i >= 9 || j < 0 || j >= 9)
				{
					cout << "coordonnees invalides" << endl;
				}
				else if (CaseVisible[i][j])
				{
					cout << "impossible de poser un drapeau sur une case revele" << endl;
				}
				else
				{
					caseFlag[i][j] = !caseFlag[i][j];
				}
			}
		}
	return 0;
}