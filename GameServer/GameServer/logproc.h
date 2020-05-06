#ifndef LOGPROC_H
#define LOGPROC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define LOG_TEXT_LENGTH	140//80
#define LOG_TEXT_LINE	30
 
extern void (*LogAdd)(char* szLog,...);
extern void (*LogAddC)(BYTE, char*, ...);
extern void (*LogAddTD)(char* szLog, ...);
extern void (*LogAddHeadHex)(char*,char*, int);
extern void (*LogTextPaint)(HWND);
extern void (*LogAddL)(char * szLog, ...);

void LogInit(int logprint);
void LogDataSet();
int LogDateChange();
void LogTextAdd(BYTE type, char* msg, int len);
void LogAddFuncVoid(char* szLog, ...);
void LogAddTimeDateVoid(char* szLog, ...);
void LogAddFunc(char* szLog, ...);
void LogAddFuncColor(BYTE Color, char* szLog, ...);
void LogAddFuncColorVoid(BYTE Color, char* szLog, ...);
void LogAddLocalFunc(char * szLog, ...);
void LogAddLocalFuncVoid(char * szLog, ...);
void LogAddTimeDateFunc(char* szLog, ...);
void LogAddHeadHexFuncVoid(char* str,char* data,int len);
void LogAddHeadHexFunc(int Type,char* data,int len);
void LogAddStrHexFunc(char* str,char* data, int len);
void LogTextClear();
void LogTextPaintProcVoid(HWND hWnd);
void LogTextPaintProc(HWND hWnd);
int LogGetFileName();
void LogClose();
void MsgBox(char *szlog, ...);
#endif

#define __CLASS__ typeid(*this).name()

#define LOG_ERROR(fmt, ...) {char __tmp[1024] = {0}; \
							sprintf(__tmp, ##fmt, ##__VA_ARGS__); \
							LogAddC(2, "[%s][%d] %s", __CLASS__, __LINE__, __tmp);}

#define LOG_INFO(fmt, ...) {char __tmp[1024] = {0}; \
							sprintf(__tmp, ##fmt, ##__VA_ARGS__); \
							LogAddC(0, "[%s][%d] %s", __CLASS__, __LINE__, __tmp);}

#define LOG_WARNING(fmt, ...) {char __tmp[1024] = {0}; \
							sprintf(__tmp, ##fmt, ##__VA_ARGS__); \
							LogAddC(1, "[%s][%d] %s", __CLASS__, __LINE__, __tmp);}