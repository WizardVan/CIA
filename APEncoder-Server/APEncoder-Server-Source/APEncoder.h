// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the APENCODER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// APENCODER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef APENCODER_EXPORTS
#define APENCODER_API __declspec(dllexport)
#else
#define APENCODER_API __declspec(dllimport)
#endif

// This class is exported from the APEncoder.dll
/*
class APENCODER_API CAPEncoder {
public:
	CAPEncoder(void);
	// TODO: add your methods here.
};

extern APENCODER_API int nAPEncoder;

APENCODER_API int fnAPEncoder(void);
*/

APENCODER_API bool AccountEncoder(unsigned char * inAccount);
APENCODER_API bool PasswordEncoder(unsigned char * inPassword);
APENCODER_API bool EncodeFunc(size_t encode_id, unsigned char * input, unsigned char * output);
APENCODER_API bool PacketEncoder(size_t encode_id, unsigned char * input, int length);