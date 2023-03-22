#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
    double INPUT_CHISLO;
    int KOLVO_CHISEL_POSLE_ZAPYATOY = 4;
    int INT_PIECE,BUFF,N;
    double FLOAT_PIECE,BUFF_FLOAT;
    int *EXTRA = new int[2];

    cout << "ВВЕДИТЕ СКОЛЬКО БИТ В ЧИСЛЕ: ";
    cin >> N;

    if (N==32){
        EXTRA[0] = 8;
        EXTRA[1] = 127;

    }
    if (N==64){
        EXTRA[0] = 11;
        EXTRA[1] = 1023;
    }
    if (N==128){
        EXTRA[0] = 15;
        EXTRA[1] = 16383;
    }

    int *INT_PIECE_DVOICH = new int[N-EXTRA[0]-1];
    int *DVOICH = new int[N];


    cout << "ВВЕДИТЕ ЧИСЛО: ";
    cin >> INPUT_CHISLO;

    INT_PIECE = INPUT_CHISLO;
    FLOAT_PIECE = INPUT_CHISLO-INT_PIECE;
    cout << INT_PIECE << endl;
    cout << FLOAT_PIECE << endl;
    BUFF = FLOAT_PIECE*pow(10,KOLVO_CHISEL_POSLE_ZAPYATOY);
    FLOAT_PIECE = BUFF/pow(10,KOLVO_CHISEL_POSLE_ZAPYATOY);
    cout << FLOAT_PIECE << endl;


    // определяем знак, запоминаем для первого бита
    DVOICH[0]=0;
    if (INT_PIECE<0){
        INT_PIECE*=-1;
        FLOAT_PIECE*=-1;
        DVOICH[0]=1;
    }

    if (INT_PIECE==0){
        FLOAT_PIECE*=-1;
        DVOICH[0]=1;
    }

    BUFF = INT_PIECE;

    int counter_int=0;

    while (BUFF>0){
        INT_PIECE_DVOICH[counter_int] = BUFF % 2;
        BUFF /= 2;
        if (BUFF==0){
            break;
        }
        counter_int++;
    }

    // такой размер мы выделяем для дробной части
    int razmer_massiva_float=N-EXTRA[0]-1-counter_int;

    int *FLOAT_PIECE_DVOICH = new int[128];

    BUFF_FLOAT = FLOAT_PIECE;

    for (int i=0;i<128;i++){
        BUFF_FLOAT*=2;
        if (BUFF_FLOAT>=1){
            FLOAT_PIECE_DVOICH[i]=1;
            BUFF_FLOAT-=1;
        }
        else{
            FLOAT_PIECE_DVOICH[i]=0;
        }
    }

    int kolvo = 0;
    // -1 потому что первую единицу не считаем
    for(int i=counter_int-1;i>=0;i--){
        cout << INT_PIECE_DVOICH[i];
        kolvo++;
    }
    cout << ",";
    for(int i=0;i<razmer_massiva_float;i++){
        cout << FLOAT_PIECE_DVOICH[i];
        kolvo++;
    }
    cout << endl;
    cout << kolvo << endl;

    // считаем смещенный порядок

    int SMESH;
    int *SMESH_DVOICH = new int[N-EXTRA[0]-1];
    int counter_smesh=0;
    int counter_smesh_for_float=0;
    int k=1;

    if (INT_PIECE==0){
        while(FLOAT_PIECE_DVOICH[counter_smesh_for_float]!=1){
            counter_smesh_for_float++;
        }
        counter_smesh_for_float++;
        SMESH = EXTRA[1]-counter_smesh_for_float;

            BUFF = SMESH;

    while (BUFF>0){
            SMESH_DVOICH[counter_smesh] = BUFF % 2;
            BUFF /= 2;
            if (BUFF==0){
                break;
            }
            counter_smesh++;
        }
    SMESH_DVOICH[counter_smesh+1] = 0;

    cout << "СМЕЩЕННЫЙ ПОРЯДОК: " << endl;
    for(int i=counter_smesh+1;i>=0;i--){
        cout << SMESH_DVOICH[i];
        DVOICH[k]=SMESH_DVOICH[i];
        k++;
    }
    cout << endl;

    }
    else{
        SMESH = EXTRA[1]+counter_int;

            BUFF = SMESH;
    while (BUFF>0){
            SMESH_DVOICH[counter_smesh] = BUFF % 2;
            BUFF /= 2;
            if (BUFF==0){
                break;
            }
            counter_smesh++;
        }
    cout << "СМЕЩЕННЫЙ ПОРЯДОК: " << endl;
    for(int i=counter_smesh;i>=0;i--){
        cout << SMESH_DVOICH[i];
        DVOICH[k]=SMESH_DVOICH[i];
        k++;
    }
    cout << endl;

    }


    // добавляем мантиссу в массив с двоичным числом

    for(int i=counter_int-1;i>=0;i--){
        DVOICH[k] = INT_PIECE_DVOICH[i];
        k++;
    }
    for(int i=0;i<razmer_massiva_float;i++){
        DVOICH[k] = FLOAT_PIECE_DVOICH[i+counter_smesh_for_float];
        k++;
    }

    cout << "ЧИСЛО " << INPUT_CHISLO << " В МАШИННОМ ПРЕДСТАВЛЕНИИ: " << endl;

    for(int i=0;i<N;i++){
        cout << DVOICH[i];
    }


return 0;
}
