#include "stdafx.h"

#if(SECURITY_SCRIPT==TRUE)

class SecurityScript
{
public:
	SecurityScript();
	~SecurityScript();
	void Encode(char* buffer, int size);
	void SetScriptBuffer( char* buffer, int size);
	void Close();
	int ReadScript(char* File);
	int WriteScript(char* File);

	void Test();

	//static HANDLE		m_hFile;
	char* m_pBuffer;
	int	  m_iBufferSize;
};
extern SecurityScript g_SecurityScript;


#endif