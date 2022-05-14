#include <math.h>
#include "StAcK.h"
#include "LiSt.h"
#include <time.h>

/** \file main.c
 * G³ówny plik programu.
 * Zawiera funkcje odpowiadaj¹ce za konwersjê zapisu ONP oraz obliczanie wprowadzonego dzia³ania.
 */

/**
*Funkcja sprawdza, czy wczytywany znak jest operatorem.
*
*Funkcja sprawdza, czy wczytany znak jest operatorem dodawania, odejmowania,
* mno¿enia, dzielenia lub potêgowania (+, -, *, /, ^). Sprawdzane jest to za pomoc¹ instrukcji if.
*@param a wczytywany znak do sprawdzenia
*@return 1 - jeœli znak jest operatorem
*@return 0 - jeœli znak nim nie jest
*/
int is_Operator(char a)
{
    if (a == '+' || a == '-' || a == '*' || a == '/' || a == '^')
    {
        return 1;
    }
    return 0;
}

/**
*Funkcja sprawdza, czy wczytywany znak jest cyfr¹ lub kropk¹.
*
*Funkcja sprawdza, czy wczytany znak jest cyfr¹ z zakresu 0-9 lub kropk¹.
* Sprawdzane jest to za pomoc¹ instrukcji if.
*@param a wczytywany znak do sprawdzenia
*@return 1 - jeœli znak jest cyfr¹ lub kropk¹
*@return 0 - jeœli znak nie jest cyfr¹ lub kropk¹
*/
int is_Number(char a)
{
    if ((a <= '9' && a >= '0') || a == '.')
    {
        return 1;
    }
    return 0;
}

/**
*Funkcja okreœla i zwraca ???
*
*????
*
*@param op wczytywany operator
*@return 1- jeœli ???
*@return 0 - jeœli ???
*/
int operator_associativity(char op)
{
    //associativity: 0 is left         1 is right
    if (op == '+' || op == '-' || op == '*' || op == '/')
    {
        return 0;
    }
    else if (op == '^')
    {
        return 1;
    }
    return 0;
}

/**
*Funkcja okreœla i zwraca pierwszeñstwo operatorów.
*
*Pierwszeñstwo operatorów ustala kolejnoœæ, w jakiej operatory
* s¹ ewaluowane. Operatory z wy¿szym pierwszeñstwem s¹ wykorzystywane jako pierwsze.
* Najwy¿sze pierwszeñstwo otrzyma operator potêgowania, nastêpnie operatory mno¿enia i dzielenia, a na koñcu dodawania i odejmowania.
* Sprawdzanie operatorów jest wykonane za pomoc¹ instrukcji if.
*@param op wczytywany operator
*@return 4 - jeœli jest to operator potêgowania
*@return 3 - jeœli jest to operator mno¿enia lub dzielenia
*@return 2 - jeœli jest to operator dodawania lub odejmowania
*@return 0 - jeœli nie jest to ¿aden z obs³ugiwanych operatorów
*/
int operator_precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 2;
    }
    else if (op == '*' || op == '/')
    {
        return 3;
    }
    else if (op == '^')
    {
        return 4;
    }
    return 0;
}

