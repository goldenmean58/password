#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int PB=12; //密码位数
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
	}
	if(strcmp(argv[1],"-a")==0){
		if(argc==3){
			char d[255]="python encipher.py -a ";
			char* c=strcat(d,argv[2]);
			system(c);
		}
	}
	if(strcmp(argv[1],"-l")==0){
		system("python encipher.py -l");
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
