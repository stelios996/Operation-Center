To programma apoteleitai apo ta e3hs arxeia:
	-main.c
	-readfunctions.c
	-structure.c
	-hash.c
	
	kai apo ta header files:
		-readfunctions.h
		-structure.h
		-hash.h
	
	ka8ws kai apo to Makefile

Sto programma exoun ulopoih8ei oles oi sunarthseis ektos apo thn top k% kai to swro

Yparxei h dunatothta separate compilation me th xrhsh tou Makefile
Metaglwtizoume patwntas thn entolh make, kai uparxei h dunatothta na sbhsoume ta object files(.o) kai to ektelesimo arxeio werhauz patwntas thn entolh make clean 

Proteinomena (HashTable1NumOfEntries,HashTable2NumOfEntries,BucketSize) gia ta arxeia eisodou apo to site tou mathimatos
	arxeio1: (10,10,1000)
	arxeio2: (10,10,1000)
	arxeio3: (10,10,1000)
	arxeio4: (10,10,1000)
	arxeio5: (50,50,2000)
	arxeio6: (50,50,10000)

--To arxeio main.c arxika elegxei posa arguments exoume kai poia einai auta kai ta anagnwrizei.Dhmiourgountai ta 2 hashtables kai an exoume dwsei th shmaia 
  -o Operations tote anoigei to arxeio eisodou Operations kai diabazei mia mia tis entoles kai ektelei tis antistoixes energeies katallhla gia ka8e entolh.An to arxeio
  eisodou exei kai thn entolh bye tote afou ektelestei kai h sunarthsh Bye uparxei erwthsh pros to xrhsth an thelei na sunexisei na dinei entoles apo to terminal h oxi.
  Epishs an den uparxei h shmaia -o Operations tote o xrhsths mporei na dinei entoles apo to terminal kai analoga thn entolh na ekteleitai kai h antistoixh energeia 
  mexri o xrhsths na apofasisei na stamathsei na dinei entoles

--To arxeio readfunctions.c perilambanei sunarthseis oi opoies xrhsimopoiountai gia na diabazontai oi antistoixes entoles apo to arxeio eisodou kai na diaxwrizontai se stoixeia pou apaitountai gia tis
  antistoixes diafores energeies kai apothikeuontai stis antistoixes metablhtes structs
	-h void ReadInsert(struct cdr_entry *cdr, char* line) dexetai ena string pou periexei mia entolh insert kai th diaxwrizei se stoixeia pou apothikeuontai sta
  antistoixa pedia tou cdr
	-h void ReadDelete(struct todel* todel1, char* line) dexetai ena string pou periexei mia entolh delete kai th diaxwrizei se stoixeia pou apothikeuontai sta 
  antistoixa pedia tou todel1
	-h void ReadFindLookup(struct tofind* tofind1, char* line) diabazei ena string pou periexei mia entolh find h lookup kai th diaxwrizei se stoixeia pou 
  apothikeuontai sta antistoixa pedia tou tofind1
	-h void ReadTopdest(struct topdest* top1, char* line) dexetai ena string pou periexei mia entolh topdest kai th diaxwrizei se stoixeia pou apothikeuontai 
  sta antisoixa pedia tou top1
	-h void ReadDump(struct dump* d,char* line) dexetai ena string pou periexei mia entolh dump kai apothikeuei to onoma tou filename(opou tha ginei to dump) 
  sto antistoixo pedio tou d
 	-h void ReadIndist(struct indist* ind1, char* line) dexetai ena string pou periexei mia entolh indist kai th diaxwrizei se stoixeia pou apothikeuontai sta 
  antistoixa pedia tou ind1
	
	-h void Separate1(struct time12* t, char* time1) dexetai ena string pou periexei wra kai th diaxwrizei se wres kai lepta kai ta apothikeuei sta antistoixa 
  pedia tou t
  	-h void Separate2(struct timedate12* t, char* time1, char* date1) dexetai ena string pou periexei wra kai ena string pou periexei hmeromhnia kai ta diaxwrizei 
  se wres kai lepta kai mera mhna etos kai ta apothikeuei sta antistoixa pedia tou t
	-h void SeparateTopdest(struct topdest_entry* t, char* callnumber) dexetai ena string pou periexei enan arithmo kai diaxwrizei ton kwdiko xwras kai ton 
  apothikeuei sto antistoixo pedio tou t 
	
