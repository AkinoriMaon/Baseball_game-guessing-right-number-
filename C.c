// Visual Studio에서 작성된 코드입니다.

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
	int i, j, strike = 0, ball = 0, challenge_time = 0, max_num = 0; // challenge_time : 도전 횟수를 저장할 변수, max_num : 최대 몇 자리의 수까지 도전할 것인지를 결정하는 변수

	printf("최대 몇 자리 수에 도전하시겠습니까? : ");
	scanf_s("%d", &max_num);
	system("cls");

	computer = (int*)malloc(sizeof(int) * max_num);
	player = (int*)malloc(sizeof(int) * max_num);

	if (computer == NULL || player == NULL)
	{
		puts("메모리 할당에 실패했습니다. 프로그램을 종료합니다.");
		return -1;
	}

	set_com_data(computer, max_num);

	puts("Start Game!");
	puts("number range : 0 ~ 9");

	while (1) // 플레이어가 3strike를 하기 전까지는 계속 반복되어야 하므로 무한 반복 설정
	{
		strike = 0;
		ball = 0;

		player_data_input(player, max_num);

		for (i = 0; i < max_num; i++)
		{
			if (player[i] < 0 || player[i] > 9) // 숫자 범위를 넘어섰는지 체크
			{
				puts("숫자 범위를 벗어났습니다. 다시 입력해주세요.\n");
				player_data_input(player, max_num);
				i = -1;
				continue;
			}

			for (j = 0; j < i; j++) // 중복 체크
			{
				if (player[i] == player[j])
				{
					puts("입력된 숫자가 중복됩니다. 다시 입력해주세요.\n");
					player_data_input(player, max_num);
					i = -1;
					break;
				}
			}
		}

		printf("\n");
		printf("당신의 추리 : ");
		for (i = 0; i < max_num; i++)
		{
			printf("%d ", player[i]);
		}
		printf("\n");

		challenge_time++;
		printf("%d번째 도전 결과 : ", challenge_time);
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

	srand(time(NULL)); // 현재시간을 이용해서 씨드 설정

	for (i = 0; i < max_num; i++) // 컴퓨터가 무작위로 숫자를 설정한다.
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

	printf("%d개의 숫자 선택 : ", max_num);

	for (i = 0; i < max_num; i++) // 입력
	{
		scanf_s("%d", &player[i]);
	}
}

void judge_result(int* computer, int* player, int* strike, int* ball, int max_num)
{
	int i, j, check; // 변수 check는 player의 배열에서 하나의 정수를 빼내서 그 숫자가 위치까지 맞는지 확인하기 위해서 생성한 변수

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