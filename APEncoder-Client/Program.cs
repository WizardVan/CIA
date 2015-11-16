using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Security.Cryptography;

namespace APDLLTEST
{
    class Program
    {
        [DllImport("APEncoder.dll",EntryPoint = "?AccountEncoder@@YA_NPAE@Z", SetLastError = true)]
        static extern bool AccountEncoder([In,Out] byte[] inAccount );
        //input:inAccount:byte[32]
        //output:inAccount:byte[32]
        //return True:Sucess False:Fail

        [DllImport("APEncoder.dll", EntryPoint = "?PasswordEncoder@@YA_NPAE@Z", SetLastError = true)]
        static extern bool PasswordEncoder([In, Out] byte[] inPassword);
        //input:inPassword:byte[32]
        //output:inPassword:byte[32]
        //return True:Sucess False:Fail

        [DllImport("APEncoder.dll", EntryPoint = "?EncodeFunc@@YA_NIPAE0@Z", SetLastError = true)]
        static extern bool EncodeFunc(int Encode_ID, [In] byte[] inPut, [Out] byte[] outPut);
        //input:Encode_ID:0-2047 inPut:MD5 byte[]
        //output:outPut:byte[16]
        //return True:Sucess False:Fail

        [DllImport("APEncoder.dll", EntryPoint = "?PacketEncoder@@YA_NIPAEH@Z", SetLastError = true)]
        static extern bool PacketEncoder(int Encode_ID, [In, Out] byte[] inPut, int Length);
		//input:Encode_ID:0-2047 inPut:Any byte[] Length：Length of inPut (in Byte)
        //output:inPut:same Length
        //return True:Sucess False:Fail

        static void Main(string[] args)
        {
            var Account= new byte[32];
            //因为算法限制所以只能输入32byte的数据，不能多也不能少哦.
            for (int i = 0; i < 32;i++ )
            {
                Account[i] = 0;
            }
            AccountEncoder(Account);
            Console.WriteLine(BitConverter.ToString(Account));

            //Console.ReadLine();
            var Password = new byte[32];
            //因为算法限制所以只能输入32byte的数据，不能多也不能少哦.
            
            for (int i = 0; i < 32; i++)
            {
                Password[i] = 0;
            }
            PasswordEncoder(Password);
            Console.WriteLine(BitConverter.ToString(Password));
           
            var info = new byte[128];
            //any length
            for (int i = 0; i < 128; i++)
            {
                info[i] = 0;
            }

            MD5 md5 = new MD5CryptoServiceProvider();
            byte[] md5info = md5.ComputeHash(info);  
            //calc MD5 first
            
            var outinfo = new byte[16];
            for (int i = 0; i < 16; i++)
            {
                outinfo[i] = 0;
            }
            EncodeFunc(1, md5info, outinfo);
            Console.WriteLine(BitConverter.ToString(outinfo));

            var PacketData = new byte[79];
            //因为算法限制所以只能输入32byte的数据，不能多也不能少哦.
            for (int i = 0; i < 79; i++)
            {
                PacketData[i] = 0x41;
            }
            PacketEncoder(1024, PacketData, 79);
            Console.WriteLine(BitConverter.ToString(PacketData));
            Console.ReadLine();
        }
    }
}
