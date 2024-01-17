#include <fcntl.h>
#include "syscalls.h"
#include <stdio.h>
#define PERMS 0666		/* RW for owner, group, others */

#undef fopen

int _fillbuf(FILE *fp);

FILE _iob[FOPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, __SRD, 0 },
	{ 0, (char *) 0, (char *) 0, __SWR, 1 },
	{ 0, (char *) 0, (char *) 0, __SWR | __SNBF, 2 }
};

FILE *fopen2(char *name, char *mode)
{
	int _file;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + FOPEN_MAX; fp++)
		if ((fp->_flags & (__SRD | __SWR)) == 0)
			break;
	if (fp >= _iob + FOPEN_MAX)
		return NULL;
	if (*mode == 'w')
		_file = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((_file = open(name, O_WRONLY, 0)) == -1)
			_file = creat(name, PERMS);
		lseek(_file, 0L, 2);
	} else
		_file = open(name, O_RDONLY, 0);
	if (_file == -1)
		return NULL;
	fp->_file = _file;
	fp->_lbfsize = 0;
	fp->_bf = NULL;
	fp->_flags = (*mode == 'r') ? __SRD : __SWR;
	return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->_flags & (__SRD | __SEOF | __SERR)) != __SRD)
		return EOF;
	bufsize = (fp->_flags & __SNBF) ? 1 : BUFSIZ;
	if (fp->_bf == NULL)
		if ((fp->_bf = (short *) malloc(bufsize)) == NULL)
			return EOF;
	fp->_p = fp->_bf;
	fp->_lbfsize = read(fp->_file, fp->_p, bufsize);
	if (--fp->_lbfsize < 0) {
		if (fp->_lbfsize == -1)
			fp->_flags |= __SEOF;
		else
			fp->_flags |= __SERR;
		fp->_lbfsize = 0;
		return EOF;
	}
	return (unsigned char) *fp->_p++;
}
