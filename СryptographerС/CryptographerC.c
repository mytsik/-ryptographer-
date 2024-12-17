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
    char textToEncode[LEN];
    fgets(textToEncode, LEN, stdin);
    textToEncode[strcspn(textToEncode, "\n")] = '\0';  // Удаляем символ новой строки, если он есть

    // Ввод ключа
    printf("\nВведите слово, которое юудет использоваться в качестве ключа шифрования\n");
    char keyword[LEN];
    fgets(keyword, LEN, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';  // Удаляем символ новой строки, если он есть

    int textLen = strlen(textToEncode);
    int keyLen = strlen(keyword);
    int i, j;

    char newKey[SIZE];
    char encryptedText[SIZE];

    // Новый ключ
    for (i = 0, j = 0; i < textLen; ++i, ++j) 
    {
        if (j == keyLen) 
        {
            j = 0;
        }
        newKey[i] = keyword[j];
    }
    newKey[i] = '\0';  // Завершаем строку новым ключом

    // Шифровка
    for (i = 0; i < textLen; i++) 
    {
        if (textToEncode[i] != ' ') {
            encryptedText[i] = (((textToEncode[i] - 'a') + (newKey[i] - 'a')) % 26) + 'a'; // Шифрование
        }
        else {
            encryptedText[i] = ' '; // Пробел остаётся неизменным
        }
    }
    encryptedText[i] = '\0';  // Завершаем строку зашифрованным текстом

    // Вывод
    printf("\nРезультат: %s\n", encryptedText);

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

        //если символ не явдяется буквой
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