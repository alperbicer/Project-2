#include <stdio.h>
#include <stdlib.h>
#define STDMAX 10000
#define STDMIN 1
#define LCODEMAX 89
#define LCODEMIN 10
#define SMSTRMAX 8
#define SMSTRMIN 1
struct student
{
    int    student_number;
    char   name[31];
    int    grade;
    int    semester_credit;
    float  gpa;
    struct student *following_student;
};
struct note
{
    int    student_number;
    int    student_point;
    struct note *following_number;
    struct note *following_point;
    struct note *previous_point;
};
struct  lesson
{
    int    course_code;
    char   course_name[26];
    int    credit;
    int    student_counter;
    float  general_gpa;
    struct note *header;
};
int select_menu(void);
int take_number(int,int);
struct student *noya_gore_ara_dondur(struct student **top_list_ptr, int wanted_student_number);
void noya_gore_sirali_ekle(struct student **top_list_ptr, struct student *oneStudent,int hash);
void bir_dersi_ilkleme(struct lesson *top_list_ptr);
void nota_gore_d_cift_sirali_ekle(struct note *top_list_ptr, struct note *novice);
void noya_gore_d_tek_sirali_ekle(struct note *top_list_ptr, struct note *novice);
void note_dugumunden_cikar(struct note *old);
void no_dugumunden_cikar(struct note *top_list_ptr,struct note *old);
void noya_gore_cikar(struct student **top_list_ptr,struct student *old);
void doneme_gore_listele(struct lesson **first_ptr,int code);
struct note *noya_gore_noteda_ara(struct note **top_list_ptr, int wanted_student_number);
void derse_gore_note_listele(struct note **top_list_ptr,struct student **top_list_ptr_2);
void sinirin_ustune_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int limit);
void sinirin_altina_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int limit);
void ogrencinin_aldigi_dersleri_ara_listele(struct lesson **top_list_ptr,int number);
void bir_sinifta_okuyan_ogr_listele(struct student **top_list_ptr,int grade);
struct note *ders_dizisinde_ogrenci_bul_dondur(struct lesson **top_list_ptr,int number);
int main()
{
    int option,number,hash,i,code,variable,Note,grade;
    float avarage;
    char go_on;
    struct student *student_number_hash_table[100]= {NULL};
    struct lesson *lesson_pointer_array[90]= {NULL};
    struct note *header_list;
    struct note *oneNote;
    struct lesson *oneLesson;
    struct student *oneStudent;
    do
    {
        option=select_menu();
        switch(option)
        {
        case 1:

            printf("Ogrenci numarasini giriniz (1-10000):");
            number=take_number(STDMIN,STDMAX);
            hash=(number-1)/100+1;
            if(noya_gore_ara_dondur(&student_number_hash_table[hash],number)==NULL)
            {
                oneStudent=malloc(sizeof(struct student));
                oneStudent->student_number=number;
                printf("Ogrencinin adini giriniz:");
                fflush(stdin);
                gets(oneStudent->name);
                printf("Ogrencinin sinifini giriniz(1-4):");
                oneStudent->grade=take_number(1,4);
                oneStudent->semester_credit=0;
                oneStudent->gpa=0;
                noya_gore_sirali_ekle(&student_number_hash_table,oneStudent,hash);
            }
            else printf("Bu numaraya sahip ogrenci zaten var!\n");
            break;
        case 2:
            printf("Dersin donemini giriniz(1-8):");
            code=take_number(SMSTRMIN,SMSTRMAX);
            code=code*10;
            for(i=code; i<code+10; i++)
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
                    bir_dersi_ilkleme(oneLesson);
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
            code=take_number(LCODEMIN,LCODEMAX);
            if(lesson_pointer_array[code]!=NULL)
            {
                do
                {
                    printf("Ogrencinin numarasini giriniz(1-10000):");
                    number=take_number(STDMIN,STDMAX);
                    hash=(number-1)/100+1;
                    if((oneStudent=noya_gore_ara_dondur(&student_number_hash_table[hash],number))!=NULL)
                    {
                        oneNote=ders_dizisinde_ogrenci_bul_dondur(&lesson_pointer_array[code],number);
                        if(!oneNote)
                        {
                            printf("Ogrencinin notunu giriniz:");
                            scanf("%d",&Note);
                            oneNote=malloc(sizeof(struct note));
                            oneNote->student_number=number;
                            oneNote->student_point=Note;
                            lesson_pointer_array[code]->general_gpa=(float)(Note+lesson_pointer_array[code]->general_gpa*lesson_pointer_array[code]->student_counter)/(lesson_pointer_array[code]->student_counter+1);
                            lesson_pointer_array[code]->student_counter++;
                            variable=oneStudent->semester_credit;
                            oneStudent->semester_credit+=lesson_pointer_array[code]->credit;
                            if(oneStudent->semester_credit!=0)
                                oneStudent->gpa=(float)(oneStudent->gpa*variable+lesson_pointer_array[code]->credit*Note)/oneStudent->semester_credit;
                            header_list=lesson_pointer_array[code]->header;
                            nota_gore_d_cift_sirali_ekle(header_list,oneNote);
                            noya_gore_d_tek_sirali_ekle(header_list,oneNote);
                            printf("Ogrencinin bilgileri basari ile eklenmistir!\n");
                            printf("Bu derse kayitli baska bir ogrenci bilgisi girecek misiniz?<E/e--H/h: ");
                            fflush(stdin);
                            scanf(" %c",&go_on);
                        }
                        else
                        {
                            printf("Bu ogrenci bu dersi zaten aliyor\n");
                            printf("Bu derse kayitli baska bir ogrenci bilgisi girecek misiniz?<E/e--H/h: ");
                            fflush(stdin);
                            scanf(" %c",&go_on);
                        }
                    }
                    else printf("Boyle bir ogrenci kaydi bulunamadi!\n");
                }
                while(go_on=='e' || go_on=='E');
            }
            else printf("Boyle bir ders bulunamadi!\n");
            break;
        case 4:
            printf("Dersin kodunu giriniz(%d-%d):",LCODEMIN,LCODEMAX);
            code=take_number(LCODEMIN,LCODEMAX);
            if((oneLesson=lesson_pointer_array[code])!=NULL)
            {
                printf("Ogrencinin numarasini giriniz(%d-%d):",STDMIN,STDMAX);
                number=take_number(STDMIN,STDMAX);
                hash=(number-1)/100+1;
                if((oneStudent=noya_gore_ara_dondur(&student_number_hash_table[hash],number))!=NULL )
                {
                    oneNote=malloc(sizeof(struct note));
                    if((oneNote=noya_gore_noteda_ara(&oneLesson->header,number))!=NULL)
                    {
                        avarage=(float)lesson_pointer_array[code]->general_gpa*lesson_pointer_array[code]->student_counter-oneNote->student_point;
                        printf("Ogrencinin yeni notunu giriniz:");
                        scanf("%d",&Note);
                        if(oneStudent->semester_credit!=0)
                            oneStudent->gpa=(oneStudent->gpa*oneStudent->semester_credit-oneNote->student_point+Note)/oneStudent->semester_credit;
                        oneNote->student_point=Note;
                        note_dugumunden_cikar(oneNote);
                        nota_gore_d_cift_sirali_ekle(oneLesson->header,oneNote);
                        if(lesson_pointer_array[code]->student_counter!=0)
                            lesson_pointer_array[code]->general_gpa=(float)(Note+avarage)/(lesson_pointer_array[code]->student_counter);
                        printf("Tebrikler basariyla guncellediniz :) \n");
                    }
                    else printf("Bu ogrenci bu dersi almamistir!\n");
                }
                else printf("Boyle bir ogrencinin kaydi bulunamamistir!\n");
            }
            else printf("Boyle bir ders kaydi bulunamamistir!\n");
            break;
        case 5:
            printf("Ogrenci numarasini giriniz(%d-%d):",STDMIN,STDMAX);
            number=take_number(STDMIN,STDMAX);
            hash=(number-1)/100+1;
            if((oneStudent=noya_gore_ara_dondur(&student_number_hash_table[hash],number))!=NULL)
            {
                number=oneStudent->student_number;
                for(i=0; i<90; i++)
                {
                    if(lesson_pointer_array[i])
                    {
                        oneNote=malloc(sizeof(struct note));
                        oneNote=ders_dizisinde_ogrenci_bul_dondur(&lesson_pointer_array[i],number);
                        if(oneNote)
                        {
                            note_dugumunden_cikar(oneNote);
                            no_dugumunden_cikar(lesson_pointer_array[i]->header,oneNote);
                            lesson_pointer_array[i]->student_counter+=-1;
                            if(lesson_pointer_array[i]->student_counter!=0)
                                lesson_pointer_array[i]->general_gpa=(float)(lesson_pointer_array[i]->general_gpa*(lesson_pointer_array[i]->student_counter+1)-oneNote->student_point)/lesson_pointer_array[i]->student_counter;
                            else lesson_pointer_array[i]->general_gpa=0;
                            free(oneNote);
                        }
                    }
                }
                noya_gore_cikar(&student_number_hash_table[hash],oneStudent);
                free(oneStudent);
                printf("Basariyla ogrencinin kaydini sildiniz!\n");
            }
            else printf("Boyle bir ogrenci zaten yok :) \n");
            break;
        case 6:
            printf("Dersin kodunu giriniz(%d-%d):",LCODEMIN,LCODEMAX);
            code=take_number(LCODEMIN,LCODEMAX);
            if((oneLesson=lesson_pointer_array[code])!=NULL)
            {
                oneStudent=malloc(sizeof(struct student));
                oneNote=malloc(sizeof(struct note));
                printf("Ders Kodu  Ders Adi         Kredi  Ogrenci Say   Not Ort\n");
                printf("---------  ---------------  -----  -----------   -------\n");
                printf(" %-9d  %-16s  %-7d  %d  %12.2f\n",oneLesson->course_code,oneLesson->course_name,oneLesson->credit,oneLesson->student_counter,oneLesson->general_gpa);
                printf("Dersi Alan Ogrenciler:\n");
                derse_gore_note_listele(&lesson_pointer_array[code]->header,&student_number_hash_table);
            }
            else printf("Boyle bir ders kaydi bulunamadi :/ \n");
            break;
        case 7:
            printf("Ders kodunu giriniz(%d-%d):",LCODEMIN,LCODEMAX);
            code=take_number(LCODEMIN,LCODEMAX);
            if((oneLesson=lesson_pointer_array[code])!=NULL)
            {
                printf("Goruntulemek istediginiz alt siniri giriniz:");
                scanf("%d",&number);
                sinirin_ustune_gore_listele(&lesson_pointer_array[code]->header,&student_number_hash_table,number);
            }
            break;
        case 8:
            printf("Ders kodunu giriniz(%d-%d):",LCODEMIN,LCODEMAX);
            code=take_number(LCODEMIN,LCODEMAX);
            if((oneLesson=lesson_pointer_array[code])!=NULL)
            {
                printf("Goruntulemek istediginiz ust siniri giriniz:");
                scanf("%d",&number);
                sinirin_altina_gore_listele(&lesson_pointer_array[code]->header,&student_number_hash_table,number);
            }
            break;
        case 9:
            printf("Listelenecek derslerin donemini giriniz(%d-%d):",SMSTRMIN,SMSTRMAX);
            code=take_number(SMSTRMIN,SMSTRMAX);
            printf("Ders Kodu  Ders Adi         Kredi  Ogrenci Say   Not Ort\n");
            printf("---------  ---------------  -----  -----------   -------\n");
            doneme_gore_listele(&lesson_pointer_array,code);
            break;
        case 10:
            printf("Bilgilerini gormek istediginiz ogrencinin numarasini giriniz(%d-%d):",STDMIN,STDMAX);
            number=take_number(STDMIN,STDMAX);
            if((oneStudent=noya_gore_ara_dondur(&student_number_hash_table[hash],number))!=NULL)
            {
                printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                printf("---------  ---------------  ------  -----------   -------\n");
                printf(" %-9d  %-17s  %-8d  %d  %11.2f\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,oneStudent->semester_credit,oneStudent->gpa);
            }
            else printf("Boyle bir ogrencinin kaydi bulunamamistir!\n");
            break;
        case 11:
            printf("Ogrenci numarasini giriniz(%d-%d):",STDMIN,STDMAX);
            number=take_number(STDMIN,STDMAX);
            hash=(number-1)/100+1;
            if((oneStudent=noya_gore_ara_dondur(&student_number_hash_table[hash],number))!=NULL)
            {
                printf("Ogr No     Adi Soyadi       Sinifi   Kredi Say    Not Ort\n");
                printf("---------  ---------------  ------  -----------   -------\n");
                printf(" %-9d  %-17s  %-8d  %d  %11.2f\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,oneStudent->semester_credit,oneStudent->gpa);
                ogrencinin_aldigi_dersleri_ara_listele(&lesson_pointer_array,number);
            }
            else printf("Boyle bir ogrencinin kaydi bulunmamaktadir!\n");
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
    }
    while(option!=13);
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
    printf("       12. Bir sinifta okuyan ogrencileri listele \n");
    printf("       13. Cikis\n");
    printf("\n");
    do
    {
        printf("Seciminizi Giriniz:");
        scanf("%d",&select);
    }
    while(select<1 || select>13);
    return select;
}
int take_number(int lower_limit,int upper_limit)
{
    int number;
    do
    {
        scanf("%d",&number);
        if(number<lower_limit || number>upper_limit)
            printf("Yanlis deger girdiniz, tekrar giriniz:");
    }
    while(number<lower_limit || number>upper_limit);
    return number;
}
struct student *noya_gore_ara_dondur(struct student **top_list_ptr, int wanted_student_number)
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
        variable=variable->following_number;
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
        oneStudent=noya_gore_ara_dondur(&top_list_ptr_2[hash],number);
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
    }
    else
    {
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
void bir_dersi_ilkleme(struct lesson *top_list_ptr)
{
    top_list_ptr->general_gpa=0;
    top_list_ptr->student_counter=0;
    top_list_ptr->header=malloc(sizeof(struct note));
    top_list_ptr->header->student_number=-1;
    top_list_ptr->header->student_point=-1;
    top_list_ptr->header->following_number=top_list_ptr->header;
    top_list_ptr->header->following_point=top_list_ptr->header;
    top_list_ptr->header->previous_point=top_list_ptr->header;
}
void nota_gore_d_cift_sirali_ekle(struct note *top_list_ptr, struct note *novice)
{
    struct note *variable;
    variable=top_list_ptr->following_point;
    while (variable!=top_list_ptr && variable->student_point<novice->student_point)
        variable=variable->following_point;
    novice->following_point=variable;
    novice->previous_point=variable->previous_point;
    variable->previous_point->following_point=novice;
    variable->previous_point=novice;
}
void note_dugumunden_cikar(struct note *old)
{
    old->following_point->previous_point=old->previous_point;
    old->previous_point->following_point=old->following_point;
}
void no_dugumunden_cikar(struct note *top_list_ptr,struct note *old)
{
    struct note *variable;
    variable=top_list_ptr;
    while(variable->following_number->student_number==old->student_number)
        variable=variable->following_number;
    variable->following_number->following_number=old->following_number;
}
void noya_gore_cikar(struct student **top_list_ptr,struct student *old)
{
    struct student *variable;
    variable=*top_list_ptr;
    while(variable->following_student!=NULL && variable->following_student->student_number==old->student_number)
        variable=variable->following_student;
    if(variable->following_student!=NULL)
        variable->following_student->following_student=old->following_student;
    else *top_list_ptr=NULL;
}
void noya_gore_d_tek_sirali_ekle(struct note *top_list_ptr, struct note *novice)
{
    struct note *previous, *variable;
    previous=top_list_ptr;
    variable=top_list_ptr->following_number;
    while(variable!=top_list_ptr && variable->student_number<novice->student_number)
    {
        previous=variable;
        variable=variable->following_number;
    }
    novice->following_number=variable;
    previous->following_number=novice;
}
void doneme_gore_listele(struct lesson **first_ptr,int code)
{
    struct lesson *variable;
    int i,counter=0;
    for(i=code*10; i<(code*10)+10; i++)
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
void sinirin_ustune_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int limit)
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
        if (variable->student_point>limit)
        {
            number=variable->student_number;
            hash=(number-1)/100+1;
            oneStudent=noya_gore_ara_dondur(&top_list_ptr_2[hash],number);
            printf(" %-9d  %-16s  %-5d  %d\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,variable->student_point);
            counter++;
        }
        variable=variable->previous_point;;
    }
    printf("Notu %d nin ustunde olan ogrencilerin sayisi: %d",limit,counter);
    if(all_student!=0)
        printf("\nNotu %d nin ustunde olan ogrencilerin yuzdesi: %.2f",limit,(float)counter/all_student*100);
    else printf("\nSinifta ogrenci kalmadi!");

}
void sinirin_altina_gore_listele(struct note **top_list_ptr,struct student **top_list_ptr_2,int limit)
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
        if (variable->student_point<limit)
        {
            number=variable->student_number;
            hash=(number-1)/100+1;
            oneStudent=noya_gore_ara_dondur(&top_list_ptr_2[hash],number);
            printf(" %-9d  %-16s  %-5d  %d\n",oneStudent->student_number,oneStudent->name,oneStudent->grade,variable->student_point);
            counter++;
        }
        variable=variable->following_point;;
    }
    printf("Notu %d nin altinda olan ogrencilerin sayisi: %d",limit,counter);
    if(all_student!=0)
        printf("\nNotu %d nin altinda olan ogrencilerin yuzdesi: %.2f",limit,(float)counter/all_student*100);
    else printf("\nSinifta ogrenci kalmadi!");
}
void ogrencinin_aldigi_dersleri_ara_listele(struct lesson **top_list_ptr,int number)
{
    struct lesson *variable;
    struct note *variable2,*found;
    int i;
    for(i=10; i<=90; i++)
    {
        variable=top_list_ptr[i];
        if(variable)
        {
            variable2=variable->header;

            if((found=noya_gore_noteda_ara(&variable2,number))!=NULL)
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
    for(i=0; i<100; i++)
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
    if(gpa!=0)
        printf("\nYuzdesi: %.2f",(float)(c_gpa/gpa)*100);
    else printf("\nYuzdesi: %100");
}
struct note *ders_dizisinde_ogrenci_bul_dondur(struct lesson **top_list_ptr,int number)
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
