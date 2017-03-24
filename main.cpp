#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

void giris();
void tusfonk(int x1,int y1,int x2,int y2);
void ates(int x1,int y1,int x2,int y2,int kontrol);
void readFile();
void printWall(int i,int y);
void dusman(int,int,int,int,int);
void karala(int,int,int,int);
FILE *fp;
bool aktif=false;
int sbt=0;
int rast= 1+ rand() % 4;
int yon=0;
int deger=0;
char dgr[10];
int sayac=0;
int q1,q2,w1,w2,ek=20;
int can=950,enemy_can=600;
int bekleme=0;
int logo=0;
int main( )
{
    
	initwindow( 1000 , 700 , "Game of Team" );//Oyun Ekraný

      giris(); //Giris ekraný cagrýldý..
   
    getch();
	return( 0 );
}

// ************************* GÝRÝÞ EKRANI *************************
void giris(){
    
   if(logo==0)
   {
       readimagefile("logo.jpg",0,0,1000,700);
       delay(4000); 
   }
      logo++; 
    
    int x,y; 
    
    readimagefile("arka.jpg",0,0,1000,700);
    readimagefile("oyna.jpg",840,100,970,200);
    readimagefile("cikis.jpg",840,450,970,550);   
    readimagefile("ipuçlarý.jpg",840,200,970,300);
    readimagefile("emegigecenler.jpg",820,350,980,400);
    
while(1)//oyun basla butonu
{
   while(ismouseclick(WM_LBUTTONDOWN))
   {

    getmouseclick(WM_LBUTTONDOWN,x,y);

     if(x>840 && x<970 && y>100 && y<200)//oyna
     {
   	     cleardevice();
         readimagefile("round1.jpg",0,0,1000,700);
         delay(3000);
         cleardevice();
         int x1=350,y1=600,x2=390,y2=640;
	     
         setcolor(8);
         setlinestyle(1,1,100);
         line(0,50,1000,50);
         
         readimagefile("playeryu.jpg",x1,y1,x2,y2);
	     readFile();//Arka plan olusturuldu
         tusfonk(x1,y1,x2,y2);//resmin koordinatlarý tusfonk a gonderildi
      }
      else if(x>840 && x<970 && y>450 && y<550)//cýkýþ
      {
          exit(1);
      }
      else if(x>840 && x<970 && y>200 && y<300)//ipuçlarý
      {   
          cleardevice();
          readimagefile("nasil.jpg",0,0,1000,700);
               
      }
      else if(x>40 && x<170 && y>60 && y<130)//geri
      {
          cleardevice();      
          giris();
      }
      else if(x>820 && x<970 && y>350 && y<400)//emegi geçenler
      {
          cleardevice();
          readimagefile("emek.jpg",0,0,1000,700);
      }                                 
     }
  }	
}
//**** Giriþ ekraný bitti..
//**************************************** PLAYER HAREKET FONKSÝYONU*****************************************
void tusfonk(int x1,int y1,int x2,int y2){
    
    int sonx,sony;
    int ek=10;//hareket icin ek birim
    int kontrol=0;//hareket edilen yonu anlamak icin
    char tus;
    int a1=450,b1=250,a2=490,b2=290;//düþman tankýnýn ilk koordinatlarýný belirledik
    
    readimagefile("tanksa.jpg",a1,b1,a2,b2);//düþman tankýný ilk yerine koyduk
     
        sonx=getmaxx()-10;//ekran sýnýrlarý
        sony=getmaxy()-10;
     
     while(1)//sonsuzdöngü baþladý
     {         
         if(kbhit())
         {
             bekleme++;
             fflush(stdin);        
             tus= getch();
         if(tus==27) exit(0);
             else 
             {   
                 if(tus==77)//sag tus
                   { 
                         x1+=ek; 
                         x2+=ek;
                         if(getpixel(x2,y2)!=0 || getpixel(x2,y1)!=0 ){x1-=ek; x2-=ek;}//Duvar sýnýrlarý korundu
                         kontrol=6; //saga gitti 
                         readimagefile("playersa.jpg",x1,y1,x2,y2);
                         karala(x1-11,y1,x1,y2);
                   }
                   else if(tus==75)//sol tus
                   {    
                         x1-=ek; 
                         x2-=ek;
                         if(  getpixel(x1,y1)!=0 || getpixel(x1,y2)!=0  ){x1+=ek; x2+=ek;}//Duvar sýnýrlarý korundu
                         kontrol=4; //sola gitti 
                         readimagefile("playerso.jpg",x1,y1,x2,y2);
                         karala(x2,y1,x2+11,y2);
                   }
                   else if(tus==72)//yukarý tus
                   {
                        y1-=ek; 
                        y2-=ek;
                        if( getpixel(x1,y1-15)!=0 || getpixel(x1,y2-15)!=0 ){y1+=ek; y2+=ek;}//Duvar sýnýrlarý korundu
                        kontrol=8;  //yukarý gitti
                        readimagefile("playeryu.jpg",x1,y1,x2,y2);
                        karala(x1,y2,x2,y2+11);
                   }
                   else if(tus==80)//aþagý tus
                   {
                        y1+=ek; 
                        y2+=ek; 
                        if(getpixel(x2,y2)!=0 || getpixel(x1,y2)!=0  ){y1-=ek; y2-=ek;}//Duvar sýnýrlarý korundu
                        kontrol=2;  //asagý gitti
                        readimagefile("playeras.jpg",x1,y1,x2,y2);
                        karala(x1,y1,x2,y1-11);
                    }
                   else if(tus==32)//bosluk tusu
                   {
                       if(((x1+x2)/2)+10>(a1+a2)/2 && ((x1+x2)/2)-10<(a1+a2)/2 && (y1+y2)/2<(b1+b2)/2 && kontrol==2)
                       enemy_can-=15;
                       if(((x1+x2)/2)+10>(a1+a2)/2 && ((x1+x2)/2)-10<(a1+a2)/2 && (y1+y2)/2>(b1+b2)/2 && kontrol==8)
                       enemy_can-=15;
                       if(((y1+y2)/2)+15>(b1+b2)/2 && ((y1+y2)/2)-15<(b1+b2)/2 && (x1+x2)/2<(a1+a2)/2 && kontrol==6)
                       enemy_can-=15;
                       if(((y1+y2)/2)+15>(b1+b2)/2 && ((y1+y2)/2)-15<(b1+b2)/2 && (x1+x2)/2>(a1+a2)/2 && kontrol==4)
                       enemy_can-=15;
                        
                       ates(x1,y1,x2,y2,kontrol);//playerýn koordinatlarý ates fonk. a gonderildi.                      
                   }
                
             }
    
    }

//**** Player hareket olayý bitti..
    
    if(aktif==true)//Ateþ duvar çarpýncaya kadar ateþi hareket ettirir..
    ates(x1,y1,x2,y2,kontrol);
    
   
//***************************************** ENEMY HAREKET FONKSÝYONU***************************************************
     
   if(getpixel(a1-10,b1)==0 || getpixel(a1+60,b1)==0 || getpixel(a2-60,b2)==0 || getpixel(a2+10,b2)==0 || getpixel(a1,b1-10)==0 || getpixel(a1,b1+60)==0 || getpixel(a2,b2-60)==0 || getpixel(a2,b2+10)==0){//duvar yoksa
                                  
                                  
         if(rast==1)//yukarý ise
         {
                             yon=8;
                                    if( getpixel(a1-3,b1-3)==0 || getpixel(a1+2,b2-53)==0)//duvar görene kadar yukarý git
                                    { 
                                           b1-=ek;        
                                           b2-=ek;
                                           karala(a1,b2+11,a2,b2);
                                           readimagefile("tanky.jpg",a1,b1,a2,b2);       
                                           delay(50); 
                                            
                                     }  
                                     if(getpixel(a1-3,b1-3)!=0 || getpixel(a1+3,b2-53)!=0)//duvara geldik mi ?
                                     {
                                          rast = 1 + rand() % 4;
                                     }          
         }
         if(rast==2)//saga ise
         {
                           yon=6;
                                     if(getpixel(a1+53,b1-3)==0 || getpixel(a2+3,b2+3)==0)// duvar görene kadar saga git
                                     { 
                                           a1+=ek;        
                                           a2+=ek;
                                           karala(a1,b1,a1-11,b2);
                                           readimagefile("tanksa.jpg",a1,b1,a2,b2);       
                                           delay(50);  
                                      }
                                      if(getpixel(a1+53,b1-3)!=0 || getpixel(a2+3,b2+3)!=0)
                                      {
                                             rast = 1 + rand() % 4;
                                      }
         
         }
         if(rast==3)//aþagý ise
         {
                            yon=2;
                                      if(getpixel(a1-3,b1+53)==0 || getpixel(a2+3,b2+3)==0)//duvar görene kadar aþagý git
                                      { 
                                           b1+=ek;        
                                           b2+=ek;
                                           karala(a1,b1,a2,b1-11);
                                           readimagefile("tankas.jpg",a1,b1,a2,b2);       
                                           delay(50);  
                                      }
                                      if(getpixel(a1-3,b1+53)!=0 || getpixel(a2+3,b2+3)!=0)//duvara geldik mi ?
                                      {
                                            rast = 1 + rand() % 4;
                                      }
              
         }
         if(rast==4)//sola ise
         { 
                           yon=4;
                                     if(getpixel(a1-3,b1-3)==0 || getpixel(a2-53,b2+3)==0)//duvar görene kadar sola git
                                      { 
                                          a1-=ek;        
                                          a2-=ek;
                                          karala(a2,b1,a2+11,b2);
                                          readimagefile("tankso.jpg",a1,b1,a2,b2);       
                                          delay(50);   
                                      } 
                                      if(getpixel(a1-3,b1-3)!=0 || getpixel(a2-53,b2+3)!=0)
                                      {
                                               rast = 1 + rand() % 4;
                                      }              
         } 
}   

//**** Enemy hareket olayý bitti..

//******************************    DÜÞMAN ATEÞÞ OLAYIII ****************************      
    
    int xort=(x1+x2)/2,yort=(y1+y2)/2,aort=(a1+a2)/2,bort=(b1+b2)/2;
    int c1,c2,d1,d2,ates_kontrol;
    
    if(xort+10>aort && xort-10<aort)
    {
                  
        if(yort>bort && bekleme>3)
        {
            bekleme=0;
            readimagefile("tankas.jpg",a1,b1,a2,b2);
            delay(100);               
            can-=15;
            ates(a1,b1,a2,b2,2); 
        }      
        else if(yort>!bort && bekleme>3)
        {
            bekleme=0;
            readimagefile("tanky.jpg",a1,b1,a2,b2);
            delay(100);
            can-=15;
            ates(a1,b1,a2,b2,8);}  
     
     }
     
     if(yort+10>bort && yort-10<bort)
     {
                  
        if(xort>aort && bekleme>3)
        {
            bekleme=0;
            readimagefile("tanksa.jpg",a1,b1,a2,b2);
            delay(100);            
            can-=15;
            ates(a1,b1,a2,b2,6);
        }      
        else if(xort>!aort && bekleme>3)
        {
            bekleme=0;
            readimagefile("tankso.jpg",a1,b1,a2,b2);
            delay(100);
            can-=15;
            ates(a1,b1,a2,b2,4);
        }  
     
     }
// Düsman ates kodu bitti..     
     
//**************** SKOR ÝÇÝN YAZI ÖRNEÐÝ ********************
   deger+=1;
   sprintf(dgr,"%d",deger);
   setcolor(3);
   settextstyle(1,0,5);
   outtextxy(0,50,dgr);
   outtextxy(0,0,"PUAN");

//***************** KENDÝ CAN AZALTMA ******************
    settextstyle(1,0,3);
    outtextxy(680,15,"- YOU lÝFE -");
    setfillstyle(1,6); 
    bar(650,40,950,100);
    setfillstyle(1,RED); 
    bar(650,40,can,100);
//********************DÜSMAN CAN AZATMA*****************
    settextstyle(1,0,3);
    outtextxy(310,15,"- ENEMY lÝFE -");
    setfillstyle(1,6); 
    bar(300,40,600,100);
    setfillstyle(1,RED); 
    bar(300,40,enemy_can,100);     

//********* Ben öldüysem **********                   
    if(can<660)
    {
        cleardevice();
        settextstyle(1,0,5);
        outtextxy(50,350,"DÜELLOYU KAYBETTÝN");
        getch();
        //mouse fonksiyonuyla yeniden basla bitir felan yap..
    }                      
//****** düsman can azaltma **********

    if(enemy_can<310)
    {
       cleardevice();
       settextstyle(1,0,5);
       outtextxy(50,350,"DELLOYU KAZANDIN");
       getch();
       //mouse fonksiyonuyla yeniden basla bitir felan yap..                  
    } 

}//sonsuz döngü bitti..       
       
}

