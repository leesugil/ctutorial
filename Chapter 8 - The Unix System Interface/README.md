## 8. The UNIX System Interface
	1. File Descripters
		* More low-level I/O control than file pointers which are part of the standard C library.
		* Whenever the command interpreter (the shell) runs a program, three files are open
			* 0: stdin
			* 1: stdout
			* 2: stderr
	2. Low Level I/O - Read and Write
		* read(fd, buf, n)
			* n bytes read from fd is stored in buf
			* calling read successively reads next n bytes
			* read(0, &c, 1) reads from stdin
		* write(fd, buf, n)
			* n bytes are written into fd from buf
			* calling write successivey writes in the next n bytes
		* n = 1: unbuffered
		* n = BUFSIZ: some pre-defined number (power of 2) corresponding to a physical block size on a peripheral device.
		* static char buf[BUFSIZE]; there's nothing special about buffer. it can by any (static) character array.
	3. Open, Creat, Close, Unlink
		* fd = open(name, flags, perms);
			* flags: O_RDONLY, O_WRONLY, O_RDWR
			* perms: 0
		* fd = creat(name, perms);
			* deletes original file if it exists.
			* perms: ugo, rwx == 421
		* close(fd) ~ fclose(fp)
		* unlink(name) ~ remove: deletes the file.
	4. Random Access - Lseek
		* lseek(fd, offset, origin)
			* origin 0: offset from the beginning
			* origin 1: offset from the current position
			* origin 2: offset from the end of the file
			* returns the updated position in long (hense "long" seek) offset from the beginning
	5. Example - An implementation of Fopen and Getc
		* Example codes were too system-dependant and time-consuming for converting it into macOS, Fedora OS, and Windows 11 at the same time.
	6. Example - Listing Directories
		* Example codes were too system-dependant and time-consuming for converting it into macOS, Fedora OS, and Windows 11 at the same time.
	7. Example - A Storage Allocator
		* Example codes were too system-dependant and time-consuming for converting it into macOS, Fedora OS, and Windows 11 at the same time.
