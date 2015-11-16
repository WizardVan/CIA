// APEncoder.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "APEncoder.h"
#include "d3des.h"
#include "stdio.h"

/*
// This is an example of an exported variable
APENCODER_API int nAPEncoder=0;

// This is an example of an exported function.
APENCODER_API int fnAPEncoder(void)
{
	return 42;
}
*/

unsigned char AccountKey[16] = {
	0x66, 0xF9, 0x28, 0xe8, 0xa1, 0x00, 0x9b, 0x76,
	0x29, 0xa0, 0x1f, 0x8d, 0xef, 0x45, 0x89, 0x19 };

unsigned char PasswordKey[16] = {
	0x10, 0x6e, 0xba, 0x55, 0x77, 0x61, 0xc7, 0x7e,
	0x1e, 0xea, 0x0d, 0xeb, 0x67, 0x62, 0x93, 0xdc };

//char keyseedA[] = "HelloWorld!!!!";
unsigned char keyseedA[] = "HEHEHEHE";
unsigned char NewKeyA[16];
unsigned char NewKeyAHash[16];

//char keyseedB[] = "ALLHAILRSHUI!!!!!";
unsigned char keyseedB[] = "FUCKME";
unsigned char NewKeyB[16];
unsigned char NewKeyBHash[16];

size_t encode_id_Old = 2048;

APENCODER_API bool PacketEncoder(size_t encode_id, unsigned char * input,int length)
{
	int blocksize = 0;
	int padsize = 0;
	int i;
	if (length == 0) return FALSE;
	if (pCV == NULL)return FALSE;

	if (encode_id_Old == 2048 || encode_id != encode_id_Old)
	{
		pCV->EncodeFunc(encode_id, (unsigned char*)keyseedA, NewKeyA);
		//make2key((char *)NewKeyAHash, NewKeyA);

		pCV->EncodeFunc(encode_id, (unsigned char*)keyseedB, NewKeyB);
		//make2key((char *)NewKeyBHash, NewKeyB);
		encode_id_Old = encode_id;
	}

	des2key(NewKeyA, DE1);
	blocksize = length / 16;
	padsize = length % 16;

	for (i = 0; i < blocksize; i++)
	{
		D2des(input, input);
		input += 16;
	}
	for (i = 0; i < padsize; i++)
	{
		*input = (*input) ^ (NewKeyB[i]);
		input ++;
	}
	return TRUE;
}



APENCODER_API bool AccountEncoder(unsigned char * inAccount)
{
	//inAccount[32];
	//unsigned char inAccount[32];
	UINT32 * p;
	
	p = (UINT32 *)inAccount;

	*p = (*p) ^ 0xf8ebd0a7;
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

	des2key(AccountKey, EN0);
	D2des(inAccount, inAccount);
	D2des(inAccount + 16, inAccount + 16);

	return TRUE;
}


APENCODER_API bool PasswordEncoder(unsigned char * inPassword)
{
	//inAccount[32];
	//unsigned char inAccount[32];
	UINT32 * p;
	p = (UINT32 *)inPassword;
	*p = (*p) ^ 0xf24d83e5;
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
	des2key(PasswordKey, EN0);
	D2des(inPassword, inPassword);
	D2des(inPassword + 16, inPassword + 16);

	return TRUE;
}

APENCODER_API bool EncodeFunc(size_t encode_id, unsigned char * input, unsigned char * output)
{
	if (pCV == NULL)return FALSE;
	pCV->EncodeFunc(encode_id, input, output);
	return TRUE;
}


/*

// This is the constructor of a class that has been exported.
// see APEncoder.h for the class definition
CAPEncoder::CAPEncoder()
{
	return;
}

*/