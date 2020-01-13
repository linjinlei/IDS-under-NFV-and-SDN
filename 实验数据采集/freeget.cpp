#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
using namespace std;
string getTime()
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep));
    return tmp;
}
int main()
{
    ofstream fout("free_info.csv", ios::out);
    string input = "";
    // 首先输出第一行提示栏
    fout << "time,Mem_total,Mem_used,Mem_free,Mem_shared,Mem_buff/cache,Mem_available,Swap_total,Swap_used,Swap_free" << endl;
    while(1)
    {
        system("free > freeinfo.txt");
        ifstream fin("freeinfo.txt", ios::in);
        getline(fin, input);
        // 输出系统时间
        string time = getTime();
        fout << time << ",";
        // 读取Mem行
        getline(fin, input);
        int i  = 4;
        while(input[i] == ' ')
            i++;
        for(i; i < input.size(); i++)
        {
            if(input[i] == ' ')
            {
                fout << ",";
                while(input[i] == ' ')
                    i++;
                i--;
            }
            else
                fout << input[i];
        }
        fout << ",";
        // 读取Swap行
        getline(fin, input);
        i = 5;
        while(input[i] == ' ')
            i++;
        for(i; i < input.size(); i++)
        {
            if(input[i] == ' ')
            {
                fout << ",";
                while(input[i] == ' ')
                    i++;
                i--;
            }
            else
                fout << input[i];
        }
        fout << endl;
        sleep(1);
    }
    return 0;
}
