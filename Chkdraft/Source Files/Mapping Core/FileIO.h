#ifndef FILEIO_H
#define FILEIO_H
#include "Buffer.h"
#include "SFmpqapi.h"

// MPQ handling

bool OpenArchive(const char* szFilePath, const char* FileName, MPQHANDLE &hMpq);

bool CloseArchive(MPQHANDLE mpq);

bool FileToBuffer(MPQHANDLE &hMpq, const char* fileName, buffer &buf);

bool FileToBuffer(MPQHANDLE &hStarDat, MPQHANDLE &hBrooDat, MPQHANDLE &hPatchRt, MPQHANDLE &hPriority, const char* fileName, buffer& buf);

bool FileToBuffer(MPQHANDLE &hStarDat, MPQHANDLE &hBrooDat, MPQHANDLE &hPatchRt, const char* fileName, buffer& buf);

// General program IO

OPENFILENAME GetScSaveOfn(char* szFileName);

bool FileToBuffer(const char* FileName, buffer &buf);

DWORD GetSubKeyString(HKEY hParentKey, const char* subKey, const char* valueName, char* data, DWORD* dataSize);

bool GetRegString(char* dest, u32 destSize, const char* subKey, const char* valueName);

bool GetRegScPath(char* dest, u32 destSize);

#endif