// UpdateINI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CmdLine.h"

void Usage()
{
    _tprintf(_T("UpdateINI -s \"Section\" \"Key\" \"Value\" \"File\"\n"));
    _tprintf(_T("\n"));
}

//bool InitializeEmptyUnicodeINIFile(LPCSTR pszFileName);

int _tmain(int argc, _TCHAR* argv[])
{
    cmdCommandLine Params(argc, argv);

    bool bSet = false;
    int nSwitchS = 0;

    //set
    if( Params.bGetFlag( ( nSwitchS = Params.iFindFlag( 's' ) ) )|| Params.bGetFlag( ( nSwitchS = Params.iFindFlag( 'S' ) ) ))
    {
        bSet = true;
    }

    if (bSet)
    {
        Params.bGetFlag( nSwitchS );

        TCHAR* pszSection = Params.cpNextFlagParam();
        TCHAR* pszKey = Params.cpNextFlagParam();
        TCHAR* pszValue = Params.cpNextFlagParam();
        TCHAR* pszFile = Params.cpNextFlagParam();

        if (!pszSection || !pszKey || !pszValue || !pszFile)
        {
            Usage();
            return -1;
        }

        //TODO: Should I be 'smart' here and try to figure out if the section/key/value are unicode,
        //      make that a command line parameter option, or something else?
        //bool bInitialized = InitializeEmptyUnicodeINIFile(pszFile)
        BOOL bRet = ::WritePrivateProfileString(pszSection, pszKey, pszValue, pszFile);

        if (!bRet)
        {
            DWORD dwRet = ::GetLastError();
            _tprintf(_T("WritePrivateProfileString failed.  GLE=%u\n"), dwRet);
            return dwRet;
        }
    }
    else
    {
        Usage();
    }

    return 0;
}

//for later reference: prepping a file for unicode strings
/*
bool InitializeEmptyUnicodeINIFile(LPCTSTR pszFileName)
{
    //only  initialize if file does not exist
    if(INVALID_FILE_ATTRIBUTES == ::GetFileAttributes(pszFileName))
    {
        // write the Utf-16-LE BOM
        WORD wBOM = 0xFEFF;
        DWORD NumberOfBytesWritten = 0;

        HANDLE hFile = ::CreateFile(pszFileName, GENERIC_WRITE, 0, 
            NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        ::WriteFile(hFile, &wBOM, sizeof(WORD), &NumberOfBytesWritten, NULL);
        ::CloseHandle(hFile);
        return true;
    }
    else
    {
        return false;
    }
}
*/