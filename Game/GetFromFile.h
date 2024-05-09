#ifndef GETFROMFILE_H_INCLUDED
#define GETFROMFILE_H_INCLUDED
#include <bits/stdc++.h>
#include <fstream>
int Get_From_File(const char* filename)
{
    int n;
    std::ifstream file(filename);
    file >> n;
    file.close();
    return n;
}

void Write_To_File(const char* filename, int x)
{
    std::ofstream file(filename);
    file << x;
    file.close();
}

#endif // GETFROMFILE_H_INCLUDED
