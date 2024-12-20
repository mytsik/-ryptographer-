#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LEN 81
#define SIZE 1000

int OverUnderBorder(int length, int index) //когда нужный индекс выходит за пределы массива алфавита
{
    return (index + length) % length;
}

int Vigenere()
{

    printf("\nВведите текст, который хотите зашифровать:\n");
    char text[LEN];
    fgets(text, LEN, stdin);
    text[strcspn(text, "\n")] = '\0';  // Удаляем символ новой строки, если он есть

    // Ввод ключа
    printf("\nВведите слово, которое будет использоваться в качестве ключа шифрования\n");
    char key[LEN];
    fgets(key, LEN, stdin);
    key[strcspn(key, "\n")] = '\0';  // Удаляем символ новой строки, если он есть

    int text_len = strlen(text);
    int key_len = strlen(key);
    
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    char result_key[] = "";
    char result[] = "";

    //int res_key_len = strlen(result_key);
    //for (int i = 0; i < res_key_len; i++) // удаляю символы М
    //    result_key[i] = '\0';

    int i, j;
    // Новый ключ
    for (i = 0, j = 0; i < text_len; ++i) 
    {
        if (j == key_len)  
            j = 0; //если дошли до конца ключа то начать сначала

        char text_i[] = { text[i] , '\0' };

        if (strstr(not_letters, text_i))
            strcat(result_key, text_i);
        else
        {
            char key_j[] = { key[j] , '\0' };
            strcat(result_key, key_j);
            j += 1;
        }                          
    }
    result_key[i] = '\0';
      
    int k;
    for (k = 0; k < text_len; ++k)
    {       
        char text_k[] = { text[k] , '\0' };

        if (!strstr(not_letters, text_k))
            result[k] = (((text[k] - 'a') + (result_key[k] - 'a')) % 26) + 'a'; // шифрование            
        else
            result[k] = text[k];
    }
    result[k] = '\0';  

    // Вывод
    printf("\nРезультат: %s\n", result);

    scanf("%*[^\n]");
    scanf("%*c");

    return 1;

}


int Caesar()
{    
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

        // Обработка русских букв
        /*if (strchr(rus_lower, current_char) || strchr(rus_upper, current_char))
        {
            for (int j = 0; j < rus_length; j++)
            {
                int sum_id = step + j;

                if (current_char == rus_upper[j])
                {
                    if (sum_id >= rus_length)
                    {
                        result[result_index++] = rus_upper[OverBorder(rus_length, sum_id)];
                    }
                    else if (sum_id < 0)
                    {
                        result[result_index++] = rus_upper[UnderBorder(rus_length, sum_id)];
                    }
                    else
                    {
                        result[result_index++] = rus_upper[sum_id];
                    }
                    break;
                }

                if (current_char == rus_lower[j])
                {
                    if (sum_id >= rus_length)
                    {
                        result[result_index++] = rus_lower[OverBorder(rus_length, sum_id)];
                    }
                    else if (sum_id < 0)
                    {
                        result[result_index++] = rus_lower[UnderBorder(rus_length, sum_id)];
                    }
                    else
                    {
                        result[result_index++] = rus_lower[sum_id];
                    }
                    break;
                }
            }
        }*/
    }

    result[result_index] = '\0';
    printf("\nРезультат: %s\n", result);

    return 1;
}

void main()
{
	setlocale(LC_ALL, "RUS");

	int choice;
	printf("Выберите метод шифрования(введите цифру):\n1 - Шифр Цезаря: шифрует по буквам алфавита\n2 - Шифр Виженера: шифрует с помощью ключа\n3 - Шифр Атбаш: шифрует в обратном порядке\n\n");
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
        default:
            printf("Введенный вами вариант отсутствует\n");
	}
}