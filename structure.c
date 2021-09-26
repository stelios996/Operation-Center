#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "structure.h"


#define CDRBUCKET_SIZE 15000

struct ht_entry* CreateHashTable(int h){
	int i;
	struct ht_entry* HashTable;
	HashTable = malloc( h*sizeof(struct ht_entry) );	//desmeuw xwro gia h stoixeia gia ton hashtable
	if(HashTable == NULL){
		perror("Error allocating HashTable\n");
		return NULL;
	}
	for( i=0; i<h; i++){					//gia ka8e stoixeio tou hashtable dhmiourgw kai to arxiko tou keno bucket
		struct bucket* bucket1;
		bucket1= malloc(sizeof(struct bucket));

		bucket1->bucket_entries = NULL;
		bucket1->next_bucket = NULL;
		bucket1->count = 0;
	
		HashTable[i].current_bucket = bucket1;
		HashTable[i].first_bucket = bucket1;
	}
//	printf("HashTable has been set\n");	
	return HashTable;					//epistrefw ton hashtable
}

int Insert(struct ht_entry *ht1, struct ht_entry *ht2,int h1, int h2, struct cdr_entry *cdr, int bucket_size){

	int bucket_capacity = bucket_size / (14*sizeof(char));//o ari8mos stoixeiwn pou xwraei se ena bucket
	int cdrbucket_capacity = CDRBUCKET_SIZE / (56*sizeof(char)+2*sizeof(int));	 //o ari8mos stoixeiwn pou xwraei se ena cdr_bucket
//	printf("bucket_capacity=%d\tcdrbucket_capacity=%d\n",bucket_capacity,cdrbucket_capacity);

//------insert to HashTable1
	printf("\ninsert >>>>\n");
	int bucket_pos, cdrbucket_pos;
	unsigned long pos =(unsigned long) hashfunction(cdr->originator_number)%h1;   //h thesh tou hashtable1 pou tha ginei insert to stoixeio
//	printf("pos = %lu\t",pos);

	struct bucket* pointer = NULL;
	pointer = ht1[pos].first_bucket;	//3ekinw apo to prwto bucket tou ht1[pos]
	if(pointer==NULL){
		perror("IError: pointer to first bucket NULL\n");
		return -10;
	}

	int flag=0;
	if(pointer->count!=0){							//an den einai keno to bucket
		while( pointer!=NULL){						//e3etazw ola ta buckets
			int i;
			for(i=0; i < pointer->count; i++){			//oles tis eggrafes tou bucket
				if(strcmp(pointer->bucket_entries[i].callnumber, cdr->originator_number) == 0){	//an uparxei sto bucket	
					pointer->bucket_entries[i].pcdr->count++;			
					if(pointer->bucket_entries[i].pcdr->count <= cdrbucket_capacity){	//an uparxei xwros sto cdr_bucket	
						cdrbucket_pos = (pointer->bucket_entries[i].pcdr->count) - 1;	//h 8esh pou tha mpei

						struct cdr_entry* current2;			//eisagwgh sto cdr_bucket_entries
						current2 = &(pointer->bucket_entries[i].pcdr->cdrbucket_entries[cdrbucket_pos]);					
						current2->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
						if(current2->cdr_uniq_id==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current2->cdr_uniq_id, cdr->cdr_uniq_id);
						//puts(current2->cdr_uniq_id);

						current2->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
						if(current2->originator_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current2->originator_number, cdr->originator_number);
						//puts(current2->originator_number);

						current2->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
						if(current2->destination_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current2->destination_number, cdr->destination_number);		
						//puts(current2->destination_number);			

						current2->date = malloc(strlen(cdr->date)*sizeof(char));
						if(current2->date==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current2->date, cdr->date);
						//puts(current2->date);

						current2->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
						if(current2->init_time==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current2->init_time, cdr->init_time);
						//puts(current2->init_time);

						current2->duration = cdr->duration;
						//printf("%d ",current2->duration);

						current2->type = cdr->type;
						//printf("%c ",current2->type);

						current2->tarrif = cdr->tarrif;
						//printf("%c ",current2->tarrif);

						current2->fault_condition = cdr->fault_condition;
						//printf("%d \n",current2->fault_condition);

					}else{						//an den uparxei xwros sto cdr_bucket
						struct cdr_bucket* pcdr2;		//dhmiourgw neo kai eisagw to stoixeio
						pcdr2 = malloc(sizeof(struct cdr_bucket));
						if(pcdr2==NULL){
							perror("IError: cannot allocate cdr_bucket\n");
							return -3;
						}
						pcdr2->cdrbucket_entries = NULL;
						pcdr2->next_cdr_bucket = NULL;
						pcdr2->count = 0;

						pointer->bucket_entries[i].pcdr->next_cdr_bucket = pcdr2;	//katallhlh ana8esh deiktwn
						pointer->bucket_entries[i].pcdr = pcdr2;
						pointer->bucket_entries[i].pcdr->count++;
						cdrbucket_pos = (pointer->bucket_entries[i].pcdr->count) - 1;	//h 8esh pou tha mpei

						pointer->bucket_entries[i].pcdr->cdrbucket_entries=malloc(cdrbucket_capacity*sizeof(struct cdr_entry));										//dhmiourgia pinaka cdrs
						if(pointer->bucket_entries[i].pcdr->cdrbucket_entries == NULL){
							perror("IError: cannot allocate cdrbucket_entries table\n");
							return -4;
						}						

						struct cdr_entry* current3;		//eisagwgh sto cdr_bucket_entries
						current3 = &(pointer->bucket_entries[i].pcdr->cdrbucket_entries[cdrbucket_pos]);

						current3->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
						if(current3->cdr_uniq_id==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current3->cdr_uniq_id, cdr->cdr_uniq_id);
						//puts(current3->cdr_uniq_id);

						current3->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
						if(current3->originator_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current3->originator_number, cdr->originator_number);
						//puts(current3->originator_number);

						current3->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
						if(current3->destination_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current3->destination_number, cdr->destination_number);	
						//puts(current3->destination_number);				

						current3->date = malloc(strlen(cdr->date)*sizeof(char));
						if(current3->date==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current3->date, cdr->date);
						//puts(current3->date);

						current3->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
						if(current3->init_time==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current3->init_time, cdr->init_time);
						//puts(current3->init_time);

						current3->duration = cdr->duration;
						//printf("%d ",current3->duration);

						current3->type = cdr->type;
						//printf("%c ",current3->type);

						current3->tarrif = cdr->tarrif;
						//printf("%c ",current3->tarrif);

						current3->fault_condition = cdr->fault_condition;
						//printf("%d \n",current3->fault_condition);

					}
					flag=1;		//h eisagwgh egine
					break;
				}	
			}
			if(flag==1){		
				break;		//h eisagwgh egine bgainw apo to loop
			}else{
				pointer = pointer->next_bucket;	//h eisagwgh den egine-psaxnw sto epomeno bucket
			}
		}
	}	
	if(flag==0){							//an den uparxei 3ana sta buckets(flag=0)

		ht1[pos].current_bucket->count++;

		if( ht1[pos].current_bucket->count <= bucket_capacity){		//an uparxei xwros sto trexon bucket

										//dhmiourgia pinaka bucket_entries
			if(ht1[pos].current_bucket->count==1){			//1h eisagwgh -malloc
				ht1[pos].current_bucket->bucket_entries = malloc(bucket_capacity*sizeof(struct bucket_entry));
				if(ht1[pos].current_bucket->bucket_entries == NULL){
					perror("IError: cannot allocate bucket_entries table\n");
					return -2;
				}
			}

			bucket_pos = (ht1[pos].current_bucket->count) -1;		//h thesh pou tha mpei

			ht1[pos].current_bucket->bucket_entries[ bucket_pos ].callnumber = malloc(14*sizeof(char));
			strcpy(ht1[pos].current_bucket->bucket_entries[ bucket_pos ].callnumber, cdr->originator_number);//eisagwgh sto bucket
			//puts(ht1[pos].current_bucket->bucket_entries[ bucket_pos ].callnumber);			

			struct cdr_bucket* cdr1;				//dhmiourgia cdr_bucket gia auto to stoixeio tou bucket
			cdr1 = malloc(sizeof(struct cdr_bucket));
			if(cdr1 == NULL){
				perror("IError: cannot allocate cdr_bucket\n");
				return -3;
			}
			cdr1->cdrbucket_entries = NULL;
			cdr1->next_cdr_bucket = NULL;
			cdr1->count = 0;

			ht1[pos].current_bucket->bucket_entries[ bucket_pos ].pcdr = cdr1;	//katallhlh ana8esh deiktwn
			ht1[pos].current_bucket->bucket_entries[ bucket_pos ].first = cdr1;
			ht1[pos].current_bucket->bucket_entries[ bucket_pos ].pcdr->count++;
			
			if(ht1[pos].current_bucket->bucket_entries[ bucket_pos ].pcdr->count ==1){	//an einai keno
				ht1[pos].current_bucket->bucket_entries[ bucket_pos ].pcdr->cdrbucket_entries = malloc(cdrbucket_capacity*sizeof(struct cdr_entry));					//dhmiourgia pinaka cdrs cdr_bucket_entries
				if(ht1[pos].current_bucket->bucket_entries[ bucket_pos ].pcdr->cdrbucket_entries == NULL){
					perror("IError: cannot allocate cdrbucket_entries table\n");
					return -4;
				}
			}

			cdrbucket_pos = (ht1[pos].current_bucket->bucket_entries[bucket_pos].pcdr->count) - 1; //h thesh pou tha mpei
			//printf("cdrbucket_pos=%d\n",cdrbucket_pos);
			
			struct cdr_entry* current;				//eisagwgh stoixeiou sto cdr_bucket_entries
			current = &(ht1[pos].current_bucket->bucket_entries[ bucket_pos ].pcdr->cdrbucket_entries[cdrbucket_pos]); 

			current->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
			if(current->cdr_uniq_id==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current->cdr_uniq_id, cdr->cdr_uniq_id);
			//puts(current->cdr_uniq_id);

			current->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
			if(current->originator_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current->originator_number, cdr->originator_number);
			//puts(current->originator_number);

			current->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
			if(current->destination_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current->destination_number, cdr->destination_number);					
			//puts(current->destination_number);

			current->date = malloc(strlen(cdr->date)*sizeof(char));
			if(current->date==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current->date, cdr->date);
			//puts(current->date);

			current->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
			if(current->init_time==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current->init_time, cdr->init_time);
			//puts(current->init_time);

			current->duration = cdr->duration;
			//printf("%d ",current->duration);

			current->type = cdr->type;
			//printf("%c ",current->type);

			current->tarrif = cdr->tarrif;
			//printf("%c ",current->tarrif);

			current->fault_condition = cdr->fault_condition;
			//printf("%d \n",current->fault_condition);

		}else{					//den uparxei xwros sto bucket 
			struct bucket* pb;		//ftiaxnw neo kai kanw thn eisagwgh
			pb = malloc(sizeof(struct bucket));
			if(pb==NULL){
				perror("IError: cannot allocate bucket\n");
				return -1;
			}
			pb->bucket_entries = NULL;
			pb->next_bucket = NULL;
			pb->count = 0;
		
			ht1[pos].current_bucket->next_bucket = pb;
			ht1[pos].current_bucket = pb;

			ht1[pos].current_bucket->count++;
			int bpos = (ht1[pos].current_bucket->count)-1;	//h thesh pou tha mpei
			ht1[pos].current_bucket->bucket_entries = malloc(bucket_capacity*sizeof(struct bucket_entry));//dhmiourgw pinaka bucket_entries
			if(ht1[pos].current_bucket->bucket_entries == NULL){
				perror("IError: cannot allocate bucket_entries table\n");
				return -2;
			}
			ht1[pos].current_bucket->bucket_entries[bpos].callnumber = malloc(14*sizeof(char));
			strcpy(ht1[pos].current_bucket->bucket_entries[ bpos ].callnumber, cdr->originator_number);//eisagwgh sto bucket
			//puts(ht1[pos].current_bucket->bucket_entries[ bpos ].callnumber);

			struct cdr_bucket* cdr1;
			cdr1 = malloc(sizeof(struct cdr_bucket));	//dhmiourgia cdr_bucket gia auto to stoixeio tou bucket
			if(cdr1==NULL){
				perror("IError: cannot allocate cdr_bucket\n");
				return -3;
			}
			cdr1->cdrbucket_entries = NULL;
			cdr1->next_cdr_bucket = NULL;
			cdr1->count = 0;

			ht1[pos].current_bucket->bucket_entries[ bpos ].pcdr = cdr1;	//ane8esh deiktwn
			ht1[pos].current_bucket->bucket_entries[ bpos ].pcdr->count++;

			int cdr_bpos = (ht1[pos].current_bucket->bucket_entries[ bpos ].pcdr->count)-1;//h 8esh pou tha mpei

			ht1[pos].current_bucket->bucket_entries[bpos].pcdr->cdrbucket_entries = malloc(cdrbucket_capacity*sizeof(struct cdr_entry));								//dhmiourgia pinaka cdrs cdrbucket_entries
			if(ht1[pos].current_bucket->bucket_entries[bpos].pcdr->cdrbucket_entries == NULL){
				perror("IError: cannot allocate cdrbucket_entries table\n");
				return -4;
			}

			struct cdr_entry* current1;			//eisagwgh sto cdrbucket_entries
			current1 = &(ht1[pos].current_bucket->bucket_entries[bpos].pcdr->cdrbucket_entries[cdr_bpos]);
			
			current1->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
			if(current1->cdr_uniq_id==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current1->cdr_uniq_id, cdr->cdr_uniq_id);
			//puts(current1->cdr_uniq_id);

			current1->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
			if(current1->originator_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current1->originator_number, cdr->originator_number);
			//puts(current1->originator_number);

			current1->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
			if(current1->destination_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current1->destination_number, cdr->destination_number);					
			//puts(current1->destination_number);

			current1->date = malloc(strlen(cdr->date)*sizeof(char));
			if(current1->date==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current1->date, cdr->date);
			//puts(current1->date);

			current1->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
			if(current1->init_time==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current1->init_time, cdr->init_time);
			//puts(current1->init_time);

			current1->duration = cdr->duration;
			//printf("%d ",current1->duration);

			current1->type = cdr->type;
			//printf("%c ",current1->type);

			current1->tarrif = cdr->tarrif;
			//printf("%c ",current1->tarrif);

			current1->fault_condition = cdr->fault_condition;		
			//printf("%d \n",current1->fault_condition);	

		}
	}
	printf("OK\n");		//eisagwgh sto 1o hashtable oloklhrw8hke
//	printf("Insert to HashTable1 complete.....\n");


//------insert to HashTable2	(idia me thn insert gia to hashtable1 mono pou kanoume hash me to cdr->destination_number)
	printf("\ninsert >>>>\n");
	int bucket_pos2, cdrbucket_pos2;
	unsigned long pos2 =(unsigned long) hashfunction(cdr->destination_number)%h2;//h thesh tou hashtable2 pou tha ginei insert to stoixeio
//	printf("pos2 = %lu\t",pos2);

	struct bucket* pointer2 = NULL;
	pointer2 = ht2[pos2].first_bucket;
	if(pointer2==NULL){
		perror("IError: pointer to first bucket NULL\n");
		return -10;
	}

	int flag2=0;
	if(pointer2->count!=0){							//an den einai keno to bucket
		while( pointer2!=NULL){						//e3etazw ola ta buckets
			int i2;
			for(i2=0; i2 < pointer2->count; i2++){			//oles tis eggrafes tou bucket
				if(strcmp(pointer2->bucket_entries[i2].callnumber, cdr->destination_number) == 0){	//an uparxei
						
					pointer2->bucket_entries[i2].pcdr->count++;			
					if(pointer2->bucket_entries[i2].pcdr->count <= cdrbucket_capacity){	//an uparxei xwros sto cdr_bucket
						cdrbucket_pos2 = (pointer2->bucket_entries[i2].pcdr->count) - 1;	//h thesh pou tha mpei

						struct cdr_entry* current4;		//eisagwgh sto cdr_bucket_entries
						current4 = &(pointer2->bucket_entries[i2].pcdr->cdrbucket_entries[cdrbucket_pos2]);					
						current4->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
						if(current4->cdr_uniq_id==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current4->cdr_uniq_id, cdr->cdr_uniq_id);
						//puts(current4->cdr_uniq_id);

						current4->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
						if(current4->originator_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current4->originator_number, cdr->originator_number);
						//puts(current4->originator_number);

						current4->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
						if(current4->destination_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current4->destination_number, cdr->destination_number);		
						//puts(current4->destination_number);			

						current4->date = malloc(strlen(cdr->date)*sizeof(char));
						if(current4->date==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current4->date, cdr->date);
						//puts(current4->date);

						current4->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
						if(current4->init_time==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current4->init_time, cdr->init_time);
						//puts(current4->init_time);

						current4->duration = cdr->duration;
						//printf("%d ",current4->duration);

						current4->type = cdr->type;
						//printf("%c ",current4->type);

						current4->tarrif = cdr->tarrif;
						//printf("%c ",current4->tarrif);

						current4->fault_condition = cdr->fault_condition;
						//printf("%d \n",current4->fault_condition);

					}else{						//an den uparxei xwros sto cdr_bucket
						struct cdr_bucket* pcdr3;		//dhmiourgw neo kai eisagw to stoixeio
						pcdr3 = malloc(sizeof(struct cdr_bucket));
						if(pcdr3==NULL){
							perror("IError: cannot allocate cdr_bucket\n");
							return -3;
						}
						pcdr3->cdrbucket_entries = NULL;
						pcdr3->next_cdr_bucket = NULL;
						pcdr3->count = 0;

						pointer2->bucket_entries[i2].pcdr->next_cdr_bucket = pcdr3;//katallhlh anathesh deiktwn
						pointer2->bucket_entries[i2].pcdr = pcdr3;
						pointer2->bucket_entries[i2].pcdr->count++;
						cdrbucket_pos2 = (pointer2->bucket_entries[i2].pcdr->count) - 1;	//h thesh pou tha mpei

						pointer2->bucket_entries[i2].pcdr->cdrbucket_entries=malloc(cdrbucket_capacity*sizeof(struct cdr_entry));									//dhmiourgia pinaka cdrs cdrbucket_entries
						if(pointer2->bucket_entries[i2].pcdr->cdrbucket_entries == NULL){
							perror("IError: cannot allocate cdrbucket_entries table\n");
							return -4;
						}
						struct cdr_entry* current5;	//eisagwgh sto cdrbucket_entries
						current5 = &(pointer2->bucket_entries[i2].pcdr->cdrbucket_entries[cdrbucket_pos2]);

						current5->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
						if(current5->cdr_uniq_id==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current5->cdr_uniq_id, cdr->cdr_uniq_id);
						//puts(current3->cdr_uniq_id);

						current5->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
						if(current5->originator_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current5->originator_number, cdr->originator_number);
						//puts(current5->originator_number);

						current5->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
						if(current5->destination_number==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current5->destination_number, cdr->destination_number);	
						//puts(current5->destination_number);				

						current5->date = malloc(strlen(cdr->date)*sizeof(char));
						if(current5->date==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current5->date, cdr->date);
						//puts(current5->date);

						current5->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
						if(current5->init_time==NULL){
							perror("IError: cannot allocate cdr element\n");
							return -5;
						}
						strcpy(current5->init_time, cdr->init_time);
						//puts(current5->init_time);

						current5->duration = cdr->duration;
						//printf("%d ",current5->duration);

						current5->type = cdr->type;
						//printf("%c ",current5->type);

						current5->tarrif = cdr->tarrif;
						//printf("%c ",current5->tarrif);

						current5->fault_condition = cdr->fault_condition;
						//printf("%d \n",current5->fault_condition);

					}
					flag2=1; //h eisagwgh egine
					break;
				}	
			}
			if(flag2==1){
				break;		//h eisagwgh egine-bgainw apo thn epanalhpsh
			}else{
				pointer2 = pointer2->next_bucket; //h eisagwh den egine-psaxnw sto epomeno bucket
			}
		}
	}	
	if(flag2==0){							//an den uparxei 3ana sta buckets(flag=0)

		ht2[pos2].current_bucket->count++;

		if( ht2[pos2].current_bucket->count <= bucket_capacity){		//an uparxei xwros sto trexon bucket

										//dhmiourgia pinaka bucket_entries
			if(ht2[pos2].current_bucket->count==1){			//1h eisagwgh -malloc
				ht2[pos2].current_bucket->bucket_entries = malloc(bucket_capacity*sizeof(struct bucket_entry));
				if(ht2[pos2].current_bucket->bucket_entries == NULL){
					perror("IError: cannot allocate bucket_entries table\n");
					return -2;
				}
			}

			bucket_pos2 = (ht2[pos2].current_bucket->count) -1;	//h 8esh pou tha mpei stobucket	

			ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].callnumber = malloc(14*sizeof(char));
			strcpy(ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].callnumber, cdr->destination_number);//eisagwgh sto bucket
			//puts(ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].callnumber);			

			struct cdr_bucket* cdr2;		//dhmiourgia cdr_bucket gia auto to stoixeio toi bucket
			cdr2 = malloc(sizeof(struct cdr_bucket));
			if(cdr2 == NULL){
				perror("IError: cannot allocate cdr_bucket\n");
				return -3;
			}
			cdr2->cdrbucket_entries = NULL;
			cdr2->next_cdr_bucket = NULL;
			cdr2->count = 0;

			ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].pcdr = cdr2;	//katallhlh anathesh deiktwn
			ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].first = cdr2;
			ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].pcdr->count++;
			
			if(ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].pcdr->count ==1){	//an einai keno
				ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].pcdr->cdrbucket_entries = malloc(cdrbucket_capacity*sizeof(struct cdr_entry));				//dhmiourgia pinaka cdrs cdrbucket_entries
				if(ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].pcdr->cdrbucket_entries == NULL){
					perror("IError: cannot allocate cdrbucket_entries table\n");
					return -4;
				}
			}

			cdrbucket_pos2 = (ht2[pos2].current_bucket->bucket_entries[bucket_pos2].pcdr->count) - 1; //h thsh pou tha mpei
			//printf("cdrbucket_pos2=%d\n",cdrbucket_pos2);
			
			struct cdr_entry* current6;				//eisagwgh sto cdrbucket_entries
			current6 = &(ht2[pos2].current_bucket->bucket_entries[ bucket_pos2 ].pcdr->cdrbucket_entries[cdrbucket_pos2]); 

			current6->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
			if(current6->cdr_uniq_id==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}	
			strcpy(current6->cdr_uniq_id, cdr->cdr_uniq_id);
			//puts(current6->cdr_uniq_id);

			current6->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
			if(current6->originator_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current6->originator_number, cdr->originator_number);
			//puts(current6->originator_number);

			current6->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
			if(current6->destination_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current6->destination_number, cdr->destination_number);					
			//puts(current6->destination_number);

			current6->date = malloc(strlen(cdr->date)*sizeof(char));
			if(current6->date==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current6->date, cdr->date);
			//puts(current6->date);

			current6->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
			if(current6->init_time==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current6->init_time, cdr->init_time);
			//puts(current6->init_time);

			current6->duration = cdr->duration;
			//printf("%d ",current6->duration);

			current6->type = cdr->type;
			//printf("%c ",current6->type);

			current6->tarrif = cdr->tarrif;
			//printf("%c ",current6->tarrif);

			current6->fault_condition = cdr->fault_condition;
			//printf("%d \n",current6->fault_condition);

		}else{					//den uparxei xwros sto bucket 
			struct bucket* pb2;		//ftiaxnw neo kai kanw thn eisagwgh
			pb2 = malloc(sizeof(struct bucket));
			if(pb2==NULL){
				perror("IError: cannot allocate bucket\n");
				return -1;
			}
			pb2->bucket_entries = NULL;
			pb2->next_bucket = NULL;
			pb2->count = 0;
		
			ht2[pos2].current_bucket->next_bucket = pb2;
			ht2[pos2].current_bucket = pb2;

			ht2[pos2].current_bucket->count++;
			int bpos2 = (ht2[pos2].current_bucket->count)-1;		//h 8esh pou tha mpei
			ht2[pos2].current_bucket->bucket_entries = malloc(bucket_capacity*sizeof(struct bucket_entry));//dhmiourgia pinaka bucket_entries
			if(ht2[pos2].current_bucket->bucket_entries==NULL){
				perror("IError: cannot allocate bucket_entries table\n");
				return -2;
			}
			ht2[pos2].current_bucket->bucket_entries[bpos2].callnumber = malloc(14*sizeof(char));
			strcpy(ht2[pos2].current_bucket->bucket_entries[ bpos2 ].callnumber, cdr->destination_number);//eisagwgh sto bucket
			//puts(ht2[pos2].current_bucket->bucket_entries[ bpos2 ].callnumber);

			struct cdr_bucket* cdr2;				//dhmiourgia cdr_bucket gia auto to stoixeio tou bucket
			cdr2 = malloc(sizeof(struct cdr_bucket));
			if(cdr2==NULL){
				perror("IError: cannot allocate cdr_bucket\n");
				return -3;
			}
			cdr2->cdrbucket_entries = NULL;
			cdr2->next_cdr_bucket = NULL;
			cdr2->count = 0;

			ht2[pos2].current_bucket->bucket_entries[ bpos2 ].pcdr = cdr2;
			ht2[pos2].current_bucket->bucket_entries[ bpos2 ].pcdr->count++;

			int cdr_bpos2 = (ht2[pos2].current_bucket->bucket_entries[ bpos2 ].pcdr->count)-1;	//h 8esh pou tha mpei

			ht2[pos2].current_bucket->bucket_entries[bpos2].pcdr->cdrbucket_entries = malloc(cdrbucket_capacity*sizeof(struct cdr_entry));					//dhmiourgia pinaka cdrs cdrbucket_entries
			if(ht2[pos2].current_bucket->bucket_entries[bpos2].pcdr->cdrbucket_entries == NULL){
				perror("IError: cannot allocate cdrbucket_entries table\n");
				return -4;
			}

			struct cdr_entry* current7;		//eisagwgh sto cdrbucket_entries
			current7 = &(ht2[pos2].current_bucket->bucket_entries[bpos2].pcdr->cdrbucket_entries[cdr_bpos2]);
			
			current7->cdr_uniq_id = malloc(strlen(cdr->cdr_uniq_id)*sizeof(char));
			if(current7->cdr_uniq_id==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current7->cdr_uniq_id, cdr->cdr_uniq_id);
			//puts(current7->cdr_uniq_id);

			current7->originator_number = malloc(strlen(cdr->originator_number)*sizeof(char));
			if(current7->originator_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current7->originator_number, cdr->originator_number);
			//puts(current7->originator_number);

			current7->destination_number = malloc(strlen(cdr->destination_number)*sizeof(char));
			if(current7->destination_number==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current7->destination_number, cdr->destination_number);					
			//puts(current7->destination_number);

			current7->date = malloc(strlen(cdr->date)*sizeof(char));
			if(current7->date==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current7->date, cdr->date);
			//puts(current7->date);

			current7->init_time = malloc(strlen(cdr->init_time)*sizeof(char));
			if(current7->init_time==NULL){
				perror("IError: cannot allocate cdr element\n");
				return -5;
			}
			strcpy(current7->init_time, cdr->init_time);
			//puts(current7->init_time);

			current7->duration = cdr->duration;
			//printf("%d ",current7->duration);

			current7->type = cdr->type;
			//printf("%c ",current7->type);

			current7->tarrif = cdr->tarrif;
			//printf("%c ",current7->tarrif);

			current7->fault_condition = cdr->fault_condition;		
			//printf("%d \n",current7->fault_condition);	

		}
	}
	printf("OK\n");		//eisagwgh sto 2o hashtable oloklhrwthike
