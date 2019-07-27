// Visual Studio���� �ۼ��� �ڵ��Դϴ�.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void set_com_data(int* computer, int max_num);
void player_data_input(int* player, int max_num);
void judge_result(int* computer, int* player, int* strike, int* ball, int max_num);

int main()
{
	int* computer;
	int* player;
	int i, j, strike = 0, ball = 0, challenge_time = 0, max_num = 0; // challenge_time : ���� Ƚ���� ������ ����, max_num : �ִ� �� �ڸ��� ������ ������ �������� �����ϴ� ����

	printf("�ִ� �� �ڸ� ���� �����Ͻðڽ��ϱ�? : ");
	scanf_s("%d", &max_num);
	system("cls");

	computer = (int*)malloc(sizeof(int) * max_num);
	player = (int*)malloc(sizeof(int) * max_num);

	if (computer == NULL || player == NULL)
	{
		puts("�޸� �Ҵ翡 �����߽��ϴ�. ���α׷��� �����մϴ�.");
		return -1;
	}

	set_com_data(computer, max_num);

	puts("Start Game!");
	puts("number range : 0 ~ 9");

	while (1) // �÷��̾ 3strike�� �ϱ� �������� ��� �ݺ��Ǿ�� �ϹǷ� ���� �ݺ� ����
	{
		strike = 0;
		ball = 0;

		player_data_input(player, max_num);

		for (i = 0; i < max_num; i++)
		{
			if (player[i] < 0 || player[i] > 9) // ���� ������ �Ѿ���� üũ
			{
				puts("���� ������ ������ϴ�. �ٽ� �Է����ּ���.\n");
				player_data_input(player, max_num);
				i = -1;
				continue;
			}

			for (j = 0; j < i; j++) // �ߺ� üũ
			{
				if (player[i] == player[j])
				{
					puts("�Էµ� ���ڰ� �ߺ��˴ϴ�. �ٽ� �Է����ּ���.\n");
					player_data_input(player, max_num);
					i = -1;
					break;
				}
			}
		}

		printf("\n");
		printf("����� �߸� : ");
		for (i = 0; i < max_num; i++)
		{
			printf("%d ", player[i]);
		}
		printf("\n");

		challenge_time++;
		printf("%d��° ���� ��� : ", challenge_time);
		judge_result(computer, player, &strike, &ball, max_num);
		printf("\n");

		if (strike == max_num)
		{
			puts("Game Over!");
			break;
		}
	}

	return 1;
}

void set_com_data(int* computer, int max_num)
{
	int i, j;

	srand(time(NULL)); // ����ð��� �̿��ؼ� ���� ����

	for (i = 0; i < max_num; i++) // ��ǻ�Ͱ� �������� ���ڸ� �����Ѵ�.
	{
		int temp;
		
		computer[i] = rand() % 9;
		temp = computer[i];
		
		for (j = 0; j < i; j++)
		{
			if (computer[i] == computer[j])
			{
				i--;
				break;
			}
		}
	}
}

void player_data_input(int* player, int max_num)
{
	int i;

	printf("%d���� ���� ���� : ", max_num);

	for (i = 0; i < max_num; i++) // �Է�
	{
		scanf_s("%d", &player[i]);
	}
}

void judge_result(int* computer, int* player, int* strike, int* ball, int max_num)
{
	int i, j, check; // ���� check�� player�� �迭���� �ϳ��� ������ ������ �� ���ڰ� ��ġ���� �´��� Ȯ���ϱ� ���ؼ� ������ ����

	for (i = 0; i < max_num; i++)
	{
		check = player[i];

		for (j = 0; j < max_num; j++)
		{
			if (check == computer[j] && i == j)
			{
				(*strike) += 1;
			}
			
			if (check == computer[j] && i != j)
			{
				(*ball) += 1;
			}
		}
	}

	if (*strike == 0 && *ball == 0)
	{
		printf("out!!\n");
	}
	else
	{
		printf("%d strike, %d ball!!\n", *strike, *ball);
	}
}