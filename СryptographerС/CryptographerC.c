#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 1000

int OverUnderBorder(int length, int index) //когда нужный индекс выходит за пределы массива алфавита
{
    return (index + length) % length;
}


int Atbash()
{
    printf("\nВведите текст, который хотите зашифровать:\n");
    char text[SIZE];
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';  //удаление символа новой строки

    int text_len = strlen(text);

    for (int i = 0; i < text_len; i++)
    {
        if (isalpha(text[i])) 
        {
            if (isupper(text[i])) 
                text[i] = 'A' + ('Z' - text[i]);
            else if (islower(text[i])) 
                text[i] = 'a' + ('z' - text[i]);
        }
    }
    text[text_len] = '\0';
    printf("\nРезультат: %s\n", text);
    return 1;
}

int Vigenere()
{
    printf("\nВведите текст, который хотите зашифровать:\n");
    char text[SIZE];
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';  //удаление символа новой строки

    printf("\nВведите слово, которое будет использоваться в качестве ключа шифрования\n");
    char key[SIZE];
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0';  //удаление символа новой строки

    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0; i < key_len; i++) //если в ключе есть прописные буквы то сделать их строчными
        key[i] = tolower(key[i]);
    
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    char result_key[SIZE];
      
    // итоговый ключ
    for (int i = 0, j = 0; i < text_len; i++) 
    {
        if (j == key_len)  
            j = 0; //если дошли до конца ключа то начать сначала

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

        if (!strstr(not_letters, text_k))
            text[k] = (((text[k] - 'a') + (result_key[k] - 'a')) % 26) + 'a'; // шифрование                    
    }
    text[text_len] = '\0';

    printf("\nРезультат: %s\n", text);    

    return 1;
}


int Caesar()
{
    setlocale(LC_ALL, "RUS");

    const char* eng_lower = "abcdefghijklmnopqrstuvwxyz";
    const char* eng_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* rus_lower = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
    const char* rus_upper = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const char* not_letters = " #$%&*+-=?@^_,./0123456789!";

    // длины алфавитов
    int eng_length = strlen(eng_lower);
    int rus_length = strlen(rus_lower);

    char result[SIZE]; // результирующий массив
    int result_index = 0; // индекс в результате

    char text[SIZE];
    printf("\nВведите текст, который хотите зашифровать:\n");
    fgets(text, sizeof(text), stdin); // \n появляется после этого до считывания step      

    int step;
    printf("\nВведите значение для сдвига(отрицательное значение для сдвига влево, положительное значение для сдвига вправо):\n");
    scanf_s("%d", &step);
    
    // обработка каждого символа
    for (int i = 0; i < strlen(text); i++)
    {
        char current_char = text[i];
        int added = 0;

        //если символ не является буквой
        for (int t = 0; t < strlen(not_letters); t++)
        {
            if (current_char == not_letters[t])
            {
                result[result_index++] = current_char;
                added = 1;
                continue;
            }
        }

        if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //английские буквы
        {
            for (int j = 0; j < eng_length; j++)
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
            for (int j = 0; j < rus_length; j++)
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
    printf("\nРезультат: %s\n", result);

    return 1;
}

void main()
{
	setlocale(LC_ALL, "RUS");

    while (1) 
    {
        printf("\033[0d\033[2J"); //очистка консоли

        int choice;
        printf("Выберите метод шифрования(введите цифру):\n1 - Шифр Цезаря: шифрует по буквам алфавита\n2 - Шифр Виженера: шифрует с помощью ключа\n3 - Шифр Атбаш: шифрует в обратном порядке\n\nЧтобы выйти введите 0\n\n");
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

                    printf("\nПродолжить пользоваться шифром Цезаря? (Да - 1, нет - 0)\n");
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

                    printf("\nПродолжить пользоваться шифром Виженера? (Да - 1, нет - 0)\n");
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

                    printf("\nПродолжить пользоваться шифром Атбаш? (Да - 1, нет - 0)\n");
                    scanf_s("%d", &cont);
                    if (cont == 0)
                        break;
                }
                break;
            }
            case 0:
                break;
            default:
                printf("Введенный вами вариант отсутствует\n");            
        }
        if (choice == 0)
            break;
    }      
}