//	printf("Insert to HashTable2 complete.....\n\n");

	free(cdr->cdr_uniq_id);
	free(cdr->originator_number);
	free(cdr->destination_number);
	free(cdr->date);
	free(cdr->init_time);

	return 0;
}

int PrintHashTable(struct ht_entry *ht, int h){

	int i,j,k;
	struct bucket *pointer1;
	struct cdr_bucket *pointer2;
	printf("CDR_UNIQ_ID-ORIGINATOR_NUMBER-DESTINATION_NUMBER - DATE - INIT_TIME-DURATION-TYPE-TARRIF-FAULT_CONDITION\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
	for(i=0; i<h; i++){				//gia ola ta stoixeia tou hashtable
		pointer1 = ht[i].first_bucket;		//3ekinw apo to 1o bucket
		if(pointer1!=NULL){
			while( pointer1!=NULL ){
				for(j=0; j < pointer1->count; j++){			//gia ola ta stoixeia tou pinaka bucket_entries
					pointer2 = pointer1->bucket_entries[j].first;	//3ekinw apo to 1o cdr_bucket
					while(pointer2!=NULL){
						for(k=0; k<pointer2->count; k++){   //gia ola ta stoixeia tou cdrbucket_entries		
							printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
							printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
							printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
							printf("%s\t",pointer2->cdrbucket_entries[k].date);
							printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
							printf("%d\t",pointer2->cdrbucket_entries[k].duration);
							printf("%c\t",pointer2->cdrbucket_entries[k].type);
							printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
							printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
						}
						pointer2 = pointer2->next_cdr_bucket; //epomeno cdr_bucket
					}			
				}
				pointer1 = pointer1->next_bucket;	//epomeno bucket
			}
		}
	}
	printf("Print successful\n\n");
	return 0;
}

int Delete(struct ht_entry *ht1, int h1, struct todel* todel1){

	unsigned long ht_pos = (unsigned long) hashfunction(todel1->caller)%h1; //h 8esh tou hashtable tou stoixeiou pros diagrafh
//	printf("pos=%lu\n",ht_pos);
	int j,k,l,x,flag=0;
	struct bucket *pointer1,*head1,*prev1;
	struct cdr_bucket *pointer2,*head2,*prev;

	head1 = ht1[ht_pos].first_bucket;		//3ekinw apo to 1o bucket
	pointer1 = head1;
	while(pointer1!=NULL){
		for(j=0; j<(pointer1->count); j++){	//gia ola ta stoixeia tou pinaka bucket_entries
			if(strcmp(pointer1->bucket_entries[j].callnumber, todel1->caller)==0){	//an brw ton caller
				head2 = pointer1->bucket_entries[j].first;	//3ekinw apo to 1o cdr_bucket
				pointer2 = head2;
				while(pointer2!=NULL){
					for(k=0; k<pointer2->count; k++){	//gia ola ta stoixeia tou cdr_bucket
						if(strcmp(pointer2->cdrbucket_entries[k].cdr_uniq_id, todel1->cdr_uniq_id)==0){
					//an brw to cdr pou thelw to diagrafw
							free(pointer2->cdrbucket_entries[k].cdr_uniq_id);
							free(pointer2->cdrbucket_entries[k].originator_number);
							free(pointer2->cdrbucket_entries[k].destination_number);	
							free(pointer2->cdrbucket_entries[k].date);
							free(pointer2->cdrbucket_entries[k].init_time);
							if(pointer2->count!=1){	//an den einai to monadiko stoixeio sto cdrbucket_entries
								pointer2->count--;	//meiwnw ton arithmo twn stoixeiwn kata 1
								for(l=k; l<pointer2->count;l++){//kanw olis8hsh ta stoixeia 1 8esh pisw ston pinaka,apo th 8esh tou stoixeiou pou diagrafw kai meta wste oi pointer2->count prwtes theseis na einai gemates
									if(l==k){
										pointer2->cdrbucket_entries[l].cdr_uniq_id=malloc((strlen(pointer2->cdrbucket_entries[l+1].cdr_uniq_id)+1)*sizeof(char));
										pointer2->cdrbucket_entries[l].originator_number=malloc((strlen(pointer2->cdrbucket_entries[l+1].originator_number)+1)*sizeof(char));
										pointer2->cdrbucket_entries[l].destination_number=malloc((strlen(pointer2->cdrbucket_entries[l+1].destination_number)+1)*sizeof(char));
										pointer2->cdrbucket_entries[l].date=malloc((strlen(pointer2->cdrbucket_entries[l+1].date)+1)*sizeof(char));
										pointer2->cdrbucket_entries[l].init_time=malloc((strlen(pointer2->cdrbucket_entries[l+1].init_time)+1)*sizeof(char));
									}
									strcpy(pointer2->cdrbucket_entries[l].cdr_uniq_id, pointer2->cdrbucket_entries[l+1].cdr_uniq_id);
									strcpy(pointer2->cdrbucket_entries[l].originator_number, pointer2->cdrbucket_entries[l+1].originator_number);
									strcpy(pointer2->cdrbucket_entries[l].destination_number, pointer2->cdrbucket_entries[l+1].destination_number);
									strcpy(pointer2->cdrbucket_entries[l].date, pointer2->cdrbucket_entries[l+1].date);
									strcpy(pointer2->cdrbucket_entries[l].init_time, pointer2->cdrbucket_entries[l+1].init_time);
									pointer2->cdrbucket_entries[l].duration=pointer2->cdrbucket_entries[l+1].duration;
									pointer2->cdrbucket_entries[l].type=pointer2->cdrbucket_entries[l+1].type;
									pointer2->cdrbucket_entries[l].tarrif=pointer2->cdrbucket_entries[l+1].tarrif;
									pointer2->cdrbucket_entries[l].fault_condition=pointer2->cdrbucket_entries[l+1].fault_condition;
								}
								flag=1;break;		//h diagrafh egine bgainw apo thn epanalhpsh
							}else if (pointer2->count == 1){//an einai to monadiko stoixeio sto cdrbucket_entries
								pointer2->count--;	//meiwnw ton ari8mo twn stoixeiwn kata 1
								if(pointer2==head2){	//an auto to cdr_bucket einai h kefalh
									if(head2->next_cdr_bucket == NULL){//den uparxei allo cdr_bucket
										free(head2->cdrbucket_entries);
										head2=NULL;
										pointer1->bucket_entries[j].pcdr=NULL;
									}else{		//alliws h kefalh deixnei sto epomeno cdr_bucket
										pointer2=head2->next_cdr_bucket;
										head2->next_cdr_bucket=NULL;
										free(head2->cdrbucket_entries);
										head2=pointer2;
									}
								}else{			//an auto to cdr_bucket den einai h kefalh
									prev=head2;	//briskw ton prohgoumeno kai diagrafw auto to cdr_bucket apo th lista
									while(prev->next_cdr_bucket!=NULL && prev->next_cdr_bucket!=pointer2){
										prev=prev->next_cdr_bucket;
									}
									free(pointer2->cdrbucket_entries);
									prev->next_cdr_bucket=prev->next_cdr_bucket->next_cdr_bucket;
									if(pointer2==pointer1->bucket_entries[j].pcdr){
										pointer1->bucket_entries[j].pcdr=prev;	
									}
									pointer2->next_cdr_bucket=NULL;
									free(pointer2);
								}
								flag=1;break;	
							}	
						}
					}
					if(flag==1){		
						break;	//h diagrafh egine bgainw apo thn epanalhpsh
					}else{
						pointer2=pointer2->next_cdr_bucket;	//alliws sunexizw na psaxnw sto epomeno cdr_bucket
					}
				}
				if(pointer1->count!=1){		//an to bucket  den exei mono ena stoixeio
					if(head2==NULL){	//kai to sugkekrimeno stoixeio tou bucket den exei cdr_bucket
						free(pointer1->bucket_entries[j].callnumber);
						pointer1->count--;	//meiwnw ton arithmo twn stoixeiwn tou bucket kata ena
						for(x=j; x < (pointer1->count); x++){//kanw olis8hsh ta stoixeia 1 8esh pisw ston pinaka,apo th 8esh tou stoixeiou pou diagrafw kai meta wste oi pointer1->count prwtes theseis tou bucket na einai gemates
							if(x==j){
								pointer1->bucket_entries[x].callnumber=malloc((strlen(pointer1->bucket_entries[x+1].callnumber)+1)*sizeof(char));
							}
							strcpy(pointer1->bucket_entries[x].callnumber,pointer1->bucket_entries[x+1].callnumber);
//							printf("%s %s\n",pointer1->bucket_entries[x].callnumber,pointer1->bucket_entries[x+1].callnumber);
							pointer1->bucket_entries[x].pcdr=pointer1->bucket_entries[x+1].pcdr;
							pointer1->bucket_entries[x].first=pointer1->bucket_entries[x+1].first;
						}
					}
					flag=1;break;	//h diagrafh egine bgainw apo thn epanalhpsh					
				}else if(pointer1->count==1){	//an to bucket exei mono ena stoixeio
					if(head2==NULL){	//kai to sugkekrimeno stoixeio den exei cdr_buckets
						pointer1->count--;	//meiwnw ton ari8mo twn stoixeiwn tou bucket kata 1
						if(pointer1==head1){	//an auto to bucket einai h kefalh ths listas
							if(head1->next_bucket==NULL){	//an den exei epomeno
								free(head1->bucket_entries[j].callnumber);
								head1->bucket_entries[j].pcdr=NULL;
								head1->bucket_entries[j].first=NULL;
								free(head1->bucket_entries);
								head1->count=0;
							}else{		//an exei epomeno
								pointer1=head1->next_bucket;
								head1->next_bucket=NULL;
								free(head1->bucket_entries[j].callnumber);
								free(head1->bucket_entries);
								head1=pointer1;
							}
						}else{		//alliws an auto to bucket den einai h kefalh ths listas
							prev1=head1;	//briskw ton prohgoumeno tou kai diagrafw auto to bucket apo th lista
							while(prev1->next_bucket!=NULL && prev1->next_bucket!=pointer1){
								prev1=prev1->next_bucket;
							}
							free(pointer1->bucket_entries[j].callnumber);
							free(pointer1->bucket_entries);
							prev1->next_bucket=prev1->next_bucket->next_bucket;
							if(pointer1==ht1[ht_pos].current_bucket){
								ht1[ht_pos].current_bucket=prev1;
							}
							pointer1->next_bucket=NULL;
							free(pointer1);
						}
						flag=1;break; //h diagrafh egine  bgainw apo thn epanalhpsh
					}
				}				
			}	
		}
		if(flag==1){
			break;	//h diagrafh oloklhrwthike bgainw apo thn epanalhpsh
		}else{			
			pointer1 = pointer1->next_bucket;	//alliws sunexizw thn anazhthsh tou stoixeiou sto epomeno bucket
		}
	}		
	printf("\ndelete >>>>\n");
	printf("\tDeleted %s\n\n",todel1->cdr_uniq_id);
	free(todel1->cdr_uniq_id);
	free(todel1->caller);
	return 0;
}


int Find(struct ht_entry *ht1, int h1, struct tofind* tofind1){

	unsigned long ht_pos = (unsigned long) hashfunction(tofind1->caller)%h1; //briskw th 8esh tou caller ston hashtable1
//	printf("pos=%lu\n",ht_pos);

	int j,k,flag=0, noresults=1;
	struct bucket *pointer1;
	struct cdr_bucket *pointer2;
	
	printf("\nfind >>>>\n");
	pointer1 = ht1[ht_pos].first_bucket;		//3ekinw apo to 1o bucket
	while(pointer1!=NULL){
		for(j=0; j<(pointer1->count); j++){	//gia ola ta stoixeia tou pinaka bucket_entries tou bucket
			if(strcmp(pointer1->bucket_entries[j].callnumber, tofind1->caller)==0){	//an brw ton caller					
			printf("CDR_UNIQ_ID-ORIGINATOR_NUMBER-DESTINATION_NUMBER - DATE - INIT_TIME-DURATION-TYPE-TARRIF-FAULT_CONDITION\n");
			printf("--------------------------------------------------------------------------------------------------------\n");
				pointer2 = pointer1->bucket_entries[j].first; //3ekinw apo to 1o cdr_bucket
				while(pointer2!=NULL){
					for(k=0; k<pointer2->count; k++){//gia ola ta stoixeia tou cdrbucket_entries tou cdr_bucket
						if(tofind1->time1==NULL && tofind1->time2==NULL && tofind1->year1==NULL && tofind1->year2==NULL){					//an den uparxoun xronikoi periorismoi
							printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
							printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
							printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
							printf("%s\t",pointer2->cdrbucket_entries[k].date);
							printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
							printf("%d\t",pointer2->cdrbucket_entries[k].duration);
							printf("%c\t",pointer2->cdrbucket_entries[k].type);
							printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
							printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
							noresults=0;
	
						}else if(tofind1->time1!=NULL && tofind1->time2!=NULL && tofind1->year1==NULL && tofind1->year2==NULL){					//uparxoun xronikoi periorismoi wras

							struct time12 *t1,*t2,*p;
							t1=malloc(sizeof(struct time12));
							t2=malloc(sizeof(struct time12));
							p=malloc(sizeof(struct time12));

							Separate1(t1, tofind1->time1);//xwrizw time1 se wres kai lepta						
							Separate1(t2, tofind1->time2);//xwrizw time2 se wres kai lepta
							Separate1(p, pointer2->cdrbucket_entries[k].init_time);//xwrizw thn time tou stoixeiou se wres kai lepta
								
							if( ((p->hours1 > t1->hours1) && (p->hours1 < t2->hours1)) 
				|| ((p->hours1 == t1->hours1) && (p->hours1 == t2->hours1) && (p->mins1>=t1->mins1) && (p->mins1<=t2->mins1)) 
				|| ((p->hours1==t1->hours1)&&(p->hours1<t2->hours1) && (p->mins1>=t1->mins1)) 
					|| ((p->hours1==t2->hours1)&&(p->hours1>t1->hours1)&&(p->mins1<=t2->mins1)) ){
							//brisketai mesa sto euros pou orizei to time1 kai to time2
								printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
								printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
								printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
								printf("%s\t",pointer2->cdrbucket_entries[k].date);
								printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
								printf("%d\t",pointer2->cdrbucket_entries[k].duration);
								printf("%c\t",pointer2->cdrbucket_entries[k].type);
								printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
								printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
								noresults=0;
							}
							free(t1);free(t2);free(p);
		
						}else{
						//uparxoun xronikoi periorismoi wras kai hmeromhnias

							struct timedate12 *tm1,*tm2,*x;
							tm1=malloc(sizeof(struct timedate12));
							tm2=malloc(sizeof(struct timedate12));
							x=malloc(sizeof(struct timedate12));

							Separate2(tm1,tofind1->time1, tofind1->year1);//xwrizw se wres, lepta, mera ,mhnas, etos
							Separate2(tm2,tofind1->time2, tofind1->year2);//xwrizw se wres, lepta, mera ,mhnas, etos
							Separate2(x, pointer2->cdrbucket_entries[k].init_time, pointer2->cdrbucket_entries[k].date);		//xwrizw se wres, lepta, mera ,mhnas, etos

							if( ((x->year1>tm1->year1)&&(x->year1<tm2->year1)) ||
					((x->year1==tm1->year1)&&(x->year1<tm2->year1)&&(x->month1>tm1->month1)) ||
					((x->year1==tm1->year1)&&(x->year1<tm2->year1)&&(x->month1==tm1->month1)&&(x->day1>tm1->day1))||
					((x->year1==tm2->year1)&&(x->year1>tm1->year1)&&(x->month1<tm2->month1)) ||
					((x->year1==tm2->year1)&&(x->year1>tm1->year1)&&(x->month1==tm2->month1)&&(x->day1<tm2->day1))||
					((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1>tm1->month1)&&(x->month1<tm2->month1))||
((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1<tm2->month1)&&(x->day1>tm1->day1))||
((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm2->month1)&&(x->month1>tm1->month1)&&(x->day1<tm2->day1))||
((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1==tm2->month1)&&(x->day1>tm1->day1)&&(x->day1<tm2->day1))){	
						//ikanopoiountai oi xronikoi periorismoi 
								printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
								printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
								printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
								printf("%s\t",pointer2->cdrbucket_entries[k].date);
								printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
								printf("%d\t",pointer2->cdrbucket_entries[k].duration);
								printf("%c\t",pointer2->cdrbucket_entries[k].type);
								printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
								printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
								noresults=0;
		
							}else if(((x->year1==tm1->year1)&&(x->year1<tm2->year1)&&(x->month1==tm1->month1)&&(x->day1==tm1->day1))||((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1<tm2->month1)&&(x->day1==tm1->day1))){
								if((x->hours1>tm1->hours1)|| ((x->hours1==tm1->hours1)&&(x->mins1>=tm1->mins1))){
						//ikanopoiountai oi xronikoi periorismoi 
									printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
									printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].date);
									printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
									printf("%d\t",pointer2->cdrbucket_entries[k].duration);
									printf("%c\t",pointer2->cdrbucket_entries[k].type);
									printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
									printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
									noresults=0;
								}
							}else if( ((x->year1==tm2->year1)&&(x->year1>tm1->year1)&&(x->month1==tm2->month1)&&(x->day1==tm2->day1))|| ((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm2->month1)&&(x->month1>tm1->month1)&&(x->day1==tm2->day1))){
								if((x->hours1<tm2->hours1)||((x->hours1==tm2->hours1)&&(x->mins1<=tm2->mins1))){
						//ikanopoiountai oi xronikoi periorismoi 
									printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
									printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].date);
									printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
									printf("%d\t",pointer2->cdrbucket_entries[k].duration);
									printf("%c\t",pointer2->cdrbucket_entries[k].type);
									printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
									printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
									noresults=0;
								}
		
							}else if( ((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1==tm2->month1)&&(x->day1==tm1->day1)&&(x->day1==tm2->day1)) ){
								if(((x->hours1 > tm1->hours1) && (x->hours1 < tm2->hours1)) 
				||((x->hours1==tm1->hours1) && (x->hours1 == tm2->hours1) && (x->mins1>=tm1->mins1) && (x->mins1<=tm2->mins1)) 
				||((x->hours1==tm1->hours1)&&(x->hours1<tm2->hours1) && (x->mins1>=tm1->mins1)) 
				||((x->hours1==tm2->hours1)&&(x->hours1>tm1->hours1)&&(x->mins1<=tm2->mins1)) ){
						//ikanopoiountai oi xronikoi periorismoi 
									printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
									printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].date);
									printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
									printf("%d\t",pointer2->cdrbucket_entries[k].duration);
									printf("%c\t",pointer2->cdrbucket_entries[k].type);
									printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
									printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
									noresults=0;

								}
							}
							free(tm1);free(tm2);free(x);						
						}							
					}
					pointer2=pointer2->next_cdr_bucket;	//epomeno cdr_bucket
					if(pointer2==NULL){
						flag=1;
						break;
					}	
				}
				if(flag==1){
					break;break;break;
				}	
			}
		}
		pointer1=pointer1->next_bucket;		//epomeno bucket
	}
	if(noresults==1)
		printf("\tNo CDRs found\n\n");

	free(tofind1->caller);
	if(tofind1->time1!=NULL)
		free(tofind1->time1);
	if(tofind1->time2!=NULL)
		free(tofind1->time2);
	if(tofind1->year1!=NULL)
		free(tofind1->year1);	
	if(tofind1->year2!=NULL)
		free(tofind1->year2);	
	return 0;
}

