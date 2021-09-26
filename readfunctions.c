#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "readfunctions.h"


void ReadInsert(struct cdr_entry *cdr, char* line){
	int i=0;
	while ( line[i++] !=' ' ){}			//diabazw mexri to 1o keno meta to opoio arxizoun ta stoixeia
	char* temp = malloc( 11*sizeof(char) );
	int j=0;	
	while ( line[i] != ';' ){			//diabazw to cdr_uniq_id
		temp[j++]=line[i++];
	}
	temp[j]='\0';
	cdr->cdr_uniq_id = malloc(11*sizeof(char));	
	strcpy(cdr->cdr_uniq_id, temp);			//ana8esh cdr_uniq_id sto antistoixo pedio tou cdr
//	printf("%s/",cdr->cdr_uniq_id);
	i++;
	int x;
	temp = realloc( temp,14*sizeof(char) );		//megalwnw ton temp gia na xwresei to originator_number,destination_number
	for( x=0; x<2; x++){
		j=0;
		while( line[i] != ';' ){		//diabazw ta originator_number,destination_number antoistixa se kathe epanalhpsh
			if( line[i] == '-' )
				 i++;
			temp[j++]=line[i++];
		}
		temp[j]='\0';
		if(x==0)
		{	cdr->originator_number = malloc(14*sizeof(char)); 	//ana8esh originator_number sto antistoixo pedio tou cdr
			strcpy(cdr->originator_number, temp);
//			printf("%s/", cdr->originator_number);
			}
		else
		{	cdr->destination_number = malloc(14*sizeof(char));	//ana8esh destination_number sto antistoixo pedio tou cdr
			strcpy(cdr->destination_number, temp);
//			printf("%s/", cdr->destination_number);
			}
		i++;
	}
	char* temp1 = malloc(9);
	j=0;
	while( line[i] != ';' ){			//diabazw to date
		temp1[j++]=line[i++];
	}
	temp1[j]='\0';
	cdr->date = malloc(9*sizeof(char));		//ana8esh date sto antistoixo pedio tou cdr
	strcpy(cdr->date, temp1);
	free(temp1);
//	printf("%s/",cdr->date);
	i++;
	char* temp2 = malloc( 6*sizeof(char) );
	j=0;
	while( line[i] != ';' ){			//diabazw init_time
		temp2[j++]=line[i++];
	}
	temp2[j]='\0';
	cdr->init_time = malloc( 6*sizeof(char) );	//ana8esh init_time sto antistoixo pedio tou cdr
	strcpy(cdr->init_time, temp2);
	free(temp2);
//	printf("%s/",cdr->init_time);
	i++;
	char* temp3 = malloc( 3*sizeof(char) );
	j=0;
	while( line[i] != ';' ){			//diabazw duration
		temp3[j++]=line[i++];
	}
	temp3[j]='\0';
	cdr->duration=atoi(temp3);			//ana8esh duration sto antistoixo pedio tou cdr
	free(temp3);
//	printf("%d/",cdr->duration);
	i++;
	char temp4 = line[i++];				//diabazw type
	cdr->type = temp4;				//ana8esh type sto antistoixo pedio tou cdr
	i++;
	char temp5 = line[i++];				//diabazw tarrif
	cdr->tarrif = temp5;				//ana8esh tarrif sto antistoixo pedio tou cdr
//	printf("%c/%c/", cdr->type, cdr->tarrif); 
	i++;
	char* temp6 = malloc( 4*sizeof(char) );
	j=0;
	while( line[i] != '\n' ){			//diabazw fault_condition
		temp6[j++]=line[i++];
	}
	temp6[j]='\0';
	cdr->fault_condition=atoi(temp6);		//ana8esh fault_condition sto antistoixo pedio tou cdr
	free(temp6);
//	printf("%d/\n",cdr->fault_condition);
}

