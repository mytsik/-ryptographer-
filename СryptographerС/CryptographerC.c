#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int OverUnderBorder(int length, int index) //����� ������ ������ ������� �� ������� ������� ��������
{
    return (index + length) % length;
}

int Caesar(char text[10000], int step)
{	
    const char* eng_lower = "abcdefghijklmnopqrstuvwxyz";
    const char* eng_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* rus_lower = "��������������������������������";
    const char* rus_upper = "��������������������������������";
    const char* not_letters = " #$%&*+-=?@^_,./0123456789!";

    // ����� ���������
    int eng_length = strlen(eng_lower);
    int rus_length = strlen(rus_lower);
  
    char result[1000]; // �������������� ������
    int result_index = 0; // ������ � ����������

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
       
        if (strchr(eng_lower, current_char) || strchr(eng_upper, current_char)) //���������� �����
        {
            for (int j = 0; j < eng_length; j++) 
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

        // ��������� ������� ����
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

    // ����� ����������
    result[result_index] = '\0';
    printf("���������: %s\n", result);
	return 1;
}

void main()
{
	setlocale(LC_ALL, "RUS");

    char text[100];
    printf("\n������� �����, ������� ������ �����������:\n");
    fgets(text, sizeof(text), stdin);

	char choice;
	printf("\n�������� ����� ����������(������� �����):\n1 - ���� ������: ������� �� ������ ��������\n2 - ���� ��������: ������� � ������� �����\n3 - ���� �����: ������� � �������� �������\n\n");
	scanf(" %c", &choice);

	switch (choice)
	{
		case '1':
        {
            int step;
            printf("\n������� �������� ��� ������(������������� �������� ��� ������ �����, ������������� �������� ��� ������ ������):\n");
            scanf("%d", &step);
            Caesar(text, step);
            break;
        }
        default:
            printf("������ ������� �����������\n");
	}
}