int Lookup(struct ht_entry *ht2, int h2, struct tofind* tolookup1){

	unsigned long ht_pos = (unsigned long) hashfunction(tolookup1->caller)%h2;//briskw th 8esh tou caller ston hashtable2
//	printf("pos=%lu\n",ht_pos);

	int j,k,flag=0,noresults=1;
	struct bucket *pointer1;
	struct cdr_bucket *pointer2;

	printf("\nlookup >>>>\n");
	pointer1 = ht2[ht_pos].first_bucket;	//3ekinw apo to 1o bucket
	while(pointer1!=NULL){
		for(j=0; j<(pointer1->count); j++){	//gia ola ta stoixeia tou pinaka bucket_entries tou bucket
			if(strcmp(pointer1->bucket_entries[j].callnumber, tolookup1->caller)==0){//an brw ton callee
			printf("CDR_UNIQ_ID-ORIGINATOR_NUMBER-DESTINATION_NUMBER - DATE - INIT_TIME-DURATION-TYPE-TARRIF-FAULT_CONDITION\n");
			printf("--------------------------------------------------------------------------------------------------------\n");
				pointer2 = pointer1->bucket_entries[j].first;//3ekinw apo to 1o cdr_bucket
				while(pointer2!=NULL){
					for(k=0; k<pointer2->count; k++){//gia ola ta stoixeia tou cdrbucket_entries tou cdr_bucket
						if(tolookup1->time1==NULL && tolookup1->time2==NULL && tolookup1->year1==NULL && tolookup1->year2==NULL){					//an den uparxoun xronikoi periorismoi
							printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
							printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
							printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
							printf("%s\t",pointer2->cdrbucket_entries[k].date);
							printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
							printf("%d\t",pointer2->cdrbucket_entries[k].duration);
							printf("%c\t",pointer2->cdrbucket_entries[k].type);
							printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
							printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
							noresults=0;
	
						}else if(tolookup1->time1!=NULL && tolookup1->time2!=NULL && tolookup1->year1==NULL && tolookup1->year2==NULL){			//uparxoun xronikoi periorismoi wras

							struct time12 *t1,*t2,*p;
							t1=malloc(sizeof(struct time12));
							t2=malloc(sizeof(struct time12));
							p=malloc(sizeof(struct time12));

							Separate1(t1,tolookup1->time1);//xwrizw time1 se wres kai lepta
							Separate1(t2,tolookup1->time2);//xwrizw time1 se wres kai lepta
							Separate1(p, pointer2->cdrbucket_entries[k].init_time);//xwrizw thn time tou stoixeiou se wres kai lepta

							if( ((p->hours1 > t1->hours1) && (p->hours1 < t2->hours1)) || ((p->hours1 == t1->hours1) && (p->hours1 == t2->hours1) && (p->mins1>=t1->mins1) && (p->mins1<=t2->mins1)) || ((p->hours1==t1->hours1)&&(p->hours1<t2->hours1) && (p->mins1>=t1->mins1)) || ((p->hours1==t2->hours1)&&(p->hours1>t1->hours1)&&(p->mins1<=t2->mins1)) ){
							//brisketai mesa sto euros pou orizei to time1 kai to time2
								printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
								printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
								printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
								printf("%s\t",pointer2->cdrbucket_entries[k].date);
								printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
								printf("%d\t",pointer2->cdrbucket_entries[k].duration);
								printf("%c\t",pointer2->cdrbucket_entries[k].type);
								printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
								printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
								noresults=0;
							}	
							free(t1);free(t2);free(p);	
						}else{
						//uparxoun xronikoi periorismoi wras kai hmeromhnias	

							struct timedate12 *tm1, *tm2, *x;
							tm1=malloc(sizeof(struct timedate12));	
							tm2=malloc(sizeof(struct timedate12));
							x=malloc(sizeof(struct timedate12));

							Separate2(tm1,tolookup1->time1, tolookup1->year1);//xwrizw se wres, lepta, mera ,mhnas, etos	
							Separate2(tm2,tolookup1->time2, tolookup1->year2);//xwrizw se wres, lepta, mera ,mhnas, etos	
							Separate2(x, pointer2->cdrbucket_entries[k].init_time, pointer2->cdrbucket_entries[k].date);		//xwrizw se wres, lepta, mera ,mhnas, etos

							if( ((x->year1>tm1->year1)&&(x->year1<tm2->year1)) ||
					((x->year1==tm1->year1)&&(x->year1<tm2->year1)&&(x->month1>tm1->month1)) ||
					((x->year1==tm1->year1)&&(x->year1<tm2->year1)&&(x->month1==tm1->month1)&&(x->day1>tm1->day1))||
					((x->year1==tm2->year1)&&(x->year1>tm1->year1)&&(x->month1<tm2->month1)) ||
					((x->year1==tm2->year1)&&(x->year1>tm1->year1)&&(x->month1==tm2->month1)&&(x->day1<tm2->day1))||
					((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1>tm1->month1)&&(x->month1<tm2->month1))||
((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1<tm2->month1)&&(x->day1>tm1->day1))||
((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm2->month1)&&(x->month1>tm1->month1)&&(x->day1<tm2->day1))||
((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1==tm2->month1)&&(x->day1>tm1->day1)&&(x->day1<tm2->day1)) ){	
								//ikanopoiountai oi xronikoi periorismoi
									printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
									printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].date);
									printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
									printf("%d\t",pointer2->cdrbucket_entries[k].duration);
									printf("%c\t",pointer2->cdrbucket_entries[k].type);
									printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
									printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
									noresults=0;
		
							}else if(((x->year1==tm1->year1)&&(x->year1<tm2->year1)&&(x->month1==tm1->month1)&&(x->day1==tm1->day1)) || ((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1<tm2->month1)&&(x->day1==tm1->day1)) ){
								if((x->hours1>tm1->hours1)||((x->hours1==tm1->hours1)&&(x->mins1>=tm1->mins1))){
								//ikanopoiountai oi xronikoi periorismoi
									printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
									printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].date);
									printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
									printf("%d\t",pointer2->cdrbucket_entries[k].duration);
									printf("%c\t",pointer2->cdrbucket_entries[k].type);
									printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
									printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
									noresults=0;
								}

							}else if( ((x->year1==tm2->year1)&&(x->year1>tm1->year1)&&(x->month1==tm2->month1)&& (x->day1==tm2->day1))|| ((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm2->month1)&&(x->month1>tm1->month1)&&(x->day1==tm2->day1))){
								if((x->hours1<tm2->hours1)|| ((x->hours1==tm2->hours1)&&(x->mins1<=tm2->mins1))){
								//ikanopoiountai oi xronikoi periorismoi
									printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
									printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].date);
									printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
									printf("%d\t",pointer2->cdrbucket_entries[k].duration);
									printf("%c\t",pointer2->cdrbucket_entries[k].type);
									printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
									printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
									noresults=0;
								}

							}else if( ((x->year1==tm1->year1)&&(x->year1==tm2->year1)&&(x->month1==tm1->month1)&&(x->month1==tm2->month1)&&(x->day1==tm1->day1)&&(x->day1==tm2->day1)) ){
								if(((x->hours1 > tm1->hours1) && (x->hours1 < tm2->hours1)) 
				|| ((x->hours1==tm1->hours1) && (x->hours1 == tm2->hours1) && (x->mins1>=tm1->mins1) &&(x->mins1<=tm2->mins1)) 
				|| ((x->hours1==tm1->hours1)&&(x->hours1<tm2->hours1) && (x->mins1>=tm1->mins1)) 
				|| ((x->hours1==tm2->hours1)&&(x->hours1>tm1->hours1)&&(x->mins1<=tm2->mins1)) ){
								//ikanopoiountai oi xronikoi periorismoi
									printf("%s\t",pointer2->cdrbucket_entries[k].cdr_uniq_id);
									printf("%s\t",pointer2->cdrbucket_entries[k].originator_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].destination_number);
									printf("%s\t",pointer2->cdrbucket_entries[k].date);
									printf("%s\t",pointer2->cdrbucket_entries[k].init_time);
									printf("%d\t",pointer2->cdrbucket_entries[k].duration);
									printf("%c\t",pointer2->cdrbucket_entries[k].type);
									printf("%c\t",pointer2->cdrbucket_entries[k].tarrif);
									printf("%d\n",pointer2->cdrbucket_entries[k].fault_condition);
									noresults=0;

								}
							}
							free(tm1);free(tm2);free(x);						
						}							
					}
					pointer2=pointer2->next_cdr_bucket;	//epomeno cdr_bucket
					if(pointer2==NULL){
						flag=1;
						break;
					}	
				}
				if(flag==1){
					break;break;break;
				}	
			}
		}
		pointer1=pointer1->next_bucket;		//epomeno bucket
	}
	if(noresults==1)
		printf("\tNo CDRs found\n\n");

	free(tolookup1->caller);
	if(tolookup1->time1!=NULL)
		free(tolookup1->time1);
	if(tolookup1->time2!=NULL)
		free(tolookup1->time2);
	if(tolookup1->year1!=NULL)
		free(tolookup1->year1);	
	if(tolookup1->year2!=NULL)
		free(tolookup1->year2);	
	return 0;
}

