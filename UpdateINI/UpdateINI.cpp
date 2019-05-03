// UpdateINI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CmdLine.h"

void Usage()
{
    printf("UpdateINI -s \"Section\" \"Key\" \"Value\" \"File\"\n");
    printf("NOTE that the -e, -c, and -i options are no longer supported.\n");
    printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    cmdCommandLine Params(argc, argv);

    bool bSet = false, bGetNext = false;
    int nSwitchS = 0, nSwitchN = 0, nSwitchC = 0, nSwitchE = 0, nSwitchI = 0;

    //set
    if( Params.bGetFlag( ( nSwitchS = Params.iFindFlag( 's' ) ) )|| Params.bGetFlag( ( nSwitchS = Params.iFindFlag( 'S' ) ) ))
        bSet = true;

    if( Params.bGetFlag( ( nSwitchE = Params.iFindFlag( 'e' ) ) )|| Params.bGetFlag( ( nSwitchE = Params.iFindFlag( 'E' ) ) ))
    {
        Usage();
        return -1;
    }

    if( Params.bGetFlag( ( nSwitchC = Params.iFindFlag( 'c' ) ) )|| Params.bGetFlag( ( nSwitchC = Params.iFindFlag( 'C' ) ) ))
    {
        Usage();
        return -1;
    }

    if( Params.bGetFlag( ( nSwitchI = Params.iFindFlag( 'i' ) ) )|| Params.bGetFlag( ( nSwitchI = Params.iFindFlag( 'I' ) ) ))
    {
        Usage();
        return -1;
    }

    //not impl
    //get next
    if( Params.bGetFlag( ( nSwitchN = Params.iFindFlag( 'n' ) ) )|| Params.bGetFlag( ( nSwitchN = Params.iFindFlag( 'N' ) ) ))
        bGetNext = true;

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
        Usage();

    return 0;
}

