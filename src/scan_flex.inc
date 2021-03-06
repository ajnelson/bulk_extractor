/* include file for flex-based scanners.
 *
 * The outer parent class is yyFlexLexer,
 * which is #defined to be the name specified by the flex
 * %option prefix="foo" .
 *
 * However, flex provides the class definition and the constructor.
 * This means that we cannot add additional instance variables.
 * Such variables are useful.
 *
 * The flex-created class has a function called yyFlexLexer::LexerInput
 * which is NOT virtual and which IS called from the class.
 * 
 * But this class is only called from the YY_INPUT macro which tags
 * three arguments:
 *
 *    YY_INPUT(buf,count_read,count_to_read).
 * 
 * So we create a new YY_INPUT which calls the LexerInput in
 * the subclass.
 * 
 * Notice that we do NOT want an interactive scanner:
 *
 * From the info page:

`-B, --batch, `%option batch''
     instructs `flex' to generate a "batch" scanner, the opposite of
     _interactive_ scanners generated by `--interactive' (see below).
     In general, you use `-B' when you are _certain_ that your scanner
     will never be used interactively, and you want to squeeze a
     _little_ more performance out of it.  If your goal is instead to
     squeeze out a _lot_ more performance, you should be using the
     `-Cf' or `-CF' options, which turn on `--batch' automatically
     anyway.

`-I, --interactive, `%option interactive''
     instructs `flex' to generate an interactive scanner.  An
     interactive scanner is one that only looks ahead to decide what
     token has been matched if it absolutely must.  It turns out that
     always looking one extra character ahead, even if the scanner has
     already seen enough text to disambiguate the current token, is a
     bit faster than only looking ahead when necessary.  But scanners
     that always look ahead give dreadful interactive performance; for
     example, when a user types a newline, it is not recognized as a
     newline token until they enter _another_ token, which often means
     typing in another whole line.
*/
      size_t pos;
      size_t point;
      bool   eof;
      const sbuf_t &sbuf;

#define YY_INPUT(buf,result,max_size)\
      result = LexerInput((char *)buf,(size_t)max_size); 

      size_t LexerInput(char *buf,size_t max_size){
      	      if(eof) return 0;
	      if((int)max_size < 0) max_size=0;
      	      int count = 0;
      	      if(max_size + point > sbuf.bufsize){
	         max_size = sbuf.bufsize - point;
              }
	      while(max_size > 0){
	         *buf = (char)sbuf[point];
		 buf++;
		 point++;
		 max_size--;
		 count++;
  	      }
	      return count;
      }
      virtual int yylex();
      void run(){
          while(yylex()!=0){
	  }
      }

