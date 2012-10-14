/*	Tic Tac Toe, tre pÂ rad. Made by Runar Ovesen Hjerpbakk 2003.
 Downloaded from Runar pÂ NTNU (www.stud.ntnu.no/~hjerpbak)
 E-Mail: hjerpbak@stud.ntnu.no
 Version: 0.99 HISTORY:
 V 0.30: Input OK
 V 0.50: Bare multiplayer
 V 0.70: Jalla AI
 V 0.80: Bedre AI
 V 0.90: Ganske bra AI
 V 0.99: Kan velge mellom 2 player, easy, medium eller hard
 V 1.00: Hard AI helt ferdig. FINAL VERSION */

#include <iostream> //for inn/ut
#include <stdlib.h> //For system()
#include <time.h> //for time() (som for¯vrig er ant sekunder siden kl 00.00.00 1. januar 1970 GMT hvis du har time(0)

char cRute[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; //rutene
int nPlayer = 0;
int nGame_mode = 0;
int nRute_poeng[] = { 2, 1, 2, 1, 6, 1, 2, 1, 2 }; //Poengene til rutene, bestemmer stort sett hvor ai'en skal flytte

//Prototyping av funksjonene
void tegn_brett(); //tegner brettet
void input(char cPlayer); // Tar input
bool vinner(char cPlayer); //sjekker om noen har vunnet
void comp_player(char cPlayer);	//AI
bool sjekk_rute(int nRute_nr);	//sjekker om den aktuelle ruta er tom
void sette_poeng(int nRute_nr); //setter poeng etter at man har lagt
int finn_max(); //finner ruten med flest poeng, der skal mr. ai sette sin brikke
void welcome(); //velkomstskjerm

void input(char cPlayer) //Tar input
{
	char cValg[100];
	int nValg = -5;
	
	while (nValg < 1 || nValg > 9)
    {
        std::cout<<std::endl<<"Player "<<nPlayer<<" place your "<<cPlayer<<": "; //player 1/2 place your X/O:
        std::cin.getline (cValg,100); //Tar input som en string...
        nValg = atoi (cValg); //Mekker int av stringen...
    }
	nValg --;
	if (sjekk_rute(nValg) == true)
    {
        std::cout<<"You must select an empty square...\n";
        input(cPlayer);
    }
	else
    {
        cRute[nValg] = cPlayer;
        if (nGame_mode == 3 || nGame_mode == 4)
        {
            sette_poeng(nValg);
        }
    }
}

void tegn_brett() //Spillebrettet
{
	int nDummy = -3;
	system("cls");
	std::cout<<"Tic Tac Toe v.1.00 by Lord Sankra, 2003"<<std::endl<<std::endl;
	for (int nX = 0; nX <= 6; nX++)
    {
        if (nX % 2 == 0)
        {
            std::cout<<"<----------------->"<<std::endl;
            nDummy += 3;
        }
        else
        {
            std::cout<<"<  "<<cRute[0+nDummy]<<"  |  "<<cRute[1+nDummy]<<"  |  "<<cRute[2+nDummy]<<"  >"<<std::endl;
        }
    }
}

bool vinner(char cPlayer) //Finner ut hvem som vant
{
	bool bVinner = false;
	if (cRute[0] == cPlayer && cRute[1] == cPlayer && cRute[2] == cPlayer)
    {
        bVinner = true;
    }
	else if (cRute[3] == cPlayer && cRute[4] == cPlayer && cRute[5] == cPlayer)
    {
        bVinner = true;
    }
	else if (cRute[6] == cPlayer && cRute[7] == cPlayer && cRute[8] == cPlayer)
    {
        bVinner = true;
    }
	else if (cRute[0] == cPlayer && cRute[3] == cPlayer && cRute[6] == cPlayer)
    {
        bVinner = true;
    }
	else if (cRute[1] == cPlayer && cRute[4] == cPlayer && cRute[7] == cPlayer)
    {
        bVinner = true;
    }
	else if (cRute[2] == cPlayer && cRute[5] == cPlayer && cRute[8] == cPlayer)
    {
        bVinner = true;
    }
	else if (cRute[0] == cPlayer && cRute[4] == cPlayer && cRute[8] == cPlayer)
    {
        bVinner = true;
    }
	else if (cRute[2] == cPlayer && cRute[4] == cPlayer && cRute[6] == cPlayer)
    {
        bVinner = true;
    }
    
	return bVinner;
}

bool sjekk_rute(int nRute_nr) //er denne ruten tom?
{
	if (cRute[nRute_nr] != ' ')
    {
        return true;
    }
	return false;
}

int finn_max() //bestemmer hvor ai'en skal sette sin brikke
{
	int nMax_verdi = -10; //setter den sÂ lavt at selv en negativ verdi vil vÊre st¯rre...
	int nMax = 0;
	int nMidlertidig[] = { 0,0,0,0,0,0,0,0,0 };
	int nCounter = 0;
	int nDummy = 4;
	for (int nX = 0; nX <= 8; nX++)
    {
        if (sjekk_rute(nX) == false) //finner maksverdi i tomme ruter
        {
            if (nMax_verdi <= nRute_poeng[nX])
            {
                nMax_verdi = nRute_poeng[nX];
                nMidlertidig[nX] = nRute_poeng[nX];
            }
        }
    }
	for (int nX = 0; nX <= 8; nX++) //unders¯ker om det er flere som inneholder maksverdi, nMidlertidig har nÂ 1 der det/de st¯rste verdien(e) er og 0 ellers
    {
        if (nMidlertidig[nX] == nMax_verdi)
        {
            nMidlertidig[nX] = 1;
            nMax = nX;
            nCounter ++;
        }
        else
        {
            nMidlertidig[nX] = 0;
        }
    }
	if (nCounter == 1) //hvis bare Ën er st¯rst, sÂ setter ai'en sin brikke der
    {
        return nMax;
    }
	else
    {
        nDummy = rand() % 9; //hvis flere er st¯rst, er det random hvor han setter (men ruta mÂ fremdeles ha st¯rst verdi)
        while (nMidlertidig[nDummy] != 1) //random modulo 9 gir et tall fra 0 til 8 (9 random tall) rand()%1 gir 0, rand()%2 0-1 osv
        {
            nDummy = rand() % 9;
        }
        return nDummy;
    }
}

void sette_poeng(int nRute_nr) //setter poeng pÂ rutene
{
	//setter poeng etter der man har lagt brikker
	if (nRute_nr == 0 && cRute[nRute_nr] == 'O') { nRute_poeng[0] = 0; nRute_poeng[1] ++; nRute_poeng[4] ++; nRute_poeng[3] ++; } //¯verst til venstre, O brikke
	else if (nRute_nr == 0 && cRute[nRute_nr] == 'X') { nRute_poeng[1] --; nRute_poeng[4] --; nRute_poeng[3] --; } //¯verst til venstre, X brikke osv lenger ned
	else if (nRute_nr == 1 && cRute[nRute_nr] == 'O') { nRute_poeng[0] ++; nRute_poeng[2] ++; nRute_poeng[3] ++; nRute_poeng[4] ++; nRute_poeng[5] ++; }
	else if (nRute_nr == 1 && cRute[nRute_nr] == 'X') { nRute_poeng[0] --; nRute_poeng[2] --; nRute_poeng[3] --; nRute_poeng[4] --; nRute_poeng[5] --; }
	else if (nRute_nr == 2 && cRute[nRute_nr] == 'O') { nRute_poeng[1] ++; nRute_poeng[4] ++; nRute_poeng[5] ++; }
	else if (nRute_nr == 2 && cRute[nRute_nr] == 'X') { nRute_poeng[1] --; nRute_poeng[4] --; nRute_poeng[5] --; }
	else if (nRute_nr == 3 && cRute[nRute_nr] == 'O') { nRute_poeng[0] ++; nRute_poeng[1] ++; nRute_poeng[4] ++; nRute_poeng[7] ++; nRute_poeng[6] ++; }
	else if (nRute_nr == 3 && cRute[nRute_nr] == 'X') { nRute_poeng[0] --; nRute_poeng[1] --; nRute_poeng[4] --; nRute_poeng[7] --; nRute_poeng[6] --; }
	else if (nRute_nr == 4 && cRute[nRute_nr] == 'O') { nRute_poeng[0] ++; nRute_poeng[1] ++; nRute_poeng[2] ++; nRute_poeng[3] ++; nRute_poeng[5] ++; nRute_poeng[6] ++; nRute_poeng[7] ++; nRute_poeng[8] ++; }
	else if (nRute_nr == 4 && cRute[nRute_nr] == 'X') { nRute_poeng[0] --; nRute_poeng[1] --; nRute_poeng[2] --; nRute_poeng[3] --; nRute_poeng[5] --; nRute_poeng[6] --; nRute_poeng[7] --; nRute_poeng[8] --; }
	else if (nRute_nr == 5 && cRute[nRute_nr] == 'O') { nRute_poeng[1] ++; nRute_poeng[2] ++; nRute_poeng[4] ++; nRute_poeng[7] ++; nRute_poeng[8] ++; }
	else if (nRute_nr == 5 && cRute[nRute_nr] == 'X') { nRute_poeng[1] --; nRute_poeng[2] --; nRute_poeng[4] --; nRute_poeng[7] --; nRute_poeng[8] --; }
	else if (nRute_nr == 6 && cRute[nRute_nr] == 'O') { nRute_poeng[3] ++; nRute_poeng[4] ++; nRute_poeng[7] ++; }
	else if (nRute_nr == 6 && cRute[nRute_nr] == 'X') { nRute_poeng[3] --; nRute_poeng[4] --; nRute_poeng[7] --; }
	else if (nRute_nr == 7 && cRute[nRute_nr] == 'O') { nRute_poeng[3] ++; nRute_poeng[4] ++; nRute_poeng[5] ++; nRute_poeng[6] ++; nRute_poeng[8] ++; }
	else if (nRute_nr == 7 && cRute[nRute_nr] == 'X') { nRute_poeng[3] --; nRute_poeng[4] --; nRute_poeng[5] --; nRute_poeng[6] --; nRute_poeng[8]	--; }
	else if (nRute_nr == 8 && cRute[nRute_nr] == 'O') { nRute_poeng[4] ++; nRute_poeng[5] ++; nRute_poeng[7] ++; }
	else if (nRute_nr == 8 && cRute[nRute_nr] == 'X') { nRute_poeng[4] --; nRute_poeng[5] --; nRute_poeng[7] --; }
	// to pÂ rad poeng
	if (cRute[0] == 'O' && cRute[1] == 'O') { nRute_poeng[2] += 10; }
	if (cRute[0] == 'X' && cRute[1] == 'X') { nRute_poeng[2] += 7; }
	if (cRute[0] == 'O' && cRute[2] == 'O') { nRute_poeng[1] += 10; }
	if (cRute[0] == 'X' && cRute[2] == 'X') { nRute_poeng[1] += 7; }
	if (cRute[1] == 'O' && cRute[2] == 'O') { nRute_poeng[0] += 10; }
	if (cRute[1] == 'X' && cRute[2] == 'X') { nRute_poeng[0] += 7; }
	if (cRute[0] == 'O' && cRute[3] == 'O') { nRute_poeng[6] += 10; }
	if (cRute[0] == 'X' && cRute[3] == 'X') { nRute_poeng[6] += 7; }
	if (cRute[0] == 'O' && cRute[6] == 'O') { nRute_poeng[3] += 10; }
	if (cRute[0] == 'X' && cRute[6] == 'X') { nRute_poeng[3] += 7; }
	if (cRute[3] == 'O' && cRute[6] == 'O') { nRute_poeng[0] += 10; }
	if (cRute[3] == 'X' && cRute[6] == 'X') { nRute_poeng[0] += 7; }
	if (cRute[2] == 'O' && cRute[5] == 'O') { nRute_poeng[8] += 10; }
	if (cRute[2] == 'X' && cRute[5] == 'X') { nRute_poeng[8] += 7; }
	if (cRute[2] == 'O' && cRute[8] == 'O') { nRute_poeng[5] += 10; }
	if (cRute[2] == 'X' && cRute[8] == 'X') { nRute_poeng[5] += 7; }
	if (cRute[5] == 'O' && cRute[8] == 'O') { nRute_poeng[2] += 10; }
	if (cRute[5] == 'X' && cRute[8] == 'X') { nRute_poeng[2] += 7; }
	if (cRute[6] == 'O' && cRute[7] == 'O') { nRute_poeng[8] += 10; }
	if (cRute[6] == 'X' && cRute[7] == 'X') { nRute_poeng[8] += 7; }
	if (cRute[6] == 'O' && cRute[8] == 'O') { nRute_poeng[7] += 10; }
	if (cRute[6] == 'X' && cRute[8] == 'X') { nRute_poeng[7] += 7; }
	if (cRute[7] == 'O' && cRute[8] == 'O') { nRute_poeng[6] += 10; }
	if (cRute[7] == 'X' && cRute[8] == 'X') { nRute_poeng[6] += 7; }
	if (cRute[4] == 'O' && cRute[0] == 'O') { nRute_poeng[8] += 10; }
	if (cRute[4] == 'X' && cRute[0] == 'X') { nRute_poeng[8] += 7; }
	if (cRute[4] == 'O' && cRute[1] == 'O') { nRute_poeng[7] += 10; }
	if (cRute[4] == 'X' && cRute[1] == 'X') { nRute_poeng[7] += 7; }
	if (cRute[4] == 'O' && cRute[2] == 'O') { nRute_poeng[6] += 10; }
	if (cRute[4] == 'X' && cRute[2] == 'X') { nRute_poeng[6] += 7; }
	if (cRute[4] == 'O' && cRute[3] == 'O') { nRute_poeng[5] += 10; }
	if (cRute[4] == 'X' && cRute[3] == 'X') { nRute_poeng[5] += 7; }
	if (cRute[4] == 'O' && cRute[5] == 'O') { nRute_poeng[3] += 10; }
	if (cRute[4] == 'X' && cRute[5] == 'X') { nRute_poeng[3] += 7; }
	if (cRute[4] == 'O' && cRute[6] == 'O') { nRute_poeng[2] += 10; }
	if (cRute[4] == 'X' && cRute[6] == 'X') { nRute_poeng[2] += 7; }
	if (cRute[4] == 'O' && cRute[7] == 'O') { nRute_poeng[1] += 10; }
	if (cRute[4] == 'X' && cRute[7] == 'X') { nRute_poeng[1] += 7; }
	if (cRute[4] == 'O' && cRute[8] == 'O') { nRute_poeng[0] += 10; }
	if (cRute[4] == 'X' && cRute[8] == 'X') { nRute_poeng[0] += 7; }
	//hard ai
	if (nGame_mode == 4)
    {
        if (cRute[4] == 'O')
        {
            if (cRute[1] == 'X' && cRute[3] == 'X') { nRute_poeng[0] += 7; }
            else if (cRute[1] == 'X' && cRute[5] == 'X') { nRute_poeng[2] += 7; }
            else if (cRute[5] == 'X' && cRute[7] == 'X') { nRute_poeng[8] += 7; }
            else if (cRute[7] == 'X' && cRute[3] == 'X') { nRute_poeng[6] += 7; }
            if (cRute[3] == 'X' && (cRute[2] == 'X' || cRute[8] == 'X'))
            {
                nRute_poeng[0] += 7;
            }
            if ((cRute[0] == 'X' || cRute[6] == 'X') && cRute[5] == 'X')
            {
                nRute_poeng[2] += 7;
            }
            if ((cRute[0] == 'X' || cRute[2] == 'X') && cRute[7] == 'X' )
            {
                nRute_poeng[8] += 7;
            }
            if ((cRute[6] == 'X' || cRute[8] == 'X') && cRute[1] == 'X')
            {
                nRute_poeng[5] += 7;
            }
        }
    }
}

void comp_player(char cPlayer)  //ai :) kan brukes med spiller 1 eller 2, X eller O... jeii i might ad..
{
	if (nGame_mode == 2) //easy computer... Det er HELT random hvor han setter :)
    {
        int nDummy;
        nDummy = rand() % 9;
        while (sjekk_rute(nDummy) == true)
        {
            nDummy = rand() % 9;
        }
        cRute[nDummy] = cPlayer;
    }
	else
    {
        cRute[finn_max()] = cPlayer;
        sette_poeng(finn_max());
    }
}

void welcome() //velkomstskjerm
{
	system("cls");
	
	int nValg = 0;
	char cValg[100];
	
	std::cout<<"Welcome to Tic Tac Toe v.1.00 by Lord Sankra, 2003"<<std::endl<<std::endl;
	std::cout <<"\n1. 2 Player\n2. Easy Computer\n3. Medium Computer\n4. Hard Computer\n\nChoose game mode: ";
	std::cin.getline (cValg,100);
	nValg = atoi (cValg);
	
	switch (nValg)
    {
        case 1:
			nGame_mode = 1;
			break;
            
        case 2:
			nGame_mode = 2;
			break;
            
        case 3:
			nGame_mode = 3;
			break;
            
        case 4:
			nGame_mode = 4;
			break;
            
        default:
			std::cout<<"\nYou must insert a valid number!\n\n";
			welcome();
			break;
    }
}

int main() //Go go go..
{
	char cPlayer;
	int nCounter = 0;
    
	srand(time(0)); //seeder random generatoren slik at vi fÂr forskjellige tall for hver gjennomkj¯ring
    
	welcome();
	tegn_brett();
    
	for (int nX = 0; nX <= 8; nX++) //T¯mmer rutene
    {
        cRute[nX] = ' ';
    }
	
	while (true) //Main game loop
    {
        cPlayer = 'X'; //Spiller 1 sin tur
        nPlayer = 1;
        input(cPlayer);
        tegn_brett();
        nCounter ++;
        cPlayer = 'O'; //Spiller 2 sin tur
        nPlayer = 2;
        if (nGame_mode == 1)
        {
            input(cPlayer);
        }
        else
        {
            comp_player(cPlayer);
        }
        if (vinner('X') == true) //Vinner player 1?
        {
            break;
        }
        if (nCounter == 9) //Uavgort?
        {
            nPlayer = 3;
            break;
        }
        
        tegn_brett();
        nCounter ++;
        if (vinner('O') == true) //Vinner player 2?
        {
            break;
        }
    }
    
    switch (nPlayer)
    {
        case 1:				
            std::cout<<"Player 1 won!!!"<<std::endl<<std::endl;
            break;
            
        case 2:
            std::cout<<"Player 2 won!!!"<<std::endl<<std::endl;
            break;
            
        case 3:
            std::cout<<"It's a draw!!!"<<std::endl<<std::endl;
            break;
            
        default:
            std::cout<<"KAOS!!!!!!!!!!!!!!"<<std::endl<<std::endl; //It will never have to come to this...
            break;
    }
    system("pause");
    system("cls");
    return 0;
}
