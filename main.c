#include <stdio.h>
#include <stdlib.h>
struct ogrenci {
    int    ogrenci_numarasi;
    char   isim[31];
    int    grade;
    int    donemlik_kredi;
    float  gpa;
    struct ogrenci *sonraki_ogrenci;
};
struct note {
    int    ogrenci_numarasi;
    int    ogrenci_point;
    struct note *following_number;
    struct note *following_point;
    struct note *previous_point;
};
struct  lesson {
    int    course_code;
    char   course_isim[26];
    int    credit;
    int    ogrenci_counter;
    float  general_gpa;
    struct note *dugum_basi;
};
int select_menu();
struct ogrenci *noya_gore_ara(struct ogrenci **liste_basi_ptr, int aranan_ogrenci_nosu);
void noya_gore_sirali_ekle(struct ogrenci **ogrenci_nosu_hash_tablosu, struct ogrenci *birOgrenci,int hash);
void isaretci_dizisine_ders_ekle(struct lesson **ilk_ptr,struct lesson *yeni);
void nota_gore_d_cift_sirali_ekle(struct note *liste_basi_ptr, struct note *yeni);
void noya_gore_d_tek_sirali_ekle(struct note *liste_basi_ptr, struct note *yeni);
struct note *note_dugumunden_cikar(struct note *eski);
struct note *no_dugumunden_cikar(struct note *liste_basi_ptr,struct note *eski);
void doneme_gore_listele(struct lesson **ilk_ptr,int code);
struct note *noya_gore_noteda_ara(struct note **liste_basi_ptr, int aranan_ogrenci_nosu);
void derse_gore_note_listele(struct note **liste_basi_ptr,struct ogrenci **liste_basi_ptr_2);
void koda_gore_ara_ve_listele(struct urun *ilk_ptr, char *aranan_urun_adi);
void sinirin_ustune_gore_listele(struct note **liste_basi_ptr,struct ogrenci **liste_basi_ptr_2,int sinir_miktari);
void sinirin_altina_gore_listele(struct note **liste_basi_ptr,struct ogrenci **liste_basi_ptr_2,int sinir_miktari);
void ogrencinin_aldigi_dersleri_ara(struct lesson **liste_basi_ptr,int number);
void bir_sinifta_okuyan_ogr_listele(struct ogrenci **liste_basi_ptr,int grade);
struct note *ders_dizisinde_ogrenci_bul_dondur(struct lesson **liste_basi_ptr,int number);
int main()
{
    int option,number,hash,i,code,variable,Note,grade;
    char devam;
    struct ogrenci *ogrenci_nosu_hash_tablosu[100]={NULL};
    struct lesson *ders_pointer_dizisi[90]={NULL};
    struct note *liste_basi;
    struct note *birNote;
    struct lesson *birDers;
    struct ogrenci *birOgrenci;


     do {
                printf("\n************** Alper Bicer'in Hazirladigi 2.Donemin 2.Projesidir **************\n\n");
                option=select_menu(); // menuden gelen secimi tutar
                switch(option) { // burdaki fonksiyonlarin hepsini prototiplerinin yaninda acikladim.
                    case 1:
                        printf("Ogrenci numarasini giriniz:");
                        scanf("%d",&number);
                        hash=(number-1)/100+1;
                        if(noya_gore_ara(&ogrenci_nosu_hash_tablosu[hash],number)==NULL)
                        {
                            birOgrenci=malloc(sizeof(struct ogrenci));
                            birOgrenci->ogrenci_numarasi=number;
                            printf("Ogrencinin adini giriniz:");
                            fflush(stdin);
                            scanf("%s",birOgrenci->isim);
                            printf("Ogrencinin sinifini giriniz:");
                            scanf("%d",&birOgrenci->grade);
                            birOgrenci->donemlik_kredi=0;
                            birOgrenci->gpa=0;
                            noya_gore_sirali_ekle(&ogrenci_nosu_hash_tablosu,birOgrenci,hash);
                        }
                        else printf("Bu numaraya sahip ogrenci zaten var!\n");
                        break;
                    case 2:
                        printf("Dersin donemini giriniz");
                        scanf("%d",&code);
                            code=code*10;
                            for(i=code;i<code+10;i++)
                            {
                                if(ders_pointer_dizisi[i]==NULL)
                                {
                                    birDers=malloc(sizeof(struct lesson));
                                    birDers->course_code=i;
                                    printf("Dersin kodu %d olarak belirlenmistir!\n",i);
                                    printf("Dersin adini giriniz:");
                                    fflush(stdin);
                                    scanf("%s",birDers->course_isim);
                                    printf("Dersin kredisini giriniz:");
                                    scanf("%d",&birDers->credit);
                                    birDers->general_gpa=0;
                                    birDers->ogrenci_counter=0;
                                    birDers->dugum_basi=malloc(sizeof(struct note));
                                    birDers->dugum_basi->ogrenci_numarasi=-1;
                                    birDers->dugum_basi->ogrenci_point=-1;
                                    birDers->dugum_basi->following_number=birDers->dugum_basi;
                                    birDers->dugum_basi->following_point=birDers->dugum_basi;
                                    birDers->dugum_basi->previous_point=birDers->dugum_basi;
                                    ders_pointer_dizisi[i]=birDers;
                                    printf("Ders basariyla eklendi\n");
                                    break;
                                }
                            }
                            if(i==code+10)
                                printf("Donemlik ders sayisi dolmustur\n");
                        break;
                    case 3:
                        printf("Ders kodunu giriniz:");
                        scanf("%d",&code);
                        if(ders_pointer_dizisi[code]!=NULL)
                        {
                            do
                            {
                            printf("Ogrencinin numarasini giriniz:");
                            scanf("%d",&number);
                            hash=(number-1)/100+1;
                            if(noya_gore_ara(&ogrenci_nosu_hash_tablosu[hash],number)!=NULL)
                            {
                                printf("Ogrencinin notunu giriniz:");
                                scanf("%d",&Note);
                                birNote=malloc(sizeof(struct note));
                                birNote->ogrenci_numarasi=number;
                                birNote->ogrenci_point=Note;
                                liste_basi=ders_pointer_dizisi[code]->dugum_basi;
                                nota_gore_d_cift_sirali_ekle(liste_basi,birNote);
                                noya_gore_d_tek_sirali_ekle(liste_basi,birNote);
                                printf("Ogrencinin bilgileri basari ile eklenmistir!\n");
                                printf("Bu derse kayitli baska bir ogrenci bilgisi girecek misiniz?<E/e--H/h: ");
                                fflush(stdin);
                                scanf(" %c",&devam);
                            }else printf("Boyle bir ogrenci kaydi bulunamadi!\n");
                            }while(devam=='e' || devam=='E');
                        }else printf("Boyle bir ders bulunamadi!\n");
                        break;
                    case 4:
                        printf("Dersin kodunu giriniz:");
                        scanf("%d",&code);
                        if((birDers=ders_pointer_dizisi[code])!=NULL)
                        {
                            printf("Ogrencinin numarasini giriniz:");
                            scanf("%d",&number);
                            hash=(number-1)/100+1;
                            if(noya_gore_ara(&ogrenci_nosu_hash_tablosu[hash],number)!=NULL )
                            {
                                birNote=malloc(sizeof(struct note));
                              if((birNote=noya_gore_noteda_ara(&birDers->dugum_basi,number))!=NULL)
                              {
                                printf("Ogrencinin yeni notunu giriniz:");
                                scanf("%d",&Note);
                                birNote->ogrenci_point=Note;
                                note_dugumunden_cikar(birNote);
                                nota_gore_d_cift_sirali_ekle(birDers->dugum_basi,birNote);
                                printf("Tebrikler basariyla guncellediniz :) \n");
                              }else printf("Bu ogrenci bu dersi almamistir!\n");
                            }else printf("Boyle bir ogrencinin kaydi bulunamamistir!\n");
                        }else printf("Boyle bir ders kaydi bulunamamistir!\n");
                        break;
                    case 5:
                        printf("Ogrenci numarasini giriniz:");
                        scanf("%d",&number);
                        hash=(number-1)/100+1;
                        if((birOgrenci=noya_gore_ara(&ogrenci_nosu_hash_tablosu[hash],number))!=NULL)
                        {
                            number=birOgrenci->ogrenci_numarasi;
                            for(i=0;i<90;i++)
                            {
                                if(ders_pointer_dizisi[i])
                                {
                                 birNote=ders_dizisinde_ogrenci_bul_dondur(&ders_pointer_dizisi[i],number);
                                 if(birNote)
                                 {
                                 birNote=note_dugumunden_cikar(birNote);
                                 birNote=no_dugumunden_cikar(&ders_pointer_dizisi[i]->dugum_basi,birNote);
                                 free(birNote);
                                 }
                                }
                            }
                        }else printf("Boyle bir ogrenci yok zaten :) \n");
                        break;
                    case 6:
                        printf("Dersin kodunu giriniz");
                        scanf("%d",&code);
                        if((birDers=ders_pointer_dizisi[code])!=NULL)
                        {
                        birOgrenci=malloc(sizeof(struct ogrenci));
                        birNote=malloc(sizeof(struct note));
                        printf("Ders Kodu  Ders Adi         Kredi Ogrenci Say   Not Ort\n");
                        printf("---------  ---------------  ----  -----------   -------\n");
                        printf("%-9d  %-15s  %-4d  %d  %.2f\n",birDers->course_code,birDers->course_isim,birDers->credit,birDers->ogrenci_counter,birDers->general_gpa);
                        printf("Dersi Alan Ogrenciler:\n");
                        derse_gore_note_listele(&ders_pointer_dizisi[code]->dugum_basi,&ogrenci_nosu_hash_tablosu);
                        }else printf("Boyle bir ders kaydi bulunamadi :/ \n");
                        break;
                    case 7:
                        printf("Ders kodunu giriniz:");
                        scanf("%d",&code);
                        if((birDers=ders_pointer_dizisi[code])!=NULL)
                        {
                        printf("Goruntulemek istediginiz alt siniri giriniz:");
                        scanf("%d",&number);
                        sinirin_ustune_gore_listele(&ders_pointer_dizisi[code]->dugum_basi,&ogrenci_nosu_hash_tablosu,number);
                        }
                        break;
                    case 8:
                        printf("Ders kodunu giriniz:");
                        scanf("%d",&code);
                        if((birDers=ders_pointer_dizisi[code])!=NULL)
                        {
                        printf("Goruntulemek istediginiz ust siniri giriniz:");
                        scanf("%d",&number);
                        sinirin_altina_gore_listele(&ders_pointer_dizisi[code]->dugum_basi,&ogrenci_nosu_hash_tablosu,number);
                        }
                        break;
                    case 9:
                        printf("Listelenecek derslerin donemini giriniz:");
                        scanf("%d",&code);
                        printf("Ders Kodu  Ders Adi         Kredi Ogrenci Say   Not Ort\n");
                        printf("---------  ---------------  ----  -----------   -------\n");
                        doneme_gore_listele(&ders_pointer_dizisi,code);

                        break;
                    case 10:
                        printf("Bilgilerini gormek istediginiz ogrencinin numarasini giriniz:");
                        scanf("%d",&number);
                        if((birOgrenci=noya_gore_ara(&ogrenci_nosu_hash_tablosu[hash],number))!=NULL)
                        {
                            printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                            printf("---------  ---------------  ------  -----------   -------\n");
                            printf("%-9d  %-15s  %-4d  %d  %.2f\n",birOgrenci->ogrenci_numarasi,birOgrenci->isim,birOgrenci->grade,birOgrenci->donemlik_kredi,birOgrenci->gpa);
                        }
                        else printf("Boyle bir ogrencinin kaydi bulunamamistir!\n");
                        break;
                    case 11:
                        printf("Ogrenci numarasini giriniz:");
                        scanf("%d",&number);
                        hash=(number-1)/100+1;
                        if((birOgrenci=noya_gore_ara(&ogrenci_nosu_hash_tablosu[hash],number))!=NULL)
                        {
                            printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                            printf("---------  ---------------  ------  -----------   -------\n");
                            printf("%-9d  %-15s  %-4d  %d  %.2f\n",birOgrenci->ogrenci_numarasi,birOgrenci->isim,birOgrenci->grade,birOgrenci->donemlik_kredi,birOgrenci->gpa);
                            ogrencinin_aldigi_dersleri_ara(&ders_pointer_dizisi,number);
                        }else printf("Boyle bir ogrencinin kaydi bulunmamaktadir!\n");
                        break;
                    case 12:
                        printf("Ogrencilerini gormek istediginiz sinifi <1-4> giriniz: ");
                        scanf("%d",&grade);
                        printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                        printf("---------  ---------------  ------  -----------   -------\n");
                        bir_sinifta_okuyan_ogr_listele(&ogrenci_nosu_hash_tablosu,grade);
                        break;
                    }
                    if(option==13)
                        printf("\n\nPROGRAM SONA ERDI\n\n");
                } while(option!=13);


        return 0;
}
int select_menu(void)
{
    int select;
    printf("\n");
    printf("       1.  Yeni bir ogrenci ekle\n");
    printf("       2.  Yeni bir ders ekle\n");
    printf("       3.  Bir dersi alan ogrencilerin notlarini ekle\n");
    printf("       4.  Bir dersin ogrencilerinin notunu guncelle\n");
    printf("       5.  Ogrenci kaydi sil\n");
    printf("       6.  Bir dersin bilgilerini ve kac ogrencinin aldigini listele\n");
    printf("       7.  Bir dersi alan ogrencilerden,belirli bir notun ustundekileri listele\n");
    printf("       8.  Bir dersi alan ogrencilerden,belirli bir notun altindakileri listele\n");
    printf("       9.  Bir donemin derslerini listele\n");
    printf("       10. Bir ogrencinin bilgilerini listele\n");
    printf("       11. Bir ogrencinin bilgilerini ve aldigi dersleri listele \n");
    printf("       12. Bir sinifta okuyan ogrencileri sil \n");
    printf("       13. Cikis\n");
    printf("\n");
    do {
        printf("Seciminizi Giriniz:");
        scanf("%d", &select);
    } while(select<1 || select>13);
    return select;
}
struct ogrenci *noya_gore_ara(struct ogrenci **liste_basi_ptr, int aranan_ogrenci_nosu)
{
    struct ogrenci *gecici;
    gecici=*liste_basi_ptr;
    while (gecici!=NULL && gecici->ogrenci_numarasi<=aranan_ogrenci_nosu)
    {
        if (gecici->ogrenci_numarasi==aranan_ogrenci_nosu)
        return gecici;
        gecici=gecici->sonraki_ogrenci;
    }