/**
*Funkcja zmienia zapis z postaci infix na postfix i zapisuje ja w liscie dwukierunkowej.
*
*Funkcja wykorzystuje do swojego dzialania algorytm stacji rozrzadowej (eng. shunting yard algorithm) autorstwa Edsgera Dijkstry
*Glowna ptela while przechodzi przez kolejne elementy tablicy equation i na podstawie odpowiednich instrukcji warunkowych decudyje czy
*wczytana dana zapisac od razu na liscie output czy na stosie ops dodatkowo niktore operatory jesli maja wyzsze pierwszenstwo
*moga wymusic oproznienie czesci stosu i wpisanie go na liste output, napotkanie lewego nawiasu powoduje wpisanie go na stos operatorow,
*z kolei napotkanie prawego nawiasu powoduje oproznianie stosu operatorow i dodawanie tej zawartosci do list w ktorej jest zapisywana postac postfixowa
*to oproznianie dzieje sie dopoki nie napotkamy lewego nawiasu lub skonczy nam sie stos. Jesli petla napotka pusty element w tablicy equation czyli koniec
*dzialania to funkcja zaczyna oprozniac caly stos ops i dodaje go do listy output pomijajac niedopasowane lewe nawiasy. Po wykonaniu tej czynnosci
*zatrzymana zostaje glowna petla while znajdujaca sie w funkcji.
*
*@param equation[][] wczytywana tablica tablic w ktorej znajduja sie elementy dzialania wpisane w postaci infix
*@param ops wskaznik na wskaznik szczytu stosu na ktorym beda zapisywane operatory oraz nawiasy
*@param output wskaznik na wskaznik listy dwukierunkowej na ktorej ostatecznie zapisywana jest postac postfixowa dzialania
*@param tmp tumczasowy wskaznik na element usuniety ze stosu przy uzyciu funkcji pop, jako ze pop nie zwalnia pamieci zainicjowanej dla danej trzeba to zrobic manualnie na wskazniku tmp
*@param iterator przy kolejnych wykonaniach pierwszej petli while pozwala na przechodzenie po kolejnych elementach tablicy equation[]][]
*@return 1 - jeœli funkcja zakonczyla dzialanie
*/
int RNPconverter(char equation[6553][100], node ** ops, struct dll_node ** output)
{
    node *tmp;
    int iterator = 0;
    while (1)
    {
        if (is_Number(equation[iterator][0]))
        {
            append(output, equation[iterator]);
        }
        else if (is_Operator(equation[iterator][0]))
        {
            while ((( * ops) != NULL) &&
                    ((operator_precedence(( * ops) -> arg[0]) > operator_precedence(equation[iterator][0])) ||
                     (operator_precedence(( * ops) -> arg[0]) == operator_precedence(equation[iterator][0]) && operator_associativity(equation[iterator][0]) == 0)) &&
                    (equation[iterator][0] != '('))
            {
                tmp=pop(ops);
                append(output, tmp -> arg);
                free(tmp);
            }
            * ops = push(( * ops), equation[iterator]);

        }
        else if (equation[iterator][0] == '(')
        {
            * ops = push(( * ops), equation[iterator]);
        }
        else if (equation[iterator][0] == ')')
        {
            while ( * ops)
            {
                if (( * ops) -> arg[0] == '(')
                {
                    break;
                }
                tmp=pop(ops);
                append(output, tmp -> arg);
                free(tmp);
            }

            if (( * ops))
            {
                if (( * ops) -> arg[0] == '(')
                {
                    free(pop(ops));

                }

            }



        }
        if (equation[iterator][0] == '\0')
        {
            while (( * ops))
            {
                if (( * ops) -> arg[0] == '(')
                {
                    free(pop(ops));
                }
                else
                {
                    tmp=pop(ops);
                    append(output, tmp -> arg);
                    free(tmp);
                }
            }
            break;
        }
        iterator += 1;
    }
    return 1;
}

int count(struct dll_node ** node)
{
    struct dll_node * iter = * node;
    while (iter)
    {
        if (iter -> data[0] == '(' || iter -> data[0] == ')')
        {
            printf("\nNieodpowienio dobrane nawiasy\n");
            return 0;
        }
        if (is_Operator(iter -> data[0]))
        {
            double a = atof(iter -> prev -> prev -> data);
            double b = atof(iter -> prev -> data);
            delete_node(node, iter -> prev -> prev);
            delete_node(node, iter -> prev);
            switch (iter -> data[0])
            {
            case '+':
                a += b;
                break;
            case '-':
                a -= b;
                break;
            case '*':
                a *= b;
                break;
            case '/':
                if (b == 0)
                {
                    printf("\nNie dziel przez zero\n");
                    return 0;
                }
                a /= b;
                break;
            case '^':
                a = pow(a, b);
                break;
            }
            sprintf(iter -> data, "%lf", a);
            //printf("\n");
            //print(*node);
            //printf("\n");

        }
        if (iter)
        {
            iter = iter -> next;
        }
    }
    return 1;
}

