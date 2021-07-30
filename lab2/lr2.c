#include <stdio.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#define CHILD 0
#define ADULT 1
#define MUSIC 2
#define LIST_SIZE 50
struct repertuar
{
    char teatr_name[100];
    char spect_name[100];
    char rezh_name[100];
    int p_f;
    int p_t;
    int spect_type;
    struct{
                int min_age;
                char perf_type[12];
        } childish;
    struct{
                char perf_type[12];
        } adult;
    struct{
                char composer_name [100];
                char country[100];
                int min_age;
                int duration;
        } musical;
};
int word_len(char word[])
{
    int i = 0;
    while (word[i] != '\0')
    {
        i ++;
    }
    return i;
}
void assignation(char word1[], char word2[])
{
    int n = word_len(word2);
    for (int i = 0; i < n; i ++)
    {
        word1[i] = word2[i];
    }
    word1[n] = '\0';
}
int comparer(char word1[], char word2[])
{
    if (word_len(word1) != word_len(word2))
        return 0;
    for (int i = 0; i < word_len(word1); i ++)
    {
        if (word1[i] != word2[i])
            return 0;
    }
    return 1;
}
void printer(struct repertuar list1[], int list_size)
{
    for (int i = 0; i < list_size; i ++)
    {
        printf("%d.\n", i + 1);
        if (list1[i].spect_type == CHILD)
        {
            printf("Childish\n");
            printf("%s\n", list1[i].teatr_name);

            printf("%s\n",list1[i].spect_name);

            printf("%s\n", list1[i].rezh_name);

            printf("%d " ,list1[i].p_f);

            printf("%d\n" ,list1[i].p_t);

            printf("%d\n",list1[i].childish.min_age);

            printf("%s\n\n\n", list1[i].childish.perf_type);
        }
        else if (list1[i].spect_type == ADULT)
        {
            printf("Adult\n");

            printf("%s\n" ,list1[i].teatr_name);

            printf("%s\n",list1[i].spect_name);

            printf("%s\n", list1[i].rezh_name);

            printf("%d " ,list1[i].p_f);

            printf("%d\n" ,list1[i].p_t);

            printf("%s\n\n\n", list1[i].adult.perf_type);
        }
        else if (list1[i].spect_type == MUSIC)
        {
            printf("Musical\n");

            printf("%s\n" ,list1[i].teatr_name);

            printf("%s\n",list1[i].spect_name);

            printf("%s\n", list1[i].rezh_name);

            printf("%d " ,list1[i].p_f);

            printf("%d\n" ,list1[i].p_t);

            printf("%s\n",list1[i].musical.composer_name);

            printf("%s\n", list1[i].musical.country);

            printf("%d\n" ,list1[i].musical.min_age);

            printf("%d\n\n\n" ,list1[i].musical.duration);


        }
    }
}
void key_puziryok_by_price(struct repertuar list1[], int list_size)
{
    int price_array[list_size];
    int real_index[list_size];
    int tmp;
    clock_t fTimeStart,fTimeStop;
    for (int i = 0; i < list_size; i ++)
    {
        price_array[i] = list1[i].p_f;
        real_index[i] = i + 1;
    }
    fTimeStart = clock();
    for (int i = 0; i < list_size - 1; i ++ )
    {
        for (int j = 0; j < list_size - 1 - i; j ++)
        {
            if (price_array[j] > price_array[j + 1])
            {
                tmp = price_array[j];
                price_array[j] = price_array[j + 1];
                price_array[j  +1] = tmp;
                tmp = real_index[j];
                real_index[j] = real_index[j + 1];
                real_index[j  +1] = tmp;
            }
        }
    }
    fTimeStop = clock();/*/CLOCKS_PER_SEC;*/
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");
    printf("|CUR |REAL|SPECT_TYPE(C,A,M)   |TEATR_NAME          |SPECTACLE_NAME      |DIRECTOR_NAME       |PRICE(FROM,TO)      |\n");
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");


    for (int i = 0; i < list_size; i ++)
    {
        printf("|%4d|", i + 1);
        if (list1[real_index[i] - 1].spect_type == CHILD)
        {
            char str1[100] = "Childish";
            printf("%4d|", real_index[i]);
            printf("%20s|", str1);
            printf("%20s|", list1[real_index[i] - 1].teatr_name);

            printf("%20s|",list1[real_index[i] - 1].spect_name);

            printf("%20s|", list1[real_index[i] - 1].rezh_name);

            printf("%10d -" ,list1[real_index[i] - 1].p_f);

            printf("%8d|\n" ,list1[real_index[i] - 1].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[real_index[i] - 1].spect_type == ADULT)
        {
            char str2[100] = "Adult";
            printf("%4d|", real_index[i]);
            printf("%20s|", str2);
            printf("%20s|", list1[real_index[i] - 1].teatr_name);

            printf("%20s|",list1[real_index[i] - 1].spect_name);

            printf("%20s|", list1[real_index[i] - 1].rezh_name);

            printf("%10d -" ,list1[real_index[i] - 1].p_f);

            printf("%8d|\n" ,list1[real_index[i] - 1].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

       }
        else if (list1[real_index[i] - 1].spect_type == MUSIC)
        {
            char str3[100] = "Musical";
            printf("%4d|", real_index[i]);
            printf("%20s|", str3);
            printf("%20s|", list1[real_index[i] - 1].teatr_name);

            printf("%20s|",list1[real_index[i] - 1].spect_name);

            printf("%20s|", list1[real_index[i] - 1].rezh_name);

            printf("%10d -" ,list1[real_index[i] - 1].p_f);

            printf("%8d|\n" ,list1[real_index[i] - 1].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
    }
    double res_time = (double)((fTimeStop - fTimeStart)) / CLOCKS_PER_SEC;
    printf("\nReal time for sorting %f(s)\n", res_time);


}
void key_vstavka_by_price(struct repertuar list1[], int list_size)
{
    int price_array[list_size];
    int real_index[list_size];
    int tmp;
    int key1,key2,i, j;
    clock_t fTimeStart,fTimeStop;
    fTimeStart = clock();//CLOCKS_PER_SEC;*/
    for (int i = 0; i < list_size; i ++)
    {
        price_array[i] = list1[i].p_f;
        real_index[i] = i  + 1;
    }
    for (i = 0; i  < list_size; i ++)
    {
        j = i - 1;
        key1 = price_array[i];
        key2 = real_index[i];
        while (price_array[j] > key1 && j >= 0)
        {
            price_array[j + 1] = price_array[j];
            real_index[j + 1] = real_index[j];
            j -= 1;
        }
        price_array[j + 1] = key1;
        real_index[j  +1] = key2;
    }
    fTimeStop = clock();//CLOCKS_PER_SEC;*/
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");
    printf("|CUR |REAL|SPECT_TYPE(C,A,M)   |TEATR_NAME          |SPECTACLE_NAME      |DIRECTOR_NAME       |PRICE(FROM,TO)      |\n");
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");


    for (int i = 0; i < list_size; i ++)
    {
        printf("|%4d|", i + 1);
        if (list1[real_index[i] - 1].spect_type == CHILD)
        {
            char str1[100] = "Childish";
            printf("%4d|", real_index[i]);
            printf("%20s|", str1);
            printf("%20s|", list1[real_index[i] - 1].teatr_name);

            printf("%20s|",list1[real_index[i] - 1].spect_name);

            printf("%20s|", list1[real_index[i] - 1].rezh_name);

            printf("%10d -" ,list1[real_index[i] - 1].p_f);

            printf("%8d|\n" ,list1[real_index[i] - 1].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[real_index[i] - 1].spect_type == ADULT)
        {
            char str2[100] = "Adult";
            printf("%4d|", real_index[i]);
            printf("%20s|", str2);
            printf("%20s|", list1[real_index[i] - 1].teatr_name);

            printf("%20s|",list1[real_index[i] - 1].spect_name);

            printf("%20s|", list1[real_index[i] - 1].rezh_name);

            printf("%10d -" ,list1[real_index[i] - 1].p_f);

            printf("%8d|\n" ,list1[real_index[i] - 1].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[real_index[i] - 1].spect_type == MUSIC)
        {
            char str3[100] = "Musical";
            printf("%4d|", real_index[i]);
            printf("%20s|", str3);
            printf("%20s|", list1[real_index[i] - 1].teatr_name);

            printf("%20s|",list1[real_index[i] - 1].spect_name);

            printf("%20s|", list1[real_index[i] - 1].rezh_name);

            printf("%10d -" ,list1[real_index[i] - 1].p_f);

            printf("%8d|\n" ,list1[real_index[i] - 1].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
    }
    double res_time = (double)(fTimeStop-fTimeStart) / CLOCKS_PER_SEC;
    printf("\nReal time for sorting %f(s)\n", res_time);


}
void make_copy (struct repertuar list1[], struct repertuar list_copy[], int list_size)
{
    for (int i = 0; i < list_size; i ++)
    {
        if (list1[i].spect_type == CHILD)
        {
            assignation(list_copy[i].teatr_name, list1[i].teatr_name);

            assignation(list_copy[i].spect_name, list1[i].spect_name);

            assignation(list_copy[i].rezh_name, list1[i].rezh_name);

            list_copy[i].spect_type = list1[i].spect_type;

            list_copy[i].p_f = list1[i].p_f;

            list_copy[i].p_t = list1[i].p_t;

            list_copy[i].childish.min_age = list1[i].childish.min_age;

            assignation(list_copy[i].childish.perf_type, list1[i].childish.perf_type);
        }
        else if (list1[i].spect_type == ADULT)
        {
            list_copy[i].spect_type = list1[i].spect_type;

            assignation(list_copy[i].teatr_name, list1[i].teatr_name);

            assignation(list_copy[i].spect_name, list1[i].spect_name);

            assignation(list_copy[i].rezh_name, list1[i].rezh_name);

            list_copy[i].p_f = list1[i].p_f;

            list_copy[i].p_t = list1[i].p_t;

            assignation(list_copy[i].adult.perf_type, list1[i].adult.perf_type);
        }
        else if (list1[i].spect_type == MUSIC)
        {
            list_copy[i].spect_type = list1[i].spect_type;

            assignation(list_copy[i].teatr_name, list1[i].teatr_name);

            assignation(list_copy[i].spect_name, list1[i].spect_name);

            assignation(list_copy[i].rezh_name, list1[i].rezh_name);

            list_copy[i].p_f = list1[i].p_f;

            list_copy[i].p_t = list1[i].p_t;

            assignation(list_copy[i].musical.composer_name, list1[i].musical.composer_name);

             assignation(list_copy[i].musical.country, list1[i].musical.country);

             list_copy[i].musical.min_age = list1[i].musical.min_age;

             list_copy[i].musical.duration = list1[i].musical.duration;


        }
    }
}
void isx_puziryok_by_price(struct repertuar list1[], int list_size)
{
    int tmp;
    char tmp1 [100];
    int real_index[list_size];
    clock_t fTimeStart,fTimeStop;
    fTimeStart = clock();//CLOCKS_PER_SEC;*/
    for (int i = 0; i < list_size; i ++)
    {
        real_index[i] = i + 1;
    }
    for (int i = 0; i < list_size - 1; i ++ )
    {
        for (int j = 0; j < list_size - 1 - i; j ++)
        {
            if (list1[j].p_f > list1[j + 1].p_f)
            {
                tmp = list1[j].p_f;
                list1[j].p_f = list1[j + 1].p_f;
                list1[j  +1].p_f = tmp;

                tmp = list1[j].p_t;
                list1[j].p_t = list1[j + 1].p_t;
                list1[j  +1].p_t = tmp;

                assignation(tmp1, list1[j].teatr_name);
                assignation(list1[j].teatr_name, list1[j + 1].teatr_name);
                assignation(list1[j  +1].teatr_name, tmp1);

                assignation(tmp1, list1[j].rezh_name);
                assignation(list1[j].rezh_name, list1[j + 1].rezh_name);
                assignation(list1[j  +1].rezh_name, tmp1);

                assignation(tmp1, list1[j].spect_name);
                assignation(list1[j].spect_name, list1[j + 1].spect_name);
                assignation(list1[j  +1].spect_name, tmp1);

                tmp = list1[j].spect_type;
                list1[j].spect_type = list1[j + 1].spect_type;
                list1[j  +1].spect_type = tmp;

                tmp = real_index[j];
                real_index[j] = real_index[j + 1];
                real_index[j  +1] = tmp;
            }
        }
    }
    fTimeStop = clock();//CLOCKS_PER_SEC;*/
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");
    printf("|CUR |REAL|SPECT_TYPE(C,A,M)   |TEATR_NAME          |SPECTACLE_NAME      |DIRECTOR_NAME       |PRICE(FROM,TO)      |\n");
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");


    for (int i = 0; i < list_size; i ++)
    {
        printf("|%4d|", i + 1);
        if (list1[i].spect_type == CHILD)
        {
            char str1[100] = "Childish";
            printf("%4d|", real_index[i]);
            printf("%20s|", str1);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[i].spect_type == ADULT)
        {
            char str2[100] = "Adult";
            printf("%4d|", real_index[i]);
            printf("%20s|", str2);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[i].spect_type == MUSIC)
        {
            char str3[100] = "Musical";
            printf("%4d|", real_index[i]);
            printf("%20s|", str3);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
    }
    double res_time = (double)(fTimeStop-fTimeStart) / CLOCKS_PER_SEC;
    printf("\nReal time for sorting %f(s)\n", res_time);
}
void isx_vstavka_by_price(struct repertuar list1[], int list_size)
{
    int real_index[list_size];
    int tmp;
    int key1,key2,i, j;
    int key_p_f, key_p_t, key_spect_type;
    double used_time;
    char key_teatr[100], key_spect[100], key_rezh[100];
    char tmp1 [100];
    clock_t fTimeStart,fTimeStop;
    fTimeStart = clock()/* *1000*/;//CLOCKS_PER_SEC;*/
    for (int i = 0; i < list_size; i ++)
    {
        real_index[i] = i  + 1;
    }
    for (i = 0; i  < list_size; i ++)
    {
        j = i - 1;
        assignation(key_teatr, list1[i].teatr_name);
        assignation(key_spect, list1[i].spect_name);
        assignation(key_rezh, list1[i].rezh_name);

        key_p_f = list1[i].p_f;
        key_p_t = list1[i].p_t;
        key_spect_type = list1[i].spect_type;


        key2 = real_index[i];
        while (list1[j].p_f > key_p_f && j >= 0)
        {
            real_index[j + 1] = real_index[j];


                list1[j + 1].p_f = list1[j].p_f;

                list1[j  +1].p_t = list1[j].p_t;

                assignation(list1[j + 1].teatr_name, list1[j].teatr_name);

                assignation(list1[j  +1].rezh_name, list1[j].rezh_name);

                assignation(list1[j  +1].spect_name, list1[j].spect_name);

                list1[j  +1].spect_type = list1[j].spect_type;

            j -= 1;
        }
        list1[j + 1].p_f = key_p_f;

        list1[j  +1].p_t = key_p_t;

        assignation(list1[j + 1].teatr_name, key_teatr);

        assignation(list1[j  +1].rezh_name, key_rezh);

        assignation(list1[j  +1].spect_name, key_spect);

        list1[j  +1].spect_type = key_spect_type;

        real_index[j  +1] = key2;
    }
    fTimeStop = clock()/* *1000*/; //CLOCKS_PER_SEC;*/
 printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");
    printf("|CUR |REAL|SPECT_TYPE(C,A,M)   |TEATR_NAME          |SPECTACLE_NAME      |DIRECTOR_NAME       |PRICE(FROM,TO)      |\n");
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");


    for (int i = 0; i < list_size; i ++)
    {
        printf("|%4d|", i + 1);
        if (list1[i].spect_type == CHILD)
        {
            char str1[100] = "Childish";
            printf("%4d|", real_index[i]);
            printf("%20s|", str1);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[i].spect_type == ADULT)
        {
            char str2[100] = "Adult";
            printf("%4d|", real_index[i]);
            printf("%20s|", str2);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[i].spect_type == MUSIC)
        {
            char str3[100] = "Musical";
            printf("%4d|", real_index[i]);
            printf("%20s|", str3);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
    }
    double res_time = (double)(fTimeStop-fTimeStart) / CLOCKS_PER_SEC;
    printf("\nReal time for sorting %f(ms)\n", res_time);
}
void printer_for_info(struct repertuar list1[], int age_for_ans, int duration_for_ans, int list_size)
{
    int cur = 0;
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|----|----|\n");
    printf("|CUR.|REAL|SPECT_TYPE(C,A,M)   |TEATR_NAME          |SPECTACLE_NAME      |DIRECTOR_NAME       |PRICE(FROM,TO)      |AGE |DUR.|\n");
    printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|----|----|\n");


    for (int i = 0; i < list_size; i ++)
    {
        if (list1[i].spect_type == MUSIC)
        {
            if (list1[i].musical.min_age >= age_for_ans && list1[i].musical.duration < duration_for_ans)
            {
                char str3[100] = "Musical";
                printf("|%4d|", cur  + 1);
                cur ++;
                printf("%4d|", i + 1);
                printf("%20s|", str3);
                printf("%20s|", list1[i].teatr_name);

                printf("%20s|",list1[i].spect_name);

                printf("%20s|", list1[i].rezh_name);

                printf("%10d -" ,list1[i].p_f);

                printf("%8d|" ,list1[i].p_t);

                printf("%4d|" ,list1[i].musical.min_age);

                printf("%4d|\n" ,list1[i].musical.duration);

                printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|----|----|\n");
            }
        }
    }
}
void printer_table (struct repertuar list1[], int list_size)
{
    printf("|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");
    printf("|ID  |SPECT_TYPE(C,A,M)   |TEATR_NAME          |SPECTACLE_NAME      |DIRECTOR_NAME       |PRICE(FROM,TO)      |\n");
    printf("|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");


    for (int i = 0; i < list_size; i ++)
    {
        printf("|%4d|", i + 1);
        if (list1[i].spect_type == CHILD)
        {
            char str1[100] = "Childish";
            printf("%20s|", str1);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

        }
        else if (list1[i].spect_type == ADULT)
        {
            char str2[100] = "Adult";
            printf("%20s|", str2);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

            //printf("%s\n\n\n", list1[real_index[i]].adult.perf_type);
        }
        else if (list1[i].spect_type == MUSIC)
        {
            char str3[100] = "Musical";
            printf("%20s|", str3);
            printf("%20s|", list1[i].teatr_name);

            printf("%20s|",list1[i].spect_name);

            printf("%20s|", list1[i].rezh_name);

            printf("%10d -" ,list1[i].p_f);

            printf("%8d|\n" ,list1[i].p_t);

            printf("|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");

            /*printf("%s\n",list1[real_index[i]].musical.composer_name);

            printf("%s\n", list1[real_index[i]].musical.country);

            printf("%d\n" ,list1[real_index[i]].musical.min_age);

            printf("%d\n\n\n" ,list1[real_index[i]].musical.duration);*/
        }
    }
    //printf("|----|----|--------------------|--------------------|--------------------|--------------------|--------------------|\n");
}
int add_note(struct repertuar list1[], int list_size)
{
    int i;
    int spect_type;
    char teatrs[10][100] = {"Bolshoi", "Maliy", "Bulgakov's", "Vakhtangov's", "Lenkom", "Luna's", "Mayakovskiy's"};
    char spectacles[10][100] = { "Viy", "Master_and_Margaret", "Hamlet", "Shelkunshik", "Lebedinoe_ozero", "Otello", "12_Chairs" };
    char spectacles_for_children[7][100] = { "Dyuimovochka", "Peppy_dlinniychulok", "Zolushka", "Kashtanka", "Rusalochka" };
    char musical_specs[10][100] = { "Buratino", "Maugli", "Ognivo", "12_mesyacev", "Sinyaya_ptitsa", "Boris_Godunov", "Ruslan_i_Ludmila"};
    char rezhisor[11][100] = {"Yukhanov", "Didenko", "Rizhakov", "Serebrennikov", "Butusov", "Dodin", "Bogomolov", "Krimov", "Viripaev", "Zhenovach" };
    char composers[10][100] = { "Migulya", "Kobzon", "Ruslanova", "Visotskiy", "German", "Lemeshev", "Saulskiy" };
    char child_types[7][100] = { "fairy_tale", "play", "musical" };
    char adult_types[7][100] = { "play", "drama", "comedy" };
    char countries [7][100] = { "Russia", "USA", "Britain", "France", "Austria" };

    int teatr;
    int spectacle;
    int spectacle_for_child;
    int musical_spec;
    int rezhisorr;
    int composer;
    int child_type;
    int adult_type;
    int country;

    int p_from;
    int p_to;
    int min_age;
    int duration;
    int ret = 0;

    if (list_size >= LIST_SIZE + 100)
    {
        printf("ERROR:the table is full\n");
        return 1;
    }
    printf("Choose Theatre:\n");
    for (i = 0; i < 7; i ++)
    {
        printf("%d - %s\n", i + 1, teatrs[i]);
    }
    if (scanf("%d", &teatr) != 1 || teatr < 1 || teatr > 7)
    {
        printf("Incorrect input of the teatr_number\n");
        return 1;//ret = 1;
    }
    printf("Choose Producer:\n");
    for (i = 0; i < 7; i ++)
    {
        printf("%d - %s\n", i + 1, rezhisor[i]);
    }
    if (scanf("%d", &rezhisorr) != 1 || rezhisorr < 1 || rezhisorr > 10)
    {
        printf("Incorrect input of the Producer_number\n");
        return 1;//ret = 1;
    }
    printf("Input minimal price:\n");
    if (scanf("%d", &p_from) != 1 || p_from < 0)
    {
        printf("Incorrect input of the minimal price\n");
        return 1;//ret = 1;
    }
    printf("Input maximal price:\n");
    if (scanf("%d", &p_to) != 1 || p_to < 0)
    {
        printf("Incorrect input of the maximal price\n");
        return 1;//ret = 1;
    }
    if (p_from > p_to)
    {
        printf("Minimal price should be smaller than Maximal price\n");
        return 1;//ret = 1;
    }
    printf("Input type of spectacle:\n");
    printf("1 - Childish\n2 - Adult\n3 - Musical\n");
    if (scanf("%d", &spect_type) != 1 || spect_type < 1 || spect_type > 3)
    {
        printf("Incorrect input of the type of spectacle\n");
        return 1;//ret = 1;
    }
    if (spect_type == 1)
    {
        printf("Choose type of childish spectacle:\n");
        for (i = 0; i < 3; i ++)
        {
            printf("%d - %s\n", i + 1, child_types[i]);
        }
        if (scanf("%d", &child_type) != 1 || child_type < 1 || child_type > 3)
        {
            printf("Incorrect input of the type of childish spectacle\n");
            return 1;//ret = 1;
        }
        printf("Choose childish spectacle:\n");
        for (i = 0; i < 5; i ++)
        {
            printf("%d - %s\n", i + 1, spectacles_for_children[i]);
        }
        if (scanf("%d", &spectacle_for_child) != 1 || spectacle_for_child < 1 || spectacle_for_child > 5)
        {
            printf("Incorrect input of the childish spectacle\n");
            return 1;//ret = 1;
        }
        printf("Input age:\n");
        if (scanf("%d", &min_age) != 1 || min_age < 0)
        {
            printf("Incorrect input of the age\n");
            return 1;//ret = 1;
        }
        if (!ret)
        {
            assignation(list1[list_size - 1].teatr_name, teatrs[teatr - 1]);
            assignation(list1[list_size - 1].rezh_name, rezhisor[rezhisorr - 1]);
            assignation(list1[list_size - 1].childish.perf_type, child_types[child_type - 1]);
            assignation(list1[list_size - 1].spect_name, spectacles_for_children[spectacle_for_child - 1]);
            list1[list_size - 1].p_f = p_from;
            list1[list_size - 1].p_t = p_to;
            list1[list_size - 1].spect_type = spect_type - 1;
            list1[list_size - 1].childish.min_age = min_age;
            printf("Type: childish\nTheatre: %s\nDirector: %s\nSpec_type: %s\nSpec_name: %s\nPrice: %d - %d\nMin_age: %d\n",teatrs[teatr - 1], rezhisor[rezhisorr - 1], child_types[child_type - 1], spectacles_for_children[spectacle_for_child - 1], p_from, p_to, min_age);
        }
    }
    else if (spect_type == 2)
    {
        printf("Choose type of Adult spectacle:\n");
        for (i = 0; i < 3; i ++)
        {
            printf("%d - %s\n", i + 1, adult_types[i]);
        }
        if (scanf("%d", &adult_type) != 1 || adult_type < 1 || adult_type > 3)
        {
            printf("Incorrect input of the type of Adult spectacle\n");
            return 1;
        }
        printf("Choose Adult spectacle:\n");
        for (i = 0; i < 5; i ++)
        {
            printf("%d - %s\n", i + 1, spectacles[i]);
        }
        if (scanf("%d", &spectacle) != 1 || spectacle < 1 || spectacle > 7)
        {
            printf("Incorrect input of the Adult spectacle\n");
            ret = 1;
            return 1;
        }
        if (!ret)
        {
            assignation(list1[list_size - 1].teatr_name, teatrs[teatr - 1]);
            assignation(list1[list_size - 1].rezh_name, rezhisor[rezhisorr - 1]);
            assignation(list1[list_size - 1].adult.perf_type, adult_types[adult_type - 1]);
            assignation(list1[list_size - 1].spect_name, spectacles[spectacle - 1]);
            list1[list_size - 1].p_f = p_from;
            list1[list_size - 1].p_t = p_to;
            list1[list_size - 1].spect_type = spect_type - 1;
            printf("Type: adult\nTheatre: %s\nDirector: %s\nSpec_type: %s\nSpec_name: %s\nPrice: %d - %d",teatrs[teatr - 1], rezhisor[rezhisorr - 1], adult_types[adult_type - 1], spectacles[spectacle - 1], p_from, p_to);

        }

    }
    else if (spect_type == 3)
    {
        printf("Choose musical spectacle:\n");
        for (i = 0; i < 7; i ++)
        {
            printf("%d - %s\n", i + 1, musical_specs[i]);
        }
        if (scanf("%d", &musical_spec) != 1 || musical_spec < 1 || musical_spec > 7)
        {
            printf("Incorrect input of the musical spectacle\n");
            ret = 1;
            return 1;
        }
        printf("Input age:\n");
        if (scanf("%d", &min_age) != 1 || min_age < 0)
        {
            printf("Incorrect input of the age\n");
            ret = 1;
            return 1;
        }
        printf("Choose country:\n");
        for (i = 0; i < 5; i ++)
        {
            printf("%d - %s\n", i + 1, countries[i]);
        }
        if (scanf("%d", &country) != 1 || country < 1 || country > 5)
        {
            printf("Incorrect input of the musical spectacle\n");
            ret = 1;
            return 1;
        }
        printf("Choose composer:\n");
        for (i = 0; i < 7; i ++)
        {
            printf("%d - %s\n", i + 1, composers[i]);
        }
        if (scanf("%d", &composer) != 1 || composer < 1 || composer > 7)
        {
            printf("Incorrect input of the composer\n");
            ret = 1;
            return 1;
        }
        printf("Input Duration:\n");
        if (scanf("%d", &duration) != 1 || duration < 0)
        {
            printf("Incorrect input of the Duration\n");
            ret = 1;
            return 1;
        }
        if (!ret)
        {
            assignation(list1[list_size - 1].teatr_name, teatrs[teatr - 1]);
            assignation(list1[list_size - 1].rezh_name, rezhisor[rezhisorr - 1]);
            assignation(list1[list_size - 1].spect_name, musical_specs[musical_spec - 1]);
            list1[list_size - 1].p_f = p_from;
            list1[list_size - 1].p_t = p_to;
            list1[list_size - 1].spect_type = spect_type - 1;
            list1[list_size - 1].musical.min_age = min_age;
            assignation(list1[list_size - 1].musical.composer_name, composers[composer - 1]);
            assignation(list1[list_size - 1].musical.country, countries[country - 1]);
            list1[list_size - 1].musical.duration = duration;
            printf("Type: musical\nTheatre: %s\nDirector: %s\nSpec_name: %s\nPrice: %d - %d, Min age: %d\nComposer name: %s\nCountry: %s\n Duration: %d minutes\n",teatrs[teatr - 1], rezhisor[rezhisorr - 1], musical_specs[musical_spec - 1], p_from, p_to, min_age, composers[composer - 1], countries[country - 1], duration);

        }
    }
    return ret;
}
void delete_note (struct repertuar list1[], int list_size, int pos)
{
    for (int i = pos - 1; i < list_size - 1; i ++)
    {
        if (list1[i + 1].spect_type == CHILD)
        {
            list1[i].spect_type = CHILD;

            assignation(list1[i].teatr_name, list1[i + 1].teatr_name);

            assignation(list1[i].spect_name, list1[i + 1].spect_name);

            assignation(list1[i].rezh_name, list1[i + 1].rezh_name);

            list1[i].p_f = list1[i + 1].p_f;

            list1[i].p_t = list1[i + 1].p_t;

            list1[i].childish.min_age = list1[i + 1].childish.min_age;

            assignation(list1[i].childish.perf_type, list1[i + 1].childish.perf_type);
        }
        else if (list1[i + 1].spect_type == ADULT)
        {
            list1[i].spect_type = ADULT;

            assignation(list1[i].teatr_name, list1[i + 1].teatr_name);

            assignation(list1[i].spect_name, list1[i + 1].spect_name);

            assignation(list1[i].rezh_name, list1[i + 1].rezh_name);

            list1[i].p_f = list1[i + 1].p_f;

            list1[i].p_t = list1[i + 1].p_t;

            assignation(list1[i].adult.perf_type, list1[i + 1].adult.perf_type);
        }
        else if (list1[i + 1].spect_type == MUSIC)
        {
            list1[i].spect_type = MUSIC;

            assignation(list1[i].teatr_name, list1[i + 1].teatr_name);

            assignation(list1[i].spect_name, list1[i + 1].spect_name);

            assignation(list1[i].rezh_name, list1[i + 1].rezh_name);

            list1[i].p_f = list1[i + 1].p_f;

            list1[i].p_t = list1[i + 1].p_t;

            assignation(list1[i].musical.composer_name, list1[i + 1].musical.composer_name);

            assignation(list1[i].musical.country, list1[i + 1].musical.country);

            list1[i].musical.min_age = list1[i + 1].musical.min_age;

            list1[i].musical.duration = list1[i + 1].musical.duration;
        }
    }
}
void scanning_child(FILE *f, struct repertuar list1[], int i)
{
    char word[100];
    int moneyy;
            fscanf(f,"%s", &word);
            list1[i].spect_type = CHILD;

            fscanf(f,"%s", &word);
            strcpy(list1[i].teatr_name, word);//assignation(list1[i].teatr_name, word);

            fscanf(f,"%s", &word);
            strcpy(list1[i].spect_name, word);//assignation(list1[i].spect_name, word);

            fscanf(f,"%s", &word);
            strcpy(list1[i].rezh_name, word);//assignation(list1[i].rezh_name, word);

            fscanf(f,"%d", &moneyy);
            list1[i].p_f =  moneyy;

            fscanf(f,"%d", &moneyy);
            list1[i].p_t = moneyy;

            fscanf(f,"%d", &moneyy);
            list1[i].childish.min_age  = moneyy;

            fscanf(f,"%s", &word);
            strcpy(list1[i].childish.perf_type, word);//assignation(list1[i].childish.perf_type, word);
}
void scanning_adult(FILE *f, struct repertuar list1[], int i)
{
    int moneyy;
    char word[100];
            fscanf(f,"%s", &word);
            list1[i + 1].spect_type = ADULT;

            fscanf(f,"%s", &word);
            assignation(list1[i + 1].teatr_name, word);

            fscanf(f,"%s", &word);
            assignation(list1[i + 1].spect_name, word);

            fscanf(f,"%s", &word);
            assignation(list1[i + 1].rezh_name, word);

            fscanf(f,"%d", &moneyy);
            list1[i + 1].p_f = moneyy;

            fscanf(f,"%d", &moneyy);
            list1[i  +1].p_t = moneyy;

            fscanf(f,"%s", &word);
            assignation(list1[i + 1].adult.perf_type, word);
}
void scanning_musical(FILE *f, struct repertuar list1[], int i)
{
    char word[100];
    int moneyy;
            fscanf(f,"%s", &word);
            list1[i + 2].spect_type = MUSIC;

            fscanf(f,"%s", &word);
            assignation(list1[i + 2].teatr_name, word);

            fscanf(f,"%s", &word);
            assignation(list1[i + 2].spect_name, word);

            fscanf(f,"%s", &word);
            assignation(list1[i + 2].rezh_name, word);

            fscanf(f,"%d", &moneyy);
            list1[i + 2].p_f = moneyy;

            fscanf(f,"%d", &moneyy);
            list1[i + 2].p_t = moneyy;

            fscanf(f,"%s", &word);
            assignation(list1[i + 2].musical.composer_name, word);

            fscanf(f,"%s", &word);
            assignation(list1[i + 2].musical.country, word);

            fscanf(f,"%d", &moneyy);
            list1[i + 2].musical.min_age =  moneyy;

            fscanf(f,"%d", &moneyy);
            list1[i + 2].musical.duration = moneyy;
}
void scan_info(FILE *f, struct repertuar list1[], int list_size)
{
    if (list_size % 3 == 0)
    {
        for (int i = 0; i < list_size; i = i + 3)
        {
            scanning_child(f, list1, i);
            scanning_adult(f, list1, i);
            scanning_musical(f, list1, i);
        }
    }
    if (list_size % 3 == 1)
    {
        for (int i = 0; i < list_size - 1; i = i + 3)
        {
            scanning_child(f, list1, i);
            scanning_adult(f, list1, i);
            scanning_musical(f, list1, i);
        }
        scanning_child(f,list1,list_size - 1);
    }
    if (list_size % 3 == 2)
    {
        for (int i = 0; i < list_size - 2; i = i + 3)
        {
            scanning_child(f, list1, i);
            scanning_adult(f, list1, i);
            scanning_musical(f, list1, i);
        }
        scanning_child(f,list1,list_size - 2);
        scanning_adult(f,list1,list_size - 2);
    }
}
int main()
{
    struct repertuar list1[LIST_SIZE + 100], list_copy[LIST_SIZE + 100];
    FILE *f;
    /*char word[50];
    int moneyy;*/
    int age_for_ans;
    int duration_for_ans;
    int list_size = LIST_SIZE;
    f = fopen ("out.txt", "r");
    scan_info(f, list1, list_size);
    int choice;
    while (1)
    {
        printf("1 - show info\n");
        printf("2 - KEY_puziryok_sort_by_price\n");
        printf("3 - KEY_vstavka_sort_by_price\n");
        printf("4 - ISX_puziryok_sort_by_price\n");
        printf("5 - ISX_vstavka_sort_by_price\n");
        printf("6 - Print isx table \n");
        printf("7 - Print isx list \n");
        printf("8 - Add note\n");
        printf("9 - Delete note\n");
        printf("0 - Exit\n");
        if (scanf("%d", &choice) != 1 || choice < 0 || choice > 9)
        {
            printf("Incorrect input of the choice\n");
            //continue;//break;
            return 1;
        }
        if (choice == 1)
        {

            printf("Input age(6-12):");
            if (scanf("%d", &age_for_ans) != 1)
            {
                printf("Incorrect input of the age\n");
                //continue;//break;
                return 1;
            }
            else if ((age_for_ans < 6 || age_for_ans > 12))
            {
                printf("child age is from 6 to 12 years\n");
                //continue;//break;
                return 1;
            }
            printf("\nInput duration(60-180 minutes):");
            if (scanf("%d", &duration_for_ans) != 1)
            {
                printf("Incorrect input of the duration (minutes)\n");
                //continue;//break;
                return 1;
            }
            else if ((duration_for_ans < 60 || duration_for_ans > 180))
            {
                printf("Duration is from 60 to 180 minutes\n");
                //continue;//break;
                return 1;
            }
            printer_for_info(list1, age_for_ans, duration_for_ans, list_size);
        }
        else if (choice == 2)
        {
            key_puziryok_by_price(list1, list_size);
        }
        else if (choice == 3)
        {
            key_vstavka_by_price(list1, list_size);
        }
        else if (choice == 4)
        {
            make_copy(list1,list_copy, list_size);
            isx_puziryok_by_price(list_copy, list_size);
        }
        else if (choice == 5)
        {
            make_copy(list1, list_copy, list_size);
            isx_vstavka_by_price(list_copy, list_size);
        }
        else if (choice == 6)
        {
            printer_table(list1, list_size);
        }
        else if (choice == 7)
        {
            printer(list1, list_size);
        }
        else if (choice == 8)
        {
            list_size += 1;
            if (add_note(list1, list_size))
            {
                printf("Errors while add note\n");
                return 1;
                list_size -= 1;
            }
            else
            {
                printf("Note was added\n");
            }
        }
        else if (choice == 9)
        {
            int pos;
            printf("Input position:\n");

            if (scanf("%d", &pos) != 1 || pos < 1 || pos > list_size)
            {
                printf("Error while input position\n");
                return 1;    //continue;
            }
            else
            {
                delete_note(list1, list_size, pos);
                printf("Note was deleted\n");
                list_size --;
            }
        }
        else if (choice == 0)
       {
            printf("Exit of program\n");
            break;
       }
    }
    return 0;
}