void ReadDelete(struct todel* todel1, char* line){
	int i=0;
	while ( line[i++] !=' ' ){}			//diabazw mexri to 1o keno meta to opoio arxizoun ta stoixeia
	char* temp = malloc( 11*sizeof(char) );
	int j=0;	
	while ( line[i] != ' ' ){			//diabazw cdr_uniq_id
		temp[j++]=line[i++];
	}
	temp[j]='\0';
	todel1->cdr_uniq_id = malloc(11*sizeof(char));	
	strcpy(todel1->cdr_uniq_id, temp);		//ana8esh cdr_uniq_id sto antistoixo pedio tou todel1
	free(temp);
//	printf("%s/",todel1->cdr_uniq_id);
	i++;
	char* temp1 = malloc(14*sizeof(char));
	j=0;
	while( line[i] != '\n' ){			//diabazw caller
		if( line[i] == '-' )
			 i++;
		temp1[j++]=line[i++];
	}
	temp1[j]='\0';
	todel1->caller = malloc(14*sizeof(char));
	strcpy(todel1->caller, temp1);			//ana8esh caller sto antistoixo pedio tou todel1
	free(temp1);
//	printf("%s/\n",todel1->caller);	
}

void ReadFindLookup(struct tofind* tofind1, char* line){
	int i,blanks=0;	
	for(i=0; i<strlen(line)+1; i++){		//arxika diabazw ton arithmo ton kenwn gia na 3erw posa stoixeia
		if( line[i]==' ' )			//exei h grammh (caller, time1, time2, year1, year2)
			blanks++;
	}
	i=0;
	if ( blanks==1 ){				//an ta kena einai 1 tote exoume mono to stoixeio caller
		while ( line[i++] !=' ' ){}		//diabazw mexri to 1o keno meta tou opoiou arxizei to stoixeio
		char* temp = malloc( 14*sizeof(char) );
		int j=0;	
		while ( line[i] != '\n' ){		//diabazw caller
			if( line[i] == '-' )
				i++;
			temp[j++]=line[i++];
		}
		temp[j]='\0';
		tofind1->caller = malloc(14*sizeof(char));
		strcpy(tofind1->caller, temp);		//ana8esh caller sto antistoixo pedio tou tofind1
//		printf("%s/\n", tofind1->caller);
		free(temp);
		tofind1->time1=NULL;			//ta upoloipa pedia tou tofind1 null
		tofind1->time2=NULL;
		tofind1->year1=NULL;
		tofind1->year2=NULL;
	}else{
		while ( line[i++] !=' ' ){}		//diabazw mexri to 1o keno meta tou opoiou arxizei to stoixeio
		char* temp = malloc( 14*sizeof(char) );
		int j=0;	
		while ( line[i] != ' ' ){		//diabazw caller
			if( line[i] == '-' )
				i++;
			temp[j++]=line[i++];
		}
		temp[j]='\0';
		tofind1->caller = malloc(14*sizeof(char));
		strcpy(tofind1->caller, temp);		//ana8esh caller sto antistoixo pedio tou tofind1
//		printf("%s/", tofind1->caller);
		free(temp);
		
		if( blanks==3 ){				//an ta kena einai 3 exoume ta stoixeia caller, time1, time2
			i++;
			j=0;	
			char* temp1= malloc(6*sizeof(char));
			while ( line[i] != ' ' ){		//diabazw time1
				temp1[j++]=line[i++];
			}
			temp1[j]='\0';
			tofind1->time1= malloc(6*sizeof(char));
			strcpy(tofind1->time1, temp1);		//ana8esh time1 sto antistoixo pedio tou tofind1
			free(temp1);
//			printf("%s/", tofind1->time1);
			
			i++;
			j=0;
			char* temp2= malloc(6*sizeof(char));
			while ( line[i] != '\n' ){		//diabazw time2
				temp2[j++]=line[i++];
			}
			temp2[j]='\0';
			tofind1->time2= malloc(6*sizeof(char));
			strcpy(tofind1->time2, temp2);		//ana8esh time2 sto antistoixo pedio tou tofind1
			free(temp2);
//			printf("%s/\n", tofind1->time2);
			tofind1->year1=NULL;			//ta upoloipa pedia tou tofind1 kena
			tofind1->year2=NULL;		
		}else if( blanks==5 ){				//an ta kena einai 5 exoume ta stoixeia caller, time1, year1, time2, year2
			i++;
			j=0;	
			char* temp3= malloc(6*sizeof(char));
			while ( line[i] != ' ' ){		//diabazw time1
				temp3[j++]=line[i++];
			}
			temp3[j]='\0';
			tofind1->time1= malloc(6*sizeof(char));	
			strcpy(tofind1->time1, temp3);		//ana8esh time1 sto antistoixo pedio tou tofind1	
			free(temp3);
//			printf("%s/", tofind1->time1);
			
			i++;
			j=0;
			char* temp4= malloc(9*sizeof(char));
			while ( line[i] != ' ' ){		//diabazw year1
				temp4[j++]=line[i++];
			}
			temp4[j]='\0';
			tofind1->year1= malloc(9*sizeof(char));
			strcpy(tofind1->year1, temp4);		//ana8esh year1 sto antistoixo pedio tou tofind1
			free(temp4);
//			printf("%s/", tofind1->year1);
	
			i++;
			j=0;	
			char* temp5= malloc(6*sizeof(char));
			while ( line[i] != ' ' ){		//diabazw time2
				temp5[j++]=line[i++];
			}
			temp5[j]='\0';
			tofind1->time2= malloc(6*sizeof(char));
			strcpy(tofind1->time2, temp5);		//ana8esh time2 sto antistoixo pedio tou tofind1
			free(temp5);
//			printf("%s/", tofind1->time2);
	
			i++;
			j=0;
			char* temp6 = malloc(9*sizeof(char));
			while ( line[i] != '\n' ){		//diabazw year2
				temp6[j++]=line[i++];
			}
			temp6[j]='\0';
			tofind1->year2= malloc(9*sizeof(char));
			strcpy(tofind1->year2, temp6);		//ana8esh year2 sto antistoixo pedio tou tofind1
			free(temp6);
//			printf("%s/\n", tofind1->year2);		
		}
	}
}

