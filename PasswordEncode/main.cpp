#include <stdio.h>
#include "d3des.h"
#include <windows.h>
#include <stdint.h>

typedef unsigned char	UI08;

class IBaseVerify
{
public:
	virtual ~IBaseVerify() = 0;

	// 获得版本号
	virtual int GetVersion() = 0;
	// 获得加密组数
	virtual size_t GetEncodeNum() = 0;
	// 获得指定索引的加密组号
	virtual size_t GetEncodeId(size_t index) = 0;
	// 获得客户端条件码
	virtual UI08 * GetClientCond(size_t encode_id) = 0;
	// 获得客户端的PATCH字节码
	virtual UI08 * GetClientCode(size_t encode_id) = 0;
	// 获得加密输出
	virtual void EncodeFunc(size_t encode_id,
		UI08 * input, UI08 * output) = 0;
	// 帐号解码
	virtual bool DecodeAccount(UI08 * account) = 0;
	// 密码解码
	virtual bool DecodePassword(UI08 * password) = 0;
};


inline IBaseVerify::~IBaseVerify() {}


typedef char* (*_NxModule_GetType)();
typedef IBaseVerify* (*_NxVerify_GetInterface)();

void main()
{
	unsigned char inPassword[32];
	unsigned char *pinPassword;
	HMODULE hVDLL;
	IBaseVerify* pCV;
	_NxModule_GetType NxModule_GetType;
	_NxVerify_GetInterface NxVerify_GetInterface;
	//unsigned char outPassword[32];
	
	unsigned char PasswordKey[16] = {	
		0x10,0x6e,0xba,0x55,0x77,0x61,0xc7,0x7e,
		0x1e,0xea,0x0d,0xeb,0x67,0x62,0x93,0xdc};
   
	/*
	unsigned char PasswordKey[16] = {
		0x19,0x89,0x45,0xef,0x8d,0x1f,0xa0,0x29,
		0x76,0x9b,0x00,0xa1,0xe8,0x28,0xf9,0x66};
    
	/*
	unsigned char PasswordKey[16] = {
		0xe8, 0x28, 0xF9, 0x66, 0x76, 0x9b, 0x00, 0xa1,
		0x8d, 0x1f, 0xa0, 0x29, 0x19, 0x89, 0x45, 0xef};
	*/
	/*
	unsigned char PasswordKey[16] = {
	    0xef, 0x45, 0x89, 0x19, 0x29, 0xa0, 0x1f, 0x8d,
		0xa1, 0x00, 0x9b, 0x76, 0x66, 0xF9, 0x28, 0xe8 };
	*/

	UINT32 * p;
	SecureZeroMemory(inPassword, sizeof(inPassword));


	//memcpy(inPassword, (const char*)"LALA12345", sizeof("LALA12345"));
	//printf("%d\n", sizeof(UINT32));
	//printf("%d\n", sizeof(unsigned long));


	//SecureZeroMemory(outPassword, sizeof(outPassword));
	p = (UINT32 *)inPassword;
	
	*p = (*p) ^ 0xf24d83e5;
	//printf("0x%08X\n", (UINT32)*p);
	p++;

	*p = *p ^ 0xab2526d8;
	p++;
	
	*p = *p ^ 0x32b93688;
	p++;

	*p = *p ^ 0xaffdfe20;
	p++;

	*p = *p ^ 0xe2435ae5;
	p++;

	*p = *p ^ 0x136126b1;
	p++;

	*p = *p ^ 0x52ba6e85;
	p++;

	*p = *p ^ 0x3fa3fb23;
	p++;
	
	
	des2key(PasswordKey,EN0);

	D2des(inPassword, inPassword);

	D2des(inPassword+16, inPassword+16);

	p = (UINT32 *)inPassword;
	for (int i = 0; i < 8; i++)
	{
		printf("0x%08X\n", (UINT32)*p);
		p++;
	}


	pinPassword = inPassword;
	
	/*
	for (int i = 0; i < 32; i++)
	{
		printf("0x%08X\n", *pinPassword);

		pinPassword++;
	}
	*/
	/*
	_asm{
		INT 3
	}
	*/
	pCV->DecodePassword((unsigned char*)inPassword);
	
	//des2key(PasswordKey, DE1);

	//D2des(inPassword, inPassword);

	//D2des(inPassword + 16, inPassword + 16);

	p = (UINT32 *)inPassword;
	for (int i = 0; i < 8; i++)
	{
		printf("0x%08X\n", (UINT32)*p);
		p++;
	}
	
	//printf("%s", inPassword);

	getchar();
	return;
}
