#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <Windows.h> 
#include <time.h>
#define SIZE 1000

int OverUnderBorder(int length, int index) //когда нужный индекс выходит за пределы длины алфавита
{
    return (index + length) % length;
}

int Atbash()
{
    char eng_lower[] = "abcdefghijklmnopqrstuvwxyz";
    char eng_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rus_lower[] = "абвгдежзийклмнопрстуфхцчшщъыьэю€";
    char rus_upper[] = "јЅ¬√ƒ≈∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя";
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    printf("\n¬ведите текст, который хотите зашифровать:\n");
    char text[SIZE];
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';  //удаление символа новой строки

    clock_t time_start = clock();
    int text_len = strlen(text);

    for (int i = 0; i < text_len; i++)
    {
        char text_i[] = { text[i] , '\0' };
        
       
        if (!strstr(not_letters, text_i))
        {   
            char current_char = text[i];
            if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //английские буквы
            {
                if (isupper(current_char))
                    text[i] = 'A' + ('Z' - text[i]);
                else 
                    text[i] = 'a' + ('z' - text[i]);                
            }            
            else
            {
                if (isupper(current_char))
                    text[i] = 'ј' + ('я' - text[i]);
                else 
                    text[i] = 'а' + ('€' - text[i]);
            }                       
        }
    }
    text[text_len] = '\0';
    printf("\n–езультат: %s\n", text);

    clock_t time_end = clock() - time_start;
    double time_result = (double)time_end / CLOCKS_PER_SEC;
    printf("\n¬рем€ выполнени€: %.3lf секунд\n", time_result);
    return 1;
}

int Vigenere()
{
    char eng_lower[] = "abcdefghijklmnopqrstuvwxyz";
    char eng_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rus_lower[] = "абвгдежзийклмнопрстуфхцчшщъыьэю€";
    char rus_upper[] = "јЅ¬√ƒ≈∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя";
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    printf("\n¬ведите текст, который хотите зашифровать:\n");
    char text[SIZE];
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';  //удаление символа новой строки

    printf("\n¬ведите слово, которое будет использоватьс€ в качестве ключа шифровани€\n");
    char key[SIZE];
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0';  //удаление символа новой строки

    clock_t time_start = clock();

    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0; i < key_len; i++) //если в ключе есть прописные буквы, то сделать их строчными
        key[i] = tolower(key[i]);   
    
    char result_key[SIZE];
      
    // итоговый ключ
    for (int i = 0, j = 0; i < text_len; i++) 
    {
        if (j == key_len)  
            j = 0; //если дошли до конца ключа, то начать сначала

        char text_i[] = { text[i] , '\0' };

        if (strstr(not_letters, text_i))
            result_key[i] = text[i];
        else
        {
            result_key[i] = key[j];
            j += 1;
        }                          
    }
    result_key[text_len] = '\0';
    
    for (int k = 0; k < text_len; k++)
    {       
        char text_k[] = { text[k] , '\0' };
        char current_char = text[k];
        
        if (!strstr(not_letters, text_k)) 
        {
            if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //английские буквы
                text[k] = (((text[k] - 'a') + (result_key[k] - 'a')) % 26) + 'a'; // шифрование 

            if (strchr(rus_lower, current_char) || strchr(rus_upper, current_char)) //русские буквы
                text[k] = (((text[k] - 'а') + (result_key[k] - 'а')) % 32) + 'а'; // шифрование                
        }                               
    }
    text[text_len] = '\0';

    printf("\n–езультат: %s\n", text); 

    clock_t time_end = clock() - time_start;
    double time_result = (double)time_end / CLOCKS_PER_SEC;
    printf("\n¬рем€ выполнени€: %.3lf секунд\n", time_result);

    return 1;
}


