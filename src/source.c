/* Skeleton: General purpose advanced C source file template.*/


//LABEL Consistent comments list:
//NoDebug																		//Line normally processed, not processed for debugging purposes.
//T-ODO																			//Minus the hyphen, pseudocode regarding needed work.
//L-ABEL																		//Minus the hyphen, marks location of major code standard to C projects.
//NOT_FINAL!																		//Bad code, do not release.


//LABEL Header file includes.
//Local libraries.


//System libraries.
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
extern __pid_t getsid (__pid_t __pid) __THROW;
#include <libgen.h>
#include <fcntl.h>
#include <stdarg.h>

#include <sndfile.h>

//OS specific libraries.
#if defined (__SVR4) && defined (__sun)												//IF Solaris...
#include <sys/mkdev.h>																//...include relevant library for device number lookups.
#endif


//LABEL Preprocessor DEBUG directives. Ideally, these flags should be set by cmake.
//NoDebug #define DEBUG																		//DEBUG. Comment with NoDebug to compile a non-debug version of the program.
//NoDebug #define VERBOSE																	//VERBOSE debug. Comment with NoDebug to compile a non-debug version of the program.


//LABEL Define constants generally useful for notation purposes.
#define ProcessNoError	0															//Successful program exit.
#define ProcessOperationNotPermitted	1											//UNIX standard error code.
#define ProcessDEBUG	-1															//Use  error code -1 to indicate program is compiled for debugging.
#define RetrievalFailure	-2001281329												//Indicates failure of a function using offsets to retrieve valid data. Large negative number ensures against collisions with positive offsets.


//LABEL Global typedefs and other program specific preprocessor directives.
typedef enum { false = 0, true = 1 } bool;											//Emulates boolean functionality. Lower case type name represents highly generic fun

//Stores the program options.
typedef struct {
	bool optionOne;																	//Signals the "?" option.
	bool optionTwo;																	//Signals the "?" option.
} PROGRAM_OPTIONS;


//LABEL Global constructor functions.
PROGRAM_OPTIONS createPROGRAM_OPTIONS() {
	PROGRAM_OPTIONS prototypeProgramOptions;
	prototypeProgramOptions.optionOne = false;
	prototypeProgramOptions.optionTwo = false;
	return prototypeProgramOptions;
} //end createPROGRAM_OPTIONS


//LABEL Global variables declarations.
PROGRAM_OPTIONS programOptions;


//LABEL Support functions.
//Eats up unwanted characters after fgets. Do not use unless unwanted characters are known to exist. Cavet: Combination of EOF and excessive characters will lead fgets to prompt user for yet another line. However, this is at least less severe than leaving characters on the buffer.
inline void flushSTDIN() {
	char unwantedCharacters[10];
	while((fgets(unwantedCharacters, 10, stdin) != NULL) && !strchr(unwantedCharacters, '\n'));
} //end flushSTDIN

//Checks a pointer for NULL status, and quits with error message.
inline void detectMallocFailure(void *pointerToCheck) {
	if (pointerToCheck == NULL) {
		printf("FATAL: Memory allocation failed.\n");
		exit(errno);
	}
} //end detectMallocFailure

//Checks a pointer for NULL status, and quits with error message. Intended for fopen error checking.
inline void detectFopenFailure(void *pointerToCheck) {
	if (pointerToCheck == NULL) {
		printf("FATAL: Attempt to open file failed. Bad filename?\n");
		exit(errno);
	}
} //end detectFopenFailure

//Checks an integer for EOF, and quits with error message. Intended for fclose error checking.
inline void detectFcloseFailure(int integerToCheck) {
	if (integerToCheck == EOF) {
		printf("FATAL: Attempt to close file failed.\n");
		exit(errno);
	}
} //end detectFcloseFailure

//Handles file stat failure.
inline void handleStatFailure() {
	printf("FATAL: File stat operation failed.\n");
	exit(errno);
} //end handleStatFailure

//Checks an integer for nonzero status, and quits with error message. Intended for pipe error checking.
inline void detectPipeCreationFailure(int pipeResultToCheck) {
	if (pipeResultToCheck != 0) {
		printf("FATAL: Parent-child interprocess communication pipe creation failed.");
		exit(errno);
	}
} //end detectPipeCreationFailure

//Underlying function to permit dynamic creation of new string with sprintf. Unlike sprintf however, this RETURNS a pointer to the new string which MUST be FREE'd to prevent memory leaks.
char *dynamicSprintf(char *formatString, ...) {
	va_list variableArguments;																		//Declares variableArguments as type va_list.

	va_start(variableArguments, formatString);														//Initializes variableArguments as just past the formatString in the parameter list.
	#ifndef S_SPLINT_S //Do NOT cause splint to fail over this code.
	int stringLength = (vsnprintf(NULL, 0, formatString, variableArguments) + 1) * sizeof(char);	//Determines the number of bytes vsnprintf tries to use plus a null terminator.
	#endif //end S_SPLINT_S
	va_end(variableArguments);																		//Ends the variableArguments after vsnprintf has executed.


	#ifndef S_SPLINT_S //Do NOT cause splint to fail over this code.
	char *prototypeCharPointer = malloc(stringLength * sizeof(char));												//Mallocs a sufficiently sized string.
	#endif //end S_SPLINT_S
	detectMallocFailure(prototypeCharPointer);
	memset(prototypeCharPointer,'\0',stringLength * sizeof(char));

	va_start(variableArguments, formatString);														//Initializes variableArguments as just past the formatString in the parameter list.
	vsnprintf(prototypeCharPointer, stringLength, formatString, variableArguments);					//Actually creates and stores new string to prototypeCharPointer.
	va_end(variableArguments);																		//Ends the variableArguments after vsnprintf has executed.

	return prototypeCharPointer;
} //end dynamicSprintf