bool aktif2=true;

//***************************************** PLAYER ATEÞ ETME FONKSÝYONU ********************************************

void ates(int x1,int y1,int x2,int y2,int kontrol){//playerýn tüm koordinatlarý ve kontrol ateþ fonk a gönderildi
     
     aktif=true;
     
             if( kontrol==6 && sbt==0 || sbt==6 )//player saga gitti ise
                   { 
                              sbt=6;
                              
                              if(aktif2){
                              q1=x2;
                              q2=x2+10;
                              w1=(y1+y2)/2-5;
                              w2=(y1+y2)/2+5;
                              aktif2=false;
                              }
                              readimagefile("tanksa.jpg",q1,w1,q2,w2);
                              readimagefile("siyah.jpg",q1,w1,q2,w2);
                              q1+=80;
                              q2+=80;
                              readimagefile("sun.jpg",q1,w1,q2,w2);
                              
                              if(getpixel(q2+15,w1)!=0 && getpixel(q2+15,w2)!=0){
                                                      aktif=false;
                                                      aktif2=true;
                                                      sbt=0;
                                                      readimagefile("siyah.jpg",q1,w1,q2,w2);
                              }
                             
                   }
                   
                   else if( kontrol==4 && sbt==0 || sbt==4 )//player sola giti ise
                   {
                       sbt=4;     
                       if(aktif2){
                              
                              q1=x1-10;
                              q2=x1-20;
                              w1=(y1+y2)/2-5;
                              w2=(y1+y2)/2+5;
                              aktif2=false;
                       
                              }
                              readimagefile("tankso.jpg",q1,w1,q2,w2);  
                              readimagefile("siyah.jpg",q1,w1,q2,w2);
                              karala(q1,w1,q2+5,w2+5);
                              q1-=80;
                              q2-=80;
                              readimagefile("sun.jpg",q1,w1,q2,w2);
                              
                              if(getpixel(q1-10,w1)!=0 && getpixel(q1-10,w2)!=0){
                                                      aktif=false;
                                                      aktif2=true;
                                                      sbt=0;
                                                      readimagefile("siyah.jpg",q1,w1,q2,w2);
                                                      }
                   
                   }
                   else if (kontrol==8 && sbt==0 || sbt==8 )//player yukarý gitti ise
                   {
                      sbt=8;     
                      if(aktif2){
                              
                              q1=(((x1+x2)/2)-5);
                              q2=(((x1+x2)/2)+5);
                              w1=y1-10;
                              w2=y1; 
                              aktif2=false;
                              }
                              readimagefile("tanky.jpg",q1,w1,q2,w2);
                              readimagefile("siyah.jpg",q1,w1,q2,w2);
                              w1-=80;
                              w2-=80;
                              readimagefile("sun.jpg",q1,w1,q2,w2);
                              
                              if(getpixel(q1+25,w1)!=0 && getpixel(q2+25,w1)!=0){
                                                      aktif=false;
                                                      aktif2=true;
                                                      sbt=0;
                                                      readimagefile("siyah.jpg",q1,w1,q2,w2);
                                                      }
                    
                   }
                   else if (kontrol==2 && sbt==0 || sbt==2 )//player  asagý gitti ise
                   {
                               
                      sbt=2;
                      if(aktif2){
                              
                              q1=(((x1+x2)/2)-5);
                              q2=(((x1+x2)/2)-15);
                              w1=y2+10;
                              w2=y2; 
                              aktif2=false;
                              
                             
                              }
                              readimagefile("tankas.jpg",q1,w1,q2,w2);
                              readimagefile("siyah.jpg",q1,w1,q2,w2);
                              w1+=80;
                              w2+=80;
                              readimagefile("sun.jpg",q1,w1,q2,w2);
                              
                              if(getpixel(q1,w1+20)!=0 && getpixel(q2,w2+20)!=0){
                                                      aktif=false;
                                                      aktif2=true;
                                                      sbt=0;
                                                      readimagefile("siyah.jpg",q1,w1,q2,w2);
                                                      }
                    
                   }
}

