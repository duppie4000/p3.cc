//Auteur: Michiel Flaton S1688243
//Datum: 18 November 2016
//Text-editor: Mousepad
//Compiler: g++ (c++ 11)

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;

//Vervangt alle instanties van MAX met 30.
#define MAX 50

class Nonogram {
	public:
	Nonogram();//constructor
	void maakSchoon();
	void afdrukken();
	void vulRandom();
	void setPercentage();
	void setRijbeschr(int rij);
	void printRijbeschr(int rij);
	void setKolombeschr();
	void printKolombeschr();
	void printRand();
	void printVinkjes();
	void sorteerBeschr();
	void UpdateBeschr();
	void grootte();
	
	void CursorRechts();
	void CursorLinks();
	void CursorOmhoog();
	void CursorOmlaag();
	int CursorSettings();
	void WijzigPunt();
	
	int menu();
	int submenu();
	int randomgetal();
	int leesGetal();
	int leesKar();
	void leesBeschr();
	void leesBestandsnaam();
	void schrijfBeschr();
	
	private:
	int breedte, hoogte;
	int rijen[MAX][MAX]; //Rijbeschrijvingen
	int kolommen[MAX][MAX]; //Kolombeschrijvingen
	int kolom;
	bool nono[MAX][MAX]; 
	bool update = false; //Toggle voor het updaten van beschrijvingen
	int x, y;//Cursor coordinaten
	bool trail = false;//Toggle voor de cursor instelling
	int randperc;//bewaart het percentage voor de random vuller
	string input;
	string bestandsnaam;
};

//Constructor, maakt de arrays leeg en initialiseert membervariabelen
Nonogram::Nonogram() {
	for (int i=0; i<MAX; i++)
		for (int j=0; j<MAX; j++) {
			nono[i][j] = false;
			rijen[i][j] = 0;
			kolommen[i][j] = 0;
		}
	hoogte = 0;
	breedte = 0;
	x = 0;
	y = 0;
	randperc = 50;
	kolom = 0;
}
//Dit is een infoblokje. Wow. Spannend.
void Infoblokje() {
	cout << "**************************************************************" << endl;
	cout << "* Programmeeropdracht 3: Nonogram                            *" << endl;
	cout << "* Gemaakt door Michiel Flaton - s1688243                     *" << endl;
	cout << "* 18 november 2016                                           *" << endl;
	cout << "* Dit programma geeft beschrijvingen voor Nonogrammen en     *" << endl;
	cout << "* drukt nonogrammen af als plaatje. Ook kan het willekeurige *" << endl;
	cout << "* nonogrammen genereren en beschrijvingen inlezen uit files  *" << endl;
	cout << "* en beschrijvingen wegschrijven.                            *" << endl;
	cout << "**************************************************************" << endl;
}

//Vult de nono array willekeurig.
void Nonogram::vulRandom() {
	for (int i=0; i<MAX; i++)
		for (int j=0; j<MAX; j++) {
			if (randomgetal() >= (10 * randperc))
				nono[i][j] = false;
			else
				nono[i][j] = true;
		}
}

