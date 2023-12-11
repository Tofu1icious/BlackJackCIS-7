#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h> 
#include <vector>
#include <string>

using namespace std;

//------------------
int checkInputMenu();
int checkInput(int, int);
void drawCards(int[], int[]);
//------------------
void gameEngine(double);
void defineCards(int[], string[], string[], int[]);
void checkBalance(double);
void checkBet(double&, double);
void nextMove(int[], int[],int[], int[],  string[], string[], string[], string[], double&, double&);
void checkIfBust(int&, int&, double&, double&);
void checkIfBustHouse(int&, int&, double&, double&);
void checkIfWon21(int& ,int& ,double& ,double& );
void checkIfWon21House(int& ,int& ,double& ,double& );
void checkIfWon21House(int& ,int&, double& ,double& );
void compareCards(int& ,int&, int&, double& ,double&);
int playAgain();
//------------------
int  displayMenu();
void displayHouseCards(int[], int[], string[], string[]);
void displayHouseCards2(int[], int[], string[], string[]);
void displayPlayerCards(int[],int[], string[], string[]);
void displayBlackJack();
void dealingCard(int[], int[], string[], string[], int); 

int main()
{
    int input = displayMenu();
    if (input == 2)
    {
        cout << "Thank you for playing!";
        return 0;
    }
    else
    {
        double balence = 5;
        cout << "Starting Balence is $5\n";
        gameEngine(balence);
    }
}

//=====================GAME ENGINE============================
void gameEngine(double balence)
{
    displayBlackJack();
    cout << "What is your bet?\n";
    double bet;
    cin >> bet; 
    checkBet(bet, balence);
    int houseCards[10];
    int playerCards[10];
    int houseCardsValue[10];
    int playerCardsValue[10];
    string dispDeck[10];
    string suit[10];
    string dispDeck1[10];
    string suit1[10];

    checkBalance(balence);
    drawCards(houseCards, playerCards);
    
    displayHouseCards(houseCards, houseCardsValue, dispDeck, suit);
    displayPlayerCards(playerCards, playerCardsValue, dispDeck1, suit1);

    nextMove(playerCards, playerCardsValue, houseCards, houseCardsValue, dispDeck, suit, dispDeck1, suit1, balence, bet);
  int again = 0;
  if(balence != 0)
    {
      again = playAgain();
    }
  else
    {
      cout << "You have no more money left. Thank you for playing!\n";
    }
  if (again == 1)
    {
        gameEngine(balence);
    }
  else
    {
        checkBalance(balence);
        main(); 
    }
}

void checkBalance(double x)
{
    cout << "==========================\n";
    cout << "current Balence: $" << x << " \n";
    cout << "==========================\n";
}