int Indist(struct ht_entry *ht1, int h1, struct indist* ind1){

	struct bucket* pointer1;
	struct cdr_bucket* pointer2;
	int i,j,k,noresults=0;
//	printf("Indist caller1: %s caller2: %s .....\n", ind1->caller1, ind1->caller2);
	printf("\nindist >>>>\n");
	int found1=0, found2=0;
	for(i=0; i<h1; i++){			//gia ola ta stoixeia tou hashtable1
		pointer1=ht1[i].first_bucket;	//3ekinw apo to 1o bucket
		while(pointer1!=NULL){
			for(j=0; j < pointer1->count; j++){	//gia ola ta stoixeia tou pinaka bucket_entries tou bucket
				pointer2=pointer1->bucket_entries[j].first;	//3ekinw apo to 1o cdr_bucket
				while(pointer2!=NULL){
					for(k=0; k< pointer2->count; k++){	//psaxnw ola ta cdr_buckets na brw ton caller1 kai ton caller2
						if((strcmp(pointer2->cdrbucket_entries[k].destination_number,ind1->caller1)==0)&&(found1==0)){
							found1=1;
						}
						if((strcmp(pointer2->cdrbucket_entries[k].destination_number,ind1->caller2)==0)&&(found2==0)){
							found2=1;
						}
						if((found1==1)&&(found2==1)){
							break;break;	//brhka kai tous 2, bgainw apo thn epanalhpsh
						}
					}
					pointer2=pointer2->next_cdr_bucket;
				}
				if( (found1==1)&&(found2==1)
					&&(strcmp(pointer1->bucket_entries[j].callnumber,ind1->caller1)!=0)
					&&(strcmp(pointer1->bucket_entries[j].callnumber,ind1->caller2)!=0) ){//an exw brei kai tous 2 caller kai oi caller1 kai caller2 den exoun amesh epikoinwnia meta3u tous
						printf("\t%s\n",pointer1->bucket_entries[j].callnumber);
						noresults=1;
				}
				found1=0;
				found2=0;
			}
			pointer1=pointer1->next_bucket;		//epomeno bucket
		}
	}
	if(noresults==0)
		printf("\tNo indist found\n");

	free(ind1->caller1);
	free(ind1->caller2);

	return 0;
}

