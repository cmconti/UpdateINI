// UpdateINI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CmdLine.h"

void Usage()
{
    printf("UpdateINI -s \"Section\" \"Key\" \"Value\" \"File\"\n");
    printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    cmdCommandLine Params(argc, argv);

    bool bSet = false;
    int nSwitchS = 0;

    //set
    if( Params.bGetFlag( ( nSwitchS = Params.iFindFlag( 's' ) ) )|| Params.bGetFlag( ( nSwitchS = Params.iFindFlag( 'S' ) ) ))
        bSet = true;

    if (bSet)
    {
        BOOL bRet = 0;
        TCHAR* pszSection;
        TCHAR* pszKey;
        TCHAR* pszValue;
        TCHAR* pszFile;

        Params.bGetFlag( nSwitchS );

        pszSection = Params.cpNextFlagParam();
        pszKey = Params.cpNextFlagParam();
        pszValue = Params.cpNextFlagParam();
        pszFile = Params.cpNextFlagParam();

        if (!pszSection || !pszKey || !pszValue || !pszFile)
        {
            Usage();
            return -1;
        }

        bRet = ::WritePrivateProfileString(pszSection, pszKey, pszValue, pszFile);

        if (!bRet)
        {
            DWORD dwRet = ::GetLastError();
            printf("WritePrivateProfileString failed.  GLE=%u\n", dwRet);
            return dwRet;
        }
    }
    else
    {
        Usage();
    }

    return 0;
}

