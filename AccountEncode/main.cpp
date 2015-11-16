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
	unsigned char inAccount[32];
	unsigned char *pinAccount;
	HMODULE hVDLL;
	IBaseVerify* pCV;
	_NxModule_GetType NxModule_GetType;
	_NxVerify_GetInterface NxVerify_GetInterface;
	//unsigned char outAccount[32];
	
	unsigned char AccountKey[16] = {	
		0x66,0xF9,0x28,0xe8,0xa1,0x00,0x9b,0x76,
		0x29,0xa0,0x1f,0x8d,0xef,0x45,0x89,0x19};
   
	unsigned char NewKey[16];
	char keyseed[] = "HelloWorld!";
	unsigned char NewKeyHash[16];

	/*
	unsigned char AccountKey[16] = {
		0x19,0x89,0x45,0xef,0x8d,0x1f,0xa0,0x29,
		0x76,0x9b,0x00,0xa1,0xe8,0x28,0xf9,0x66};
    
	/*
	unsigned char AccountKey[16] = {
		0xe8, 0x28, 0xF9, 0x66, 0x76, 0x9b, 0x00, 0xa1,
		0x8d, 0x1f, 0xa0, 0x29, 0x19, 0x89, 0x45, 0xef};
	*/
	/*
	unsigned char AccountKey[16] = {
	    0xef, 0x45, 0x89, 0x19, 0x29, 0xa0, 0x1f, 0x8d,
		0xa1, 0x00, 0x9b, 0x76, 0x66, 0xF9, 0x28, 0xe8 };
	*/

	UINT32 * p;
	SecureZeroMemory(inAccount, sizeof(inAccount));
	hVDLL = LoadLibrary("NxVerify.dll");
	NxModule_GetType = (_NxModule_GetType)GetProcAddress(hVDLL, "NxModule_GetType");
	NxVerify_GetInterface = (_NxVerify_GetInterface)GetProcAddress(hVDLL, "NxVerify_GetInterface");
	//printf("0x%08X\n", GetProcAddress(hVDLL, "des2key"));
	pCV = NxVerify_GetInterface();

	//printf("%d\n", sizeof(UINT32));
	//printf("%d\n", sizeof(unsigned long));


	//SecureZeroMemory(outAccount, sizeof(outAccount));
	p = (UINT32 *)inAccount;
	/*
	*p = (*p) ^ 0xf8ebd0a7;
	//printf("0x%08X\n", (UINT32)*p);
	p++;

	*p = *p ^ 0xc4badc9c;
	p++;
	
	*p = *p ^ 0xa84fd0a2;
	p++;

	*p = *p ^ 0x74cf24b7;
	p++;

	*p = *p ^ 0x26e24c92;
	p++;

	*p = *p ^ 0x38efda09;
	p++;

	*p = *p ^ 0xc3b2d047;
	p++;

	*p = *p ^ 0x28efd49c;
	p++;
	*/
	

	pCV->EncodeFunc(1, (unsigned char*)keyseed, NewKeyHash);
	make2key((char *)NewKeyHash, NewKey);
	p = (UINT32 *)NewKey;
	for (int i = 0; i < 4; i++)
	{
		printf("0x%08X\n", (UINT32)*p);
		p++;
	}

	//des2key(AccountKey,EN0);
	
	des2key(NewKey, DE1);
	D2des(inAccount, inAccount);

	D2des(inAccount+16, inAccount+16);

	p = (UINT32 *)inAccount;
	printf("%d\n", sizeof(p));
	for (int i = 0; i < 8; i++)
	{
		printf("0x%08X\n", (UINT32)*p);
		p++;
	}

	

	pinAccount = inAccount;
	
	/*
	for (int i = 0; i < 32; i++)
	{
		printf("0x%08X\n", *pinAccount);

		pinAccount++;
	}
	*/
	/*
	_asm{
		INT 3
	}
	*/
	//pCV->DecodeAccount((unsigned char*)inAccount);
	
	des2key(NewKey, EN0);

	D2des(inAccount, inAccount);

	D2des(inAccount + 16, inAccount + 16);

	p = (UINT32 *)inAccount;
	for (int i = 0; i < 8; i++)
	{
		printf("0x%08X\n", (UINT32)*p);
		p++;
	}
	
	//printf("%s", inAccount);

	getchar();
	return;
}