//Forks to a new process with bidirectional piping. Parent and child functions should be able to accept file descriptor parameters RECEIVE and XMIT.
#define doFork(parentFunction, childFunction) {																						\
	/*Simply creates pipes. These may be read and written to by any part of this program like a normal file.*/						\
	int parentToChild [2];																											\
	int	childToParent[2];																											\
	detectPipeCreationFailure(pipe(parentToChild));	/*Create pipe for parent to issue orders.*/										\
	detectPipeCreationFailure(pipe(childToParent));	/*Create pipe for child to talk back.*/											\
																																	\
	pid_t forkResult;																												\
	if((forkResult = fork()) < 0) { /*Error condition.*/																			\
			printf("FATAL: Child process creation failed.");																		\
			exit(errno);																											\
	}																																\
	else if(forkResult != 0) {	/*Parent will execute following code concurrently with the child.*/									\
		/*Close unneeded pipes.*/																									\
		close(parentToChild[0]);	/*parentToChild[0] = CHILD_RECEIVE*/															\
		close(childToParent[1]);	/*childToParent[1] = CHILD_XMIT*/																\
																																	\
		parentFunction(childToParent[0], parentToChild[1]); /*childToParent[0] = PARENT_RECEIVE parentToChild[1] = PARENT_XMIT*/	\
																																	\
		/*Close no longer needed pipes.*/																							\
		close(childToParent[0]);		/*childToParent[0] = PARENT_RECEIVE*/														\
		close(parentToChild[1]);		/*parentToChild[1] = PARENT_XMIT*/															\
	}																																\
	else if(forkResult == 0) {	/*Child will execute following code concurrently with the parent.*/									\
		/*Close unneeded pipes.*/																									\
		close(childToParent[0]);	/*childToParent[0] = PARENT_RECEIVE*/															\
		close(parentToChild[1]);		/*parentToChild[1] = PARENT_XMIT*/															\
																																	\
		childFunction(parentToChild[0], childToParent[1]); /*parentToChild[0] = CHILD_RECEIVE childToParent[1] = CHILD_XMIT*/		\
																																	\
		exit(ProcessNoError); /*After above function has run, discontinue child process. Otherwise it will imitate its parent.*/	\
																																	\
		/*Close no longer needed pipes.*/																							\
		close(parentToChild[0]);	/*parentToChild[0] = CHILD_RECEIVE*/															\
		close(childToParent[1]);	/*childToParent[1] = CHILD_XMIT*/																\
	}																																\
} //end createFork


//LABEL Global variable constructions. The function below should be the first thing called in main() to workaround global variable limitations on constructors.
void constructGlobalVariables() {
	programOptions = createPROGRAM_OPTIONS();
} //end constructGlobalVariables


//LABEL Functions to manipulate structures that require some accounting. Functionality not provided by these functions should be safe to use directly (eg. structureName.elementName).


//LABEL General program functions start here.

//Macro function for low pass filter.
//Overuse can cause data and precision loss, especially with non-float variables.
#define lowPass(newValue, filteredValue, inertiaFloat)                            \
  filteredValue = filteredValue + (inertiaFloat * (newValue - filteredValue));

//Automatically cascades low pass filters, returning the final value as arrayName[filterLoop] .
//The arrayName is not important, however, the array must retain values from one cycle to the next (ie. static).
#define highOrderLowPass(newValue, inertiaFloat, filterOrder, arrayName)          \
  static float arrayName[(filterOrder+1)];                                        \
  arrayName[0] = newValue;                                                        \
  static int filterLoop;                                                          \
  for (filterLoop=0; filterLoop < filterOrder; filterLoop++)                      \
    lowPass(arrayName[filterLoop], arrayName[filterLoop+1], inertiaFloat);


//Core DSP processing chain.
inline double processData(double newData) {
	static double lastData;
	
	#ifdef VERBOSE
	printf("%1.32f\n", newData);
	#endif
	
} //end processData

//Program entry point.
int main (int argc, char *argv[], char **envp) {
	setvbuf(stdout,NULL,_IONBF, 0);		//Permits use of printf() where it would otherwise not produce output.

	constructGlobalVariables();		//Immediately construct global variables.
	
	// Code derrived from libsndfile examples. See the libsndfile directory for additional licensing details.
	
	SNDFILE *infile = NULL ;
	SF_INFO sfinfo ;
	
	// ArduinoDAQ/Mirage335BiosignalAmplifier data format. Also known as S32_LE .
	sfinfo.channels		= 1 ;
	sfinfo.format = SF_FORMAT_RAW | SF_FORMAT_PCM_32 | SF_ENDIAN_LITTLE;
	
	
	if ((infile = sf_open ("-", SFM_READ, &sfinfo)) == NULL) {
		printf ("Invalid input file.\n") ;
		puts (sf_strerror (NULL)) ;
		return ProcessOperationNotPermitted ;
	}
	
	//CAUTION: BLOCK_SIZE may determine latency. Lower is better.
	#define BLOCK_SIZE 4
	double buf [1 * BLOCK_SIZE] ;
	int k, m, readcount ;
	while ((readcount = sf_readf_double (infile, buf, BLOCK_SIZE)) > 0)
	{	for (k = 0 ; k < readcount ; k++)
		{	for (m = 0 ; m < 1 ; m++)
				processData(buf [k * 1 + m]);
			} ;
		} ;
	
	sf_close (infile) ;
	
	return ProcessNoError;			//Program finished without fatal errors or exit statement.
} //end main
