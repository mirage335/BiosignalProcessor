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
#include <getopt.h>

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
	char *inFileName;													//In file name.
	char *outFileName;													//Out file name.
} PROGRAM_OPTIONS;


//LABEL Global constructor functions.
PROGRAM_OPTIONS createPROGRAM_OPTIONS() {
	PROGRAM_OPTIONS prototypeProgramOptions;
	prototypeProgramOptions.inFileName = "-";										//Standard input default.
	prototypeProgramOptions.outFileName = "-";										//Standard output default.
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
//Overuse can cause data and precision loss, especially with non-float variables. Additionally, this filter's passband may not be flat.
//State variable filteredValue should be statically declared.
#define lowPass(newValue, filteredValue, inertiaFloat)                            \
  filteredValue = filteredValue + (inertiaFloat * (newValue - filteredValue));

//IIR Biquad Filter.
//Parameters b0, b1, b2, a1, a2 are filter coefficients. See http://gnuradio.4.n7.nabble.com/IIR-filter-td40994.html and http://www.earlevel.com/main/2013/10/13/biquad-calculator-v2/ .
//Data is returned in the double named [filteredValue] . This variable must be externally declared.
//State variables unique_d1_name and unique_d2_name should be statically declared doubles.
#define IIRbiquad(newValue, filteredValue, unique_d1_name, unique_d2_name, b0, b1, b2, a1, a2)			\
														\
	filteredValue = b0 * newValue + unique_d1_name;								\
	unique_d1_name = (double)b1 * (double)newValue + (double)a1 * filteredValue + unique_d2_name; 	\
	unique_d2_name = (double)b2 * (double)newValue + (double)a2 * filteredValue;

//High Order IIR Biquad Filter.
//Parameters b0, b1, b2, a1, a2 are filter coefficients. See http://gnuradio.4.n7.nabble.com/IIR-filter-td40994.html and http://www.earlevel.com/main/2013/10/13/biquad-calculator-v2/ .
//Data is returned in the double named [filteredValue] .
#define highOrderIIRbiquad(newValue, filteredValue, stateOneArrayName, stateTwoArrayName, b0, b1, b2, a1, a2, filterOrder)	\
	static double stateOneArrayName[(filterOrder+1)];									\
	static double stateTwoArrayName[(filterOrder+1)];									\
																\
	static int filterLoop;													\
																\
	static double lowerOrderFilteredValue;											\
	lowerOrderFilteredValue = newValue;											\
																\
	for (filterLoop=0; filterLoop < filterOrder; filterLoop++) {								\
		IIRbiquad(lowerOrderFilteredValue, filteredValue, stateOneArrayName[filterLoop], stateTwoArrayName[filterLoop], b0, b1, b2, a1, a2) \
		lowerOrderFilteredValue = filteredValue;									\
	}															\
  
//Core DSP processing chain.
inline double processData(double newData) {
	
	static double filteredData = 0;
	
	highOrderIIRbiquad(newData, filteredData, firstStateOne, firstStateTwo, 0.0004944331277135562, 0, -0.0004944331277135562, 0.29089453130818355, -0.9990111337445728, 100);
	
	#ifdef VERBOSE
	printf("%1.32f\n", newData);
	#endif
	
	return filteredData * 1000000;
} //end processData

void helpMessage() {
	printf("-i --inputFile		S32_LE audio input file. \"-\" for standard input (default)\n");
	printf("-o --outputFile		S32_LE audio output file. \"-\" for standard output (default)\n");
}

//Processes command line arguments with getopt, storing results in global programOptions variable.
void optionProcessor(int argc, char *argv[]) {
	while (1) {
	
		//Structure defining long options. These are passed with double dashes.
		static struct option long_options[] = {
			//Format: {"longarg", argument_requirement, flag, value/index},...{}
			{"inputFile", required_argument,       0, 'i'},
			{"outputFile", required_argument,       0, 'o'},
			{"help", no_argument,       0, 'h'},
			{0,         0,                 0,  0}
		};
		
		/* getopt_long stores the option index here. */
		int option_index = 0; //Initialize variable.
		int c = getopt_long (argc, argv, "i:o:h", long_options, &option_index); //The colons indicate which arguments take parameters. One for required, two for optional.
		
		/* Detect the end of the options. */
		if (c == -1)
			break;
		
		//Switch statement detects options by their indices.
		switch (c) {
			case 0:
				#ifdef DEBUG
				printf("option %s", long_options[option_index].name);
				if (optarg)
					printf(" with arg %s", optarg);
				#endif
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
					break;
				
			case 'i':
				programOptions.inFileName = optarg;
				break;
			
			case 'o':
				programOptions.outFileName = optarg;
				break;
			
			case 'h':
				helpMessage();
				break;
				
			case '?':
				/* getopt_long already printed an error message. */
				break;
		
			default:
				abort ();
		}
	}
} //end optionProcessor

//Program entry point.
int main (int argc, char *argv[]) {
	setvbuf(stdout,NULL,_IONBF, 0);		//Permits use of printf() where it would otherwise not produce output.

	constructGlobalVariables();		//Immediately construct global variables.
	
	optionProcessor(argc, argv);			//Process command line arguments.
	
	// Code derrived from libsndfile examples. See the libsndfile directory for additional licensing details.
	
	SNDFILE *infile = NULL ;
	SNDFILE *outfile = NULL;
	
	SF_INFO in_sfinfo ;
	SF_INFO out_sfinfo ;
	
	// ArduinoDAQ/Mirage335BiosignalAmplifier data format. Also known as S32_LE .
	in_sfinfo.channels		= 1 ;
	in_sfinfo.format = SF_FORMAT_RAW | SF_FORMAT_PCM_32 | SF_ENDIAN_LITTLE;
	
	// Baudline data format. Also known as le32f .
	out_sfinfo.channels		= 1 ;
	out_sfinfo.format = SF_FORMAT_RAW | SF_FORMAT_FLOAT | SF_ENDIAN_LITTLE;
	
	
	if ((infile = sf_open (programOptions.inFileName, SFM_READ, &in_sfinfo)) == NULL) {
		printf ("Invalid input file.\n") ;
		puts (sf_strerror (NULL)) ;
		return ProcessOperationNotPermitted ;
	}
	
	if ((outfile = sf_open (programOptions.outFileName, SFM_WRITE, &out_sfinfo)) == NULL) {
		printf ("Invalid output file.\n") ;
		puts (sf_strerror (NULL)) ;
		return ProcessOperationNotPermitted ;
	}
	
	//CAUTION: BLOCK_SIZE may determine latency. Lower is better.
	#define BLOCK_SIZE 4
	double readBuf [1 * BLOCK_SIZE] ;
	double writeBuf [1 * BLOCK_SIZE];
	int k, m, readcount ;
	while ((readcount = sf_readf_double(infile, readBuf, BLOCK_SIZE)) > 0)
	{	for (k = 0 ; k < readcount ; k++)
		{	for (m = 0 ; m < 1 ; m++)
				writeBuf[k * 1 + m] = processData(readBuf[k * 1 + m]);	//Read data out to processing function (DSP chain) one double precision float at a time.
		}
		
		//Write out buffer to file.
		sf_writef_double(outfile, writeBuf, readcount);
	}
	
	sf_close (infile) ;
	
	return ProcessNoError;			//Program finished without fatal errors or exit statement.
} //end main