int Caesar()
{ 
    char eng_lower[] = "abcdefghijklmnopqrstuvwxyz";
    char eng_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rus_lower[] = "абвгдежзийклмнопрстуфхцчшщъыьэю€";
    char rus_upper[] = "јЅ¬√ƒ≈∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя";
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    // длины алфавитов
    int eng_length = strlen(eng_lower);
    int rus_length = strlen(rus_lower);

    char result[SIZE]; // результирующий массив
    int result_index = 0; // индекс в результате

    char text[SIZE];
    printf("\n¬ведите текст, который хотите зашифровать:\n");
    fgets(text, sizeof(text), stdin);      

    int step;
    printf("\n¬ведите значение дл€ сдвига(отрицательное значение дл€ сдвига влево, положительное значение дл€ сдвига вправо):\n");
    scanf_s("%d", &step);

    clock_t time_start = clock(); //засекание времени
    // обработка каждого символа
    for (int i = 0; i < strlen(text); i++)
    {
        char current_char = text[i];
        int added = 0;

        //если символ не €вл€етс€ буквой
        for (int t = 0; t < strlen(not_letters); t++)
        {
            if (current_char == not_letters[t])
            {
                result[result_index++] = current_char;
                added = 1;
                continue;
            }
        }

        int j;
        if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //английские буквы
        {
            for (j = 0; j < eng_length; j++)
            {
                int sum_id = step + j;

                if (current_char == eng_upper[j]) //заглавные буквы
                {
                    if ((sum_id >= eng_length) || (sum_id < 0))
                        result[result_index++] = eng_upper[OverUnderBorder(eng_length, sum_id)];
                    else
                        result[result_index++] = eng_upper[sum_id];
                    break;
                }

                if (current_char == eng_lower[j]) //строчные буквы
                {
                    if ((sum_id >= eng_length) || (sum_id < 0))
                        result[result_index++] = eng_lower[OverUnderBorder(eng_length, sum_id)];
                    else
                        result[result_index++] = eng_lower[sum_id];
                    break;
                }
            }
        }
        
        if (strchr(rus_lower, current_char) || strchr(rus_upper, current_char)) //русские буквы
        {
            for (j = 0; j < rus_length; j++)
            {
                int sum_id = step + j;

                if (current_char == rus_upper[j])
                {
                    if ((sum_id >= rus_length)||(sum_id < 0))
                        result[result_index++] = rus_upper[OverUnderBorder(rus_length, sum_id)];
                    else
                        result[result_index++] = rus_upper[sum_id];
                    break;
                }

                if (current_char == rus_lower[j])
                {
                    if ((sum_id >= rus_length) || (sum_id < 0))
                        result[result_index++] = rus_lower[OverUnderBorder(rus_length, sum_id)];
                    else
                        result[result_index++] = rus_lower[sum_id];
                    break;
                }
            }
        }
    }

    result[result_index] = '\0';
    printf("\n–езультат: %s\n", result);

    clock_t time_end = clock() - time_start;
    double time_result = (double)time_end / CLOCKS_PER_SEC;
    printf("\n¬рем€ выполнени€: %.3lf секунд\n", time_result);

    return 1;
}

void main()
{
	setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (1) 
    {
        printf("\033[0d\033[2J"); //очистка консоли

        int choice;
        printf("¬ыберите метод шифровани€(введите цифру):\n1 - Ўифр ÷езар€: шифрует по буквам алфавита\n2 - Ўифр ¬иженера: шифрует с помощью ключа\n3 - Ўифр јтбаш: шифрует в обратном пор€дке\n\n„тобы выйти введите 0\n\n");
        scanf_s("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                while (1)
                {
                    //очистка буфера
                    scanf("%*[^\n]");
                    scanf("%*c");

                    int cont;

                    Caesar();

                    printf("\nѕродолжить пользоватьс€ шифром ÷езар€? (ƒа - 1, нет - 0)\n");
                    scanf_s("%d", &cont);
                    if (cont == 0)
                        break;
                }
                break;
            }
            case 2:
            {
                while (1)
                {
                    //очистка буфера
                    scanf("%*[^\n]");
                    scanf("%*c");

                    int cont;

                    Vigenere();

                    printf("\nѕродолжить пользоватьс€ шифром ¬иженера? (ƒа - 1, нет - 0)\n");
                    scanf_s("%d", &cont);
                    if (cont == 0)
                        break;
                }
                break;
            }
            case 3:
            {
                while (1)
                {
                    //очистка буфера
                    scanf("%*[^\n]");
                    scanf("%*c");                    

                    int cont;

                    Atbash();

                    printf("\nѕродолжить пользоватьс€ шифром јтбаш? (ƒа - 1, нет - 0)\n");
                    scanf_s("%d", &cont);
                    if (cont == 0)
                        break;
                }
                break;
            }
            case 0:
                break;
            default:
                printf("¬веденный вами вариант отсутствует\n");            
        }
        if (choice == 0)
            break;
    }      
}