--To arxeio hash.c perilambanei th hashfunction pou einai o algorithmos djb2 apo:	www.cse.yorku.ca/~oz/hash.html

--To arxeio structure.c perilambanei tis sunarthseis pou apaitountai gia tis diafores energeies ths askhshs
  	-h struct ht_entry* CreateHashTable(int h) dexetai ws orisma enan akeraio h kai dhmiourgei ton hashtable me h theseis,kai prosaptei se kathe thesh tou 
  hashtable to arxiko keno bucket kai telika epistrefei to hashtable pou dhmiourghse
	-h int Insert(struct ht_entry *ht1, struct ht_entry *ht2,int h1, int h2, struct cdr_entry *cdr, int bucket_size) dexetai ta 2 hashtables, to megethos tous,
  ena cdr pros eisagwgh kai to megethos tou bucket.Arxika upologizoume to posa stoixeia xwrane sto kathe bucket kai to cdr_bucket.Epeita 3ekiname thn eisagwgh 
  sto hashtable1 briskontas th thesh tou sthn opoia tha mpei kanontas hashing me to originator_number. 3ekinwntas apo to 1o bucket auths ths theshs elegxoume an 
  to originator_number tou cdr pou theloume na eisagoume uparxei se kapoio apo ta buckets ths sugkekrimenhs theshs tou hashtable1.H anazhthsh ginetai an to bucket 
  den einai keno.Tote elegxoume seiriaka ola ta buckets oles tis eggrafes kai an uparxei hdh tote an xwraei akoma mia eggrafh sto cdr_bucket auths eisagoume to 
  cdr se auto to cdr_bucket alliws an den uparxei xwros se auto to cdr_bucket dhmiourgoume ena allo kai to eisagoume se auto.An to bucket einai keno h h anazhthsh sta
  buckets htan apotuxhs tote efoson xwraei sto bucket h eggrafh eisagoume to originator_number ths sto bucket kai dhmiourgoume to cdr_bucket opou ekei eisagoume ola 
  ta stoixeia tou cdr.An den xwraei h eggrafh sto bucket tote dhmiourgoume ena allo bucket kai eisagoume to originator_number ths eggrafhs se auto to bucket kai 
  oloklhrh thn eggrafh sto cdr_bucket pou dhmiourgoume gia auto to originator_number. H eisagwgh sto hashtable2 einai paromoia me thn eisagwgh gia  to hashtable1 mono 
  pou kanoume hashing me to destination_number kai sta buckets eisagoume to destination_number tou cdr  
	-h int Delete(struct ht_entry *ht1, int h1, struct todel* todel1) arxika briskei th thesh pou brisketai o caller sto hashtable1.Sth sunexeia 3ekinwntas apo 
  to prwto bucket auths ths theshs anazhtoume se kathe bucket na broume ton caller kai otan ton broume anazhtoume se kathe cdr_bucket tou na broume thn eggrafh pou
  theloume na diagrapsoume.Otan th broume sto cdr_bucket tote elegxoume an uparxoun polles eggrafes se auto to cdr_bucket h mono mia.An oi eggrafes pou uparxoun
  einai polles tote diagrafoume authn pou theloume kai olisthainoume tis epomenes apo auth th thesh eggrafes mia thesh pros ta pisw ston pinaka wste oi count prwtes
  theseis sto cdr_bucket na einai kathlleimenes.An h eggrafh pou theloume na diagrapsoume einai h monadikh pou uparxei ston pinaka tou cdr_bucket tote e3etazoume an
  auto to cdr_bucket einai h kefalh ths listas twn cdr_bucket h exei kapoia allh thesh sth lista.An einai h kefalh tote elegxoume an exei epomeno h oxi kai diagrafoume
  katallhla to cdr_bucket alliws an den einai h kefalh briskoume ton prohgoumeno tou kai diagrafoume katallhla to cdr_bucket.Etsi afou diagrapsame th eggrafh apo ta
  cdr_bucket e3etazoume sth sunexeia gia to bucket sth thesh pou brisketai o caller an to bucket exei polla h ena monadiko stoixeio.An exei polla stoixeia kai h lista
  me ta cdr_buckets einai kenh meta th diagrafh pou kaname, tote diagrafoume ton caller apo to bucket kai olisthainoume apo auth th thesh kai meta tous caller mia thesh
  pisw ton kathena wste oi count prwtes theseis tou bucket na einai kathlleimenes.An o caller einai to monadiko stoixeio tou bucket kai h lista twn cdr_bucket tou einai
  kenh tote diagrafoume auto to bucket afou eleg3oume an auto to bucket einai kefalh h exei kapoia allh thesh sth lista twn buckets.Antistoixa me th diagrafh sta cdr_bucket,
  e3etazoume tis periptwseis kai kanoume thn katallhlh diagrafh
  	-h int Find(struct ht_entry *ht1, int h1, struct tofind* tofind1) briskoume arxika th thesh pou brisketai o caller ston hashtable1 kai 3ekiname thn anazhthsh apo to
  to prwto bucket auths ths theshs kai psaxnoume se ola ta buckets na vroume ton caller.Afou ton broume tote psaxnoume se ola ta cdr_bucket auths ths theshs na broume tis
  eggrafes pou theloume.Analoga thn periptwsh an den exoume xronikous periorismous,an exoume xronikous periorismous wras h an exoume xronikous periorismous wras kai 
  hmeromhnias tote antistoixa h ektupwnoume oles tis eggrafes twn cdr_bucket, h mono autes pou ikanopoioun tous xronikous periorismous wras h mono autes pou ikanopoioun
  tous xronikous periorismous wras kai hmeromhnias
	-h int Lookup(struct ht_entry *ht2, int h2, struct tofind* tolookup1) einai antistoixh me thn int Find(struct ht_entry *ht1, int h1, struct tofind* tofind1) alla
  edw h anazhthsh tou callee ginetai ston hashtable2
	-h int PrintHashTable(struct ht_entry *ht, int h) ektupwnei gia oles tis theseis tou hashtable,gia ola ta bucket, oles tis eggrafes pou uparxoun se ola ta 
  cdr_buckets
	-h int Indist(struct ht_entry *ht1, int h1, struct indist* ind1) psaxnei gia olous tous sundromhtes pou briskontai ston hashtable1, ola ta buckets kai cdr_buckets
  antistoixa pou exoun kalesei kai ton caller1 kai ton caller2 kai tous ektupwnei  mono an o caller1 kai o caller2 den exoun amesh epikoinwnia
	-h int Topdest(struct ht_entry *ht1, int h1, struct topdest* top1) psaxnei arxika sth sugkekrimenh thesh tou hashtable1 pou brisketai o caller,se ola ta 
  buckets kai ta antistoixa cdr_buckets tous na brei thn eggrafh pou zhtame.An broume to originator_number se kapoio bucket tote metrame ola ta stoixeia pou uparxoun 
  sta cdr_buckets auths ths theshs kai kratame auth th thesh.Dhmiourgoume ena pinaka megethous ths prohgoumenhs metrhshs kai gia kathe eggrafh pou brisketai sta
  cdr_buckets ths theshs pou brhkame, pairnoume ton kwdiko xwras kai an den uparxei hdh ston pinaka pou ftiaksame ton eisagoume kai au3anoume kai to metrhth klhsewn 
  autou tou kwdikou.An uparxei hdh ston pinaka tote au3anoume to metrhth autou tou kwdikou.Telika briskoume to max se auton ton pinaka me to megalutero metrhth klhsewn
  kai ektupwnoume olous tous kwdikous xwrwn pou o metrhths klhsewn tous einai isos me to max
	-h int Bye(struct ht_entry *ht1, struct ht_entry *ht2, int h1, int h2) diagrafei kai gia ta 2 hashtable oti egine dynamically allocation, katastrefei ola ta
  cdr_buckets,buckets kai telika kai ta 2 hashtables
	-h int Dump(struct ht_entry* ht, int h, FILE* fp) ektupwnei gia oles tis theseis tou hashtable,gia ola ta bucket, oles tis eggrafes pou uparxoun se ola ta 
  cdr_buckets sto arxeio fp
