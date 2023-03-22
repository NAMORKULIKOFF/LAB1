#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>


using namespace std;


int main()
{
    string SHCHISLO,BUFFstr;
    bool flag;
    int BUFF,counter=0,counterBUFF=0,MNOJ=1,SMESHPOR=0,STEPEN,INT_CH=0,N;
    double result,DR_CH=0;
    cout << "ВВЕДИТЕ ЧИСЛО В ШЕСТНАДЦАТИРАЗРЯДНОЙ ФОРМЕ:";
    cin >> SHCHISLO;
    cout << "ВВЕДИТЕ СКОЛЬКО БИТ В ЧИСЛЕ:";
    cin >> N;
    int *BUFFDVOICH = new int[4];
    int *EXTRA = new int[2];
    int *DVOICH = new int[N];

    if (N==32){
        EXTRA[0] = 8;
        EXTRA[1] = 127;

    }
    if (N==64){
        EXTRA[0] = 11;
        EXTRA[1] = 1023;
    }

    //if (N==128)


    for(const char c: SHCHISLO)
    {
        flag = false;
        if (c == 'A'){
            BUFF = 10;
            flag=true;
        }

        if (c == 'B'){
            BUFF = 11;
            flag=true;
        }

        if (c == 'C'){
            BUFF = 12;
            flag=true;
        }

        if (c == 'D'){
            BUFF = 13;
            flag=true;
        }

        if (c == 'E'){
            BUFF = 14;
            flag=true;
        }

        if (c == 'F'){
            BUFF = 15;
            flag=true;
        }
        if (flag==false){
            BUFFstr = c;
            BUFF = stoi(BUFFstr);
            }
        counterBUFF=0;
        while (BUFF>0){
                BUFFDVOICH[counterBUFF] = BUFF % 2;
                BUFF /= 2;
                counterBUFF++;
        }
        for (int i=3;i>-1;i--){
            DVOICH[counter] = BUFFDVOICH[i];
            counter++;
            BUFFDVOICH[i]=0;
        }
    }
    for(int i=0;i<N;i++){
        cout << DVOICH[i];
    }
    cout << endl;

    if (DVOICH[0]==1)
        MNOJ=-1;
    STEPEN = 0;
    for(int i=EXTRA[0];i>0;i--){
        if (DVOICH[i]==1)
            SMESHPOR+=pow(2,STEPEN);
        STEPEN++;
    }
    cout << SMESHPOR << endl;

    if (SMESHPOR<EXTRA[1]){
        STEPEN = SMESHPOR - EXTRA[1];
        DR_CH = 0;
        DR_CH+=pow(2,STEPEN);
        STEPEN--;
        for(int i=EXTRA[0]+1;i<N;i++){
            if (DVOICH[i]==1)
                DR_CH+=pow(2,STEPEN);
            STEPEN--;
        }
        result = MNOJ*DR_CH;
    }
    else{
        SMESHPOR = SMESHPOR - EXTRA[1];
        STEPEN=0;
        INT_CH=0;
        DR_CH=0;
        for(int i=SMESHPOR+EXTRA[0];i>EXTRA[0];i--){
            if (DVOICH[i]==1)
                INT_CH+=pow(2,STEPEN);
            STEPEN++;
        }

        INT_CH+=pow(2,STEPEN);
        STEPEN=-1;
        for(int i=SMESHPOR+EXTRA[0]+1;i<N;i++){
            if (DVOICH[i]==1)
                DR_CH+=pow(2,STEPEN);
            STEPEN--;
        }
    result = MNOJ*(INT_CH+DR_CH);

    }

    cout << result;


  return 0;
}
