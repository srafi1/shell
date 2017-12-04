# shell    
Shell written in C | Systems MP2 Project  
  
## Features  
- Prompts for commands which are then run in child processes  
- Runs multiple commands on one line (separated by semicolons)  
- Redirects STDIN using < and STDOUT using >  
- Redirects both STDIN and STDOUT using |  
- Parses through and strips extra whitespace  
- Helps me pass this class!  
  
## Attempted features  
- Utilizing multiple pipes to create a chain of commands  
- Showing user/hostname in prompt before path  
  
## Bugs:  
- Redirecting STDIN from a file that doesn't exist makes the shell keep expecting input  
- Using multiple of |, <, or > may cause a seg fault  
## Function headers:  
  
============ shell.c ===============  
  
/* main():  
runs the shell in an infinite loop, constantly asking for input  
  
args:  
  
return:  
    exit code  
*/  
  
============ tokenizer.c ===========  
  
/* int count_char()  
counts the number of occurences of c in string  
  
args:  
    c: character to be counted  
    string: string to count from  
return:  
    number of occurences  
*/  
  
/* void shift_array_back_at  
moves array elements one position back  
  
args:  
    original: array to be modified  
    length: length of given array  
return:  
  
*/  
  
/* void shift_string_back_at  
moves characters one position back in string  
  
args:  
    original: string to be modified  
return:  
    character that was overwritten  
*/  
  
/* char strip_by  
looks for all occurences of delete_dis and removes the first character  
  
args:  
    original: string to be modified  
    delete_dis: substring to look for  
return:  
    character that is overwritten  
*/  
  
/* char strip_front_by  
looks for all occurences of delete_dis and removes the second character  
  
args:  
    original: string to be modified  
    delete_dis: substring to look for  
return:  
    character that is overwritten  
*/  
  
/* void strip_extra_blankspace  
strips all unnecessary whitespace from string  
  
args:  
    original: string to be modified  
return:  
  
*/  
  
/* void printarr  
prints out an array of strings  
  
args:  
    args: array of strings  
return:  
  
*/  
  
/* char* get_stdin  
gets the portion of the given input that should used for stdin  
  
args:  
    input: string to look through  
return:  
    filename to for stdin or NULL if not provided  
*/  
  
/* char* get_stdout  
gets the portion of the given input that should used for stdout  
  
args:  
    input: string to look through  
return:  
    filename to for stdout or NULL if not provided  
*/  
  
/* void delete_stdin  
deletes the portion of the given input that was used for stdin  
  
args:  
    input: string to look through  
return:  
  
*/  
  
/* void delete_stdout  
deletes the portion of the given input that was used for stdout  
  
args:  
    input: string to look through  
return:  
  
*/  
  
============ exec.c ================  
  
/* void exec_in_fork  
forks and then runs given command in the child process  
  
args:  
    command: command to be run  
    in: filename to look for stdin or NULL  
    out: filename to look for stdout or NULL  
return:  
  
*/  
  
/* void exec_pipe  
forks and then runs given commands, piping input from one to the other  
  
args:  
    cmd1: command to take input from  
    cmd2: command to give input to  
return:  
  
*/  
  
/* void exec_all_in_line  
splits line by semicolons and executes each portion separately  
  
args:  
    line: line of commands  
return:  
  
*/
