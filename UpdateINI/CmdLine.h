#ifndef CMNDLINE_H

#define CMNDLINE_H

#define MAX_FLAG_PARAMS 10

#include <tchar.h>

class cmdFlag
{
public:

    // Constructor and Destructor
    cmdFlag( _TCHAR cInitFlag );
    ~cmdFlag();

    // Methods
    BOOL AddParam( _TCHAR *ParamLocation );
    _TCHAR *GetParam( int Index );
    _TCHAR GetFlag();

private:

    // Data
    _TCHAR Flag;
    _TCHAR *FlagParams[ MAX_FLAG_PARAMS ];
    int iNumParams;
};

class cmdCommandLine
{
public:

    // Constructor and Destructor
    cmdCommandLine( int iArgumentCount, _TCHAR **caArgumentArray );
    ~cmdCommandLine();

    // Public Methods
    int iFindFlag( _TCHAR cFlag );
    BOOL bGetFlag( int FlagID );
    _TCHAR cCurrentFlag() { return afFlagArray[ iCurrentFlag ]->GetFlag(); }
    _TCHAR *cpNextFlagParam( );

private:

    // Data
    int iArgCnt;            // Count of the Arguments
    _TCHAR **caArgArry;     // Array with the Arguments

    cmdFlag **afFlagArray;  // Array of flag class objects
    int iFlagCount;         // Number of flag objects in the array
    int iCurrentFlag;       // Current Flag for processing
    int iCurrentParam;  // Current Parameter in the Flag
};

#endif