void drawCards(int houseCards[], int playerCards[])
{
    srand(static_cast<unsigned int>(time(0)));
    vector<int> deck(52);
    int temp[10];
    for (int i = 0; i < 52; ++i)
    {
         deck[i] = i + 1;
    }
    for (int i = 0; i < 10; ++i)
    {
        temp[i] = rand() % deck.size();
        houseCards[i] = deck[temp[i]];
        deck.erase(deck.begin() + temp[i]);
      
        temp[i] = rand() % deck.size();
        playerCards[i] = deck[temp[i]];
        deck.erase(deck.begin() + temp[i]);
    }
}
void nextMove(int playerCards[], int playerCardsValue[],int houseCards[], int houseCardsValue[], string card[], string type[], string card1[], string type1[], double& balence, double& bet)
{  
  int total = 0;
  int temp = 0;
  int temp2 = 0;
  int totalHouse = 0;
  
  cout << "Please respond with numerical input! \n";
  cout << "(1) hit\n";
  cout << "(2) stand\n";
  cout << "(3) double down\n";
  int input = checkInput(1, 3);
  for(int i = 0; i < 8; i++)
    {
    switch (input)
      {
        case 1:       
          dealingCard(playerCards, playerCardsValue, card1, type1, i+2); 
          cout << "Current Value: ";
          for (int j = 0; j < i+3; j++)
            {
              total += playerCardsValue[j];
            }          
          cout << total << endl; 
          temp = total; 
          checkIfWon21(total, i, balence, bet);
          checkIfBust(total, i, balence, bet);
          break;
        case 2:
          cout << "You have chosen to stand\n";
          cout << "The House's cards are: \n";
          displayHouseCards2(houseCards, houseCardsValue, card, type);
          cout << "Current Value: ";
          totalHouse = 0; 
          for (int j = 0; j < i+2; j++)
            {
              totalHouse = totalHouse + houseCardsValue[j];
              temp2 = totalHouse;
            }          
          cout << temp2 << endl;
          if (totalHouse > 16)
          {
            cout << "The House has chosen to stand\n";
            checkIfWon21House(totalHouse, i, balence, bet);
          }
          else
          {
            while(totalHouse < 17)
            {
              cout << "The House draws\n";
              dealingCard(houseCards, houseCardsValue, card, type, i+2);
              cout << "New Value: ";
              totalHouse = 0;
              for (int j = 0; j < i+3; j++)
                {
                  totalHouse += houseCardsValue[j];
                }
               cout << totalHouse << endl; 
              temp2 = totalHouse;
              i++;
            }
          }
          checkIfBustHouse(totalHouse, i, balence, bet);
          compareCards(temp2, temp, i, balence, bet); 
          break;
        case 3: 
          temp2 = 0; 
          temp = 0; 
          cout << "You chose to double down\n";
          bet = bet * 2;
          dealingCard(playerCards, playerCardsValue, card1, type1, i+2); 
          cout << "Current Value: ";
          for (int j = 0; j < i+3; j++)
            {
              total += playerCardsValue[j];
            }          
          cout << total << endl; 
          temp = total; 
          checkIfWon21(total, i, balence, bet);
          checkIfBust(total, i, balence, bet);
          cout << "The House's cards are: \n";
          displayHouseCards2(houseCards, houseCardsValue, card, type);
          cout << "Current Value: ";
          totalHouse = 0; 
          for (int j = 0; j < i+2; j++)
            {
              totalHouse = totalHouse + houseCardsValue[j];
              
            }  
          temp2 = totalHouse;
          cout << temp2 << endl;
          if (totalHouse > 16)
          {
            cout << "The House has chosen to stand\n";
            checkIfWon21House(totalHouse, i, balence, bet);
          }
          else
          {
            while(totalHouse < 17)
            {
              cout << "The House draws\n";
              dealingCard(houseCards, houseCardsValue, card, type, i+2);
              cout << "New Value: ";
              totalHouse = 0;
              for (int j = 0; j < i+3; j++)
                {
                  totalHouse += houseCardsValue[j];
                }
               cout << totalHouse << endl; 
              temp2 = totalHouse;
              i++;
            }
          }
          checkIfBustHouse(temp2, i, balence, bet);
          compareCards(temp2, temp, i, balence, bet); 
          i = 8;
          break;
        default:
          cout << "Error!\n";
          break;
      }
      
      if(i != 8 )
      {
        cout << "Please respond with numerical input! \n";
        cout << "(1) hit\n";
        cout << "(2) stand\n";
        input = checkInput(1, 2);
      }
    }
}
void checkIfWon21(int& total,int& i,double& balence,double& bet)
{
  if(total == 21)
  {
    i = 8; 
    cout << "You won the hand!\n";
    balence += bet;
    cout << "Your new balence is: $" << balence << endl;
    total = 0;
  }
}
void checkIfWon21House(int& total,int& i,double& balence,double& bet)
  {
    if(total == 21)
    {
      i = 8; 
      cout << "The House wins the hand!\n";
      balence -= bet;
      cout << "Your new balence is: $" << balence << endl;
      total = 0;
    }
  }
