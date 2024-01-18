## 7. Input and Output
	1. Standard Input and Output
		* stdin is set to the system keyboard by default.
		* getchar() returns the next input character each time it is called, or EOF when it encounters the of file.
		* prog \<infile
		* otherprog | prog
		* stdout is set to the system monitor by default.
		* putchar(c) puts the character c on stdout. returns the character written, or EOF if an error occurs.
		* prog \>outfile
		* prog | anotherprog
	2. Formatted Output - printf
		* %-15.10s
		* sprintf(char \*string, char \*format, arg1, arg2, ...);
	3. Variable-length Argument Lists
		* int printf(char \*fmt, ...);
		* va_list ap;	points to each unnamed arg in turn
		* va_start(ap, fmt);	make app point to 1st unnamed arg
		* va_end(ap);	clean up when done
	4. Formatted Input - scanf
		* scanf, sscanf
		* if (scanf("%d %s %d", &day, monthname, &year) == 3)
		* if (scanf("%d/%d/%d", &month, &day, &year) == 3)
	5. File Access
		* FILE \*fp
		* fp = fopen("filename", "r")
		* getc(fp)
		* putc(fp)
		* formatted input or output
		* fscanf(fp, fmt, ...)
		* fprintf(fp, fmt, ...)
		* fclose(fp)
	6. Error Handling - Stderr and Exit
		* fprintf(stderr, "error!\n");
		* exit(0), exit(1), ...
		* prog 2>/dev/null
	7. Line Input and Output
		* fgets(line, maxline+1, fp)
		* fputs(line, fp)
		* gets(line) == fgets(line, , stdin)
		* puts(line) == fputs(line, stdout)
	8. Miscellaneous Functions
		1. String Operations
			* strcat: string concatenate
			* strncat: string concatenate n characters only
			* strcmp: string comparison
			* strncmp: string comparison n characters only
			* strcpy: string copy
			* strncpy: string copy n characters only
			* strlen: string length
			* strchar: character in string
			* strrchar: character in string, reverse
			* strstr: substring in string
		2. Character Class Testing and Conversion
			* isalpha
			* isupper
			* islower
			* isdigit
			* isalnum
			* isspace
			* toupper
			* tolower
		3. Ungetc
			* similar to ungetc but uses FILE instead of custom buffer
		4. Command Execution
			* system("date");
		5. Storage Management
			* void \*malloc(size_t n)
			* void \*calloc(size_t n, size_t size)	array of n objects of size size
			* ip = (int \*) calloc(n, sizeof(int));
		6. Mathematical Functions
			* sin
			* cos
			* atan2	in radians
			* exp
			* log
			* log10
			* pow
			* sqrt
			* fabs
		7. Random Number generation
			* a = rand()
			* srand(0)
