#ifndef __APGlbal__H__
#define __APGlbal__H__

typedef unsigned char	UI08;

class IBaseVerify
{
public:
	virtual ~IBaseVerify() = 0;

	// ��ð汾��
	virtual int GetVersion() = 0;
	// ��ü�������
	virtual size_t GetEncodeNum() = 0;
	// ���ָ�������ļ������
	virtual size_t GetEncodeId(size_t index) = 0;
	// ��ÿͻ���������
	virtual UI08 * GetClientCond(size_t encode_id) = 0;
	// ��ÿͻ��˵�PATCH�ֽ���
	virtual UI08 * GetClientCode(size_t encode_id) = 0;
	// ��ü������
	virtual void EncodeFunc(size_t encode_id,
		UI08 * input, UI08 * output) = 0;
	// �ʺŽ���
	virtual bool DecodeAccount(UI08 * account) = 0;
	// �������
	virtual bool DecodePassword(UI08 * password) = 0;
};

extern IBaseVerify* pCV;


#endif // !__APGlbal__H__