//Stelt het percentage in dat moet worden gevuld met de random functie
void Nonogram::setPercentage() {
	int temp = 0;
	cout << "Vul een percentage in (1-100)\n";
	temp = leesGetal();
	if (temp < 1 || temp > 100) {
		cout << "Ongeldige waarde\n";
		setPercentage();
	}
	else {
		randperc = temp;
		cout << "Percentage ingesteld op " << randperc << "%.\n";
	}
}
//Geeft de gebruiker aan het begin de keuze om een beschrijving in te
//lezen of zelf een nonogram te tekenen.
void start()
{
	string input;
	Nonogram a;
	cout << "Wilt u een beschrijving inlezen?" << endl;
	cout << "Y / N" << endl;
	input = a.leesKar();
	if(input == "Y" || input == "y") {
		a.leesBestandsnaam();
		a.leesBeschr();
	}
	else if(input == "N" || input == "n") 
		a.grootte();
	else {
		cout << "Ongeldige optie, programma sluit.";
		exit(1);
	}
	a.menu();
}
//Dit is een main-functie
int main() {
	Infoblokje();
	start();
	return 0;
}
//De opties. Van het menu. Duh.
void MenuOpties() {
	cout << "S\e[4mc\e[0mhoon, ";
	cout << "\e[4mW\e[0millekeurig, ";
	cout << "\e[4mP\e[0marameters, ";
	cout << "\e[4mU\e[0mpdate beschrijvingen, ";
	cout << "\e[4mS\e[0mtoppen\n";
	
	cout << "Cursor: " << "\e[4mL\e[0minks, ";
	cout << "\e[4mR\e[0mechts, ";
	cout << "\e[4mO\e[0mmhoog, ";
	cout << "\e[4mB\e[0meneden, ";
	cout << "\e[4mF\e[0mlip punt\n";
}
//Hoofdmenu
int Nonogram::menu() {
	do {
		afdrukken();
		MenuOpties();
		input = leesKar();
		switch (input[0]) {
			case 'C': case 'c':
				maakSchoon();
				break;
			case 'W': case 'w':
				vulRandom();
				break;
			case 'P': case 'p':
				submenu();
				break;
			case 'S': case 's':
				return 1;
				break;
			case 'O': case 'o':
				CursorOmhoog();
				break;
			case 'L': case 'l':
				CursorLinks();
				break;
			case 'B': case 'b':
				CursorOmlaag();
				break;
			case 'R': case 'r':
				CursorRechts();
				break;
			case 'F': case 'f':
				WijzigPunt();
				break;
			case 'U': case'u':
				UpdateBeschr();
				break;
			default:
				cout << "Ongeldige Keuze\n";
				break;
		}
	} while (input != "S");
	return 0;
}
//De opties van het submenu. Wow, verassend.
void subOpties() {
	cout << "\e[4mG\e[0mrootte, ";
	cout << "Cursor \e[4mI\e[0mnstelling, ";
	cout << "\e[4mW\e[0mijzig Random Percentage, ";
	cout << "Beschrijving \e[4mL\e[0mezen / \e[4mS\e[0mchrijven, ";
	cout << "\e[4mT\e[0merug\n";
	
}
//Submenu
int Nonogram::submenu() {
	do {
		subOpties();
		input = leesKar();
		switch (input[0]) {
			case 'G': case 'g':
				grootte();
				break;
			case 'I': case 'i':
				CursorSettings();
				break;
			case 'W': case 'w':
				setPercentage();
				break;
			case 'L': case 'l':
				leesBestandsnaam();
				leesBeschr();
				break;
			case 'S': case 's':
				schrijfBeschr();
				break;
			case 'T': case 't':
				return 1;
				break;
			default:
				cout << "Ongeldige Keuze\n";
				break;
		}
	} while (input != "T");
	return 1;
}

//Schoont de array
void Nonogram::maakSchoon() {
	for (int i=0; i < MAX; i++)
		for (int j=0; j < MAX; j++)
			nono[i][j] = false;
}
//Leest getallen in en negeert ongeldige karakters
int Nonogram::leesGetal() {
	int out = 0;
	char in [MAX];
	
	for (int i=0; i < MAX; i++)
		in[i] = 0;

	cin >> ws; //Leest en verwijdert alle whitespaces voor input
	cin.get(in , MAX);

	for (int i=0; i < MAX; i++) {
		if('0' <= in[i] && in[i] <= '9' && out < 1000) {
			out = out * 10;
			out += in[i] - '0';
		}
	}
	return out;
}

//Leest karakters in voor de menu's
int Nonogram::leesKar() {
	char in;
	cin >> ws;
	cin.get(in);
	return in;
}

//Drukt de bovenste en onderste rand van het nonogram af
void Nonogram::printRand() {
	int rand = breedte + 2;
	while (rand != 0) {
		cout << "#" << ' ';
		rand --;
	}
	cout << endl;
}

void Nonogram::printVinkjes() {
	int vinkjes = breedte;
	cout << "  ";
	while(vinkjes > 0) {
		cout << "V ";
		vinkjes--;
	}
	cout << endl;
}



