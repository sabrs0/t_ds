#include <stdio.h>
#include <stdlib.h>
int main()
{
    char teatrs[10][100] = {"Bolshoi", "Maliy", "Bulgakov's", "Vakhtangov's", "Lenkom", "Luna's", "Mayakovskiy's"};
    char spectacles[10][100] = { "Viy", "Master_and_Margaret", "Hamlet", "Shelkunshik", "Lebedinoe_ozero", "Otello", "12_Chairs" };
    char spectacles_for_children[7][100] = { "Dyuimovochka", "Peppy_dlinniychulok", "Zolushka", "Kashtanka", "Rusalochka" };
    char musical_specs[10][100] = { "Buratino", "Maugli", "Ognivo", "12_mesyacev", "Sinyaya_ptitsa", "Boris_Godunov", "Ruslan_i_Ludmila"};
    char rezhisor[11][100] = {"Yukhanov", "Didenko", "Rizhakov", "Serebrennikov", "Butusov", "Dodin", "Bogomolov", "Krimov", "Viripaev", "Zhenovach" };
    char composers[10][100] = { "Migulya", "Kobzon", "Ruslanova", "Visotskiy", "German", "Lemeshev", "Saulskiy" };
    int p_from;
    int p_to;
    int age_from;
    int age_to;
    int min_age;
    char child_types[7][100] = { "fairy_tale", "play", "musical" };
    char adult_types[7][100] = { "play", "drama", "comedy" };
    char countries [7][100] = { "Russia", "USA", "Britain", "France", "Austria" };
    int duration;
    FILE *f;
    f = fopen("out.txt", "w");
    int opredelitel = 0;
    int t_i;
    int sp_i;
    int sp_f_c_i;
    int r_i;
    int comp_i;
    int chil_i;
    int ad_i;
    int mus_i;
    int countr_i;
    int dur;

    for (int i = 0; i < 50; i ++)
    {
        t_i = 0 + rand() % (6 - 0 + 1);
        r_i = 0 + rand() % (9 - 0 + 1);
        p_from = 300 + rand() % (600 - 300 + 1);
        p_to = 2500 + rand() % (20000 - 2500 + 1);

        //fprintf(f,"\n\n%d.\n",i + 1 );

        if (opredelitel == 0)
        {
            min_age = 6 + rand() % (12 - 6 + 1);
            chil_i = 0 + rand() % (2 - 0 + 1);
            sp_f_c_i = 0 + rand() % (4 - 0 + 1);
            fprintf(f,"Childish\n");
            fprintf(f,"%s\n",teatrs[t_i]);
            fprintf(f,"%s\n",spectacles_for_children[sp_f_c_i] );
            fprintf(f,"%s\n", rezhisor[r_i]);
            fprintf(f,"%d\n",p_from);
            fprintf(f,"%d\n",p_to );
            fprintf(f,"%d\n",min_age );
            fprintf(f,"%s\n",child_types[chil_i]);

        }
        else if (opredelitel == 1)
        {
            sp_i = 0 + rand() % (6 - 0 + 1);
            ad_i = 0 + rand() % (2 - 0 + 1);
            fprintf(f, "Adult\n");
            fprintf(f,"%s\n",teatrs[t_i]);
            fprintf(f,"%s\n",spectacles[sp_i]);
            fprintf(f,"%s\n", rezhisor[r_i]);
            fprintf(f,"%d\n",p_from);
            fprintf(f,"%d\n",p_to );
            fprintf(f,"%s\n",adult_types[ad_i]);

        }
        else if (opredelitel == 2)
        {
            comp_i = 0 + rand() % (6 - 0 + 1);
            countr_i = 0 + rand() % (4 - 0 + 1);
            min_age = 6 + rand() % (12 - 6 + 1);
            duration = 60 + rand() % (180 - 60 + 1);
            mus_i = 0 + rand() % (6 - 0 + 1);
            fprintf(f, "Musical\n");
            fprintf(f,"%s\n",teatrs[t_i]);
            fprintf(f,"%s\n",musical_specs[mus_i]);
            fprintf(f,"%s\n", rezhisor[r_i]);
            fprintf(f,"%d\n",p_from);
            fprintf(f,"%d\n",p_to );
            fprintf(f,"%s\n",composers[comp_i]);
            fprintf(f,"%s\n",countries[countr_i]);
            fprintf(f,"%d\n",min_age );
            fprintf(f,"%d\n",duration);
        }
        opredelitel +=1;
        opredelitel = opredelitel % 3;

    }
    fclose(f);

}
