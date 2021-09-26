#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "readfunctions.h"
#include "hash.h"


int main(int argc, char* argv[]){
	
	int HashTable1NumOfEntries,HashTable2NumOfEntries, BucketSize;
	int filename=0;
	FILE* Operations;
	if (argc<7 || argc>9){
		perror("Wrong number of arguments: Execution call =\n\t./werhauz -o Operations -h1 HashTable1NumOfEntries -h2 HashTable2NumOfEntries -s BucketSize\nwhere: \n\t-o Operations is optional\n");	
		return -1;
	}else{
		int i;
		for(i=1; i<argc; i++){					//diabazw ta arguments
			if( strcmp(argv[i], "-o")==0 ){			//an brw -o
				Operations = fopen( argv[i+1], "r" );	//anoigw to arxeio gia diabasma
				if ( Operations == NULL ){
					perror("Error in opening file/n");
					return -1;
				}
				filename=1;				//flag oti uparxei arxeio apopou tha diabasoume prwta entoles
			}else if( strcmp( argv[i], "-h1" )==0 ){	//briskw -h1
				HashTable1NumOfEntries = atoi(argv[i+1]);			
			}else if( strcmp( argv[i], "-h2" )==0 ){	//briskw -h2
				HashTable2NumOfEntries = atoi(argv[i+1]);
			}else if( strcmp( argv[i], "-s" )==0 ){		//briskw -s
				BucketSize = atoi(argv[i+1]);
			}
		}	
	}
	int res1, res2, res3, res4, res5, res6, res7, res8, res9, afterbye=0;
	if(filename==1){					//an uparxei arxeio eisodou entolwn
		struct ht_entry *ht1=NULL, *ht2=NULL;
		ht1=CreateHashTable(HashTable1NumOfEntries);	//dhmiourgw hashtable1
		if(ht1==NULL){
			perror("Error allocating hashtable1\n");
			return -1;
		}
		printf("HashTable1 has been created\n");
		ht2=CreateHashTable(HashTable2NumOfEntries);	//dhmiourgw hashtable2
		if(ht2==NULL){
			perror("Error allocating hashtable2\n");
			return -1;
		}
		printf("HashTable2 has been created\n");
		printf("BucketSize = %d\n",BucketSize);
					
		char *line;		
		while(!feof(Operations)){		//diabazei to arxeio grammh-grammh mexri na ftasei sto telos 
			line = malloc(80*sizeof(char));	//kai analoga thn periptwsh kalei kai thn katallhlh sunarthsh
			fgets(line, 80, Operations);	
			if( strstr(line, "insert")!=NULL ){
				struct cdr_entry cdri;
				ReadInsert(&cdri, line);
				res1 = Insert(ht1, ht2, HashTable1NumOfEntries, HashTable2NumOfEntries, &cdri, BucketSize);
				if(res1!=0)
					return -1;

			}else if( strstr(line, "delete")!=NULL ){
				struct todel todel1;
				ReadDelete(&todel1, line);
				res2 = Delete(ht1, HashTable1NumOfEntries, &todel1);
				if(res2!=0)
					return -2;

			}else if( strstr(line, "find")!=NULL ){
				struct tofind tofind1;
				ReadFindLookup(&tofind1,line);
				res3 = Find(ht1, HashTable1NumOfEntries, &tofind1);
				if(res3!=0)
					return -3;
	
			}else if( strstr(line, "lookup")!=NULL ){
				struct tofind tolookup1;
				ReadFindLookup(&tolookup1,line);
				res4 = Lookup(ht2, HashTable2NumOfEntries, &tolookup1);
				if(res4!=0)
					return -4;
	
			}else if( strstr(line, "indist")!=NULL ){
				struct indist ind1;
				ReadIndist(&ind1,line);
				res5 = Indist(ht1, HashTable1NumOfEntries, &ind1);
				if(res5!=0)
					return -5;
	
			}else if( strstr(line, "topdest")!=NULL && strlen(line)>9 ){
				struct topdest top1;
				ReadTopdest(&top1,line);
				res6 = Topdest(ht1, HashTable1NumOfEntries, &top1);
				if(res6!=0)
					return -6;
			
			}else if( strstr(line, "bye")!=NULL ){
				res7 = Bye(ht1, ht2, HashTable1NumOfEntries, HashTable2NumOfEntries);
				if(res7!=0)
					return -7;
				ht1=NULL;
				ht2=NULL;
				afterbye=1;		//an theloume na sunexisoume
		
			}else if( strstr(line, "print")!=NULL ){
				if(strstr(line, "hashtable1")!=NULL){
					printf("\nprint hashtable1 >>>>\n");
					res8 = PrintHashTable(ht1, HashTable1NumOfEntries);
				}else{
					printf("\nprint hashtable2 >>>>\n");
					res8 = PrintHashTable(ht2, HashTable2NumOfEntries);
				}
				if(res8!=0)
					return -8;
		
			}else if( strstr(line, "dump")!=NULL ){
				struct dump d;			
				ReadDump(&d,line);
				if(strstr(line, "hashtable1")!=NULL){
					printf("\ndump hashtable1 >>>>\n");
					FILE *fp1;
					fp1=fopen(d.filename, "w");
					res9 = Dump(ht1, HashTable1NumOfEntries, fp1);
					fclose(fp1);
				}else{
					printf("\ndump hashtable2 >>>>\n");
					FILE *fp2;
					fp2=fopen(d.filename, "w");
					res9 = Dump(ht2, HashTable2NumOfEntries, fp2);
					fclose(fp2);
				}
				if(res9!=0)
					return -9;
	
			}/*else if( strstr(line, "top")!=NULL && strlen(line)<=8 ){
				int top = ReadTop(line);
			}*/
			free(line);
 		}
		fclose(Operations);		//kleinw to arxeio
	}
	if(filename==0 || afterbye==1){			//den uparxei arxeio eisodou entolwn-diabazoume apo to terminal entoles
		int ch1;				//an afterbye==1 exoume diabasei kai exoume teleiwsei me to arxeio eisodou
		if(afterbye==1){
			printf("DO YOU WANT TO CONTINUE?\n\tPRESS :\t1 FOR YES\n\t\t0 FOR NO\n");
			scanf("%d",&ch1);
			getchar();
			if(ch1==0){
				printf("EXIT\n");
				return 0;
			}
		}
		struct ht_entry *ht01=NULL, *ht02=NULL;
		ht01=CreateHashTable(HashTable1NumOfEntries);	//dhmiourgw hashtable1
		if(ht01==NULL){
			perror("Error allocating hashtable1\n");
			return -1;
		}
		printf("HashTable1 has been created\n");
		ht02=CreateHashTable(HashTable2NumOfEntries);	//dhmiourgw hashtable2
		if(ht02==NULL){
			perror("Error allocating hashtable2\n");
			return -1;
		}
		printf("HashTable2 has been created\n");
		printf("BucketSize = %d\n",BucketSize);
		int i=0,cont=1,flag=0;
		char ch;
		char *line;
		printf("TYPE THE COMMAND TO BE EXECUTED\n");
		while(cont!=0){					//oso thelei o xrhsths na eisagei entoles
			line = malloc(80*sizeof(char));
			i=0;
			while((ch=getchar())!='\n')		//diabazw thn entolh kai thn apothikeuw sto line
				line[i++]=ch;
			line[i++]='\n';
			line[i]='\0';
//			printf("\n%s/\n",line);
			if( strstr(line, "insert")!=NULL ){	//analoga thn periptwsh kalw kai thn katallhlh sunarthsh
				struct cdr_entry cdri;
				ReadInsert(&cdri, line);
				res1 = Insert(ht01, ht02, HashTable1NumOfEntries, HashTable2NumOfEntries, &cdri, BucketSize);
				if(res1!=0)
					return -1;

			}else if( strstr(line, "delete")!=NULL ){
				struct todel todel1;
				ReadDelete(&todel1, line);
				res2 = Delete(ht01, HashTable1NumOfEntries, &todel1);
				if(res2!=0)
					return -2;

			}else if( strstr(line, "find")!=NULL ){
				struct tofind tofind1;
				ReadFindLookup(&tofind1,line);
				res3 = Find(ht01, HashTable1NumOfEntries, &tofind1);
				if(res3!=0)
					return -3;
	
			}else if( strstr(line, "lookup")!=NULL ){
				struct tofind tolookup1;
				ReadFindLookup(&tolookup1,line);
				res4 = Lookup(ht02, HashTable2NumOfEntries, &tolookup1);
				if(res4!=0)
					return -4;
	
			}else if( strstr(line, "indist")!=NULL ){
				struct indist ind1;
				ReadIndist(&ind1,line);
				res5 = Indist(ht01, HashTable1NumOfEntries, &ind1);
				if(res5!=0)
					return -5;
	
			}else if( strstr(line, "topdest")!=NULL && strlen(line)>9 ){
				struct topdest top1;
				ReadTopdest(&top1,line);
				res6 = Topdest(ht01, HashTable1NumOfEntries, &top1);
				if(res6!=0)
					return -6;
			
			}else if( strstr(line, "bye")!=NULL ){
				res7 = Bye(ht01, ht02, HashTable1NumOfEntries, HashTable2NumOfEntries);
				if(res7!=0)
					return -7;
				ht01=NULL;
				ht02=NULL;
//				return 0;
		
			}else if( strstr(line, "print")!=NULL ){
				if(strstr(line, "hashtable1")!=NULL){
					printf("\nprint hashtable1 >>>>\n");
					res8 = PrintHashTable(ht01, HashTable1NumOfEntries);
				}else{
					printf("\nprint hashtable2 >>>>\n");
					res8 = PrintHashTable(ht02, HashTable2NumOfEntries);
				}
				if(res8!=0)
					return -8;
		
			}else if( strstr(line, "dump")!=NULL ){
				struct dump d;			
				ReadDump(&d,line);
				if(strstr(line, "hashtable1")!=NULL){
					printf("\ndump hashtable1 >>>>\n");
					FILE *fp1;
					fp1=fopen(d.filename, "w");
					res9 = Dump(ht01, HashTable1NumOfEntries, fp1);
					fclose(fp1);
				}else{
					printf("\ndump hashtable2 >>>>\n");
					FILE *fp2;
					fp2=fopen(d.filename, "w");
					res9 = Dump(ht02, HashTable2NumOfEntries, fp2);
					fclose(fp2);
				}
				if(res9!=0)
					return -9;
	
			}/*else if( strstr(line, "top")!=NULL && strlen(line)<=8 ){
				int top = ReadTop(line);
			}*/			

			printf("\nPRESS:\n\t1 TO CONTINUE\n\t0 TO EXIT\n");
			scanf("%d",&cont);
			if(cont!=1 && cont!=0){
				while(cont!=1 && cont!=0){
					printf("WRONG CHARACTER ...TRY AGAIN\n");			
					scanf("%d",&cont);
				}
			}
			if(cont==1){
				getchar();
				printf("TYPE THE COMMAND TO BE EXECUTED\n");
				free(line);	
			}else if(cont==0){
				printf("EXIT\n");
				break;
			}	
		}	
	}
	return 0;
}
