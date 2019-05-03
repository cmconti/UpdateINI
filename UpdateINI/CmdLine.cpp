#include "stdafx.h"

#include <windows.h>
#include <ctype.h>

#ifdef _UNICODE
#include <wchar.h>
#endif

#include "CmdLine.h"

cmdFlag::cmdFlag( _TCHAR cInitFlag ) :
    Flag(cInitFlag),
    iNumParams(-1)
{
    memset(FlagParams, 0, sizeof(FlagParams));
}

cmdFlag::~cmdFlag()
{
    for( int i = 0; i <= iNumParams; i++ )
    {
        _TCHAR* pch = FlagParams[i];
        delete[] pch;
    }
}

_TCHAR cmdFlag::GetFlag()
{
    return( Flag );
}

_TCHAR *cmdFlag::GetParam( int Index )
{
    if( -1 == iNumParams || Index < 0 || Index > iNumParams )
        return NULL;
    else
        return FlagParams[ Index ];
}

BOOL cmdFlag::AddParam( _TCHAR *ParamLocation )
{
    _TCHAR *CurrentLocation = ParamLocation;

    if( iNumParams == MAX_FLAG_PARAMS - 1 )
        return( FALSE );

    size_t cchParamLocationBuffer = _tcslen( CurrentLocation ) + 1;
    FlagParams[ ++iNumParams ] = new _TCHAR[ cchParamLocationBuffer ];
    _tcscpy_s( FlagParams[ iNumParams ], cchParamLocationBuffer, CurrentLocation );

    return( TRUE );
}

cmdCommandLine::cmdCommandLine( int iArgumentCount, _TCHAR **caArgumentArray ) :
    iArgCnt(iArgumentCount),
    caArgArry(caArgumentArray),
    afFlagArray(NULL),
    iFlagCount(0),
    iCurrentFlag(0),
    iCurrentParam(0)

{
    for( int i = 0; i < iArgCnt; i++ )
    {
        if( ( caArgArry[i][0] == '-' || caArgArry[i][0] == '/' ) &&
            _istalnum( caArgArry[i][1] ) )
            iFlagCount ++;
    }

    if( iFlagCount )
    {
        afFlagArray = new  cmdFlag *[ iFlagCount ];
        int WhichFlag = -1;

        for( int i = 0; i < iArgCnt; i++ )
        {
            if( caArgArry[i][0] == '-' || caArgArry[i][0] == '/' )
            {
#ifdef _UNICODE
                if( iswalnum( caArgArry[i][1] ) )
#else
                if( isalnum( caArgArry[i][1] ) )
#endif
                {
                    afFlagArray[ ++WhichFlag ] = new cmdFlag( caArgArry[i][1] );

                    if( caArgArry[i][2] != '\0' )
                        afFlagArray [ WhichFlag ]->AddParam( &caArgArry[i][2] );
                }
            }
            else
            {
                if( -1 < WhichFlag )
                    afFlagArray[ WhichFlag ]->AddParam( caArgArry[i] );
            }
        }
    }
    else
    {
        afFlagArray = NULL;
    }
}

cmdCommandLine::~cmdCommandLine()
{
    if( afFlagArray )
    {
        for( int i = 0; i < iFlagCount; i++ )
        {
            cmdFlag* pcf = afFlagArray[i];
            delete pcf;
        }

        delete [] afFlagArray;
    }
}

int cmdCommandLine::iFindFlag( _TCHAR cFlag )
{
    int iFlagID = -1;

    // Look at all of the arguments.
    for( int i = 0; i < iFlagCount; i++ )
    {
        if( afFlagArray[i]->GetFlag() == cFlag )
        {
            iFlagID = i;
        }
    }

    return( iFlagID );
}

BOOL cmdCommandLine::bGetFlag( int iFlagID )
{
    if( iFlagID < 0 || iFlagID >= iFlagCount )
    {
        return( FALSE );
    }
    else
    {
        iCurrentFlag = iFlagID;
        iCurrentParam = 0;
        return( TRUE );
    }
}

_TCHAR *cmdCommandLine::cpNextFlagParam()
{
    return ( afFlagArray[ iCurrentFlag ]->GetParam( iCurrentParam++ ) );
}