#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "MyString.h"

using namespace std;

int Random(int maxValue)
{
    float r = ((double) rand() / (RAND_MAX));
    return r * maxValue;
}

//exo 1
void ConvertIntoGreyScale(void *pImage, int SizeX, int SizeY)
{
    // j'assume que les octets representer par F dans 0XFF000000 sont l'alpha
    int32_t **pixels = (int32_t**)pImage;
    for(int i = 0; i < SizeX; i++)
    {
        for(int j = 0; j < SizeY; j++)
        {
            unsigned char red = (pixels[i][j] & 0x00FF0000) >> 16;
            unsigned char green = (pixels[i][j] & 0x0000FF00) >> 8;
            unsigned char blue = pixels[i][j] & 0x000000FF;

            cout << "index = " << i << ", " << j << endl;
            cout << "red = " << (int32_t)red << endl;
            cout << "green = " << (int32_t)green << endl;
            cout << "blue = " << (int32_t)blue << endl;

            red = red * 30 / 100;
            green = green * 59 / 100;
            blue = blue * 11 / 100;

            cout << "red gray scale = " << (int32_t)red << endl;
            cout << "green gray scale = " << (int32_t)green << endl;
            cout << "blue gray scale = " << (int32_t)blue << endl;
            cout << endl;

            pixels[i][j] = (pixels[i][j] & 0xFF000000) + ((int32_t)red << 16) + ((int32_t)green << 8) + ((int32_t)blue);
        }
    }
}

//exo 3
int *RandomArray(int n, int suffle = 10000)
{
    if(n <= 0)
    {
        return nullptr;
    }

    int *j = new int[n];
    for(int i = 0; i < n; i++)
    {
        j[i] = i + 1;
    }

    for(int i = 0; i < suffle; i++)
    {
        int index1 = Random(n);
        int index2 = Random(n);
        swap(j[index1], j[index2]);
        /*int s = j[index1];
        j[index1] = j[index2];
        j[index2] = s;*/
    }
    return j;
}

//exo 4
bool Decompress(unsigned char *pucIn, unsigned char *pucOut, unsigned long unOutMaxSize)
{
    unsigned long i = 0;
    unsigned long indexOut = 0;
    while(!pucIn[i] == 0)
    {
       if((pucIn[i] & 0b10000000) == 0)
        {
            unsigned char index = pucIn[i];
            i++;
            while(index > 0)
            {
                pucOut[indexOut] = pucIn[i];
                indexOut++;
                i++;
                index--;
            }
        }
        else if((pucIn[i] & 0b10000000) == 128)
        {
            unsigned char index = pucIn[i] & 0b01111111;
            for(unsigned char j = 0; j <= index; j++)
            {
                pucOut[indexOut] = pucIn[i + 1];
                indexOut++;
            }
            i += 2;
        }



        if(indexOut > unOutMaxSize + 1)
        {
            return false;
        }
    }
    return true;
}

char* Exo5(MyString **str, int length)
{
    char *final = new char();
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < str[i]->length; j++)
        {
            if(i == 0)
            {
                final[j] = str[i]->phrase[j];
            }
            else
            {
                if(final[j] < str[i]->phrase[j])
                {
                    final[j] = str[i]->phrase[j];
                }
            }
        }
    }
    return final;
}

int main()
{

    // EXO 1
    cout << "EXO 1 :" << endl;
    int32_t **pixel = new int*();
    *pixel = new int[2];
    *(pixel + 1) = new int[2];

    pixel[0][0] = 0x11105236;
    pixel[0][1] = 0x11655889;
    pixel[1][0] = 0x11327233;
    pixel[1][1] = 0x11900242;


    cout << hex;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            cout << hex << "value initial = " << pixel[i][j] << endl;
        }
    }
    cout << dec;

    ConvertIntoGreyScale(pixel, 2, 2);

    cout << hex;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            cout << "value final = " << pixel[i][j] << endl;
        }
    }
    cout << dec;

    for(int i = 0; i < 2; i++)
    {
        delete pixel[i];
    }
    delete pixel;


    cout << endl;
    cout << endl;


    // EXO 3
    //je ne l'ai pas mis, mais je suppose que j'aurai pu include <ctime>
    //pour randomiser la seed
    cout << "EXO 3 :" << endl;
    int *tab = RandomArray(100);
    for(int i = 0; i < 100; i++)
    {
        cout << "tab" << i << " = " << tab[i] << endl;
    }
    delete tab;
    cout << endl;
    cout << endl;



    //EXO 4
    cout << "EXO 4 :" << endl;
    cout << hex;
    unsigned char out[5];
    unsigned char in[] = {0x02, 0x45, 0x67, 0x83, 0xFF, 0x00};

    if(Decompress(in, out, 5))
    {
        cout << "decompression ok" << endl;
    }

    for(int i = 0; i < 5; i++)
    {
        cout << "out = " << (unsigned int)out[i] << endl;
    }
    cout << dec;


    cout << endl;
    cout << endl;


    //EXO5
    cout << "EXO 5 :" << endl;
    MyString *tabStr[] =
        {
            new MyString("Je_teste cette phrase.", 22),
            new MyString("Je teste 2 fois", 15)
        };

    char *res = Exo5(tabStr, 2);
    for(int i = 0; i < 2; i++)
    {
        cout << "current string = " << tabStr[i]->phrase << endl;
    }
    cout << "string final = " << res << endl;

    for(int i = 0; i < 2; i++)
    {
        delete tabStr[i];
    }
    delete tabStr;



    return 0;
}