void checkIfBust(int& total,int& i, double& balence,double& bet)
{
  if (total > 21)
  {
    i = 8;
    cout << "Sorry you've gone bust!\n";
    balence -= bet;
  }
  else
  {
    total = 0;
  }  
}
void checkIfBustHouse(int& total,int& i, double& balence,double& bet)
{
  if (total > 21)
  {
    i = 8;
    cout << "The House has gone bust!\n";
    balence += bet;
  }
  total = 0;
}
void compareCards(int& totalHouse, int& total, int& i, double& balence, double& bet)
{
  if (totalHouse > total)
  {
    i = 8;
    cout << "The House wins the hand!\n";
    balence -= bet; 
  }
  else if (totalHouse == total)
    {
      i = 8;
      cout << "There is a Tie, no payout!\n"; 
    }
  else
  {
    i = 8;
    cout << "You win the hand!\n";
    balence += bet; 
  }
}

//=====================LOGIC FUNCTIONS============================
int checkInputMenu()
{
    int input;
    cin >> input;
    if (input != 1 && input != 2)
    {
        cout << "Please input a valid number!\n";
        checkInputMenu();
    }
    return input;
}
int checkInput(int x, int y)
{
  int input;
  cin >> input;
  while (input < 1 || input > 3)
    {
      cout << "Please input a valid number!\n";
      cin >> input;
    }
  return input;
}
void checkBet(double& bet, double balence)
{
  if(bet < 0)
  {
    cout << "Please input a valid bet! Yes you can bet 0! But not lesser values.\n";
    cin >> bet;
    checkBet(bet, balence);
  }
  if(bet > balence)
  {
    cout << "Please input a valid bet! Your bet exceeds your total balance.\n";
    cout << "Your total balance is: $" << balence << endl;
    cin >> bet;
    checkBet(bet, balence);
  }
}
void defineCards(int house[], string suit[], string dispDeck[], int value[])
{
    for (int i = 0; i < 10; ++i)
      {
        if (house[i] < 14)
        {
          suit[i] = " SPADES ";
        }
        else if (house[i] < 28)
        {
          suit[i] = " CLUBS  ";
        }
        else if (house[i] < 42)
        {
          suit[i] = " HEARTS ";
        }
        else
        {
          suit[i] = "DIAMOND ";
        }
        if(house[i] == 1 || house[i] == 14 || house[i] == 27 || house[i] == 40)
          {
            dispDeck[i] = "A ";
            value[i] = 1;
          }
        else if(house[i] == 2 || house[i] == 15 || house[i] == 28 || house[i] == 41)
          {
            dispDeck[i] = "2 ";
            value[i] = 2;
          }
        else if(house[i] == 3 || house[i] == 16 || house[i] == 29 || house[i] == 42)
          {
            dispDeck[i] = "3 ";
            value[i] = 3;
          }
        else if(house[i] == 4 || house[i] == 17 || house[i] == 30 || house[i] == 43)
          {
            dispDeck[i] = "4 ";
            value[i] = 4;
          }
        else if(house[i] == 5 || house[i] == 18 || house[i] == 31 || house[i] == 44)
          {
            dispDeck[i] = "5 ";
            value[i] = 5;
          }
        else if(house[i] == 6 || house[i] == 19 || house[i] == 32 || house[i] == 45)
          {
            dispDeck[i] = "6 ";
            value[i] = 6;
          }
        else if(house[i] == 7 || house[i] == 20 || house[i] == 33 || house[i] == 46)
          {
            dispDeck[i] = "7 ";
            value[i] = 7;
          }
        else if(house[i] == 8 || house[i] == 21 || house[i] == 34 || house[i] == 47)
          {
            dispDeck[i] = "8 ";
            value[i] = 8;
          }
        else if(house[i] == 9 || house[i] == 22 || house[i] == 35 || house[i] == 48)
          {
            dispDeck[i] = "9 ";
            value[i] = 9;
          }
        else if(house[i] == 10 || house[i] == 23 || house[i] == 36 || house[i] == 49)
          {
            dispDeck[i] = "10";
            value[i] = 10;
          }
        else if(house[i] == 11 || house[i] == 24 || house[i] == 37 || house[i] == 50)
          {
            dispDeck[i] = "J ";
            value[i] = 10;
          }
        else if(house[i] == 12 || house[i] == 25 || house[i] == 38 || house[i] == 51)
          {
            dispDeck[i] = "Q ";
            value[i] = 10;
          }
        else 
          {
            dispDeck[i] = "K ";
            value[i] = 10;
          }
        
      }
}
// ===================================DISPLAYS===============================

