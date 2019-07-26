// Visual Studio���� �ۼ��� �ڵ��Դϴ�.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 3

void set_com_data(int* computer);
void player_data_input(int* player);
void judge_result(int* computer, int* player, int* strike, int* ball);

int main()
{
	int computer[MAX_SIZE];
	int player[MAX_SIZE];
	int i, j, strike = 0, ball = 0, challenge_time = 0; // ���� Ƚ���� ������ ����

	set_com_data(computer);

	puts("Start Game!");
	puts("number range : 0 ~ 9");

	while (1) // �÷��̾ 3strike�� �ϱ� �������� ��� �ݺ��Ǿ�� �ϹǷ� ���� �ݺ� ����
	{
		strike = 0;
		ball = 0;

		player_data_input(player);

		for (i = 0; i < MAX_SIZE; i++)
		{
			if (player[i] < 0 || player[i] > 9) // ���� ������ �Ѿ���� üũ
			{
				printf("���� ������ ������ϴ�. �ٽ� �Է����ּ���.\n");
				printf("\n");
				player_data_input(player);
				i = -1;
				continue;
			}

			for (j = 0; j < i; j++) // �ߺ� üũ
			{
				if (player[i] == player[j])
				{
					printf("�Էµ� ���ڰ� �ߺ��˴ϴ�. �ٽ� �Է����ּ���.\n");
					printf("\n");
					player_data_input(player);
					i = -1;
					break;
				}
			}
		}

		printf("\n");
		printf("����� �߸� : ");
		for (i = 0; i < MAX_SIZE; i++)
		{
			printf("%d ", player[i]);
		}
		printf("\n");

		challenge_time++;
		printf("%d��° ���� ��� : ", challenge_time);
		judge_result(computer, player, &strike, &ball);
		printf("\n");

		if (strike == 3)
		{
			puts("Game Over!");
			break;
		}
	}

	return 1;
}

void set_com_data(int* computer)
{
	int i, j;

	srand(time(NULL)); // ����ð��� �̿��ؼ� ���� ����

	for (i = 0; i < MAX_SIZE; i++) // ��ǻ�Ͱ� �������� ���ڸ� �����Ѵ�.
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

void player_data_input(int* player)
{
	int i;

	printf("%d���� ���� ���� : ", MAX_SIZE);

	for (i = 0; i < MAX_SIZE; i++) // �Է�
	{
		scanf_s("%d", &player[i]);
	}
}

void judge_result(int* computer, int* player, int* strike, int* ball)
{
	int i, j, check; // ���� check�� player�� �迭���� �ϳ��� ������ ������ �� ���ڰ� ��ġ���� �´��� Ȯ���ϱ� ���ؼ� ������ ����

	for (i = 0; i < MAX_SIZE; i++)
	{
		check = player[i];

		for (j = 0; j < MAX_SIZE; j++)
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

	if (*strike != 0 && *ball != 0)
	{
		printf("%d strike, %d ball!!\n", *strike, *ball);
	}
	else
	{
		printf("out!!\n");
	}
}