void Separate1(struct time12* t, char* time1){	//dexetai ena string pou periexei mia wra kai to xwrizei se wres kai lepta
	int i,j=0;
	char h1[3],min1[3];
	for(i=0; i<2;i++){		//diabazei thn wra
		h1[i]=time1[i];
	}
	h1[2]='\0';
	t->hours1=atoi(h1);		//ana8esh wras sto antistoixo pedio tou t
	for(i=3; i<5; i++){		//diabazei ta lepta
		min1[j++]=time1[i];
	}
	min1[2]='\0';
	t->mins1=atoi(min1);		//ana8esh leptwn sto antistoixo pedio tou t
//	printf("%d %d\n", t->hours1, t->mins1);
}

void Separate2(struct timedate12* t, char* time1, char* date1){	//dexetai 2 strings, ena pou periexei thn wra kai ena thn hmeromhnia
	int i,j=0;						//kai xwrizei thn wra se wres kai lepta kai thn hmeromhnia se mera,mhna,xrono
	char h1[3],min1[3];
	for(i=0; i<2;i++){		//diabazw thn wra
		h1[i]=time1[i];
	}
	h1[2]='\0';
	t->hours1=atoi(h1);		//ana8esh wras sto antistoixo pedio tou t
	for(i=3; i<5; i++){		//diabazw ta lepta
		min1[j++]=time1[i];
	}
	min1[2]='\0';
	t->mins1=atoi(min1);		//ana8esh leptwn sto antistoixo pedio tou t
//	printf("%d %d\n", t->hours1, t->mins1);
	
	char d1[3],m1[3],y1[5];
	for(i=0; i<2;i++){		//diabazw th mera
		d1[i]=date1[i];
	}
	d1[2]='\0';
	t->day1=atoi(d1);		//ana8esh meras sto antistoixo pedio tou t
	j=0;
	for(i=2; i<4; i++){		//diabazw to mhna
		m1[j++]=date1[i];
	}
	m1[2]='\0';
	t->month1=atoi(m1);		//ana8esh mhna sto antistoixo pedio tou t
	j=0;
	for(i=4; i<8; i++){		//diabazw to xrono
		y1[j++]=date1[i];
	}
	y1[4]='\0';
	t->year1=atoi(y1);		//ana8esh xronou sto antistoixo pedio tou t
//	printf("%d %d %d %d %d\n", t->hours1, t->mins1, t->day1, t->month1, t->year1);
}