int Topdest(struct ht_entry *ht1, int h1, struct topdest* top1){

	unsigned long ht_pos = (unsigned long) hashfunction(top1->caller)%h1;	//briskw th 8esh pou brisketai o top1-<caller sto hashtable1
//	printf("pos=%lu\n",ht_pos);

	int j, bucket_pos, sumcdr=0, noresults=0;
	struct bucket *pointer1;
	struct cdr_bucket *pointer2;

	pointer1=ht1[ht_pos].first_bucket;	//3ekinw apo to 1o bucket tou
	while(pointer1!=NULL){
		for(j=0; j < pointer1->count; j++){	//gia ola ta stoixeia tou pinaka bucket_entries tou bucket
			if(strcmp(pointer1->bucket_entries[j].callnumber, top1->caller)==0){ //an to brw sto bucket_entries ton caller
				noresults=1;
				bucket_pos=j;
				pointer2=pointer1->bucket_entries[j].first;	//3ekinw apo to 1o cdr_bucket
				while(pointer2!=NULL){
					sumcdr += pointer2->count;		//sumcdr = o arithmos twn cdrs pou antistoixoun ston caller
					pointer2=pointer2->next_cdr_bucket;	//epomeno cdr_bucket
				}
				break;break;break;	//anazhthsh oloklhrwthike - e3odos apo tis epanalhpseis
			}
		}
		pointer1=pointer1->next_bucket;	//epomeno bucket
	}
	if(noresults==1){	//an h anzhthsh htan epituxhs
		int x,k,l,tablecount=0;
		struct topdest_entry *table, t;
		table=malloc(sumcdr*sizeof(struct topdest_entry));	//dhmiourgw enan pinaka table megethous sumcdr
		for(x=0; x<sumcdr; x++){
			table[x].count=0;				//arxikopoiw ta count tous se 0
		}	
		struct cdr_bucket *pointer;
		pointer=ht1[ht_pos].first_bucket->bucket_entries[bucket_pos].first;	//gia ton sugkekrimeno caller
		int flag=0;
		while(pointer!=NULL){
			for(k=0; k<pointer->count; k++){  //gia ola ta stoixeia tou cdrbucket_entries tou sugkekrimenou caller
				SeparateTopdest(&t, pointer->cdrbucket_entries[k].destination_number);	//diaxwrizw ton kwdiko xwras 
				if(tablecount==0){					//an o pinakas table einai kenos
					table[0].charcode=malloc(4*sizeof(char));	//eisagw ton sugkekrimeno kwdiko xwras ston table 
					strcpy(table[0].charcode, t.charcode);
					table[0].code=t.code;
					table[0].count++;				//au3anw ton metrhth tou
					tablecount++;					//au3anw ton ari8mo twn stoixeiwn tou table
				}else{				//an o table den einai kenos
					for(l=0; l<tablecount; l++){	//an o kwdikos xwras uparxei ston table
						if(table[l].code==t.code){
							table[l].count++;	//au3anw to metrhth tou
							flag=1;			
							break;			//bgainw apo thn epanalhpsh
						}
					}
					if(flag==0){		//an den uparxei ston table
						table[tablecount].charcode=malloc(4*sizeof(char));
						strcpy(table[tablecount].charcode, t.charcode);	//ton eisagw ston table
						table[tablecount].code=t.code;
						table[tablecount].count++;			//au3anw to metrhth tou
						tablecount++;			//au3anw ton ari8mo twn stoixeiwn tou table
					}
				}
				flag=0;
			}
			pointer=pointer->next_cdr_bucket;	//paw sto epomeno cdr_bucket
		}
		int y, max=-1;
		for(y=0; y<tablecount; y++){		//anazhthsh ston pinaka table na brw th max timh
			if(table[y].count>max){
				max=table[y].count;
			}
		}
		printf("\ntopdest >>>>\n");
		for(y=0; y<tablecount; y++){		//ektupwnw tous kwdikous xwras pou exoun thn idia timh me to max
			if(table[y].count==max){
				printf("\tCountry code : %s , Calls made: %d\n",table[y].charcode, table[y].count);
			}
		}
		printf("\n");
		for(y=0; y<tablecount; y++)
			free(table[y].charcode);
		free(table);
		free(top1->caller);
	}else{
		printf("\tNo calls found\n\n");	
	}
	return 0;
}

