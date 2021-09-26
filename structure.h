struct cdr_entry{
	char* cdr_uniq_id;
	char* originator_number;
	char* destination_number;
	char* date;
	char* init_time;
	int duration;
	char type;
	char tarrif;
	int fault_condition;
};

struct cdr_bucket{
	struct cdr_entry* cdrbucket_entries;
	struct cdr_bucket* next_cdr_bucket;	
	int count;
};

struct bucket_entry{
	char* callnumber;
	struct cdr_bucket* pcdr;
	struct cdr_bucket* first;
};

struct bucket{
	struct bucket_entry* bucket_entries;
	struct bucket* next_bucket;
	int count;
};

struct ht_entry{
	struct bucket* current_bucket;
	struct bucket* first_bucket;
};

struct todel{
	char* cdr_uniq_id;
	char* caller;
};

struct tofind{
	char* caller;
	char* time1;
	char* time2;
	char* year1;
	char* year2;
};

struct indist{
	char* caller1;
	char* caller2;
};

struct topdest{
	char* caller;
};

struct dump{
	char* filename;
};

struct ht_entry *CreateHashTable(int h);
int Insert(struct ht_entry *ht1, struct ht_entry *ht2, int h1, int h2, struct cdr_entry *cdr, int bucket_size );
int Delete(struct ht_entry *ht1, int h1, struct todel* todel1);
int Find(struct ht_entry *ht1, int h1, struct tofind* tofind1);
int Lookup(struct ht_entry *ht2, int h2, struct tofind* tolookup1);
int Indist(struct ht_entry *ht1, int h1, struct indist* ind1);
int Topdest(struct ht_entry *ht1, int h1, struct topdest* top1);
int PrintHashTable(struct ht_entry *ht, int h);
int Bye(struct ht_entry *ht1, struct ht_entry *ht2, int h1, int h2);
int Dump(struct ht_entry *ht, int h, FILE* fp);

struct time12{
	int hours1, mins1;
};

struct timedate12{
	int day1, month1, year1, hours1, mins1;
};

void Separate1(struct time12* t, char* time1);
void Separate2(struct timedate12* t, char* time1, char* date1);

struct topdest_entry{
	char* charcode;
	int code;
	int count;
};

void SeparateTopdest(struct topdest_entry* t, char* callnumber);


