IntegrityCheck is an integrity checker for NxVerify.It uses MD5 first and EncodeFunc after.It looks like dynamic because the result of EncodeFunc is depend on encode_id which is sent by server.The checker can work on both client and server side. IntegrityCheck是一个完整性验证器，它先对信息进行MD5摘要然后使用EncodeFunc进行动态的摘要。由于EncodeFunc需要使用encode_id来进行摘要变幻，因此实际上它的结果可以看做是动态的。这个验证器可以用于客户端和服务端，两部分做相同的计算即可。