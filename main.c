#include <stdio.h>
#include <stdlib.h>
struct student {
    int    student_number;
    char   name[31];
    int    grade;
    int    semester_credit;
    float  gpa;
    struct student *following_student;
};
struct note {
    int    student_number;
    int    student_point;
    struct note *following_number;
    struct note *following_point;
    struct note *previous_point;
};
struct  lesson {
    int    course_code;
    char   course_name[26];
    int    credit;
    int    student_counter;
    float  general_gpa;
    struct note *header;
};
int select_menu(void);
int take_number(int,int);
struct student *noya_gore_ara(struct student **top_list_ptr, int wanted_student_number);
void noya_gore_sirali_ekle(struct student **top_list_ptr, struct student *oneStudent,int hash);
void isaretci_dizisine_ders_ekle(struct lesson **first_ptr,struct lesson *new);
void nota_gore_d_cift_sirali_ekle(struct note *top_list_ptr, struct note *new);
void noya_gore_d_tek_sirali_ekle(struct note *top_list_ptr, struct note *new);
struct note *note_dugumunden_cikar(struct note *old);
struct note *no_dugumunden_cikar(struct note *top_list_ptr,struct note *old);
struct student *noya_gore_cikar(struct student **top_list_ptr,struct student *old);
void doneme_gore_listele(struct lesson **first_ptr,int code);
struct note *noya_gore_noteda_ara(struct note **top_list_ptr, int wanted_student_number);
void derse_gore_note_listele(struct note **top_list_ptr,struct student **top_list_ptr_2);
void sinirin_ustune_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int sinir_miktari);
void sinirin_altina_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int sinir_miktari);
void studentnin_aldigi_dersleri_ara(struct lesson **top_list_ptr,int number);
void bir_sinifta_okuyan_ogr_listele(struct student **top_list_ptr,int grade);
struct note *ders_dizisinde_student_bul_dondur(struct lesson **top_list_ptr,int number);
int main()
{
    int option,number,hash,i,code,variable,Note,grade;
    float avarage;
    char go_on;
    struct student *student_number_hash_table[100]={NULL};
    struct lesson *lesson_pointer_array[90]={NULL};
    struct note *header_list;
    struct note *birNote;
    struct lesson *oneLesson;
    struct student *oneStudent;


     do {
                printf("\n************** Alper Bicer'in Hazirladigi 2.Donemin 2.Projesidir **************\n\n");
                option=select_menu(); // menuden gelen secimi tutar
                switch(option) { // burdaki fonksiyonlarin hepsini prototiplerinin yaninda acikladim.
                    case 1:
                        printf("Ogrenci numarasini giriniz (1-10000):");
                        number=take_number(1,10000);
                        hash=(number-1)/100+1;
                        if(noya_gore_ara(&student_number_hash_table[hash],number)==NULL)
                        {
                            oneStudent=malloc(sizeof(struct student));
                            oneStudent->student_number=number;
                            printf("Ogrencinin adini giriniz:");
                            fflush(stdin);
                            gets(oneStudent->name);
                            printf("Ogrencinin sinifini giriniz:");
                            scanf("%d",&oneStudent->grade);
                            oneStudent->semester_credit=0;
                            oneStudent->gpa=0;
                            noya_gore_sirali_ekle(&student_number_hash_table,oneStudent,hash);
                        }
                        else printf("Bu numaraya sahip ogrenci zaten var!\n");
                        break;
                    case 2:
                        printf("Dersin donemini giriniz(1-8):");
                        code=take_number(1,8);
                            code=code*10;
                            for(i=code;i<code+10;i++)
                            {
                                if(lesson_pointer_array[i]==NULL)
                                {
                                    oneLesson=malloc(sizeof(struct lesson));
                                    oneLesson->course_code=i;
                                    printf("Dersin kodu %d olarak belirlenmistir!\n",i);
                                    printf("Dersin adini giriniz:");
                                    fflush(stdin);
                                    gets(oneLesson->course_name);
                                    printf("Dersin kredisini giriniz:");
                                    scanf("%d",&oneLesson->credit);
                                    oneLesson->general_gpa=0;
                                    oneLesson->student_counter=0;
                                    oneLesson->header=malloc(sizeof(struct note));
                                    oneLesson->header->student_number=-1;
                                    oneLesson->header->student_point=-1;
                                    oneLesson->header->following_number=oneLesson->header;
                                    oneLesson->header->following_point=oneLesson->header;
                                    oneLesson->header->previous_point=oneLesson->header;
                                    lesson_pointer_array[i]=oneLesson;
                                    printf("Ders basariyla eklendi\n");
                                    break;
                                }
                            }
                            if(i==code+10)
                                printf("Donemlik ders sayisi dolmustur\n");
                        break;
                    case 3:
                        printf("Ders kodunu giriniz(10-89):");
                        code=take_number(10,89);
                        if(lesson_pointer_array[code]!=NULL)
                        {
                            do
                            {
                            printf("Ogrencinin numarasini giriniz(1-10000):");
                            number=take_number(1,10000);
                            hash=(number-1)/100+1;
                            if((oneStudent=noya_gore_ara(&student_number_hash_table[hash],number))!=NULL)
                            {
                                printf("Ogrencinin notunu giriniz:");
                                scanf("%d",&Note);
                                birNote=malloc(sizeof(struct note));
                                birNote->student_number=number;
                                birNote->student_point=Note;
                                lesson_pointer_array[code]->general_gpa=(float)(Note+lesson_pointer_array[code]->general_gpa*lesson_pointer_array[code]->student_counter)/(lesson_pointer_array[code]->student_counter+1);
                                lesson_pointer_array[code]->student_counter++;
                                variable=oneStudent->semester_credit;
                                oneStudent->semester_credit+=lesson_pointer_array[code]->credit;
                                oneStudent->gpa=(float)(oneStudent->gpa*variable+lesson_pointer_array[code]->credit*Note)/oneStudent->semester_credit;
                                header_list=lesson_pointer_array[code]->header;
                                nota_gore_d_cift_sirali_ekle(header_list,birNote);
                                noya_gore_d_tek_sirali_ekle(header_list,birNote);
                                printf("Ogrencinin bilgileri basari ile eklenmistir!\n");
                                printf("Bu derse kayitli baska bir ogrenci bilgisi girecek misiniz?<E/e--H/h: ");
                                fflush(stdin);
                                scanf(" %c",&go_on);
                            }else printf("Boyle bir ogrenci kaydi bulunamadi!\n");
                            }while(go_on=='e' || go_on=='E');
                        }else printf("Boyle bir ders bulunamadi!\n");
                        break;
                    case 4:
                        printf("Dersin kodunu giriniz(10-89):");
                        code=take_number(10,89);
                        if((oneLesson=lesson_pointer_array[code])!=NULL)
                        {
                            printf("Ogrencinin numarasini giriniz(1-10000):");
                            number=take_number(1,10000);
                            hash=(number-1)/100+1;
                            if((oneStudent=noya_gore_ara(&student_number_hash_table[hash],number))!=NULL )
                            {
                                birNote=malloc(sizeof(struct note));
                              if((birNote=noya_gore_noteda_ara(&oneLesson->header,number))!=NULL)
                              {
                                avarage=(float)lesson_pointer_array[code]->general_gpa*lesson_pointer_array[code]->student_counter-birNote->student_point;
                                printf("Ogrencinin new notunu giriniz:");
                                scanf("%d",&Note);
                                oneStudent->gpa=(oneStudent->gpa*oneStudent->semester_credit-birNote->student_point+Note)/oneStudent->semester_credit;
                                birNote->student_point=Note;
                                birNote=note_dugumunden_cikar(birNote);
                                nota_gore_d_cift_sirali_ekle(oneLesson->header,birNote);
                                lesson_pointer_array[code]->general_gpa=(float)(Note+avarage)/(lesson_pointer_array[code]->student_counter);
                                printf("Tebrikler basariyla guncellediniz :) \n");
                              }else printf("Bu ogrenci bu dersi almamistir!\n");
                            }else printf("Boyle bir ogrencinin kaydi bulunamamistir!\n");
                        }else printf("Boyle bir ders kaydi bulunamamistir!\n");
                        break;
                    case 5:
                        printf("Ogrenci numarasini giriniz(1-10000):");
                        number=take_number(1,10000);
                        hash=(number-1)/100+1;
                        if((oneStudent=noya_gore_ara(&student_number_hash_table[hash],number))!=NULL)
                        {
                            number=oneStudent->student_number;
                            for(i=0;i<90;i++)
                            {
                                if(lesson_pointer_array[i])
                                {
                                 birNote=malloc(sizeof(struct note));
                                 birNote=ders_dizisinde_student_bul_dondur(&lesson_pointer_array[i],number);
                                 if(birNote)
                                 {
                                 birNote=note_dugumunden_cikar(birNote);
                                 birNote=no_dugumunden_cikar(lesson_pointer_array[i]->header,birNote);
                                 lesson_pointer_array[i]->student_counter+=-1;
                                 if(lesson_pointer_array[i]->student_counter!=0)
                                 lesson_pointer_array[i]->general_gpa=(float)(lesson_pointer_array[i]->general_gpa*(lesson_pointer_array[i]->student_counter+1)-birNote->student_point)/lesson_pointer_array[i]->student_counter;
                                 else lesson_pointer_array[i]->general_gpa=0;
                                 free(birNote);
                                 }
                                }
                            }
                            oneStudent=noya_gore_cikar(&student_number_hash_table[hash],oneStudent);
                            free(oneStudent);
                            printf("Basariyla ogrencinin kaydini sildiniz!\n");
                        }else printf("Boyle bir ogrenci yok zaten :) \n");
                        break;
                    case 6:
                        printf("Dersin kodunu giriniz(10-89):");
                        code=take_number(10,89);
                        if((oneLesson=lesson_pointer_array[code])!=NULL)
                        {
                        oneStudent=malloc(sizeof(struct student));
                        birNote=malloc(sizeof(struct note));
                        printf("Ders Kodu  Ders Adi         Kredi  Ogrenci Say   Not Ort\n");
                        printf("---------  ---------------  -----  -----------   -------\n");
                        printf(" %-9d  %-16s  %-7d  %d  %12.2f\n",oneLesson->course_code,oneLesson->course_name,oneLesson->credit,oneLesson->student_counter,oneLesson->general_gpa);
                        printf("Dersi Alan Ogrenciler:\n");
                        derse_gore_note_listele(&lesson_pointer_array[code]->header,&student_number_hash_table);
                        }else printf("Boyle bir ders kaydi bulunamadi :/ \n");
                        break;
                    case 7:
                        printf("Ders kodunu giriniz(10-89):");
                        code=take_number(10,89);
                        if((oneLesson=lesson_pointer_array[code])!=NULL)
                        {
                        printf("Goruntulemek istediginiz alt siniri giriniz:");
                        scanf("%d",&number);
                        sinirin_ustune_gore_listele(&lesson_pointer_array[code]->header,&student_number_hash_table,number);
                        }
                        break;
                    case 8:
                        printf("Ders kodunu giriniz(10-89):");
                        code=take_number(10,89);
                        if((oneLesson=lesson_pointer_array[code])!=NULL)
                        {
                        printf("Goruntulemek istediginiz ust siniri giriniz:");
                        scanf("%d",&number);
                        sinirin_altina_gore_listele(&lesson_pointer_array[code]->header,&student_number_hash_table,number);
                        }
                        break;
                    case 9:
                        printf("Listelenecek derslerin donemini giriniz(1-8):");
                        code=take_number(1,8);
                        printf("Ders Kodu  Ders Adi         Kredi  Ogrenci Say   Not Ort\n");
                        printf("---------  ---------------  -----  -----------   -------\n");
                        doneme_gore_listele(&lesson_pointer_array,code);

                        break;
                    case 10:
                        printf("Bilgilerini gormek istediginiz ogrencinin numarasini giriniz(1-10000):");
                        number=take_number(1,10000);
                        if((oneStudent=noya_gore_ara(&student_number_hash_table[hash],number))!=NULL)
                        {
                            printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                            printf("---------  ---------------  ------  -----------   -------\n");
                            printf(" %-9d  %-17s  %-8d  %d  %11.2f\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,oneStudent->semester_credit,oneStudent->gpa);
                        }
                        else printf("Boyle bir ogrencinin kaydi bulunamamistir!\n");
                        break;
                    case 11:
                        printf("Ogrenci numarasini giriniz(1-10000):");
                        number=take_number(1,10000);
                        hash=(number-1)/100+1;
                        if((oneStudent=noya_gore_ara(&student_number_hash_table[hash],number))!=NULL)
                        {
                            printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                            printf("---------  ---------------  ------  -----------   -------\n");
                            printf(" %-9d  %-17s  %-8d  %d  %11.2f\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,oneStudent->semester_credit,oneStudent->gpa);
                            studentnin_aldigi_dersleri_ara(&lesson_pointer_array,number);
                        }else printf("Boyle bir ogrencinin kaydi bulunmamaktadir!\n");
                        break;
                    case 12:
                        printf("Ogrencilerini gormek istediginiz sinifi (1-4) giriniz: ");
                        grade=take_number(1,4);
                        printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                        printf("---------  ---------------  ------  -----------   -------\n");
                        bir_sinifta_okuyan_ogr_listele(&student_number_hash_table,grade);
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
int take_number(int alt_sinir,int ust_sinir)  // klasik numara alma fonksiyonu
{
    int sayi;
    do
    {
        scanf("%d",&sayi);
        if(sayi<alt_sinir || sayi>ust_sinir)
            printf("Yanlis deger girdiniz, tekrar giriniz:");
    }while(sayi<alt_sinir || sayi>ust_sinir);
    return sayi;
}
struct student *noya_gore_ara(struct student **top_list_ptr, int wanted_student_number)
{
    struct student *variable;
    variable=*top_list_ptr;
    while (variable!=NULL && variable->student_number<=wanted_student_number)
    {
        if (variable->student_number==wanted_student_number)
        return variable;
        variable=variable->following_student;
    }

    return NULL;
}
struct note *noya_gore_noteda_ara(struct note **top_list_ptr, int wanted_student_number)
{
    struct note *variable;
    variable=*top_list_ptr;
    variable=variable->following_number;
    while (variable!=variable->following_number && variable->student_number<=wanted_student_number)
    {
        if (variable->student_number==wanted_student_number)
        return variable;
        variable=variable->following_point;
    }

    return NULL;
}
void derse_gore_note_listele(struct note **top_list_ptr,struct student **top_list_ptr_2)
{
    struct note *variable;
    struct student *oneStudent;
    int hash,number;
    variable=*top_list_ptr;
   variable=variable->following_number;
   while(variable!=*top_list_ptr)
   {
       number=variable->student_number;
       hash=(number-1)/100+1;
       oneStudent=noya_gore_ara(&top_list_ptr_2[hash],number);
       printf("  Ogr No       Ad Soyad     Sinif   Not \n");
       printf("---------  ---------------  -----  ------\n");
       printf(" %-9d  %-16s  %-5d  %d\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,variable->student_point);
       variable=variable->following_number;
   }
}
void noya_gore_sirali_ekle(struct student **top_list_ptr, struct student *oneStudent,int hash)
{
    struct student *previous,*variable;
    if(top_list_ptr[hash]==NULL)
    {
        oneStudent->following_student=NULL;
        top_list_ptr[hash]=oneStudent;
    }
        else if(oneStudent->student_number<top_list_ptr[hash]->student_number)
        {
            oneStudent->following_student=top_list_ptr[hash];
            top_list_ptr[hash]=oneStudent;
        }else {
            previous=top_list_ptr[hash];
                                variable=top_list_ptr[hash]->following_student;

                                 while (variable!=NULL && variable->student_number<oneStudent->student_number)
                                 {
                                     previous=variable;
                                     variable=variable->following_student;
                                 }
                                oneStudent->following_student=variable;
                                previous->following_student=oneStudent;
                             }

                            printf("Ogrenci basariyla eklendi\n");
}
void isaretci_dizisine_ders_ekle(struct lesson **first_ptr,struct lesson *new)
{
    new->header=*first_ptr;
    *first_ptr=new;
}
void nota_gore_d_cift_sirali_ekle(struct note *top_list_ptr, struct note *new)
{
    struct note *variable;
    variable=top_list_ptr->following_point;
    while (variable!=top_list_ptr && variable->student_point<new->student_point)
        variable=variable->following_point;

    new->following_point=variable;
    new->previous_point=variable->previous_point;
    variable->previous_point->following_point=new;
    variable->previous_point=new;
}
struct note *note_dugumunden_cikar(struct note *old)
{
    old->following_point->previous_point=old->previous_point;
    old->previous_point->following_point=old->following_point;
    return old;
}
struct note *no_dugumunden_cikar(struct note *top_list_ptr,struct note *old)
{
    struct note *variable;
    variable=top_list_ptr;
    while(variable->following_number->student_number==old->student_number)
        variable=variable->following_number;
    variable->following_number->following_number=old->following_number;
    return old;
}
struct student *noya_gore_cikar(struct student **top_list_ptr,struct student *old)
{
    struct student *variable;
    variable=*top_list_ptr;
    while(variable->following_student!=NULL && variable->following_student->student_number==old->student_number)
        variable=variable->following_student;
    if(variable->following_student!=NULL)
        variable->following_student->following_student=old->following_student;
    else *top_list_ptr=NULL;
    return old;
}
void noya_gore_d_tek_sirali_ekle(struct note *top_list_ptr, struct note *new)
{
    struct note *previous, *variable;

    previous=top_list_ptr;
    variable=top_list_ptr->following_number;
    while(variable!=top_list_ptr && variable->student_number<new->student_number)
    {
        previous=variable;
        variable=variable->following_number;
    }

    new->following_number=variable;
    previous->following_number=new;
}
void doneme_gore_listele(struct lesson **first_ptr,int code)
{
    struct lesson *variable;
    int i,counter=0;
    for(i=code*10;i<(code*10)+10;i++)
    {
        variable=first_ptr[i];
        if(variable!=NULL)
        {
        printf(" %-9d  %-16s  %-7d  %d  %12.2f\n",variable->course_code,variable->course_name,variable->credit,variable->student_counter,variable->general_gpa);
        counter+=variable->credit;
        }

    }
    printf("Derslerin kredi toplami %d",counter);
}
void sinirin_ustune_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int sinir_miktari)
{
    int number,hash,counter=0,all_student=0;
    struct note *variable;
    struct student *oneStudent;
    variable=*top_list_ptr;
    variable=variable->previous_point;
       printf("  Ogr No       Ad Soyad     Kredi   Not \n");
       printf("---------  ---------------  -----  ------\n");
        while (variable!=*top_list_ptr)
        {
            all_student++;
            if (variable->student_point>sinir_miktari)
            {
                number=variable->student_number;
                hash=(number-1)/100+1;
                oneStudent=noya_gore_ara(&top_list_ptr_2[hash],number);
                printf(" %-9d  %-16s  %-5d  %d\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,variable->student_point);
                counter++;
            }
            variable=variable->previous_point;;
        }
    printf("Notu %d nin ustunde olan ogrencilerin sayisi: %d",sinir_miktari,counter);
    if(all_student!=0)
    printf("\nNotu %d nin ustunde olan ogrencilerin yuzdesi: %.2f",sinir_miktari,(float)counter/all_student*100);
    else printf("\nSinifta ogrenci kalmadi!");

}
void sinirin_altina_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int sinir_miktari)
{
    int number,hash,counter=0,all_student=0;
    struct note *variable;
    struct student *oneStudent;
    variable=*top_list_ptr;
    variable=variable->following_point;
       printf("  Ogr No       Ad Soyad     Kredi   Not \n");
       printf("---------  ---------------  -----  ------\n");
        while (variable!=*top_list_ptr)
        {
            all_student++;
            if (variable->student_point<sinir_miktari)
            {
                number=variable->student_number;
                hash=(number-1)/100+1;
                oneStudent=noya_gore_ara(&top_list_ptr_2[hash],number);
                printf(" %-9d  %-16s  %-5d  %d\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,variable->student_point);
                counter++;
            }
            variable=variable->following_point;;
        }
    printf("Notu %d nin altinda olan ogrencilerin sayisi: %d",sinir_miktari,counter);
    if(all_student!=0)
    printf("\nNotu %d nin altinda olan ogrencilerin yuzdesi: %.2f",sinir_miktari,(float)counter/all_student*100);
    else printf("\nSinifta ogrenci kalmadi!");
}
void studentnin_aldigi_dersleri_ara(struct lesson **top_list_ptr,int number)
{
    struct lesson *variable;
    struct note *variable2,*bulundu;
    int i;

    for(i=10;i<=90;i++)
    {
        variable=top_list_ptr[i];
        if(variable)
        {
        variable2=variable->header;

        if((bulundu=noya_gore_noteda_ara(&variable2,number))!=NULL)
        {
        printf("Ders Kodu  Ders Adi         Kredi Say   Not Ort\n");
        printf("---------  ---------------  ---------   -------\n");
        printf(" %-9d  %-18s %-9d %.2f\n",variable->course_code,variable->course_name,variable->credit,variable->general_gpa);
        }
        }
    }
}
void bir_sinifta_okuyan_ogr_listele(struct student **top_list_ptr,int grade)
{
    struct student *variable;
    int i,counter=0,gpa=0,c_gpa=0;
    for(i=0;i<100;i++)
    {
        variable=top_list_ptr[i];
        while(variable)
        {
            if(variable->grade==grade)
            {
                printf(" %-9d  %-17s  %-8d  %d  %11.2f\n",variable->student_number,variable->name,variable->grade,variable->semester_credit,variable->gpa);
                counter++;
                gpa+=variable->gpa;
                if(variable->gpa<60)
                    c_gpa++;
            }
            variable=variable->following_student;
        }
    }
    printf("Sinifin ogrenci sayisi: %d",counter);
    printf("\nSinifin genel not ortalamasi: %d",gpa);
    printf("\nAgirlikli not ortalamasi 60 ' in altinda olan ogr sayisi: %d",c_gpa);
    printf("\nYuzdesi: %.2f",(float)(c_gpa/gpa)*100);
}
struct note *ders_dizisinde_student_bul_dondur(struct lesson **top_list_ptr,int number)
{
    struct lesson *variable;
    struct note *variable_note,*following_note;
    variable=*top_list_ptr;
        variable_note=variable->header;
        following_note=variable_note->following_number;
            while(following_note!=NULL && variable_note!=following_note)
            {
                if(following_note->student_number==number)
                    return following_note;
                following_note=following_note->following_number;
            }

    if(variable_note==following_note)
       return NULL;
}


