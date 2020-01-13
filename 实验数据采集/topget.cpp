#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
int main()
{
    ofstream fout("top_info.csv", ios::out);
    string input = "";
    // 首先输出第一行提示栏
    fout << "time,PID,USER,PR,NI,VIRT,RES,SHR,S,%CPU,%MEM,TIME+,COMMAND" << endl;
    cout << "Please choose the process you want to monitor" << endl;
    cout << "1. tcpreplay" << endl;
    cout << "2. floodlight" << endl;
    int choice;
    cin >> choice;
    while(1)
    {
        if(choice == 1)
            system("top -p `pidof tcpreplay | sed 's/ /,/g'` -n 1 -d 1 -b > topinfo.txt");
        else if(choice == 2)
            system("top -p `pidof java | sed 's/ /,/g'` -n 1 -d 1 -b > topinfo.txt");
        else
        {
            cout << "wrong choice" << endl;
            break;
        }
        ifstream fin("topinfo.txt", ios::in);
        // 读取时间信息
        getline(fin, input);
        for(int i = 6; i <= 13; i++)
            fout << input[i];
//        fout << ",";
        for(int i = 0; i < 7; i++)
            getline(fin, input);
        // 输出所有信息 逗号隔开
        for(int i = 0; i < input.size(); i++)
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
        fin.close();
        sleep(1);
    }
    fout.close();
    return 0;
}
