// UpdateINI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void Usage()
{
    _tprintf(_T("UpdateINI -s \"Section\" \"Key\" \"Value\" \"File\"\n"));
    _tprintf(_T("\n"));
}

//bool InitializeEmptyUnicodeINIFile(LPCSTR pszFileName);
class cmdLine
{
public:
    cmdLine() : bSet(false), m_pszSection(nullptr), m_pszKey(nullptr), m_pszValue(nullptr), m_pszFile(nullptr) {}
    bool Parse(int argc, _TCHAR* argv[])
    {
        if (argc != 6)
        {
            return false;
        }
        if ((0 == _tcsnicmp(_T("-s"), argv[1], 2)) || (0 == _tcsnicmp(_T("/s"), argv[1], 2)))
        {
            if (0 == _tcslen(argv[2]))
            {
                return false;
            }
            if (0 == _tcslen(argv[3]))
            {
                return false;
            }
            if (0 == _tcslen(argv[4]))
            {
                return false;
            }
            size_t pathlen = _tcslen(argv[5]);
            if ((0 == pathlen) || (_MAX_PATH < pathlen))
            {
                return false;
            }
            bSet = true;
            //could do other path/file validation, but leave that as an exercise for later
            m_pszSection = argv[2];
            m_pszKey = argv[3];
            m_pszValue = argv[4];
            m_pszFile = argv[5];
        }
        else
        {
            return false;
        }
        return true;
    }

    bool bSet;
    LPCTSTR m_pszSection;
    LPCTSTR m_pszKey;
    LPCTSTR m_pszValue;
    LPCTSTR m_pszFile;
};

int _tmain(int argc, _TCHAR* argv[])
{
    cmdLine Params;

    if (Params.Parse(argc, argv))
    {
        LPCTSTR pszSection = Params.m_pszSection;
        LPCTSTR pszKey = Params.m_pszKey;
        LPCTSTR pszValue = Params.m_pszValue;
        LPCTSTR pszFile = Params.m_pszFile;

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
        return ERROR_BAD_ARGUMENTS; //TODO: Allow /? without returning error
    }

    return 0;
}

//for later reference: prepping a file for unicode strings
#if 0
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
#endif