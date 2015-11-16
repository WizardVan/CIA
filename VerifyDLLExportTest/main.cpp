#include <stdio.h>
#include <windows.h>

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
//	_GetVersion pGetVersion;
	hVDLL = LoadLibrary("NxVerify.dll");
	NxModule_GetType = (_NxModule_GetType)GetProcAddress(hVDLL, "NxModule_GetType");
	NxVerify_GetInterface = (_NxVerify_GetInterface)GetProcAddress(hVDLL, "NxVerify_GetInterface");

	pCV = NxVerify_GetInterface();
	//pGetVersion = &(pCV->GetVersion);
	
	unsigned char Account[] = "JGSAHSSSSSSSSSSSSSSSSSSSSSHHHHHHHHHHHHHHHHHHHHHHHHHHHJJJJJJJJJJJJJJJJJJJJJJJSSSSSSSSSSSSSSSSSSSSSSSSGGGGGGGGGGGGGGGGGGSSSSSSSSSSSSSSSSSSSSSS";
	unsigned char oAccount[0xFF] = "";
	unsigned int *p;
	pCV->EncodeFunc(1412, Account, oAccount);
	p = (unsigned int *)oAccount;
	
	for (int i = 0; i < 0xff; i++)
	{
		printf("0x%02X ", oAccount[i]);
	}

	printf("\n");

	for (int i = 0; i < 64;i++)
	{
		printf("0x%08X\n", *p);
		p++;
	}

	getchar();

}