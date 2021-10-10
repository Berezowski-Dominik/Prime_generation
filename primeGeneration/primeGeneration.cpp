#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

//  Krok 1 wyznaczamy liczby pierwsze dla wartosci od 2 do sqrt(MAX) - wykonuje to funkcja sieteEratostenesa
//  Przyklad: przedzia³ liczb 10 - 121 czyli otrzymuje tablice liczb 2, 3, 5, 7, 11

//  Krok 2 robimy sito Eratostenesa segmentowane
//  Przyklad: przedzia³ liczb 10 - 121 
//  Bierzemy pierwsz¹ liczbe pierwsz¹ to jest 2 i eliminujemy z przedzia³u wielokrotnoœci tej liczby tj 10, 12 .. 120
//  Tak samo postepujemy z nastepna liczba pierwsza czyli 3 elimunujemy z przedzia³u wielokrotnoœci tj 12, 15 .. 120
//  Tak postepujemy z kazda liczba pierwsza uzyskana w Kroku 1
//  Pozostale liczby, które pozosta³y s¹ liczbami pierwszymi


void sieteEratostenesa(int max, vector <int>& primeNumbersTable);

void segmentedSieveEratostenesa(int min, int max, vector <int> helpPrimeTable);

int main()
{
    int interval;
    int maxValue = 0;

    string help;
    
    vector <int> lastNumbers;
    vector <int> firstNumbers;

    vector <int> helpPrimeTable;

    vector <string> inputString;
    
    getline(cin, help);
    interval = stoi(help);

    for (int i = 0; i < interval; i++)
    {
        getline(cin, help);
        inputString.push_back(help);
        firstNumbers.push_back(stoi(inputString[i].substr(0)));
        std::size_t pos = inputString[i].find(" ");
        lastNumbers.push_back(stoi(inputString[i].substr(pos)));

        if (maxValue < stoi(inputString[i].substr(pos)))
            maxValue = stoi(inputString[i].substr(pos));
    }

    for (int i = 0; i < interval; i++)
    {
        sieteEratostenesa(lastNumbers[i], helpPrimeTable);
        segmentedSieveEratostenesa(firstNumbers[i], lastNumbers[i], helpPrimeTable);
        helpPrimeTable.clear();
    }
    

    return 0;
}

void sieteEratostenesa(int max, vector <int>& primeNumbersTable)
{
    int size = sqrt(max) + 1;
    bool* trueTable = new bool[size];

    trueTable[0] = false;
    trueTable[1] = false;

    for (int i = 2; i < size; i++)
    {
        trueTable[i] = true;
    }

    for (int i = 2; i < size; i++)
    {
        if (trueTable[i] == true)
        {
            int j = 2 * i;
            while (j < size)
            {
                trueTable[j] = false;
                j = j + i;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (trueTable[i] == true)
        {
            primeNumbersTable.push_back(i);
        }
    }

    delete[] trueTable;
}

void segmentedSieveEratostenesa(int min, int max, vector <int> helpPrimeTable)
{
    if (min == 1)
        min++;

    int size = max - min + 1;

    bool* trueTable = new bool[size];

    for (int i = 0; i < size; i++)
    {
        trueTable[i] = true;
    }

    for (int i = 0; i < helpPrimeTable.size(); i++)
    {
        int primeNumber = helpPrimeTable[i];
        int help_number = primeNumber * primeNumber;

        if (help_number < min) 
            help_number = ((min + primeNumber - 1) / primeNumber) * primeNumber;

        for (; help_number <= max; help_number += primeNumber)
        {
            trueTable[help_number - min] = false;
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (trueTable[i] == true)
        {
            cout << min + i << endl;
        }
    }

    cout << endl;

    delete[] trueTable;
}
