#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

int mygetch()
{
    struct termios oldt, newt;
    int c;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}


int detect_long_key()
{
	int delete = 0;
	char begin = mygetch();
	switch (begin)
	{
		case '[':
		{
			char term_type = mygetch();
			if (isdigit(term_type))
			{
				char second_char = mygetch();
				switch (term_type)
				{
					case '1':
						switch (second_char)
						{
							case '0':
								printf("[F0]: ");
								break;
							case '1':
								printf("[F1]: ");
								break;
							case '2':
								printf("[F2]: ");
								break;
							case '3':
								printf("[F3]: ");
								break;
							case '4':
								printf("[F4]: ");
								break;
							case '5':
								printf("[F5]: ");
								break;
							case '6':
								printf("Unknown key: ");
								break;
							case '7':
								printf("[F6]: ");
								break;
							case '8':
								printf("[F7]: ");
								break;
							case '9':
								printf("[F8]: ");
								break;
							case '~':
								printf("[Home]: ");
						}
						if (second_char != '~')
						{
							printf("27 %d %d %d 126", begin, term_type, second_char);
							mygetch();
						}
						else
							printf("27 %d %d 126", begin, term_type);
						break; // case 1
					case '2':
						switch (second_char)
						{
							case '0':
								printf("[F9]: ");
								break;
							case '1':
								printf("[F10]: ");
								break;
							case '3':
								printf("[F11]: ");
								break;
							case '4':
								printf("[F12]: ");
								break;
							case '~':
								printf("[Insert]: ");
							default:
								printf("Unknown key: ");
						}
						if (second_char != '~')
						{
							printf("27 %d %d %d 126", begin, term_type, second_char);
							mygetch();
						}
						else
							printf("27 %d %d 126", begin, term_type);
						break; // case 2
					case '3':
						printf("[Delete]: 27 %d %d 126", begin, term_type);
						delete = 1;
						break;
					case '4':
						printf("[End]: 27 %d %d 126", begin, term_type);
						mygetch();
						break;
					case '5':
						printf("[Page Up]: 27 %d %d 126", begin, term_type);
						mygetch();
						break;
					case '6':
						printf("[Pg Down]: 27 %d %d 126", begin, term_type);
						mygetch();
						break;
					case '7':
						printf("[Home]: 27 %d %d 126", begin, term_type);
						mygetch();
						break;
					case '8':
						printf("[End]: 27 %d %d 126", begin, term_type);
						mygetch();
						break;
					case '9':
						printf("Unknown key: 27 %d %d 126", begin, term_type);
						break;
				}
			}
			else
			{
				switch (term_type)
				{
					case 'A':
						printf("[Up]: 27 %d %d", begin, term_type);
						break;
					case 'B':
						printf("[Down]: 27 %d %d", begin, term_type);
						break;
					case 'C':
						printf("[Right]: 27 %d %d", begin, term_type);
						break;
					case 'D':
						printf("[Left]: 27 %d %d", begin, term_type);
						break;
					case 'F':
						printf("[End]: 27 %d %d", begin, term_type);
						break;
					case 'G':
						printf("[Keypad 5]: 27 %d %d", begin, term_type);
						break;
					case 'H':
						printf("[Home]: 27 %d %d", begin, term_type);
						break;
					default:
						printf("Unknown key: 27 %d %d", begin, term_type);
				} //switch
			} // else
			break;
		}
		case 'O':
		{
			char letter = mygetch();
			switch (letter)
			{
				case 'P':
					printf("[F1]: 27 %d %d", begin, letter);
					break;
				case 'Q':
					printf("[F2]: 27 %d %d", begin, letter);
					break;
				case 'R':
					printf("[F3]: 27 %d %d", begin, letter);
					break;
				case 'S':
					printf("[F4]: 27 %d %d", begin, letter);
					break;
			}
		}
	}
	printf("\n");
	return delete;
}

int main()
{
	while (1)
	{
		char c = mygetch();
		if (c == 27)
		{
			if (detect_long_key() == 1)
				break;
		}
		else if (iscntrl(c))
		{
			printf("%d\n", c);
		}
		else
		{
			printf("%c\n", c);
		}
	}
	
	return 0;
}