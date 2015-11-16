#include <stdio.h>
#include <windows.h>
#include "md5.h"

typedef unsigned char	UI08;

/*
class __declspec(dllimport) CVerify
{
public:
virtual int _ECVerify(int);
virtual int GetVersion(); //10072370 f   Verify.obj
virtual int GetEncodeNum(); // 10072380 f   Verify.obj
virtual int GetEncodeId(int); // 10072390 f   Verify.obj
virtual void GetClientCond(int); // 100723a0 f   Verify.obj
virtual void GetClientCode(int); // 100723b0 f   Verify.obj
virtual void EncodeFunc(int, int, int); // 100723c0 f   Verify.obj IMPORTANT
virtual char DecodeAccount(char *); // 100723e0 f   Verify.obj IMPORTANT
virtual char DecodePassword(int); // 100724c0 f   Verify.obj IMPORTANT
protected:
private:
};
*/

class IBaseVerify
{
public:
	virtual ~IBaseVerify() = 0;

	// 获得版本号
	virtual int GetVersion() = 0;
	// 获得加密组数(总的组数)
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
//typedef int(*_GetVersion)();
//_NxVerify_GetInterface




void main()
{
	HMODULE hVDLL;
	IBaseVerify* pCV;
	_NxModule_GetType NxModule_GetType;
	_NxVerify_GetInterface NxVerify_GetInterface;

	size_t cEncode_Id = 1;
	//	_GetVersion pGetVersion;
	hVDLL = LoadLibrary("NxVerify.dll");
	NxModule_GetType = (_NxModule_GetType)GetProcAddress(hVDLL, "NxModule_GetType");
	NxVerify_GetInterface = (_NxVerify_GetInterface)GetProcAddress(hVDLL, "NxVerify_GetInterface");

	pCV = NxVerify_GetInterface();
	unsigned char buf[128];
	
	ZeroMemory(buf, sizeof(buf));
	//memcpy(buf, (const char*)"A", sizeof("A"));

	MD5 alg;
	alg.update(buf, sizeof(buf));
	alg.finalize();
	
	UI08 output[16];



	unsigned int *p;

	p = (unsigned int *)alg.digest;
	for (int i = 0; i < 4; i++)
	{
		printf("0x%08x\n", *p);
		p++;
	}

	pCV->EncodeFunc(cEncode_Id, alg.digest, output);


	p = (unsigned int *)output;
	for (int i = 0; i < 4; i++)
	{
		printf("0x%08x\n", *p);
		p++;
	}
	getchar();
}