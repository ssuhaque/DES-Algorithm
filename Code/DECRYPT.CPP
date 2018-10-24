#include"crypt_1.h"


void main(int argc,char *argv[])
{
   clrscr();
   int a;
   if(argc!=3){printf("Format: c:>decrypt filename filename" ); exit(1); }

   if((meg=fopen(argv[1],"rb"))==NULL)
     {
      printf("\nCant open encrypted file");
      getche();
      exit(1);
     }

   keyc();
   output=fopen(argv[2],"wb");
   printf("\n\n\n\tFile Decryption in process. Please Wait....");
   openinput();
   printf("\n\n\n\tFile decrypted in %s\n\n\n",argv[2]);
   fcloseall();

}

void openinput(void)
{
   int a,flag=0,count;

   while(!feof(meg)){
		     count=0;
		     for(a=0;a<8;a++)
		       mesg[a]=0;
		     for(a=0;a<8;a++)
		     {
		       fscanf(meg,"%c",&mes[a]);
		       if(feof(meg))
			{
			 flag=1;
			 break;
			}
		       count=1;
		       mesg[a]=mes[a];
		     }
		     if(flag)
		      break;
		     message();

		    }


  if(flag && count)
    message();
  fcloseall();
}


int bit2(int n,char *x)
{
int group,p,mask;
group=n/8;
p=n%8;
mask=pow(2,7-p);
return (  (x[group] & mask) ? 1:0);
}



void keyc(void)
{
//char cipher[8]="4Wy›¼ßñ";// for cipher
char cipher[8]; printf("   Enter The Key You Want\n   It should be not longer than  8 character: ");
for(int z=0;z<8;z++)
  cipher[z]=getche();
printf("\n\n\tThankyou For entering chiperkey which is:  ");
for(z=0;z<8;z++)
 printf("%c",cipher[z]);

char c[17][4];
char d[17][4];// c&d for permutated 1/2 key
char kp[7]={0,0,0,0,0,0,0};
char kcd[17][7];
int a,i,x=0,y=0,b=0,v=0,block,p;
//cleaning c and d
for(a=0;a<17;a++)for(i=0;i<4;i++){c[a][i]=0;d[a][i]=0;}
for(a=0;a<17;a++)for(i=0;i<7;i++){kcd[a][i]=0;}
for(a=0;a<7;a++)
   {
   for(i=0;i<8;i++)
      {
       if(bit2(pc1[y][x]-1,cipher)==1)	  kp[a]=kp[a]+pow(2,7-i);x++;
       if(x==7){x=0;y++;}
      }
    }

// for c0 and d0
b=0;v=7;
for(a=0;a<56;a++)
   {
       if( bit2(a,kp)==1)
	 {
	 if(a<28) {c[0][b]=c[0][b]+pow(2,v);}
	 if(a>27){d[0][b]=d[0][b]+pow(2,v);}
	 }
	 v--;if(v==-1){v=7;b++;}
       if(a==27){v=7;b=0;}
    }
// c[0] and d[0] made
i=pow(2,7);v=pow(2,6);x=pow(2,4);y=pow(2,5);
for(int k=0;k<17;k++)
   {
   for(a=shift[k];a<28;a++)
      {
     block=(a-shift[k])/8;p=(a-shift[k])%8;b=pow(2,7-p);
     if(bit2(a,c[k])==1)  c[k+1][block]=c[k+1][block]+b;
     if(bit2(a,d[k])==1)  d[k+1][block]=d[k+1][block]+b;
      }// c
    if(shift[k]==1)
       {
       if(( (c[k][0] & i ) ? 1:0)==1) c[k+1][3]=c[k+1][3]+x;
       if(( (d[k][0] & i ) ? 1:0)==1) d[k+1][3]=d[k+1][3]+x;
       }
    if(shift[k]==2)
       {
	if(( (c[k][0] & i)  ? 1:0)==1)c[k+1][3]=c[k+1][3]+y;
	if(( (c[k][0] & v)  ? 1:0)==1)c[k+1][3]=c[k+1][3]+x;
	if(( (d[k][0] & i)  ? 1:0)==1)d[k+1][3]=d[k+1][3]+y;
	if(( (d[k][0] & v)  ? 1:0)==1)d[k+1][3]=d[k+1][3]+x;
       }
   }//c++
// adding c and d back together
v=7;
for(a=1;a<17;a++)
    {
    for(i=0;i<56;i++)
       {
	block=i/8;p=i%8;b=pow(2,7-p);
	if(i<28)if(bit2(i,c[a])==1)kcd[a][block]=kcd[a][block]+b;
	if(i>27)
	  {
	   if(i==28){v=0;}
	   if(bit2(v,d[a])==1)kcd[a][block]=kcd[a][block]+b;
	  }
	v++;
       }
    }// end of kcd loop

x=0;y=0;v=0;
for(v=1;v<17;v++)
   {
   x=0;y=0;
   for(a=0;a<6;a++)
      {
       for(i=0;i<8;i++)
	  {
	   if(bit2(pc2[y][x]-1,kcd[v])==1) key[v][a]=key[v][a]+pow(2,7-i);
	   x++;
	   if(x==6){x=0;y++;}
	  }
      }
   }
}




