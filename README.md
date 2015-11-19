CIA contains password and account encoder, an integrity checker and a dynamic data stream encoder for NxVerify.NxVerify includes an decode mechanism for account and password.CIA recovers the corresponding encode mechanism. CIA also recovers the integrity check mechanism in NxVerify that can be used as MD5.Based on these two parts,CIA creates a dynamic encryption method can be used on any size data.

CIA包含了一套与NxVerify匹配的帐号密码加密和完整性检测机制。由于NxVerify本身包含了一套账号密码的解码机制，所以CIA还原了对应的加密机制。CIA同时还原了整个完整性检查的过程，基于这两部分的功能上，CIA另外包含了一套用于流式加密的动态对称加密组件。