int Bye(struct ht_entry *ht1, struct ht_entry *ht2, int h1, int h2){

	int i,j,k;
	struct bucket *pointer1, *temp1;
	struct cdr_bucket *pointer2,*temp2;
	for(i=0; i<h1; i++){			//gia ola ta stoixeia tou hashtable1 
		pointer1=ht1[i].first_bucket;	//3ekinw apo to 1o bucket
		while(pointer1!=NULL){
			for(j=0; j < pointer1->count; j++){			//gia ola ta stoixeia tou pinaka bucket_entries tou bucket
				pointer2=pointer1->bucket_entries[j].first;	//3ekinw apo to 1o cdr_bucket
				while(pointer2!=NULL){
					for(k=0; k < pointer2->count; k++){	//gia ola ta stoixeia tou cdrbucket_entries tou cdr_bucket
						free(pointer2->cdrbucket_entries[k].cdr_uniq_id);
						free(pointer2->cdrbucket_entries[k].originator_number);
						free(pointer2->cdrbucket_entries[k].destination_number);
						free(pointer2->cdrbucket_entries[k].date);
						free(pointer2->cdrbucket_entries[k].init_time);
					}
					free(pointer2->cdrbucket_entries);	//diagrafw ton pinaka cdrbucket_entries tou cdr_bucket
					temp2=pointer2->next_cdr_bucket;
					pointer2->next_cdr_bucket=NULL;
					pointer2=temp2;				//epomeno cdr_bucket
				}
			}
			free(pointer1->bucket_entries);		//diagrafw ton pinaka bucket_entries tou bucket
			temp1=pointer1->next_bucket;
			pointer1->next_bucket=NULL;			
			pointer1=temp1;				//epomeno bucket
		}
		ht1[i].current_bucket=NULL;
	}
	free(ht1);

	for(i=0; i<h2; i++){				//gia ola ta stoixeia tou hashtable2
		pointer1=ht2[i].first_bucket;		//3ekinw apo to 1o bucket
		while(pointer1!=NULL){
			for(j=0; j < pointer1->count; j++){			//gia ola ta stoixeia tou pinaka bucket_entries tou bucket
				pointer2=pointer1->bucket_entries[j].first;	//3ekinw apo to 1o cdr_bucket
				while(pointer2!=NULL){
					for(k=0; k < pointer2->count; k++){	//gia ola ta stoixeia tou cdrbucket_entries tou cdr_bucket
						free(pointer2->cdrbucket_entries[k].cdr_uniq_id);
						free(pointer2->cdrbucket_entries[k].originator_number);
						free(pointer2->cdrbucket_entries[k].destination_number);
						free(pointer2->cdrbucket_entries[k].date);
						free(pointer2->cdrbucket_entries[k].init_time);
					}
					free(pointer2->cdrbucket_entries);	//diagrafw ton pinaka cdrbucket_entries tou cdr_bucket
					temp2=pointer2->next_cdr_bucket;
					pointer2->next_cdr_bucket=NULL;
					pointer2=temp2;			//epomeno cdr_bucket
				}
			}
			free(pointer1->bucket_entries);		//diagrafw ton pinaka bucket_entries tou bucket
			temp1=pointer1->next_bucket;
			pointer1->next_bucket=NULL;			
			pointer1=temp1;			//epomeno bucket
		}
		ht2[i].current_bucket=NULL;
	}
	free(ht2);
	
	printf("Bye >>>>\n\n");
	return 0;
}

