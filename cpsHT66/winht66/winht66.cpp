#include <stdio.h>
#include <windows.h>

//WINHT66 by ackerman
//DUMP and SEND file.dat RADIO HESENATE HT66 WINDOWS
//MINGW32
//gcc -s -O2 winht66.cpp -owinht66.exe

//#define COM_PORT "\\\\.\\COM14"  //COM1, COM2, etc.

char paramPort[256]="14"; //COM14
char paramSendFile[256]="custom.dat";
unsigned char gb_do_dump=0;
unsigned char gb_do_send=0;
unsigned char gb_do_help=0;
char cHex[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char dataSendFile[1024];
unsigned short int gb_contDataSendFile=0;
char dataSendTX[20][64];

char COM_PORT[256]="\\\\.\\COM";
HANDLE hComm;

//HANDSHAKE BEGIN
char trama0[8]={0x02,0x54,0x39,0x39,0x39,0x52,0x41,0x4D}; //T999RAM
char trama1[1]={0x02};
char trama2[1]={0x06};
char trama3[1]={0x05};
char trama4[1]={0x06};
//HANDSHAKE END
//GET CHANNEL BEGIN
char trama5[4]={0x52,0x00,0x00,0x0D};
//GET CHANNEL END

unsigned char gb_error=0;
unsigned char gb_warn=0;
char cadOut[1024];
unsigned char gb_receiv[1024];
unsigned short int gb_receiv_cont=0;

void initSerialPort(void);
void sendData(const char* data,unsigned short int auxSize);
void receiveData(char expectedValue);
void closeSerialPort(void);
void ShowOut(void);
void SendHandshake(void);
void DumpMemRadio(void);
void LoadSendFile(void);
void ShowSendFile(void);
void SendMemRadio(void);
void ClearBuffers(void);
void DoAction(int argc, char **argv);
void ChkFileSize(int aSize);
void GetParam(int argc, char **argv);
void ShowHelp(void);
unsigned char GetIdHex(char c);
void PrepareSendBytes(void);
void ShowDataSendTX(void);

//*******************************************
unsigned char GetIdHex(char c)
{
 unsigned char aReturn=0;
 
 for (unsigned char i=0;i<16;i++)
 {
  if (cHex[i]==c)
  {
   aReturn= i;
   break;
  }
 }
 
 return aReturn;
}

//*******************************************
void initSerialPort()
{
 char cadPort[512]="";
 sprintf(cadPort,"%s%s",COM_PORT,paramPort);
      
 //hComm = CreateFile(COM_PORT,GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, 0, NULL);
 hComm = CreateFile(cadPort,GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, 0, NULL);
 if (hComm == INVALID_HANDLE_VALUE)
 {
  printf("ERROR!!! OPEN serial port\n");
  return;
 }

 DCB dcbSerialParams = {0};

 //Obtain the current serial port settings
 if (!GetCommState(hComm, &dcbSerialParams))
 {
  printf("ERROR!!! get status port\n");
  CloseHandle(hComm);
  return;
 }

 //Parameter settings: 9600 baud, 8 data bits, no parity, 1 stop bit
 dcbSerialParams.BaudRate = CBR_9600;
 dcbSerialParams.ByteSize = 8;
 dcbSerialParams.StopBits = ONESTOPBIT;
 dcbSerialParams.Parity = NOPARITY;

 //Apply settings to the serial port
 if (!SetCommState(hComm, &dcbSerialParams))
 {
  printf("ERROR!!! config serial port\n");
  CloseHandle(hComm);
  return;
 }

 // Configurar el tiempo de espera para la lectura
 COMMTIMEOUTS timeouts = {0};
 timeouts.ReadIntervalTimeout = 50;
 timeouts.ReadTotalTimeoutConstant = 50;
 timeouts.ReadTotalTimeoutMultiplier = 10;
 timeouts.WriteTotalTimeoutConstant = 50;
 timeouts.WriteTotalTimeoutMultiplier = 10;

 SetCommTimeouts(hComm, &timeouts);
 printf("Serial port configured correctly\n");
}

//****************************************************************
void sendData(const char* data,unsigned short int auxSize)
{
 unsigned char aux;
 DWORD bytesWritten;
    
 if (gb_error==1)
 {
  return;
 }
    
 if (!WriteFile(hComm, data, auxSize, &bytesWritten, NULL))
 {
  printf("ERROR!!! sending data\n");
  gb_error=1;
 }
 else
 {
  //printf("Datos enviados: %s\n", data);
  printf("TX:");
  for (unsigned short int i=0;i<auxSize;i++)
  {
   aux= (unsigned char)data[i];
   printf("%02X ",aux);
  }
        
  printf("   TEXT:");
  for (unsigned short int i=0;i<auxSize;i++)
  {
   aux= (unsigned char)data[i];
   printf("%c",aux);
  }
  printf("\n");
 }
}

//****************************************************************
void receiveData(char expectedValue)
{
 unsigned char aux;
 char buffer[256];
 DWORD bytesRead;
    
 if (gb_error==1)
 {
  return;
 }
            
 if (ReadFile(hComm, buffer, sizeof(buffer), &bytesRead, NULL))
 {
  if (bytesRead > 0)
  {
   buffer[bytesRead] = '\0';  //force null end
   printf("RX:");
   for (unsigned short int i=0;i<bytesRead;i++)
   {
    aux=(unsigned char)buffer[i];
    printf("%02X ",aux);
    gb_receiv[gb_receiv_cont]= aux;
    gb_receiv_cont++;
   }
   printf("\n");        
  }
  else
  {
   gb_error=1;            
   printf("ERROR!!! No data received.\n");
  }
 }
 else
 {
  gb_error=1;
  printf("ERROR!!! receiving data\n");
 }
 
 if (buffer[0]!=expectedValue)
 {
  gb_warn=1;
  printf("WARN!!! expected value %02X\n",expectedValue);
 }
}

//*************************************************
void closeSerialPort()
{
 CloseHandle(hComm);
 printf("Serial port close\n");
}


//**************************************************
void ShowOut()
{
 unsigned char contLine=0;
 printf("\n\n");
 printf("Total:%d\n",gb_receiv_cont);
 
 printf("[M31_Analog_Redio]\r\n");
 
 for (unsigned short int i=0; i<gb_receiv_cont;i++)
 {
  printf("%02X ",gb_receiv[i]);
  
  contLine++;
  if(contLine>=17)
  {
   printf(" \r\n"); 
   contLine=0;
  }
 }
}

//********************************************
void SaveOut()
{
 unsigned char contLine=0;
 FILE *fOut;
 
 fOut = fopen("dataload.dat","w");
 if (fOut!=NULL)
 { 
  fprintf(fOut,"[M31_Analog_Redio]\n");
 
  for (unsigned short int i=0; i<gb_receiv_cont;i++)
  {
   fprintf(fOut,"%02X ",gb_receiv[i]);
   
   contLine++;
   if(contLine>=17)
   {
    fprintf(fOut,"\n");
    contLine=0;
   }
  }     
  fclose(fOut);
 }
 else 
 {
  printf("ERROR!!! Write dump file\n");
 }
}

//********************************
void SendHandshake()
{
 gb_receiv_cont=0;
 //sendData("T999RAM");
 sendData(trama0,sizeof(trama0));
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;
 
 sendData(trama1,sizeof(trama1));
 receiveData(0x06); //expected value 0600000000000000
 gb_receiv_cont=0;
 
 sendData(trama2,sizeof(trama2));
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;
  
 sendData(trama3,sizeof(trama3));
 receiveData(0xFF); //expected value FFFFFFFFFFFF
 gb_receiv_cont=0;
 
 sendData(trama4,sizeof(trama4));
 receiveData(0x06); //expected value 0x06
 gb_receiv_cont=0;
}

//*********************************
void DumpMemRadio()
{
 int auxContBytes=0;
 
 initSerialPort();  //Init serial
 
 SendHandshake();
 
 gb_receiv_cont=0;
 for (unsigned char i=0;i<18;i++)
 {
  sendData(trama5,sizeof(trama5));
  receiveData(0x57); //expected value 5700000D318DA802318DA802FFFFFFFFFF
  trama5[2]+=0x0D; //Add channel
 }

 closeSerialPort();  //Close serial

 ShowOut();
 

 auxContBytes= (18+2); //Head [M31_Analog_Redio]
 auxContBytes+= (18*(17+2));
 ChkFileSize((gb_receiv_cont*2)+auxContBytes); //Check 974 bytes size
  
 if (gb_error==0)
 {
  SaveOut();
 }
 else
 {
  printf("ERROR!!! File dataload.dat not save\n");
 }
}

//******************************************
void LoadSendFile()
{
 int c=0;
 unsigned short int cntLine=0;
 long int sizeFile=-1;
 
 gb_contDataSendFile=0; 
 
 FILE *f= fopen(paramSendFile,"r");
 if (f!=NULL)
 {
  fseek(f,0,SEEK_END);
  sizeFile= ftell(f);
  fseek(f,0, SEEK_SET);
  
  if (sizeFile<974)
  {
   gb_error=1;
   printf("ERROR!!! The file is not 974 bytes in size\n");
   fclose(f);
   return;
  }    
  
  while ((c= fgetc(f))!= EOF)
  {
   if (c=='\n')
   {                 
    cntLine++; 
    //printf("\n"); 
   }
   else
   {
    if (cntLine>0)
    {
     for (unsigned char i=0;i<16;i++)
     {
      if (c==cHex[i])
      {
       //printf("%c",c);
       dataSendFile[gb_contDataSendFile]=c;
       gb_contDataSendFile++;
      }
     }
    }
   }
  }//fin while
  
  fclose(f);
 }
 else
 {
  gb_error=1;
  printf("ERROR!!! File %s not load\n",paramSendFile);
 }
}

//******************************************
void ShowSendFile()
{
 unsigned char contLine=0;
 unsigned char canal=0;
 
 for (unsigned short i=0;i<gb_contDataSendFile;i++)
 {
  printf("%c",dataSendFile[i]);
  dataSendTX[canal][contLine]= dataSendFile[i];
  dataSendTX[canal][(contLine+1)]='\0';
  
  contLine++;
  if (contLine>=34)
  {//17x2
   printf("\n");
   contLine=0;  
   canal++; 
  }
 }
}

//******************************************
void PrepareSendBytes()
{
 unsigned char contRead=0;
 unsigned char contWrite=0;
 char carHex=' ';
 unsigned char highByte=0;
 unsigned char lowByte=0;
 unsigned char auxByte=0;
 unsigned short int tot=0;
 
 for (unsigned char canal=0;canal<18;canal++)
 {
  contRead=0;
  contWrite=0;  
  tot= strlen(dataSendTX[canal]);
  while (contRead<tot)
  {
   carHex= dataSendTX[canal][contRead];
   highByte= GetIdHex(carHex);
   contRead++;
   carHex= dataSendTX[canal][contRead];
   lowByte= GetIdHex(carHex);  
   contRead++;
  
   auxByte= (highByte<<4)|lowByte;
   dataSendTX[canal][contWrite]= auxByte;
   dataSendTX[canal][(contWrite+1)]='\0';
   contWrite++;
  }
 }
}

//******************************************
void ShowDataSendTX()
{
 printf("\n"); 
 for (unsigned char canal=0;canal<18;canal++)     
 {
  for (unsigned short int i=0;i<34;i++)
  {
   printf("%c",dataSendTX[canal][i]);  
  }
  printf("\n");
 }
}

//******************************************
void SendMemRadio()
{
 gb_error=0;
 gb_warn=0;
 
 LoadSendFile();
 if(gb_error==1){ return; }
 ShowSendFile();
 if(gb_error==1) { return;}
 PrepareSendBytes();
 ShowDataSendTX();
     

 gb_error=0;     
 initSerialPort();  //Init serial
 
 SendHandshake();
 
 gb_receiv_cont=0;
 for (unsigned char i=0;i<18;i++)
 {
  sendData(dataSendTX[i],34);
  receiveData(0x06);  //expected value 06
 }

 closeSerialPort();  //Close serial     
 
}

//******************************************
void ClearBuffers()
{
 for (unsigned short i=0;i<sizeof(cadOut);i++){ cadOut[i]=' '; }
 cadOut[0]='\0';
 
 for (unsigned short i=0;i<sizeof(gb_receiv);i++){ gb_receiv[i]=0; }     

 for (unsigned short i=0;i<sizeof(dataSendFile);i++){ dataSendFile[i]=0; }     
 dataSendFile[0]='\0';
 
 for (unsigned short j=0;j<20;j++)
 {
  for (unsigned short int i=0;i<64;i++)
  {
   dataSendTX[j][i]=' ';
  }
  dataSendTX[j][0]='\0';
 }
 
 gb_error=0;
 gb_warn=0;
 gb_receiv_cont= 0;
}

//***************************************
void DoAction(int argc, char **argv)
{
 if (gb_do_help==1)
 {
  ShowHelp();
  return;
 }
 
 if (gb_do_dump==1)
 {
  DumpMemRadio();
 }
 
 if (gb_do_send==1)
 {
  SendMemRadio();
 }
 
 if(gb_warn==1)
 {
  printf("WARN!!! Warning ocurred\n");
 }
 
 if(gb_error==1)
 {
  printf("ERROR!!! ERROR ocurred\n");
 } 
}

//***************************************
void ChkFileSize(int aSize)
{
 printf("Check file size(974 bytes):%d\n",aSize);
 if (aSize<974)
 {
  printf("ERROR!!! The file is not 974 bytes in size\n");
  gb_error= 1;
 }
}

//***************************************
void GetParam(int argc, char **argv)
{
 gb_do_dump=0;     
 gb_do_send=0;
 const char *cad; 
 
 for (unsigned short int i=1;i<argc;i++)
 {
  //printf("%d %s\n",i,argv[i]);
  if (strstr(argv[i],"-p")!=NULL)
  {  
   cad= argv[i];
   cad+=2;
   //printf("%s\n",cad);
   sprintf(paramPort,"%s",cad);
  }
  else
  {
   if (strstr(argv[i],"-d")!=NULL)
   {
    gb_do_dump=1;
   }
   else
   {
    if (strstr(argv[i],"-s")!=NULL)
    {
     cad= argv[i];
     cad+=2;
     //printf("%s\n",cad);
     sprintf(paramSendFile,"%s",cad);                               
     gb_do_send=1;
    }
    else
    {
     if (strstr(argv[i],"-?")!=NULL)        
     {
      gb_do_help=1;
     }
    }
   }
  }
 }
 
 printf("Param Port:%s\n",paramPort);
 if (gb_do_dump==1)
 {
  printf("Param Dump\n");
 }
 if (gb_do_send==1)
 {
  printf("Param Send:%s\n",paramSendFile);
 }
 //system("PAUSE");
}

//***************************************
void ShowHelp()
{
 printf(" WINHT66 by ackerman                            2026/01/04\n");
 printf(" ----------------------------------------------------------\n");
 printf("  -p(number port) -- COM port\n");
 printf("  -d              -- receive dump mem radio in dataload.dat\n");
 printf("  -s(file.ext)    -- send to radio file file.ext\n");
 printf("  -?              -- show help\n");
 printf("\n");
 printf(" Example dump memory radio from COM14 in dataload.dat:\n");
 printf("   winht66 -p14 -d\n");
 printf("\n");
 printf(" Example send custom.dat to memory radio from COM14:\n");
 printf("   winht66 -p14 -scustom.dat\n");
 printf("\n");
}



//********
//* MAIN *
//********
int main(int argc, char **argv)
{
 ClearBuffers();
 
 //printf("argc:%d\n",argc);
 if (argc<3)
 {  
  ShowHelp();
 }
 else
 {
  GetParam(argc,argv);
  DoAction(argc,argv);
 } 

    
 //system("PAUSE");
 return 0;
}













//Load DUMP
//TX 025439393952414D      T999RAM
//RX 06
//TX 02
//RX 0600000000000000
//TX 06
//RX 06
//TX 05
//RX FFFFFFFFFFFF
//TX 06
//RX 06
//TX 5200000D                      R<NUL><NUL>
//RX 5700000D318DA802318DA802FFFFFFFFFF
//52000D0D57000D0D1392A8021392A802FFFFFFFFFF
//52001A0D57001A0DF596A802F596A802FFFFFFFFFF
//5200270D5700270DD79BA802D79BA802FFFFFFFFFF
//5200340D5700340DB9A0A802B9A0A802FFFFFFFFFF
//5200410D5700410D9BA5A8029BA5A802FFFFFFFFFF
//52004E0D57004E0D7DAAA8027DAAA802FFFFFFFFFF
//52005B0D57005B0D5FAFA8025FAFA802FFFFFFFFFF
//5200680D5700680D41B4A80241B4A802FFFFFFFFFF
//5200750D5700750D23B9A80223B9A802FFFFFFFFFF
//5200820D5700820D05BEA80205BEA802FFFFFFFFFF
//52008F0D57008F0DE7C2A802E7C2A802FFFFFFFFFF
//52009C0D57009C0DC9C7A802C9C7A802FFFFFFFFFF
//5200A90D5700A90DABCCA802ABCCA802FFFFFFFFFF
//5200B60D5700B60D8DD1A8028DD1A802FFFFFFFFFF
//5200C30D5700C30D6FD6A8026FD6A802FFFFFFFFFF
//5200D00D5700D00D1801060000F8FF00FFFFFFE80E
//5200DD0D5700DD0DFFFFFFFFFFFFFFFFFFFFFFFFFF

//WRITE
//TX 025439393952414D
//RX 06
//TX 02
//RX 0600000000000000
//TX 06
//RX 06
//TX 05
//RX FFFFFFFFFFFF
//TX 06
//RX 06
//TX 5700000D318DA802318DA802FFFFFFFFFF
//RX 06
//TX 57000D0D1392A8021392A802FFFFFFFFFF
//RX 06
//TX 57001A0DF596A802F596A802FFFFFFFFFF
//RX 06
//TX 5700270DD79BA802D79BA802FFFFFFFFFF
//RX 06
//TX 5700340DB9A0A802B9A0A802FFFFFFFFFF
//RX 06
//TX 5700410D9BA5A8029BA5A802FFFFFFFFFF
//RX 06
//TX 57004E0D7DAAA8027DAAA802FFFFFFFFFF
//RX 06
//TX 57005B0D5FAFA8025FAFA802FFFFFFFFFF
//RX 06
//TX 5700680D41B4A80241B4A802FFFFFFFFFF
//RX06
//TX 5700750D23B9A80223B9A802FFFFFFFFFF
//RX06
//TX 5700820D05BEA80205BEA802FFFFFFFFFF
//RX06
//TX 57008F0DE7C2A802E7C2A802FFFFFFFFFF
//RX06
//TX 57009C0DC9C7A802C9C7A802FFFFFFFFFF
//RX06
//TX 5700A90DABCCA802ABCCA802FFFFFFFFFF
//RX06
//TX 5700B60D8DD1A8028DD1A802FFFFFFFFFF
//RX06
//TX 5700C30D6FD6A8026FD6A802FFFFFFFFFF
//RX06
//TX 5700D00D1801060000F8FF00FFFFFFE80E
//RX06
//TX 5700DD0DFFFFFFFFFFFFFFFFFFFFFFFFFF
//RX06
//TX 62