void ReadTopdest(struct topdest* top1, char* line){
	int i=0;
	while ( line[i++] !=' ' ){}	//diabazw mexri to 1o keno meta tou opoiou arxizei to stoixeio
	char* temp = malloc( 14*sizeof(char) );	
	int j=0;
	while( line[i] != '\n' ){	//diabazw ton caller
		if( line[i] == '-' )
			 i++;
		temp[j++]=line[i++];
	}
	temp[j]='\0';
	top1->caller = malloc(14*sizeof(char));
	strcpy(top1->caller, temp);	//ana8esh caller sto antistoixo pedio tou top1
//	printf("read: %s/\n", top1->caller);
	free(temp);			
}

void SeparateTopdest(struct topdest_entry* t, char* callnumber){ 	//dexetai ena string pou periexei enan arithmo thlefwnou kai 3exwrizei
									//ton 3-pshfio kwdiko xwras 
	int i;
	char codenumber[4];
	for(i=0; i<3; i++){		//diabazei ton kwdiko xwras
		codenumber[i]=callnumber[i];
	}
	codenumber[i]='\0';
	t->charcode=malloc(4*sizeof(char));
	strcpy(t->charcode,codenumber);	//ana8esh kwdikou xwras sto antistoixo pedio tou t
	t->code=atoi(codenumber);	//ana8esh kwdikou xwras ws akeraio sto antistoixo pedio tou t
//	printf("code =%d c =%s\n",t->code,t->charcode);
}

void ReadDump(struct dump* d,char* line){

	int i,j,x=0,count=0,chars=0;
	while(count!=2){		//diabazw ta 2 prwta kena meta ta opoia arxizei to onoma tou filename
		if(line[i]==' ')
			count++;
		i++;
	}
	j=i;
	while(line[i++]!='\n')		//diabazw ton arithmo twn xarakthrwn tou filename
		chars++;
	char* temp = malloc((chars+1)*sizeof(char));
	i=j;
	while(line[i]!='\n')		//diabazw to filename
		temp[x++]=line[i++];
	temp[x]='\0';
	d->filename=malloc((chars+1)*sizeof(char));
	strcpy(d->filename, temp);	//ana8esh filename sto antistoixo pedio tou d
//	printf("%s/\n",d->filename);
	free(temp);
}

void ReadIndist(struct indist* ind1, char* line){
	int i=0;
	while ( line[i++] !=' ' ){}		//diabazw mexri to 1o keno meta tou opoiou arxizoun ta stoixeia
	char* temp = malloc( 14*sizeof(char) );	
	int j=0;
	while( line[i] != ' ' ){		//diabazw ton caller1
		if( line[i] == '-' )
			 i++;
		temp[j++]=line[i++];
	}
	temp[j]='\0';
	ind1->caller1 = malloc(14*sizeof(char));
	strcpy(ind1->caller1, temp);		//ana8esh caller1 sto antistoixo pedio tou ind1
//	printf("%s/", ind1->caller1);
	free(temp);	
	i++;
	j=0;
	char* temp1 = malloc( 14*sizeof(char) );
	while( line[i] != '\n' ){		//diabazw ton caller2
		if( line[i] == '-' )
			 i++;
		temp[j++]=line[i++];
	}
	temp1[j]='\0';
	ind1->caller2 = malloc(14*sizeof(char));
	strcpy(ind1->caller2, temp1);		//ana8esh caller2 sto antisoixo pedio tou ind1
//	printf("%s/\n", ind1->caller2);
	free(temp1);	
}


/*int ReadTop(char* line){	//diabazei ton mexri 3 pshfia arithmo k gia thn top k%
	int i=0;
	while ( line[i++] !=' ' ){}
	char* temp = malloc(4*sizeof(char));
	int j=0;
	while( line[i] != '\n' ){
		temp[j++]=line[i++];
	}
	temp[j]='\0';	
	int top = atoi(temp);
	free(temp);
	printf("top=%d\n",top);
	return top;
}*/
