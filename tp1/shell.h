#include <fcntl.h>

typedef struct scmd {
	char ** cmd;
	int size;
	int ret_type;
	int fetch_args;
	char * file_in;
	char * file_out;
	int pipe_in[2];		// 0 pour celui qui lit, 1 pour celui qui ecrit
	int pipe_out[2];	// pareil
} cmd;

typedef struct sdelete_elem {
	struct sdelete_elem * next;
	struct sdelete_elem * prev;
	void * to_delete;
} delete_elem; 

void start () {
	char str_input[100];
	int size, end;
	int cmd_type;
	int blocking_cmd;
	int i;

	for (i = 0; i < 100; i++)
		str_input[i] = ' ';
	
	while (1) {
		printf ("mtos %% ");
		fgets(str_input, 99, stdin);
		size = strlen(str_input);

		if (str_input[0] == 'q' && str_input[1] == 10)
			break;
		
		blocking_cmd = blocking (str_input, size, &end);
		size -= end;
		
		while ((cmd_type = last_cmd(str_input, size, &end)) != 0) {
			if (cmd_type == 1) {
				char * args[number_space(str_input, size-end)];
			}
		}
	}
}

int last_cmd (char * str, int size, int * end) {
	if (size > 0) {
		int a = size;
		while (a > 0) {
			if (str[a] == '|') {
				*end = size - a;
				return 2;
			}
			else if (str[a] == '<') {
				*end = size - a;
				return 3;
			}
			else if (str[a] == '>') {
				*end = size - a;
				return 4;
			}
			a--;
		}
		return 1;
	}
	else {
		return 0;
	}
}

int blocking (char * str, int size, int * end) {
	int a = size;
	while (a > 0) {
		if (str[a] == '&') {
			*end = size - a;
			return 1;
		}
	}
	return 0;
}

int number_space (char * str, int size) {
	int i = 0;
	int r = 0;
	while (i < size) {
		if (str[i] == ' ') {
			r++;
			while (str[i] == ' ') {
				i++;
				if (i == size){
					r--;
					break;
				}
			}
		}
		else {
			i++;
		}
	}
	return r;
}

void simple_cmd (char ** argv) {
	int pid;
	if ((pid = fork()) == 0) {
		execvp(argv[0], argv);
		exit(0);
	}
}

void tofile_cmd (cmd * c) {
	int fd;
	if ((fd = open(c->file_out, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR))) {
		printf ("Erreur ouverture fichier");
		return;
	}
	

	dup2(fd, 1);   
	dup2(fd, 2); 

	int pid;
	if ((pid = fork()) == 0) {
		execvp((c->cmd)[0], c->cmd);
		exit(0);
	}

	close(fd);     // fd no longer needed - the dup'ed handles are sufficient	
}

void topipe_cmd (cmd * c) { 
	close((c->pipe_out)[0]);
	
	dup2((c->pipe_out)[1], 1);   
	dup2((c->pipe_out)[1], 2); 

	int pid;
	if ((pid = fork()) == 0) {
		execvp((c->cmd)[0], c->cmd);
		close((c->pipe_out)[1]);
		exit(0);
	} 
}
