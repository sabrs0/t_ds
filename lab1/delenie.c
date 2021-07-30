#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int number_input(char c_arr2[], int leng, int *exp_len, int expon[],int *sign_float ,int *sign_exp, int arr2[],int * point_index, int *m,int * mant_len)
{
    int i;
    int ret = 0;
    int mant_sign_checker = 0;
    int exp_sign_checker = 0;
    int point_checker = 0;
    int exp_checker = 0;
    int exp_place = 0;
    if (c_arr2[0] == '+' || c_arr2[0] >= '0' && c_arr2[0]<= '9')
    {
        *sign_float = 1;
    }
    else if (c_arr2[0] == '-')
        *sign_float = -1;
    else
        {
            printf("ERROR:Incorrect first symbol\n");
            return 1;
        }
    for (i = 0; i < leng; i ++)
    {
        if (c_arr2[i]!= 'E' && c_arr2[i]!= '+' && c_arr2[i]!= '-' && c_arr2[i]!= '.' && (c_arr2[i] < '0' || c_arr2[i]>'9'))
        {
            printf("ERROR:Incorrect symbols in string\n");
            return 1;
        }
    }
    for (i = 0; i < leng;  i++)
    {
        if (c_arr2[i] == '+' || c_arr2[i] == '-')
        {
            if (i != 0 && (c_arr2[i - 1] != 'E') )
        {
            printf("3ERROR:Incorrect input of number: no sign after E\n");
            return 1;
        }
        }
    }
    for (i = 0; i < leng;  i++)
    {
        if (c_arr2[i] == 'E')
        {
            exp_checker ++;
            exp_place = i;
            if (i < 2 || i == leng - 1)
        {
            printf("4ERROR:Incorrect input of number: nothing after E\n");
            return 1;
        }
        }
    }
    if (exp_checker != 1)
        {
            printf("5ERROR:Incorrect input of number\n");
            return 1;
        }
    int point_place;
    for (i = 0; i < leng;  i++)
    {
        if (c_arr2[i] == '.')
        {
            point_checker ++;
            point_place = i;
        }
    }
    if (point_place >= exp_place)
        {
            printf("6ERROR:Incorrect input of number: point after E\n");
            return 1;
        }
    if (point_checker != 1)
        return 1;
    for (i = 0; i < exp_place; i ++)
    {
        if ((c_arr2[i] == '+' || c_arr2[i] == '-') && i != 0)
        {
            printf("7ERROR:Incorrect input of number: sign after numbers\n");
            return 1;
        }
    }
    int ind = 0;
    int ind_check = 0;
    for (i = 0; i < exp_place; i ++)
    {
        if (c_arr2[i] == '.')
            *point_index = ind - 1;
        if (c_arr2[i] >= '0' && c_arr2[i]<= '9')
        {
            arr2[ind] = c_arr2[i] - 48;
            ind ++;
        }
        if (c_arr2[i] == '.' && i + 1 < exp_place && c_arr2[i + 1] == '0' && i + 2 == exp_place && ind == 30)
        {
            ind_check = 1;
        }
    }
    if (ind_check)
        ind --;
    *m = ind + 1;
    if (ind > 30)
    {

        printf("8ERROR:Length of number is more than 30 symbols\n");
        return 1;
    }
    for (int i = exp_place + 1; i < leng; i++)
    {
        if ((c_arr2[i]<'0' || c_arr2[i]>'9') && c_arr2[i]!= '+' && c_arr2[i]!= '-')
        {
            printf("9ERROR:Incorrect input of number: symbols are not numbers or not signs\n");
            return 1;
        }
    }
    if (c_arr2[exp_place + 1] == '-' || c_arr2[exp_place + 1] == '+' || c_arr2[exp_place + 1] >= '0' && c_arr2[exp_place + 1]<= '9')
    {
        for (int i = exp_place + 2; i < leng; i++)
        {
            if (c_arr2[i]<'0' || c_arr2[i]>'9')
            {
                printf("10ERROR:symbols after E are not numbers and not signs\n");
                return 1;
            }
        }
    }
    else
    {
        printf("11ERROR:symbols after E are not numbers and not signs\n");
        return 1;
    }

    if (!ret)
    {
        if (c_arr2[exp_place + 1] == '-')
            *sign_exp = -1;
        else if (c_arr2[exp_place + 1] == '+' || c_arr2[exp_place + 1] >= '0' && c_arr2[exp_place + 1]<= '9')
            *sign_exp = 1;
    }
    if (c_arr2[exp_place + 1] == '-' || c_arr2[exp_place + 1] == '+')
    {
        *exp_len = leng - exp_place  - 2;
    }
    else
    {
        *exp_len = leng - exp_place - 1;
    }
    if (*exp_len <= 0)
    {
        printf("12ERROR:E length is too small\n");
        return 1;
    }
    if (*exp_len > 30)
    {
        printf("13ERROR:E length is too big\n");
        return 1;
    }
    if (*exp_len > 1)
    {
        if (c_arr2[exp_place + 1] == '0' || ((c_arr2[exp_place + 1] == '+' || c_arr2[exp_place + 1] == '-')&&(c_arr2[exp_place + 2] == '0')))
        {
            printf("14ERROR:Incorrect E input\n");
            return 1;
        }
    }
    int j = 0;
    for (int i = exp_place + 1; i < leng; i++)
    {
        if (c_arr2[i]!= '+' && c_arr2[i]!= '-')
        {
            expon[j] = c_arr2[i] - 48;
            j ++;
        }
    }
    *mant_len = exp_place - point_place - 1;
    *m = *m - 1;
    return 0;
}
void input_instructions()
{
    //инструкция по вводу данных
    printf("Division\n");
    printf("First number input: +-m.nE+-exp, m and n are a number( m + n no more than 30 symbols), exp no more than 5 symbols\n");
    printf("Second number input: +-m.nE+-exp, m and n are a number( m + n no more than 30 symbols), exp no more than 5 symbols\n");

}
void multiply_on_figure(int arr_isx[], int fig, int arr_res[], int n, int *n_res)
{//учти, что исходный массив сдвинут в лево, а результатный массив - ваправо, arr_isx - занулен, размер  - 40
    int um = 0;
    int j = 59;
    for (int i = n - 1; i >= 0; i --)
    {
        arr_res[j] = (arr_isx[i] * fig + um) %10;
        um = (arr_isx[i] * fig + um) / 10;
        j --;
    }
    arr_res[j] = um;
    if (um)
        j--;
    *n_res = 59 - j;
    //сдвиг влево
    for (int i = 0; i < *n_res; i ++)
    {
        arr_res[i] = arr_res[i + 60 - *n_res];
    }
}
int is_a_bigger_equal_b(int arr1[], int arr2[], int len1, int len2)
{
    int ret = 1;
    if (len1 > len2)
        ret = 1;
    else if (len1 < len2)
        ret = 0;
    else
    {
        for (int i = 0; i < len1; i ++)
        {
            if (arr1[i] != arr2[i])
            {
                if (arr1[i] < arr2[i])
                    ret = 0;
                else
                    ret = 1;
                break;
            }
        }
    }
    return ret;
}
int is_a_bigger_b(int arr1[], int arr2[], int len1, int len2)
{
    if (len1 > len2)
        return 1;
    else if (len1 < len2)
        return 0;
    else
    {
        for (int i = 0; i < len1; i ++)
        {
            if (arr1[i] != arr2[i])
            {
                if (arr1[i] < arr2[i])
                    return 0;
                else if (arr1[i] > arr2[i])
                    return 1;
            }
        }
    }
    return 0;
}
void make_int_a_b(int *point_index1, int *len1, int *point_index2, int *len2, int mant1, int mant2)
{
    int min_m, max_m;
    if (mant1 < mant2)
        min_m = mant1;
    else
        min_m = mant2;
    if (mant1 > mant2)
        max_m = mant1;
    else
        max_m = mant2;
    *point_index1 = *point_index1 + min_m;
    *point_index2 = *point_index2 + min_m;
    int diff = max_m - min_m;
    *point_index1 = *point_index1 + diff;
    *point_index2 = *point_index2 + diff;
    *len1 = *len1 + max_m - mant1;
    *len2 = *len2 + max_m - mant2;
}
void subtraction(int arr1[], int arr2[], int len1, int len2, int *len_a1)
{
    if (len1 > len2)
    {
        for (int i = len1 - 1; i >= (len1 - len2); i --)
        {
            arr2[i] = arr2[i - (len1 - len2)];
        }
        for (int i = 0; i < (len1 - len2); i ++)
            arr2[i] = 0;
    }
    int flag_ten = 0;
    int x;
    int zan = 0;
    for (int i = len1 - 1; i >= 0; i --)
    {
        x = arr1[i] - arr2[i] - flag_ten;
        if (x < 0)
        {
            x += 10;
            flag_ten = 1;
        }
        else
        {
            flag_ten = 0;
        }
        arr1[i] = x;
    }
    int count_nulls = 0;
    while (arr1[count_nulls] == 0)
    {
        if (count_nulls == len1)
            break;
        count_nulls++;
    }
    for (int j = count_nulls; j < 60; j ++)
    {
        arr1[j - count_nulls] = arr1[j];
    }
    *len_a1 = *len_a1 - count_nulls;

}
void make_a_size_equal_orbigger_b_size(int arr1[], int arr2[], int *len1, int len2, int *len_res)
{
    if (*len1 < len2)
    {
        *len_res = *len_res + len2 - *len1;
        *len1 = len2;
    }
    if (!is_a_bigger_equal_b(arr1, arr2, *len1, len2))
    {
            *len1 = *len1 + 1;
            *len_res = *len_res + 1;
    }
}
void make_a_size_equal_orbigger_b_size_cycle(int arr1[], int arr2[], int *len1, int len2, int *len_res, int *point_index_res, int *flag_p_i)
{
    int len1_bef = *len1;
    if (*len1 < len2)
    {
        for (int i = 0; i < len2 - len1_bef; i ++)
        {
            *len1 = *len1 + 1;
            *len_res = *len_res + 1;
            if (!*flag_p_i)
            {
                if (*len1 - len1_bef == 1)
                {
                    *point_index_res = *len_res - 1;
                }
                *flag_p_i = 1;
            }
        }
        if (!is_a_bigger_equal_b(arr1, arr2, *len1, len2))
        {
                *len1 = *len1 + 1;
                if (!*flag_p_i)
                {
                    *point_index_res = *len_res - 1;
                    *flag_p_i = 1;
                }
                *len_res = *len_res + 1;
        }
        else
        {
            *len_res = *len_res - 1;
        }
    }
    else
    {
        *len1 = *len1 + 1;
        if (!*flag_p_i)
        {
            *point_index_res = *len_res - 1;
            *flag_p_i = 1;
        }
    }
}
int is_a_null(int arr1[], int len1)
{
    for (int i = 0; i < 60; i ++)
    {
        if (arr1[i] != 0)
            return 0;
    }
    return 1;
}
void make_equality(int arr1[], int arr2[], int len)
{
    for (int i = 0; i < len; i ++)
    {
        arr1[i] = arr2[i];
    }
}
int find_result_figure(int arr1[], int arr2[], int len1, int len2)
{
    int c = 0;
    int arr_helper[60] = {0};
    int len_a_helper;
    for (int i = 0; i < 11; i ++)
    {
        for (int j = 0; j < 60; j ++)
            arr_helper[j] = 0;
        multiply_on_figure(arr2,i,arr_helper, len2,&len_a_helper);
        if (is_a_bigger_b(arr_helper, arr1,len_a_helper, len1))
        {
            c = i - 1;
            break;
        }
    }
    return c;
}
void rm_zeros(int arr[], int *len, int *point_index)
{
    int count_nulls = 0;
    while (arr[count_nulls] == 0)
    {
        if (count_nulls == *len)
            break;
        count_nulls++;
    }
    for (int j = count_nulls; j < 60; j ++)
    {
        arr[j - count_nulls] = arr[j];
    }
    *len = *len - count_nulls;
    *point_index = *point_index - count_nulls;
}
void add_zeros_res(int *len_res, int arr1[], int *len1)
{
    int count_zeros = 0;
    for (int i = 0; i < *len1; i ++)
    {
        if (!arr1[i])
            count_zeros++;
        else
            break;
    }
    *len_res = *len_res + count_zeros;
    *len1 = *len1 - count_zeros;
}
void subtraction_for_find_index(int arr1[], int arr2[], int len1, int len2, int *len_a1, int *real_len1)
{
    if (len1 > len2)
    {
        for (int i = len1 - 1; i >= (len1 - len2); i --)
        {
            arr2[i] = arr2[i - (len1 - len2)];
        }
        for (int i = 0; i < (len1 - len2); i ++)
            arr2[i] = 0;
    }
    int flag_ten = 0;
    int x;
    int zan = 0;
    for (int i = len1 - 1; i >= 0; i --)
    {
        x = arr1[i] - arr2[i] - flag_ten;
        if (x < 0)
        {
            x += 10;
            flag_ten = 1;
        }
        else
        {
            flag_ten = 0;
        }
        arr1[i] = x;
    }
    int count_nulls = 0;
    while (arr1[count_nulls] == 0)
    {
        if (count_nulls == len1)
            break;
        count_nulls++;
    }
    for (int j = count_nulls; j < 60; j ++)
    {
        arr1[j - count_nulls] = arr1[j];
    }
    *len_a1 = *len_a1 - count_nulls;
    *real_len1 = *real_len1 - count_nulls;
    if (count_nulls == 60)
        *real_len1 = 0;

}
void make_division(int arr1[], int arr2[], int len1, int len2, int point_index1, int arr_res[], int *point_index_res, int *len_res, int point_index2, int point_index1_real, int point_index2_real, int max_m)
{
    //printf("\ndivision:\n");
    int flag_p_i = 0;
    int len1_check = 0;
    int int_arr1[60] = {0};
    int int_arr2[60] = {0};
    int int_len1 = point_index1_real + 1;
    int int_len2= point_index2_real + 1;
    int arr_helper[60];
    int e_p[60];
    int len_e_p;
    int len_a_helper;
    int result_figure;
    *point_index_res = -1;
    if (!is_a_bigger_equal_b(arr1,arr2,len1,len2))
    {
            make_a_size_equal_orbigger_b_size(arr1,arr2,&len1,len2,len_res);
            *point_index_res = -1;
            flag_p_i = 1;
    }
    while (!is_a_null(arr1, len1) && *len_res < 31)
    {
        len_e_p = 0;
        for (int i = 0; i < 60; i ++)
            e_p[i] = 0;
        if (!is_a_bigger_equal_b(arr1,arr2,len1,len2))
        {
            make_a_size_equal_orbigger_b_size_cycle(arr1,arr2,&len1,len2,len_res, point_index_res, &flag_p_i);
        }
        len_a_helper = len2;
        make_equality(arr_helper,arr1, len2);
        if(is_a_bigger_b(arr2,arr_helper,len2,len_a_helper))
        {
            arr_helper[len2] = arr1[len2];
            len_a_helper ++;
        }
        result_figure = find_result_figure(arr_helper, arr2, len_a_helper, len2);
        arr_res[*len_res] = result_figure;
        *len_res = *len_res + 1;
        multiply_on_figure(arr2,result_figure,e_p,len2,&len_e_p);
        subtraction(arr1,e_p,len_a_helper, len_e_p, &len1);
        add_zeros_res(len_res,arr1,&len1);
    }
    if (!flag_p_i)
        *point_index_res = *len_res - 1;
}
void okruglenie(int arr_res[],int *len_res)
{
    int len_cycle;
    int um = 0;
    int x;
    if (*len_res > 30)
    {
        if (arr_res[*len_res - 1] < 5)
        {
            *len_res = *len_res - 1;
        }
        else
        {
            *len_res = *len_res - 1;
            len_cycle = *len_res;
            for (int i = len_cycle - 1; i >= 0; i --)
            {
                x = (arr_res[i] + 1);
                arr_res[i] = x % 10;
                if (arr_res[i] != 0)
                    break;
                else
                {
                    *len_res = *len_res - 1;
                }
            }
        }
    }
}
int check_cycle(int arr_res[], int len_res, int arr_cyc[], int len_cyc)
{
    int ind = 0;
    for (int i = 0; i < 30; i ++)
    {
        if (arr_res[i] != 0)
            break;
        ind ++;
    }
    int flag = 0;
    for (int j = ind; j < 30 - len_cyc; j ++)
    {
        for (int i = 0; i < len_cyc; i ++)
        {
            if (arr_res[j + i] != arr_cyc[i])
            {
                flag ++;
                break;
            }
        }
        j = j + len_cyc;
    }
    if (flag)
        return 1;
    return 0;
}
void make_cycled(int arr_res[], int arr_len)
{
    int arr_cyc[30];
    int arr_cyc_len = 0;
    int ind = 0;
    int zero_flag = 0;
    for (int i = 0; i < 30; i ++)
    {

        if (arr_res[i] == 0)
            ind++;
        else
            break;
    }
    for (int i = ind; i < 30; i ++)
    {
        arr_cyc[i - ind] = arr_res[i];
        arr_cyc_len ++;
        if (!check_cycle(arr_res, arr_len, arr_cyc, arr_cyc_len))
        {
            for (int j = 0; j < arr_cyc_len; j ++)
            {
                if (arr_cyc[j] == 0 && !zero_flag)
                {
                    for (int k = j; k < arr_cyc_len - 1; k ++)
                    {
                        arr_cyc[k] = arr_cyc[k + 1];
                    }
                    zero_flag = 1;
                }
            }
            break;
        }
    }
    int index_cyc = 0;
    for (int i = ind; i < 30; i ++)
    {
        arr_res[i] = arr_cyc[index_cyc % arr_cyc_len];
        index_cyc ++;
    }
}
int print_result(int arr_res[],int len_res,int exp_number1, int sign1, int is_zero, int p_i)\
{
    if (len_res > 30)
        len_res = 30;
    char sign;
    printf("result:\n");
    if (p_i == -1)
    {
        exp_number1 += (0);
        p_i = 0;
    }
    else
        exp_number1 += (p_i + 1);
    if (sign1 < 0)
        sign = '-';
    else
        sign = '+';
    printf("%c", sign);
    if (is_zero)
    {
        make_cycled(arr_res, len_res);
        if (exp_number1 > 99999 || exp_number1 < -99999)
        {
            printf("ERROR:The E is too large");
            return 1;
        }
        for (int i = 0; i < len_res; i ++)
        {
            printf("%d", arr_res[i]);
            if (i == 0)
                printf(".");
        }
        printf("E%d", exp_number1);
    }
    else
    {
        make_cycled(arr_res, len_res);
        if (exp_number1 > 99999 || exp_number1 < -99999)
        {
            printf("ERROR:The E is too large");
            return 1;
        }
        else
        {
            printf("0.");
            for (int i = 0; i < len_res; i ++)
            {
                printf("%d", arr_res[i]);
            }
            printf("E%d", exp_number1);
        }
    }
    return 0;
}
int main()
{
    setbuf(stdout, NULL);// отключеие буферизации
    char c_arr1[40];// массивы для ввода чисел
    char c_arr2[40];
    int int_part_length;//длины ответа в неформатированном виде
    int sign1;
    int sign2;
    char sign;// Знак результата
    int exp_len1;// количество символов в числе порядка
    int exp_len2;
    int exp_number1;// порядок в форме целого числа
    int exp_number2;
    int arr1[60] = {0};// массивы , которые предназначены для введения в них исходных чисел и дальнейшей операции умножения
    int arr2[60] = {0};
    int arr_res[32] = {0};
    int point_index1;
    int point_index2;
    int point_index1_real;
    int point_index2_real;
    int sign_exp1;
    int sign_exp2;
    int expon1[10] = {0}; // массив , который предназначен для введения в него исходного порядка
    int expon2[10] = {0};
    int n; // количество цифр в первом числе
    int m; // количество цифр во втором числе
    int step = 0;
    int ind = 0;
    int i =0,j = 0;
    int flag = 0;// используется множество раз в программе
    int ind2;
    int mnojitel = 1;
    int ret = 0;
    char ans[40];
    int mant_len1;
    int mant_len2;
    int len_res = 0;
    int point_index_res;
    int array_cycled[30];
    int is_zero;
    int max_m;
    input_instructions();
    printf("Input first number:\n");
    printf("|----|----|----|----|----|----|\n");
    j = 0;
    i = 0;
    //в данном цикле происходит ввод числа, параллельно заполняются данные, необходимые для умножения и вывода ответа , например: знак числа,целочисленный массив arr2, данные необходимые для обработки порядка
    scanf("%s", &c_arr1);
    int leng1 = strlen(c_arr1);
    int check_input;
    check_input = number_input(c_arr1,leng1,&exp_len1,expon1,&sign1,&sign_exp1, arr1, &point_index1, &m, &mant_len1);
    if (check_input)
        return 1;
    printf("Input second number:\n");
    printf("|----|----|----|----|----|----|\n");
    scanf("%s", &c_arr2);
    int leng2 = strlen(c_arr2);
    check_input = number_input(c_arr2,leng2,&exp_len2,expon2,&sign2,&sign_exp2, arr2, &point_index2, &n, &mant_len2);
    if (check_input)
        return 1;
    if (is_a_null(arr2,m))
    {
        printf("ERROR: Division on 0\n");
        return 1;
    }
    if (is_a_null(arr1,n))
    {
        printf("0.0E0\n");
    }
    else
    {
        if (mant_len1 > mant_len2)
            max_m = mant_len1;
        else
            max_m = mant_len2;
        point_index1_real = point_index1;
        point_index2_real = point_index2;
        make_int_a_b(&point_index1, &m, &point_index2, &n, mant_len1, mant_len2);
        rm_zeros(arr1,&m,&point_index1);
        rm_zeros(arr2,&n,&point_index2);
        make_division(arr1, arr2, m, n, point_index1,arr_res, &point_index_res, &len_res, point_index2, point_index1_real,point_index2_real, max_m);
        //преобразование порялка в целое число
        exp_number1 = 0;
        for (i = 0; i < exp_len1 - 1; i ++)
            mnojitel *= 10;
        for (i = 0, j = exp_len1; i < exp_len1; i ++, j --)
        {
            exp_number1 += expon1[i] * mnojitel;
            mnojitel /= 10;
        }
        exp_number1 *= sign_exp1;

        mnojitel = 1;
        exp_number2 = 0;
        for (i = 0; i < exp_len2 - 1; i ++)
            mnojitel *= 10;
        for (i = 0, j = exp_len2; i < exp_len2; i ++, j --)
        {
            exp_number2 += expon2[i] * mnojitel;
            mnojitel /= 10;
        }
        exp_number2 *= sign_exp2;
        // Проверка порядка
        if (fabs(exp_number1) > 99999)
        {
            printf("ERROR:The E is too large");
            return 1;
        }
        if (fabs(exp_number2) > 99999)
        {
            printf("ERROR:The E is too large");
            return 1;
        }
        exp_number1 = exp_number1 - exp_number2; //+ (point_index_res + 1);
        sign1 *= sign2;
        if (!arr_res[0])
            is_zero = 1;
        else
            is_zero = 0;
        okruglenie(arr_res, &len_res);
        print_result(arr_res,len_res,exp_number1, sign1, is_zero, point_index_res);
    }
    return 0;
}