int Dump(struct ht_entry* ht, int h, FILE* fp){
		
	int i,j,k;
	struct bucket *pointer1;
	struct cdr_bucket *pointer2;
	fprintf(fp, "CDR_UNIQ_ID-ORIGINATOR_NUMBER-DESTINATION_NUMBER - DATE - INIT_TIME-DURATION-TYPE-TARRIF-FAULT_CONDITION\n");
	fprintf(fp, "--------------------------------------------------------------------------------------------------------\n");
	for(i=0; i<h; i++){			//gia ola ta stoixeia tou hashtable
		pointer1 = ht[i].first_bucket;	//3ekinw apo to 1o bucket
		if(pointer1!=NULL){
			while( pointer1!=NULL ){
				for(j=0; j < pointer1->count; j++){	//gia ola ta stoixeia tou pinaka bucket_entries
					pointer2 = pointer1->bucket_entries[j].first;//3ekinw apo to 1o cdr_bucket
					while(pointer2!=NULL){
						for(k=0; k<pointer2->count; k++){ 	//gia ola ta stoixeia tou pinaka cdrbucket_entries
						//ektupwnw sto stream fp
							fprintf(fp, "%s\t", pointer2->cdrbucket_entries[k].cdr_uniq_id);
							fprintf(fp, "%s\t", pointer2->cdrbucket_entries[k].originator_number);
							fprintf(fp, "%s\t", pointer2->cdrbucket_entries[k].destination_number);
							fprintf(fp, "%s\t", pointer2->cdrbucket_entries[k].date);
							fprintf(fp, "%s\t", pointer2->cdrbucket_entries[k].init_time);
							fprintf(fp, "%d\t", pointer2->cdrbucket_entries[k].duration);
							fprintf(fp, "%c\t", pointer2->cdrbucket_entries[k].type);
							fprintf(fp, "%c\t", pointer2->cdrbucket_entries[k].tarrif);
							fprintf(fp, "%d\n", pointer2->cdrbucket_entries[k].fault_condition);
						}
						pointer2 = pointer2->next_cdr_bucket;	//epomeno cdr_bucket
					}			
				}
				pointer1 = pointer1->next_bucket;			//epomeno bucket
			}
		}
	}
	printf("Dump successful\n\n");
	return 0;
}