void displayHouseCards(int house[],int type[], string dispDeck[], string suit[])
{  
    defineCards(house, suit, dispDeck, type);
    cout << "-----------House--------------\n";
    cout << "------------------------------\n";
    cout << "  ________     ________\n";
    cout << " |$$$$$$$$|   |" << dispDeck[1] << "      |\n";
    cout << " |$$$$$$$$|   |        |\n";
    cout << " |$$CIS7$$|   |" << suit[1] << "|\n";
    cout << " |$CASINO$|   |        |\n";
    cout << " |$$$$$$$$|   |        |\n";
    cout << " |$$$$$$$$|   |      " << dispDeck[1] << "|\n";
    cout << " |________|   |________|\n";

}

void displayPlayerCards(int player[], int type[], string dispDeck1[], string suit1[])
{    
    defineCards(player, suit1, dispDeck1, type);
    cout << "\n\nYour Card's Value: " << type [0] + type [1] << "\n";
    cout << "------------------\n";
    cout << "Your Cards: \n";
    cout << "  ________     ________\n";
    cout << " |" << dispDeck1[0] << "      |   |" << dispDeck1[1] << "      |\n";
    cout << " |        |   |        |\n";
    cout << " |" << suit1[0] << "|   |" << suit1[1] << "|\n";
    cout << " |        |   |        |\n";
    cout << " |        |   |        |\n";
    cout << " |      " << dispDeck1[0] << "|   |      " << dispDeck1[1] << "|\n";
    cout << " |________|   |________|\n";
}
void displayBlackJack()
{
    cout << R"(
    | $$__  $$| $$                    | $$         |__  $$                    | $$      
    | $$  \ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$      | $$  /$$$$$$   /$$$$$$$| $$   /$$
    | $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/      | $$ |____  $$ /$$_____/| $$  /$$/
    | $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/  /$$  | $$  /$$$$$$$| $$      | $$$$$$/ 
    | $$  \ $$| $$ /$$__  $$| $$      | $$_  $$ | $$  | $$ /$$__  $$| $$      | $$_  $$ 
    | $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \  $$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$ \  $$
    |_______/ |__/ \_______/ \_______/|__/  \__/ \______/  \_______/ \_______/|__/  \__/

)";
}

int displayMenu()
{
    cout << "Welcome to CIS 7 Casino BlackJack! \n";
    cout << "-----------------------------------------\n";
    cout << "Please input numerical values only!\n";
    cout << "1. Play BlackJack \n";
    cout << "2. Quit\n";
    cout << "-----------------------------------------\n";
    int input = checkInputMenu();
    return input;
}
void dealingCard(int card[],int type[], string dispDeck[], string suit[], int i)
{
  cout << "Dealing Card... \n";
  cout << "New Card dealt: \n";
  cout << "   ________\n";
  cout << "  |" << dispDeck[i] << "      |\n";
  cout << "  |        |\n";
  cout << "  |" << suit[i] << "|\n";
  cout << "  |        |\n";
  cout << "  |        |\n";
  cout << "  |      " << dispDeck[i] << "|\n";
  cout << "  |________|\n";
}
int playAgain()
{
  cout << "Would you like to play again? \n";
  cout << "1. Yes \n";
  cout << "2. No \n";
  int input = checkInput(1,2);
  return input;
}
void displayHouseCards2(int house[],int type[], string dispDeck[], string suit[])
{  
    cout << "-----------House--------------\n";
    cout << "------------------------------\n";
    cout << "  ________     ________\n";
    cout << " |" << dispDeck[0] << "      |   |" << dispDeck[1] << "      |\n";
    cout << " |        |   |        |\n";
    cout << " |" << suit[1] << "|   |" << suit[1] << "|\n";
    cout << " |        |   |        |\n";
    cout << " |        |   |        |\n";
    cout << " |      " << dispDeck[0] << "|   |      " << dispDeck[1] << "|\n";
    cout << " |________|   |________|\n";

}