    return NULL;
}
struct note *noya_gore_noteda_ara(struct note **liste_basi_ptr, int aranan_ogrenci_nosu)
{
    struct note *gecici;
    gecici=*liste_basi_ptr;
    gecici=gecici->following_number;
    while (gecici!=gecici->following_number && gecici->ogrenci_numarasi<=aranan_ogrenci_nosu)
    {
        if (gecici->ogrenci_numarasi==aranan_ogrenci_nosu)
        return gecici;
        gecici=gecici->following_point;
    }

    return NULL;
}
void derse_gore_note_listele(struct note **liste_basi_ptr,struct ogrenci **liste_basi_ptr_2)
{
    struct note *gecici;
    struct ogrenci *birogrenci;
    int hash,number;
    gecici=*liste_basi_ptr;
   // birogrenci=*liste_basi_ptr_2[13];
   gecici=gecici->following_number;
   while(gecici!=*liste_basi_ptr)
   {
       number=gecici->ogrenci_numarasi;
       hash=(number-1)/100+1;
       birogrenci=noya_gore_ara(&liste_basi_ptr_2[hash],number);
       printf("  Ogr No       Ad Soyad     Kredi   Not \n");
       printf("---------  ---------------  ----  ------\n");
       printf("%-9d  %-15s  %-4d  %d\n",birogrenci->ogrenci_numarasi,birogrenci->isim,birogrenci->donemlik_kredi,gecici->ogrenci_point);
       gecici=gecici->following_number;
   }
}
void noya_gore_sirali_ekle(struct ogrenci **ogrenci_nosu_hash_tablosu, struct ogrenci *birOgrenci,int hash)
{
    struct ogrenci *onceki,*gecici;
    if(ogrenci_nosu_hash_tablosu[hash]==NULL)
    {
        birOgrenci->sonraki_ogrenci=NULL;
        ogrenci_nosu_hash_tablosu[hash]=birOgrenci;
    }
        else if(birOgrenci->ogrenci_numarasi<ogrenci_nosu_hash_tablosu[hash]->ogrenci_numarasi)
        {
            birOgrenci->sonraki_ogrenci=ogrenci_nosu_hash_tablosu[hash];
            ogrenci_nosu_hash_tablosu[hash]=birOgrenci;
        }else {
            onceki=ogrenci_nosu_hash_tablosu[hash];
                                gecici=ogrenci_nosu_hash_tablosu[hash]->sonraki_ogrenci;

                                 while (gecici!=NULL && gecici->ogrenci_numarasi<birOgrenci->ogrenci_numarasi)
                                 {
                                     onceki=gecici;
                                     gecici=gecici->sonraki_ogrenci;
                                 }
                                birOgrenci->sonraki_ogrenci=gecici;
                                onceki->sonraki_ogrenci=birOgrenci;
                             }

                            printf("Ogrenci basariyla eklendi\n");
}
void isaretci_dizisine_ders_ekle(struct lesson **ilk_ptr,struct lesson *yeni)
{
    yeni->dugum_basi=*ilk_ptr;
    *ilk_ptr=yeni;
}
void nota_gore_d_cift_sirali_ekle(struct note *liste_basi_ptr, struct note *yeni)
{
    struct note *gecici;
    gecici=liste_basi_ptr->following_point;
    while (gecici!=liste_basi_ptr && gecici->ogrenci_point<yeni->ogrenci_point)
        gecici=gecici->following_point;

    yeni->following_point=gecici;
    yeni->previous_point=gecici->previous_point;
    gecici->previous_point->following_point=yeni;
    gecici->previous_point=yeni;
}
struct note *note_dugumunden_cikar(struct note *eski)
{
    eski->following_point->previous_point=eski->previous_point;
    eski->previous_point->following_point=eski->following_point;
}
struct note *no_dugumunden_cikar(struct note *liste_basi_ptr,struct note *eski)
{
    struct note *gecici;
    gecici=liste_basi_ptr;
    while(gecici->following_number->ogrenci_numarasi==eski->ogrenci_numarasi)
        gecici=gecici->following_number;
    gecici->following_number->following_number=eski->following_number;
}
void noya_gore_d_tek_sirali_ekle(struct note *liste_basi_ptr, struct note *yeni)
{
    struct note *onceki, *gecici;

    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->following_number;
    while(gecici!=liste_basi_ptr && gecici->ogrenci_numarasi<yeni->ogrenci_numarasi)
    {
        onceki=gecici;
        gecici=gecici->following_number;
    }

    yeni->following_number=gecici;
    onceki->following_number=yeni;
}
void doneme_gore_listele(struct lesson **ilk_ptr,int code)
{
    struct lesson *gecici;
    int i;
    for(i=code*10;i<(code*10)+10;i++)
    {
        gecici=ilk_ptr[i];
        if(gecici!=NULL)
        printf("%-9d  %-15s  %-4d  %.2f\n",gecici->course_code,gecici->course_isim,gecici->credit,gecici->ogrenci_counter,gecici->general_gpa);
    }
    printf("Derserin kredi toplami %d");
}
void sinirin_ustune_gore_listele(struct note **liste_basi_ptr,struct ogrenci **liste_basi_ptr_2,int sinir_miktari)
{
    int i,number,hash;
    struct note *gecici;
    struct ogrenci *birogrenci;
    gecici=*liste_basi_ptr;
    gecici=gecici->previous_point;
    printf("  Ogr No       Ad Soyad     Kredi   Not \n");
    printf("---------  ---------------  ----  ------\n");
        while (gecici!=*liste_basi_ptr)
        {
            if (gecici->ogrenci_point>sinir_miktari)
            {
                number=gecici->ogrenci_numarasi;
                hash=(number-1)/100+1;
                birogrenci=noya_gore_ara(&liste_basi_ptr_2[hash],number);
                printf("%-9d  %-15s  %-4d  %d\n",birogrenci->ogrenci_numarasi,birogrenci->isim,birogrenci->donemlik_kredi,gecici->ogrenci_point);
            }

            gecici=gecici->previous_point;;
        }
}
void sinirin_altina_gore_listele(struct note **liste_basi_ptr,struct ogrenci **liste_basi_ptr_2,int sinir_miktari)
{
    int i,number,hash;
    struct note *gecici;
    struct ogrenci *birogrenci;
    gecici=*liste_basi_ptr;
    gecici=gecici->following_point;
    printf("  Ogr No       Ad Soyad     Kredi   Not \n");
    printf("---------  ---------------  ----  ------\n");
        while (gecici!=*liste_basi_ptr)
        {
            if (gecici->ogrenci_point<sinir_miktari)
            {
                number=gecici->ogrenci_numarasi;
                hash=(number-1)/100+1;
                birogrenci=noya_gore_ara(&liste_basi_ptr_2[hash],number);
                printf("%-9d  %-15s  %-4d  %d\n",birogrenci->ogrenci_numarasi,birogrenci->isim,birogrenci->donemlik_kredi,gecici->ogrenci_point);
            }

            gecici=gecici->following_point;;
        }
}
void ogrencinin_aldigi_dersleri_ara(struct lesson **liste_basi_ptr,int number)
{
    struct lesson *gecici;
    struct note *gecici2,*bulundu;
    int i;

    for(i=10;i<=90;i++)
    {
        gecici=liste_basi_ptr[i];
        if(gecici)
        {
        gecici2=gecici->dugum_basi;

        if((bulundu=noya_gore_noteda_ara(&gecici2,number))!=NULL)
        {
        printf("Ders Kodu  Ders Adi         Kredi Say   Not Ort\n");
        printf("---------  ---------------  ---------   -------\n");
        printf("%-9d  %-15s %-4d %.2f\n",gecici->course_code,gecici->course_isim,gecici->credit,gecici->general_gpa);
        }
        }
    }
}
void bir_sinifta_okuyan_ogr_listele(struct ogrenci **liste_basi_ptr,int grade)
{
    struct ogrenci *gecici;
    int i,counter=0,gpa=0,c_gpa=0;
    for(i=0;i<100;i++)
    {
        gecici=liste_basi_ptr[i];
        while(gecici)
        {
            if(gecici->grade==grade)
            {
                printf("%-9d  %-15s  %-4d  %d  %.2f\n",gecici->ogrenci_numarasi,gecici->isim,gecici->grade,gecici->donemlik_kredi,gecici->gpa);
                counter++;
                gpa+=gecici->gpa;
                if(gecici->gpa<60)
                    c_gpa++;
            }
            gecici=gecici->sonraki_ogrenci;
        }
    }
    printf("Sinifin ogrenci sayisi: %d",counter);
    printf("\nSinifin genel not ortalamasi: %d",gpa);
    printf("\nAgirlikli not ortalamasi 60’in altinda olan ogr sayisi: %d",c_gpa);
    printf("\nYuzdesi: %.2f",(float)(c_gpa/gpa)*100);
}
struct note *ders_dizisinde_ogrenci_bul_dondur(struct lesson **liste_basi_ptr,int number)
{
    struct lesson *gecici;
    struct note *gecici_not;
    int i;
        gecici=liste_basi_ptr[i];
        if(gecici)
        {
            while((gecici_not=gecici->dugum_basi))
            {
                if(gecici_not->ogrenci_numarasi==number)
                    return gecici_not;
                gecici_not=gecici_not->following_number;
            }return NULL;
        }else return NULL;
}


