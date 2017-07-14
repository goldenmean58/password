#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
int PB=12; //默认密码位数

void encode(char* text,char* key){
	//XOR
	srand((unsigned)time(NULL));
	int i=0;
	int k;
	while(*(text+i)!='\0'){
		k=(int)(1+rand()%9+0.5);
		*(text+i) = (int)*(text+i) ^ k;
		*(key+i)=48+k; // to string '12345679'
		i++;
	}
}

void decode(char* mText,char* key){
	int i=0;
	while(*(mText+i)!='\0'){
		if((int)*(mText+i)!=10){
			*(mText+i)=(int)(*(mText+i))^((int)(*(key+i))-48);
		}
		i++;
	}
}

int main(int argc,char*argv[]){
	if(strstr(argv[1],"--help")){
		printf("password - help you manage your passwords \n -r [bitnum] make a random password\n -a add a record\n -l list all the data\n -d <linenumber> delete one line");
	}
	if(strcmp(argv[1],"-r")==0){
		if(argc==3){
			PB=atoi(argv[2]);
		}
		//defalut 12 bit [a-z][A-Z][0-9]
		srand((unsigned)time(NULL));
		char* pPas=(char*)calloc(PB+1,1);
		for(int i=0;i<PB;i++){
			int charType=(int)(1+rand()%3+0.5);
			switch(charType){
			case 1:
				//[a-z]
				*(pPas+i)=(rand() % (122-97+1))+97;
				break;
			case 2:
				//[A-Z]
				*(pPas+i)=(rand() % (90-65+1))+65;
				break;
			case 3:
				//[0-9]
				*(pPas+i)=(rand() % (57-48+1))+48;
				break;
			}
		}
		printf(pPas);
		free(pPas);
	}
	char d[255];
	if(strcmp(argv[1],"-a")==0){
		if(argc==3){
			//sprintf(d,"encipher.py -a %s",argv[2]);
			//system(d);
			char* key=NULL;
			key=(char*)malloc(strlen(argv[2])+1);
			memset(key,0,sizeof(key));
			encode(argv[2],key);
			sprintf(argv[2],"%s\n",argv[2]);
			sprintf(key,"%s\n",key);
			FILE* fp=fopen("pdd","a");
			if(fp==NULL){
				printf("System:no data\n");
				exit(0);
			}
			fwrite(argv[2],1,strlen(argv[2]),fp);
			fclose(fp);
			FILE*f=fopen("pk","a");
			fwrite(key,1,strlen(key),f);
			fclose(f);
			free(key);
		}
	}
	if(strcmp(argv[1],"-l")==0){
		FILE *pFile=fopen("pdd","r"); 
		if(pFile==NULL)
		{
			printf("System:no data");
			exit(0);
		}
		fseek(pFile,0,SEEK_END); 
		int len=ftell(pFile); 
		char* mText; //new char[1]; 
		mText=(char*)malloc(len+1);
		rewind(pFile);
		fread(mText,1,len,pFile); 
		mText[len]=0; 
		fclose(pFile); 
		
		pFile=fopen("pk","r"); //获取文件的指针
		char *pkey;  //定义文件指针
		fseek(pFile,0,SEEK_END); //把指针移动到文件的结尾 ，获取文件长度
		len=ftell(pFile); //获取文件长度
		pkey=(char*)malloc(len+1); //定义数组长度
		rewind(pFile); //把指针移动到文件开头 因为我们一开始把指针移动到结尾，如果不移动回来 会出错
		fread(pkey,1,len,pFile); //读文件
		pkey[len]=0; //把读到的文件最后一位 写为0 要不然系统会一直寻找到0后才结束
		fclose(pFile); // 关闭文件
		decode(mText,pkey);
		printf(mText);
		free(mText);
		free(pkey);
	}
	if(strcmp(argv[1],"-d")==0){
		//get line
		int line=atoi(argv[2]);
		//nl regular_express.txt | sed '5d'
		char buf[255];
		sprintf(buf,"sed -i \'%dd\' pdd;sed -i \'%dd\' pk",line,line);
		system(buf);
	}
}
