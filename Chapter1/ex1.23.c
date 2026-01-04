// /*
// Exercise 1-23:
// Write a program to remove all comments from a C program.
// Handle strings and character constants properly.
// */

// #include <stdio.h>
// int main()
// {
//     int c, prev = 0;
//     int in_comment = 0;
//     int in_string = 0;
//     int in_char = 0;
//     while ((c = getchar()) != EOF)
//     {
//         if (in_comment)
//         {
//             if (prev == '*' && c == '/')
//                 in_comment = 0;
//         }
//         else if (in_string)
//         {
//             putchar(c);
//             if (c == '"' && prev != '\\')
//                 in_string = 0;
//         }
//         else if (in_char)
//         {
//             putchar(c);
//             if (c == '\'' && prev != '\\')
//                 in_char = 0;
//         }
//         else
//         {
//             if (prev == '/' && c == '*')
//             {
//                 in_comment = 1;
//                 prev = 0;
//                 continue;
//             }
//             else if (c == '"')
//             {
//                 in_string = 1;
//                 putchar(c);
//             }
//             else if (c == '\'')
//             {
//                 in_char = 1;
//                 putchar(c);
//             }
//             else if (prev)
//                 putchar(prev);
//         }
//         prev = c;
//     }
//     return 0;
// }


#include <stdio.h>

int main(){
	int state = 0;
	int state1 = 0;
	char c;
	while(!state && (c=getchar())!=EOF){
		if(c == '\"'){
			state1 = !state1;
			putchar('\"');
		}
		else if(state1 == 0 && c == '/'){
			char d = getchar();
			if(d == '/'){
				char h = getchar();
				if(h == EOF){
					break;
				}
				while(h!='\n'){
					h = getchar();
					if(h == EOF){
						state = 1;
						break;
					}
				}
				if(!state)
				putchar('\n');
			}
			else if(d == '*'){
				char h = getchar();
				if(h == EOF){
					break;
				}
				else{
					char j = getchar();
					if(j == EOF){
						break;
					}
					else{
						while(!(h=='*' && j=='/')){
							h = j;
							j = getchar();
							if(j == EOF){
								state = 1;
								break;
							}
						}
					}
				}
			}	
			else{
				putchar(c);
				if(d == EOF){
					break;
				}
				putchar(d);
				if(d == '\"'){
					state1 = !state1;
				}
						
			}
			
			
		}
		else{
			putchar(c);
		}
	}
}