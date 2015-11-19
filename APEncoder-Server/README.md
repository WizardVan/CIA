APEncoder is a NxVerify encryption tool.It contains an account encoder/decoder,a password encoder/decoder ,an integrity checker and a packet encoder/decoder.

The account encoder/decoder and password encoder/decoder are same as AccountEncoder and PasswordEncoder so just read that repo.

The integrity checker is same as IntegrityCheck so also read that repo XD.

PacketEncoder is a dynamic stream encoder/decoder.It can decode packets from client.It also can encode packets sent to client.It is not same as PacketEncoder function on client side.

PacketEncoder uses EncodeFunc and encode_id to generate new key dynamically.After key generated,D2des uses the one of the paired key to encrypt whole blocks and second part of key to encrypt the paddings.

ServerDecoder is a simple sample to test the tool.

APEncoder是一个为NxVerify设计的加密套件。它包括了一套账号加密解密、密码加密解密、完整性检查和数据包加密解密装置。

账号加密解密、密码加密解密装置与AccountEncoder和PasswordEncoder是一样的，因此去读那些源吧。

完整性检查器和IntegrityCheck也是一样的，所以你只能去那边啦~

PacketEncoder是一个动态的对称流式加密系统，这个系统可以同时工作在服务器上和客户端上，它既可以解密来自客户端的包，也可以加密发送给客户端的包，要注意的是这个函数与客户端的函数有些微差别不能混用。

PacketEncoder首先使用EncodeFunc和encode_id来生成新的动态秘钥。在新的秘钥生成之后，D2des会首先使用新的秘钥中的一把来加密16位的区块部分，随后用另一把钥匙对后面补足的部分进行加密。

ServerDecoder则是一个非常简陋的测试实例。
