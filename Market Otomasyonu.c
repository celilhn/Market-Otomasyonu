#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<time.h>


struct Urun
{
    int barkod;
    char ad[50];
    int kategori;
    float fiyat;
};

struct Market
{
    struct Urun* liste[1000];
    int urunsayisi;
};

int barkodolustur(struct Market* m)
{
    int i;
    int random;
    int buldu = 0;
    while(buldu == 0)
    {
        random = rand()%900 +100;
        buldu = 1;
        for(i=0;i<m->urunsayisi;i++)
        {
            if(m->liste[i]->barkod == random)
            {
                buldu = 0;
                break;
            }
        }
    }
    return random;

}

struct Urun* urunTanimla(struct Market* m,char adic[50],int katic, float fiyatic)
{
    struct Urun* u = (struct Urun*)malloc(sizeof(struct Urun));

    u->barkod = barkodolustur(m);
    u->kategori = katic;
    u->fiyat = fiyatic;
    int i;
    for(i=0;i<50;i++)
    {
        u->ad[i] = adic[i];
    }
    return u;
}


struct Market* marketac()
{
    struct Market* m = (struct Market*)malloc(sizeof(struct Market));
    struct Urun* u = m->liste[0];
    int i;
    for(i=0;i<1000;i++) //POINTER OFFSET
    {
    	struct Urun* u1= u + i;
    	u1 = NULL;
	}
    m->urunsayisi = 0;
    return m;
}

void urunekle(struct Market* m,char adic[50],int katic, float fiyatic)
{
    struct Urun* u = urunTanimla(m,adic,katic,fiyatic);
    m->liste[m->urunsayisi] = u;
    m->urunsayisi +=1;

    FILE * barkoddosya;
    barkoddosya = fopen("barkod.txt","w");
    int i;
    for(i=0;i<m->urunsayisi;i++)
    {
        fprintf(barkoddosya,"Barkod: %d Ad: %s Kategori: %d Birim/Kg Fiyat: %.2f\n",m->liste[i]->barkod,m->liste[i]->ad,m->liste[i]->kategori,m->liste[i]->fiyat);
    }
    fclose(barkoddosya);
}

void tarayici(int satir)
{ 

       FILE *fp;
   int ch;
    fp = fopen( "barkod.txt" , "r" );
   while(1) {
      ch = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      printf("%c", ch);
   }
   rewind(fp);
   printf("\n");
   fclose(fp);
}
struct Fatura
{
    int tarih;
    char ad[50];
    float toplamf;
    int barkod;
};

struct Fatura* faturaolustur(int tarih, char ad[50],int barkod, float toplamf)
{
    struct Fatura* f = (struct Fatura*)malloc(sizeof(struct Fatura));
    f->tarih = tarih;
    int i;
    for(i=0;i<50;i++)
    {
        f->ad[i] = ad[i];
    }
    f->toplamf = toplamf;
    f->barkod = barkod;
    return f;
}


struct Musteri
{
    struct Fatura* fis[200];
    int adet;
};

struct Musteri* musteriac()
{
    struct Musteri* mu = (struct Musteri*)malloc(sizeof(struct Musteri));
    mu->adet = 0;
    return mu;
}

void urunal(struct Musteri* m,struct Urun* u,float miktar,int tarih)
{
    struct Fatura* f= faturaolustur(tarih,u->ad,u->barkod,(miktar*u->fiyat));
    m->fis[m->adet] = f;
    m->adet +=1;

    FILE * fisdosya;
    fisdosya = fopen("fatura.txt","w");
    int i;
    for(i=0;i<m->adet;i++)
    {
        fprintf(fisdosya,"Barkod: %d Ad: %s Fiyat: %.2f  Tarih: %d\n",m->fis[i]->barkod,m->fis[i]->ad,m->fis[i]->toplamf,m->fis[i]->tarih);
    }
    fclose(fisdosya);
}

int main()
{
    struct Market* m = marketac();
    struct Musteri* mu = musteriac();

    int gun = 0;
    int secim = 0;

    while(secim != 4)
    {
        printf("************%d. Gun Market Acildi*************\n",gun);
        printf("1-Urun Ekle\n2-Urun Listeleme\n3-Urun Satin al\n4-Cikis\nSecim Yapiniz:\n");
        scanf("%d",&secim);
        while(secim==1)
        {
            char adic[50];
            int katic;
            float fiyatic;

            printf(" Urun Adi: "); scanf("%s",adic);
            printf("Urun Kategorisi: "); scanf("%d",&katic);
            printf("Urun birim/kg fiyati: "); scanf("%f",&fiyatic);

            urunekle(m, adic, katic,  fiyatic);
            printf("Urun eklendi\n1-Yeni Urun Ekle\n2-Urun Listeleme\n3-Urun Satin al\n4-Cikis\nSecim Yapiniz:\n"); scanf("%d",&secim);
        }

        while(secim==2)
        {
            tarayici(m->urunsayisi);
            printf("Urunler Listelendi\n1-Yeni Urun Ekle(yeni gun)\n2-Urun Listeleme\n3-Urun Satin al\n4-Cikis\nSecim Yapiniz:\n"); scanf("%d",&secim);
        }
        while(secim==3)
        {
            int bar,i;
            printf(" Urun Barkod Kodu Giriniz: ");scanf("%d",&bar);
            struct Urun* u = NULL;
            for(i=0;i<m->urunsayisi;i++)
            {
                if(m->liste[i]->barkod == bar)
                {
                    u=m->liste[i];
                }
            }
            if(u==NULL)
            {
                printf("Urun Bulunamadi\n");
            }else{
                float mikgir;
                printf("Alacaginiz Miktari Giriniz: ");scanf("%f",&mikgir);
                urunal(mu,u,mikgir,gun);
            }
            printf("Urun Alindi\n1-Yeni Urun Ekle(yeni gun)\n2-Urun Listeleme(yeni gun)\n3-Urun Satin al\n4-Cikis\nSecim Yapiniz:\n"); scanf("%d",&secim);
        }

        gun+=1;
    }



    return 0;
}




