//****Player ates fonk bitti..

// ***************** MAP BASMA FONKSÝYONU*****************
void printWall(int i,int y)
{
    int x=(i%20)*50;
    readimagefile("wall.jpg",x,y,x+50,y+50);  
}
//********************************************************

//**************************** DOSYADAN MAP VERÝLERÝNÝ OKUYAN FONKSÝYON *************************************
void readFile()
{    
     int kat=0;
     int x,y=0;
     fp=fopen("Dosya.txt","r");
     int dizi[300];
     
     for(int i=0;!feof(fp);i++)//son karakteri görene kadar
     {
         dizi[i]=fgetc(fp);
         
         if(dizi[i]==49)
         {
                kat=i/20;
                y=50*kat;
                printWall(i,y);
         }
         else if(dizi[i]==50)
         {
                kat=i/20;
                y=50*kat;
                x =(i%20)*50;
                //readimagefile("korunan.jpg",x,y,x+67,y+100);
         }
         else if(dizi[i]==51)
         {
               kat=i/20;
               y=50*kat;
               x =(i%20)*50;
               readimagefile("deniz.jpg",x,y,x+50,y+50);
         }
                        
     }
     fclose(fp);
}

 //Dosyadan map verilerini koyan fonk. bitti...

//****** KALÝTELÝ HAREKET ÝÇÝN *********
void karala(int a1,int b1,int a2,int b2){// her harekette arkaya gittiðimiz kadarlýk siyah bar cizer..
     
     setfillstyle(1,0);
     bar(a1,b1,a2,b2);
         
     }                                                    
/********  tik tak kodu************

clock_t tik,tak;
tik=clock();
tak=tik;
while((tak/CLOCKS_PER_SEC-tik/CLOCKS_PER_SEC)<1){
tak=clock();
}

*/
