#ifndef __APGlbal__H__
#define __APGlbal__H__

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

extern IBaseVerify* pCV;


#endif // !__APGlbal__H__