/**
*Petla glowna  "do while" zapewnia tylko i wylacznie mozliwosc ponowne go wpisywania kolejnych dzialan
*w niej zagniezdzona jest petla while ktora przechodzi przez kazdy znak osobno zapisanego przez uzytkownika dzialania
*i decyduje gdzie zostanie wpisany znak jesli sprawdzony element w ktorym zapisany jest sprawdzany element jest liczba od
*1 do 9 lub jest kropka (uzylismy zamiast przecinka) zostaja zapisane w tablicy arrOfElements inkrementujac currentSpotOfElement
*gezieki temy w drugim wymiarze zapisana zostaje cala liczba, jesli petla napotka jednak nawias badz inny operator to currentSpotOfElement
*zostaje wyzerowany a currentSpot zostaje zwiekszony o jeden. Jesli zostanie tutaj rozpoznany lewy nawias a przed nim postawiona zostala
*liczba, automatycznie zostanie najpierw dodany znak mnozenia, a dopero potem lewy nawias. Po dodaniu operatora currentSpot ponownie
*zostaje zwiekszony o jeden aby przygotowac miejsce dla potecjalnej liczby. W tej petli znajduje sie tez dodatkowy warunek jesli
*zostal dodany prawy nawias to multiplier_after_right zostaje ustawiony na 1, w nastepnym wykonaniu petli sprawdzona zostaje wartosc
*tej liczby. Jesli jest ona rowna 1 oraz nowo dodawany znak jest liczba to przed dodaniem znaku dodany zostaje znak mnozenia, currentSpot
*znow jest zwiekszany o 1 oraz multiplier_after_right jest zerowany. Dopiero po tym zabiegu zaczyna sie zapisywanie liczby.
*Podobny sposob jest zastosowany jezli zostanie wykryty lewy nawias.
*Po wykonaniu dzialania oraz wypisaniu wyniku tablica arrOfElements[][] zostaje wyczyszczona, currentSpot i currentSpotOfElement sa zerowane,
*lista output jest takze czyszcona razem ze stosem ops (zabieg na stosie jest zastosowany mimo ze jest pusty aby zapobiec potecjalnym bledom).
*Na koniec glownej petli "do while" uzytkownik jest pytany czy chce wpisac kolejne dzialanie lub nie
*
*
*@param arrOfElements[][] dwuwymiarowa tablica w ktorej zapisywane jest dzialanie w postaci infix
*@param currentSpot iterator przechodzacy po pierwszym wymiarze tablicy arrOfElements[][]
*@param currentSpotOfElement iterator przechodzacy po drugim wymiarze tablicy arrOfElements[][]
*@param c zapisuje znak wpisany przez uzytkownika zeby petla while mogla zapisac wpisany znak do tablicy
*@param multiplier_after_right indykator gdzie program ma automatycznie uzupelnic znak po nawiasie znakiem mnozenia
*@param loop znak ktory jest sprawdzany zeby stwierdzic czy uzytkownik che wpisac nowe dzialanie
*@param output dwukierunkowa lista wktorej zapisana zostanie postac postfixowa a nastepnie wynik dzialania
*@param ops stos na ktorym beda tymczasowo zapisywanie operatory w funkcji RNPconverter
*/

int main()
{
    char arrOfElements[6553][100];
    int currentSpot = 0;
    struct dll_node * output = NULL;
    node * ops = NULL;
    int currentSpotOfElement = 0;
    char c;
    int multiplier_after_right = 0;
    char loop = '1';
    do
    {
        printf("Wprowadzane rownanie nalezy zakonczyc znakiem '='\n");
        scanf(" %c", & c);


        while (c != '=' && c != '\n')
        {
            if (c != '\0' && c != ' ')
            {
                if (is_Number(c))
                {
                    if (multiplier_after_right)
                    {
                        multiplier_after_right = 0;
                        arrOfElements[currentSpot][0] = '*';
                        currentSpot += 1;
                    }
                    arrOfElements[currentSpot][currentSpotOfElement] = c;
                    currentSpotOfElement += 1;
                }
                else
                {
                    if (c == '(' && multiplier_after_right)
                    {
                        arrOfElements[currentSpot][0] = '*';
                        currentSpot += 1;

                    }
                    multiplier_after_right = 0;
                    if (is_Number(arrOfElements[currentSpot][0]))
                    {

                        currentSpot += 1;
                        if (c == '(')
                        {
                            arrOfElements[currentSpot][0] = '*';
                            currentSpot += 1;
                        }
                    }
                    currentSpotOfElement = 0;
                    arrOfElements[currentSpot][currentSpotOfElement] = c;
                    currentSpot += 1;
                    if (c == ')')
                    {
                        multiplier_after_right = 1;
                    }

                }
            }
            scanf("%c", & c);
        }

        printf("ONP: ");
        RNPconverter(arrOfElements, & ops, & output);
        print(output);
        if (count( & output))
        {
            printf("\nWynik: ");
            print(output);

        }

        for (; currentSpot >= 0; currentSpot--)
        {
            strncpy(arrOfElements[currentSpot], "\0", 100);
        }
        currentSpot = 0;
        currentSpotOfElement = 0;
        remove_list( & output);
        remove_stack( & ops);
        do
        {
            printf("\n\nCo chcesz zrobic?\n0.Zakonczyc program\n1.Zapisac kolejne dzialanie\n");
            scanf(" %c", & loop);

        }
        while (loop != '1' && loop != '0');
    }
    while (loop != '0');
    return 0;
}
