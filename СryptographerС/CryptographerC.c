#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <Windows.h> 
#include <time.h>
#define SIZE 1000

int OverUnderBorder(int length, int index) //����� ������ ������ ������� �� ������� ����� ��������
{
    return (index + length) % length;
}

int Atbash()
{
    char eng_lower[] = "abcdefghijklmnopqrstuvwxyz";
    char eng_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rus_lower[] = "��������������������������������";
    char rus_upper[] = "��������������������������������";
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    printf("\n������� �����, ������� ������ �����������:\n");
    char text[SIZE];
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';  //�������� ������� ����� ������

    clock_t time_start = clock();
    int text_len = strlen(text);

    for (int i = 0; i < text_len; i++)
    {
        char text_i[] = { text[i] , '\0' };
        
       
        if (!strstr(not_letters, text_i))
        {   
            char current_char = text[i];
            if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //���������� �����
            {
                if (isupper(current_char))
                    text[i] = 'A' + ('Z' - text[i]);
                else 
                    text[i] = 'a' + ('z' - text[i]);                
            }            
            else
            {
                if (isupper(current_char))
                    text[i] = '�' + ('�' - text[i]);
                else 
                    text[i] = '�' + ('�' - text[i]);
            }                       
        }
    }
    text[text_len] = '\0';
    printf("\n���������: %s\n", text);

    clock_t time_end = clock() - time_start;
    double time_result = (double)time_end / CLOCKS_PER_SEC;
    printf("\n����� ����������: %.3lf ������\n", time_result);
    return 1;
}

int Vigenere()
{
    char eng_lower[] = "abcdefghijklmnopqrstuvwxyz";
    char eng_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rus_lower[] = "��������������������������������";
    char rus_upper[] = "��������������������������������";
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    printf("\n������� �����, ������� ������ �����������:\n");
    char text[SIZE];
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';  //�������� ������� ����� ������

    printf("\n������� �����, ������� ����� �������������� � �������� ����� ����������\n");
    char key[SIZE];
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0';  //�������� ������� ����� ������

    clock_t time_start = clock();

    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0; i < key_len; i++) //���� � ����� ���� ��������� �����, �� ������� �� ���������
        key[i] = tolower(key[i]);   
    
    char result_key[SIZE];
      
    // �������� ����
    for (int i = 0, j = 0; i < text_len; i++) 
    {
        if (j == key_len)  
            j = 0; //���� ����� �� ����� �����, �� ������ �������

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
            if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //���������� �����
                text[k] = (((text[k] - 'a') + (result_key[k] - 'a')) % 26) + 'a'; // ���������� 

            if (strchr(rus_lower, current_char) || strchr(rus_upper, current_char)) //������� �����
                text[k] = (((text[k] - '�') + (result_key[k] - '�')) % 32) + '�'; // ����������                
        }                               
    }
    text[text_len] = '\0';

    printf("\n���������: %s\n", text); 

    clock_t time_end = clock() - time_start;
    double time_result = (double)time_end / CLOCKS_PER_SEC;
    printf("\n����� ����������: %.3lf ������\n", time_result);

    return 1;
}


int Caesar()
{ 
    char eng_lower[] = "abcdefghijklmnopqrstuvwxyz";
    char eng_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rus_lower[] = "��������������������������������";
    char rus_upper[] = "��������������������������������";
    char not_letters[] = " #$%&*+-=?@^_,./0123456789!";

    // ����� ���������
    int eng_length = strlen(eng_lower);
    int rus_length = strlen(rus_lower);

    char result[SIZE]; // �������������� ������
    int result_index = 0; // ������ � ����������

    char text[SIZE];
    printf("\n������� �����, ������� ������ �����������:\n");
    fgets(text, sizeof(text), stdin);      

    int step;
    printf("\n������� �������� ��� ������(������������� �������� ��� ������ �����, ������������� �������� ��� ������ ������):\n");
    scanf_s("%d", &step);

    clock_t time_start = clock(); //��������� �������
    // ��������� ������� �������
    for (int i = 0; i < strlen(text); i++)
    {
        char current_char = text[i];
        int added = 0;

        //���� ������ �� �������� ������
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
        if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //���������� �����
        {
            for (j = 0; j < eng_length; j++)
            {
                int sum_id = step + j;

                if (current_char == eng_upper[j]) //��������� �����
                {
                    if ((sum_id >= eng_length) || (sum_id < 0))
                        result[result_index++] = eng_upper[OverUnderBorder(eng_length, sum_id)];
                    else
                        result[result_index++] = eng_upper[sum_id];
                    break;
                }

                if (current_char == eng_lower[j]) //�������� �����
                {
                    if ((sum_id >= eng_length) || (sum_id < 0))
                        result[result_index++] = eng_lower[OverUnderBorder(eng_length, sum_id)];
                    else
                        result[result_index++] = eng_lower[sum_id];
                    break;
                }
            }
        }
        
        if (strchr(rus_lower, current_char) || strchr(rus_upper, current_char)) //������� �����
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
    printf("\n���������: %s\n", result);

    clock_t time_end = clock() - time_start;
    double time_result = (double)time_end / CLOCKS_PER_SEC;
    printf("\n����� ����������: %.3lf ������\n", time_result);

    return 1;
}

void main()
{
	setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (1) 
    {
        printf("\033[0d\033[2J"); //������� �������

        int choice;
        printf("�������� ����� ����������(������� �����):\n1 - ���� ������: ������� �� ������ ��������\n2 - ���� ��������: ������� � ������� �����\n3 - ���� �����: ������� � �������� �������\n\n����� ����� ������� 0\n\n");
        scanf_s("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                while (1)
                {
                    //������� ������
                    scanf("%*[^\n]");
                    scanf("%*c");

                    int cont;

                    Caesar();

                    printf("\n���������� ������������ ������ ������? (�� - 1, ��� - 0)\n");
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
                    //������� ������
                    scanf("%*[^\n]");
                    scanf("%*c");

                    int cont;

                    Vigenere();

                    printf("\n���������� ������������ ������ ��������? (�� - 1, ��� - 0)\n");
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
                    //������� ������
                    scanf("%*[^\n]");
                    scanf("%*c");                    

                    int cont;

                    Atbash();

                    printf("\n���������� ������������ ������ �����? (�� - 1, ��� - 0)\n");
                    scanf_s("%d", &cont);
                    if (cont == 0)
                        break;
                }
                break;
            }
            case 0:
                break;
            default:
                printf("��������� ���� ������� �����������\n");            
        }
        if (choice == 0)
            break;
    }      
}