//Drukt het nonogram af in de terminal
void Nonogram::afdrukken() {
	printRand();
	for (int i=0; i < hoogte; i++) {
		kolom++;
		cout << '#' << ' ';
		for (int j=0; j < breedte; j++) {
			if (j == x && i == y)
				cout << '+' << ' ';
			else if (nono[i][j]) {
				cout << 'X' << ' ';
			}
			else
				cout << ' ' << ' ';
		}
		cout << "#" << " V ";
		if(update == true)
			setRijbeschr(i);
		printRijbeschr(i);
		cout << endl;
	}
	kolom = 0;
	printRand();
	if(update == true) {
		setKolombeschr();
		update = false;
	}
	printVinkjes();
	printKolombeschr();
}
//Vernieuwd de beschrijvingen met het huidige beeld
void Nonogram::UpdateBeschr() {
	update = true;
}
//Stelt de grootte van het nonogram in.
void Nonogram::grootte() {
	int temp1, temp2;
	cout << "Geef de hoogte van het nonogram op (2-50)\n";
	temp1 = leesGetal();
	cout << "Geef de breedte van het nonogram op (2-50)\n";
	temp2 = leesGetal();
	if (temp1 < 2 || temp1 > MAX || temp2 < 2 || temp2 > MAX) {
		cout << "Ongeldige grootte, programma sluit\n";
		exit(0);
	}
	else {
		hoogte = temp1;
		breedte = temp2;
	}
}
//Verplaatst de cursoor naar rechts
void Nonogram::CursorRechts() {
	x++;
	if(trail)
		nono[y][x] = !nono[y][x];
	if (x >= breedte)
		x = 0;
}
//en naar links
void Nonogram::CursorLinks() {
	if (x <= 0)
		x = breedte;
	x--;
	if(trail)
		nono[y][x] = !nono[y][x];
}
//en omhoog
void Nonogram::CursorOmhoog() {
	if (y == 0)
		y = hoogte;	
	y--;
	if(trail)
		nono[y][x] = !nono[y][x];
}
//En ook maar omlaag dan
void Nonogram::CursorOmlaag() {
	y++;
	if(trail)
		nono[y][x] = !nono[y][x];
	if (y == hoogte)
		y = 0;
}
//Maakt van een leeg vakje een kruisje of andersom
void Nonogram::WijzigPunt() {
	int i = 0;
	int j = 0;
	for (i=0; i < MAX; i++)
		for (j=0; j < MAX; j++)
		if (j == x && i == y)
			nono[i][j] = !nono[i][j];
}

//Bepaalt of het vakje verandert bij het verplaatsen met de cursor
int Nonogram::CursorSettings() {
	cout << "Vakjes automatisch inkleuren met de cursor?\n";
	cout << "\e[4mA\e[0man / \e[4mU\e[0mit";//Hier staat aan / uit
	input = leesKar();
	if (input == "A" || input == "a") {
		trail = true;
	}
	else if(input == "U" || input =="u") {
		trail = false;
	}
	return 1;
}

