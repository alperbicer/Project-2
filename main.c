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
    int    course_code;
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
    struct lesson *dugum_basi;
};
int select_menu();
struct student *noya_gore_ara(struct student *liste_basi_ptr, int aranan_student_nosu);
void noya_gore_sirali_ekle(struct student *liste_basi_ptr, struct student *yeni);
void isaretci_dizisine_ders_ekle(struct lesson **ilk_ptr,struct lesson *yeni);
int main()
{
    int option,number,hash,i,code,variable;
    struct student student_hash_table[1000];
    struct lesson *lesson_table[90];
    struct note list_head;
    struct note *oneNote;
    struct lesson *oneLesson;
    struct student *oneStudent;
    list_head.following_number=&list_head;
    list_head.following_point=&list_head;
    list_head.previous_point=&list_head;
    for(i=0;i<1000;i++)
        student_hash_table[i].following_student=&student_hash_table[i];
    for(i=0;i<90;i++)
        lesson_table[i]=-1;

    printf("%d",&lesson_table[17]->course_code);

     do {
                printf("\n************** Alper Bicer'in Hazirladigi 2.Donemin 2.Projesidir **************\n\n");
                option=select_menu(); // menuden gelen secimi tutar
                switch(option) { // burdaki fonksiyonlarin hepsini prototiplerinin yaninda acikladim.
                    case 1:
                        printf("Ogrenci numarasini giriniz\n");
                        scanf("%d",&number);
                        hash=number/100;
                        if(noya_gore_ara(&student_hash_table[hash],number)==NULL)
                        {
                            oneStudent=malloc(sizeof(struct student));
                            oneStudent->student_number=number;
                            printf("Ogrencinin adini giriniz:");
                            fflush(stdin);
                            scanf("%s",oneStudent->name);
                            printf("Ogrencinin sinifini giriniz:");
                            scanf("%d",&oneStudent->grade);
                            printf("Donemlik aldigi kredi sayisini giriniz:");
                            scanf("%d",&oneStudent->semester_credit);
                            printf("Donemlik agirlikli not ortalamasini giriniz:");
                            scanf("%d",&oneStudent->gpa);
                            noya_gore_sirali_ekle(&student_hash_table[hash],oneStudent);
                            printf("Ogrenci eklendi\n");
                        }
                        else
                            printf("Bu numaraya sahip ogrenci zaten var!\n");
                        break;
                    case 2:
                        printf("Dersin donemini giriniz\n");
                        scanf("%d",&code);
                            code=code*10;
                            for(i=code;i<code+10;i++)
                            {
                                if(lesson_table[i]==-1)
                                {
                                    oneLesson=malloc(sizeof(struct lesson));
                                    oneLesson->course_code=i;
                                    printf("Dersin adini giriniz:");
                                    fflush(stdin);
                                    scanf("%s",oneLesson->course_name);
                                    printf("Dersin kredisini giriniz:");
                                    scanf("%d",&oneLesson->credit);
                                    printf("Dersi alan ogrenci sayisini giriniz:");
                                    scanf("%d",&oneLesson->student_counter);
                                    printf("Dersin genel not ortalamasini giriniz:");
                                    scanf("%d",&oneLesson->general_gpa);
                                    isaretci_dizisine_ders_ekle(&lesson_table[i],oneLesson);
                                    printf("Ders basariyla eklendi\n");
                                    break;
                                }
                            }
                            if(i==code+10)
                                printf("Donemlik ders sayisi dolmustur\n");
                        break;
                    case 3:

                        break;
                    case 4:

                        break;
                    case 5:

                        break;
                    case 6:

                        break;
                    case 7:

                        break;
                    case 8:

                        break;
                    case 9:

                        break;
                    case 10:

                        break;
                    case 11:

                        break;
                    case 12:

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
struct student *noya_gore_ara(struct student *liste_basi_ptr, int aranan_student_nosu)//student listede bulunursa isaretcisi dondurulur, bulunamazsa NULL dondurulur
{
    struct student *gecici;

    gecici=liste_basi_ptr->following_student;
    while (gecici!=liste_basi_ptr && gecici->student_number<=aranan_student_nosu)
    {
        if (gecici->student_number==aranan_student_nosu) return gecici;
        gecici=gecici->following_student;
    }

    return NULL;
}
void noya_gore_sirali_ekle(struct student *liste_basi_ptr, struct student *yeni)
{
    struct student *onceki, *gecici;
    onceki=liste_basi_ptr;
    gecici=liste_basi_ptr->following_student;
    while(gecici!=liste_basi_ptr && gecici->student_number<yeni->student_number)
    {
        onceki=gecici;
        gecici=gecici->following_student;
    }

    yeni->following_student=gecici;
    onceki->following_student=yeni;
}
void isaretci_dizisine_ders_ekle(struct lesson **ilk_ptr,struct lesson *yeni)
{
    yeni->dugum_basi=*ilk_ptr;
    *ilk_ptr=yeni;
}