void message(void)
{
int a,i,x=0,y=0,b=0,sx=0,t,sy=0,epb=0,scc=0,scc2=0;
char f[4]={0,0,0,0};
char l[17][4],r[17][4];
char ep[8];
char ipm[8];
int data[8];
int dat[8];
for(a=0;a<8;a++){ep[a]=0;ipm[a]=0;data[a]=0;}
for(a=0;a<17;a++)for(b=0;b<4;b++){l[a][b]=0;r[a][b]=0;}

for(a=0;a<8;a++)
    for(i=0;i<8;i++)
      {
       if(bit2(ip[y][x]-1,mesg)==1)
       ipm[a]=ipm[a]+pow(2,7-i);x++;
      }

// dividing now

for(a=0;a<8;a++)
   {
   if(a<4) l[0][a]=ipm[a];
   else r[0][a-4]=ipm[a];
   }

for(b=1;b<17;b++)
   {
   for(a=0;a<4;a++)l[b][a]=r[b-1][a];// l[n]=r[n-1]
   //making r[n]=l[n-1] + f( r[n-1], k[n])
   // step 1= making e(r[n-1]) into ep
   y=0;x=0;
   for(a=0;a<7;a++)ep[a]=0;// cleaning ep
   for(a=0;a<6;a++)
      {
      for(i=0;i<8;i++)
	 {
	  if(bit2(e[y][x]-1,r[b-1])==1)ep[a]=ep[a]+pow(2,7-i);
	  x++;
	  if(x==6) {x=0;y++;}
	 }
      }
   // step 2= xor between ep and k[n] result saved in ep
   for(a=0;a<6;a++)
      {
      ep[a]=ep[a]^key[17-b][a];
      }
   // step 3= replacing  6 bit form ep into r[n] (4 bits)
   x=0;y=0;epb=1;scc=0;scc2=0;
   for(a=0;a<8;a++)
      {
      for(i=0;i<6;i++)
	 {
	 if(i==0)sx=0;
	 if(i==1)sy=0;
	 if(bit2(epb-1,ep)==1)
	    {
	    if(i==0)sx=2;
	    if(i==5)sx=sx+1;
	    if(i>0 || i<5)sy=sy+pow(2,4-i);
	    }
	 epb++;
	 }
      if(epb==49)epb=0;
      if(scc%2==0)r[b][scc2]=s[a][sx][sy]<<4;
      if(scc%2==1){r[b][scc2]=r[b][scc2]+s[a][sx][sy];scc2++;}scc++;
      }
   // step 4 = appling permutation p for completing f function result into f
   x=0;y=0;
   for(a=0;a<4;a++)f[a]=0;// cleaning f
   for(a=0;a<4;a++)
      {
      for(i=0;i<8;i++)
	 {
	  if(bit2(p[y][x]-1,r[b])==1)f[a]=f[a]+pow(2,7-i);
	  x++;
	  if(x==4) {x=0;y++;}
	 }
      }
   //step 5= xor f (r[n]) with l[n-1] to find r[n]
   for(a=0;a<4;a++)   r[b][a]=f[a]^l[b-1][a];
  }
   //step 6= making r[16]+l[16] into mesg
  for(a=0;a<8;a++)mesg[a]=0;//cleaning mesg
  for(a=0;a<8;a++)
     {
     if(a<4)mesg[a]=r[16][a];
     else mesg[a]=l[16][a-4];
     }
  //step 7= making final  encrypted data
  y=0;x=0;
  for(a=0;a<8;a++)data[a]=0;
  for(a=0;a<8;a++)
  for(i=0;i<8;i++)
      {
       if(bit2(ip1[y][x]-1,mesg)==1)
       data[a]=data[a]+pow(2,7-i);x++;
      }
for(a=0;a<8;a++)
  {
  fprintf(output,"%c",data[a]);
  }
}