//Bepaalt de rijbeschrijvingen aan de hand van het beeld
void Nonogram::setRijbeschr(int rij) {
		int teller = 0;
		int getal = 0;
		for (int i=0; i<breedte; i++) {
			rijen[rij][i] = 0;

			if (nono[rij][i])
				teller++;
			else if(teller > 0) {
				rijen[rij][getal] = teller;
				teller = 0;
				getal++;
			}
			if (i == breedte - 1) {
				rijen[rij][getal] = teller;
				getal ++;
			}
		}
}
//Drukt de rijbeschrijvingen af
void Nonogram::printRijbeschr(int rij) {
	int teller = 0;
	for(int j=0; j<breedte; j++) {
		if(rijen[rij][j] > 0)
			cout << rijen[rij][j] << ' ';
		else
			teller++;
		if(teller == breedte)
			cout << '0';
	}
}
//Bepaalt de kolombeschrijvingen aan de hand van het huidige beeld
void Nonogram::setKolombeschr() {
	int teller = 0;
	for(int i=0; i<hoogte; i++) {
		for(int j=kolom; j<breedte; j++) {
			if(j == kolom) {
				kolommen[i][j] = 0;
				if(nono[i][j])
					teller++;
				else if(teller > 0) {
					kolommen[i-1][j] = teller;
					teller = 0;
				}
				if(i == hoogte - 1) {
					kolommen[i][j] = teller;
					teller = 0;
					kolom++;
					if(j != breedte - 1)
						i = 0;
				}
			}
		}
	}
	kolom = 0;
	sorteerBeschr();
}
//Sorteert het kolommen-array zodat de getallen tegen de bovenrand komen
void Nonogram::sorteerBeschr() {
	int rij = 0;
	for(int i=0; i<hoogte; i++)
		for(int j=kolom; j<breedte; j++)
			if(j == kolom) {
				if(kolommen[i][j] != 0) {
					if(i != 0) {
						kolommen[rij][j] = kolommen[i][j];
						kolommen[i][j] = 0;
					}
					rij++;
				}
				if(i == hoogte - 1) {
					kolom++;
					rij = 0;
					if(j != breedte - 1)
						i = 0;
				}
			}
}

void Nonogram::printKolombeschr() {
	bool legeRij = false;
	int teller = 0;
	
	for(int i=0; i<hoogte; i++) {
		if(!legeRij) {
			cout << "  ";
			for(int j=0; j<breedte; j++) {
				if(i == 0 && kolommen[i][j] == 0)
					cout << '0' << ' ';
				
				else if(kolommen[i][j] > 0)
					cout << kolommen[i][j] << ' ';
				else {
					cout << "  ";
					teller++;
					if(teller == breedte - 1) {
						legeRij = true;
						break;
					}
				}
			}
			cout << endl;	
			teller = 0;
		}
	}
}

//Vraagt de gebruiker naar de naam van het bestand met de beshrijvingen
void Nonogram::leesBestandsnaam() {
	cout << "Geef de naam op van de file." << endl;
	cin >> bestandsnaam;
}

//Leest beschrijvingen in uit een tekstbestand
void Nonogram::leesBeschr() {
	ifstream invoer;
	invoer.open(bestandsnaam);
	int rij, kolom = 0;
	int rij2, kolom2 = 0;
	int getal = 0;

	if (! invoer) {
		cout << "Ongeldige bestandsnaam" << endl;
		exit(1);
	}

	invoer >> hoogte;
	invoer >> breedte;
	while(! invoer.eof()) {
		invoer >> getal;
		if(rij < hoogte) {
			if(getal != 0) {
				rijen[rij][kolom] = getal;
				kolom++;
			}
			else {
				rij++;
				kolom = 0;
			}
		}
		else {
			if(getal != 0) {
				kolommen[rij2][kolom2] = getal;
				rij2++;
			}
			else {
				kolom2++;
				rij2 = 0;
			}
		}
	}
	invoer.close();
}

//Schrijft de beschrijvingen van het beeld weg naar een bestand
void Nonogram::schrijfBeschr() {
	int rij = 0;
	leesBestandsnaam();
	
	ofstream uitvoer;
	uitvoer.open(bestandsnaam);
	uitvoer << hoogte << ' ' << breedte << endl;
	for(int i=0; i<hoogte; i++) {
		for(int j=0; j<breedte; j++) {
			if(rijen[i][j] != 0)
				uitvoer << rijen[i][j] << ' ';
		}
		uitvoer << 0 << endl;
	}
	do {
		if(kolommen[rij][kolom] != 0)
		{
			uitvoer << kolommen[rij][kolom] << ' ';
			rij++;
		}
		else {
			uitvoer << '0' << endl;
			kolom++;
			rij = 0;
		}
	}while(kolom < breedte);

	uitvoer.close();
	cout << "Beschrijvingen geschreven naar " << bestandsnaam << endl;
}

//Een (pseudo)random number generator
int Nonogram::randomgetal() {
	static int rnd = 42;
	rnd = (221 * rnd + 1) % 1000;
	return rnd;
} 
