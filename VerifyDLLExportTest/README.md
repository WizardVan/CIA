VerifyDLLExportTest is a simple test that shows how to export some functions in a class which is not exported by DLL.NxVerify doesn't export the functions but it leaks the address of an object of this class.VerifyDLLExportTest shows how to use this leaked address to determine and recover whole virtual function table and use these functions.

VerifyDLLExportTest是一个简单的测速来展示如何使用dll中未被导出的函数，在这个例子中，NxVerify没有导出我们需要的函数，但是它泄露了一个实例的地址，而这个实例拥有一个虚函数表，这个虚函数表包含着我们需要的函数指针。因此在这个例子中就展示了如何使用这些函数。
