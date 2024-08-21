// Detours_TextOut_2024.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#pragma comment(lib, "detoured.lib")
#pragma comment(lib, "detours.lib")

//#include <cstdio>
#include <stdio.h>
#include <windows.h>
#include "detours.h"
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>


void GetPathAndFilenameW(wchar_t* FQFilename, std::wstring* strPath, std::wstring* strFilename, std::wstring* strFilenameNoExtension, std::wstring* strExtension)
{
    std::wstring strFQFilename(FQFilename);
    
    int last_backslash_position = strFQFilename.find_last_of(L"\\/");
    int last_dot_position = strFQFilename.find_last_of(L".");
    *strPath = strFQFilename.substr(0, last_backslash_position);
    *strFilename = strFQFilename.substr(last_backslash_position + 1, (strFQFilename.length() - last_backslash_position - 1));

    if (last_dot_position > -1)
    {
        *strFilenameNoExtension = strFQFilename.substr(last_backslash_position + 1,   (last_dot_position + 1) - (last_backslash_position + 1) - 1);
        *strExtension = strFQFilename.substr((last_dot_position + 1), (strFQFilename.length() - last_dot_position - 1));
    }
    else
    {
        *strFilenameNoExtension = strFQFilename.substr(last_backslash_position + 1, (strFQFilename.length() - last_backslash_position - 1));
        *strExtension = L"";
    }

    return;
}


std::string WideToAnsiString(std::wstring ws)
{
    if (ws.empty())
    {
        return std::string();
    }
    
    int size_needed = WideCharToMultiByte(CP_ACP, 0, &ws[0], (int)ws.size(), NULL, 0, NULL, NULL);
    std::string strAnsi(size_needed, 0);
    WideCharToMultiByte(CP_ACP, 0, &ws[0], (int)ws.size(), &strAnsi[0], size_needed, NULL, NULL);
    return strAnsi;
}


int main()
{
    char DllPath[MAX_PATH] = { 0 };         // Must use ANSI to meet DetourCreateProcessWithDll specification.
    wchar_t AppPath[MAX_PATH] = { 0 };

    // Get the path and filename of the current executable.
    std::wstring strPath;
    std::wstring strFilename;
    std::wstring strFilenameNoExtension;
    std::wstring strExtension;
    wchar_t pBuf[MAX_PATH] = { 0 };
    int bytes = GetModuleFileName(NULL, pBuf, MAX_PATH);
    GetPathAndFilenameW(pBuf, &strPath, &strFilename, &strFilenameNoExtension, &strExtension);

    //std::string strPathA(strPath.begin(), strPath.end());
    std::string strPathA = WideToAnsiString(strPath);
    sprintf_s(DllPath, MAX_PATH, "%s\\SleepDLL.dll", strPathA.c_str());
    swprintf_s(AppPath, MAX_PATH, L"D:\\Development\\private\\Wordpad\\wordpad.exe");
   
    // Print paths
    printf("\n\n");
    wprintf((LPWSTR)L"Injector File: %s\n", pBuf);
    printf(          "DLL File:      %s\n", DllPath);    
    wprintf((LPWSTR)L"Target File:   %s\n", AppPath);
    printf("\n\n");
    
    return 0;
}
