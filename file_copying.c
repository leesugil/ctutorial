#include <stdio.h>

/* copy input to output; going back to the 1st version */

/* important note. at first i didn't understand how/why this works, but then i realized that this confusion is EXACTLY what the second paragraph of the section in page 18 is describing about.
 * when i declare
 * c = getchar();
 * , my misperception was that getchar() is just a feature to accept an input text stream, and
 * however long the input text stream is, the whole text stream will be stored in the variable c.
 * this didn't exactly match with the description of what getchar() does, but i assumed
 * (after the whole 7 years of phd study, i still arrogantly assume things when i don't
 * completely understand exactly what the author is saying, haha.)
 * that the input text stream as a whole should be somewhere stored as a variable first
 * in order to be analized as the first character of it, the second character of it, etc.
 * this is also a very python-oriented view,
 * but after playing with the code a litte, i figured it's a different layer of abstraction.
 * as the second paragraph explains, i don't have to "write down" an input text stream into
 * a variable like c.
 * instead, the standard library handles it, and the whole input sequence is already stored somewhere
 * in the memory.
 * what we to is to use getchar() once to access the first character of the input stream,
 * store the value in a variable like c,
 * display it (without change of line),
 * use getchar() again to access the next (second) character of the inpute stream,
 * store the value and display it (again without change of line),
 * until we hit the EOF which always exists at the end given an input stream (and follows the visual end of line of the empty character.).
 * that's why however lengthy input i provide such as 'abc', it looked like the code just copied 'abc',
 * but it wasn't that c WAS 'abc' from the beginning,
 * but c was 'a', then 'b', then 'c' through the loop.
 * and since char variable only contains 0~255 ascii code (double check),
 * they needed to use the int variable to express the EOF (which is like -1?).
 * python is indeed more conceptually close to scientific thinking,
 * whereas c is literally talking with the machine.
 * now whether the standard library can understand the input stream from a given machine or not is a different issue,
 * and i don't think i should be worried about ever encountering a device that c is not supported now.
 *
 * and of course the program was never meant to "close" and to back to the consol command line when the getchar() hit EOF.
 * instaed it just demands a new input.
 *
 * follow-up questions:
 * 1) what if i provide more input while the code is learning?
 * 2) how about special function keys such as arrows?
 *
 * i love learning.
 */

main()
{
	int c;

	c = getchar();
	while (c != EOF) {
		putchar(c);
		c = getchar();
	}
}

