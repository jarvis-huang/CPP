/*
 * Project: MiniBasic
 * Created by CS106 Assignment Wizard 0.8
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <stdio.h>
#include "genlib.h"
#include "exception.h"
#include "strlib.h"
#include "simpio.h"
#include "exp.h"
#include "eval.h"
#include "parser.h"
#include "scanadt.h"
#include <ctype.h>
#include "symtab.h"

#define MaxStatementNum  1000
typedef void (*commandFnT)(scannerADT ,string *,int *);

typedef struct {
    commandFnT fn;
} *commandEntryT;

static symtabADT commandTable;

void Initializing();
string * InitStatement();
bool IsNumber(string token);
bool IsSuitableNumber(string token);
bool IsCommand(scannerADT scanner);
bool IsStatement(scannerADT scanner);
void InitCommandTable(void);
static void DefineCommand(string cmd, commandFnT fn);
void ExecuteCommand(scannerADT scanner,string *statement,int *num);
static void RemCmd(scannerADT scanner,string *statement,int *num);
static void GotoCmd(scannerADT scanner,string *statement,int *num);
static void HelpCmd(scannerADT scanner,string *statement,int *num);
static void EndCmd(scannerADT scanner,string *statement,int *num);
static void LetCmd(scannerADT scanner,string *statement,int *num);
static void PrintCmd(scannerADT scanner,string *statement,int *num);
static void InputCmd(scannerADT scanner,string *statement,int *num);
static void IfCmd(scannerADT scanner,string *statement,int *num);
static void ListCmd(scannerADT scanner,string *statement,int *num);
static void RunCmd(scannerADT scanner,string *statement,int *num);
bool IsRelation(string str);
bool Satisfied(expressionADT exp1,string relation,expressionADT exp2);

/*Extended function*/
static void ClearCmd(scannerADT scanner,string *statement,int *num);
bool IsPrintMessage(string line);



/* Main program */

/*
	What does the main do?
	Its main purpose is to do some initialization and to 
	distinguish what is command (without line number) and
	what is statement (with line number).For commands , do
	it immediately. For statements , store it in an array
	for later use.("RUN" will call them)
*/

main()
{
    scannerADT scanner;
    string line,token,*statement;
	int *number=GetBlock(sizeof(int));

	Initializing();
	*number=0;
	scanner = NewScanner();
    SetScannerSpaceOption(scanner, IgnoreSpaces);
	statement=InitStatement();

    while (TRUE) {
        try 
		{
			line = GetLine();
			if (StringEqual(ConvertToLowerCase(line), "quit") ) exit(0);
            SetScannerString(scanner, ConvertToLowerCase(line));
			if (!MoreTokensExist(scanner)) {continue;}
			token = ReadToken ( scanner );
			if (IsNumber(token))
			{
				if (IsSuitableNumber(token))
				{
					if (MoreTokensExist(scanner))
					{
						if (!IsCommand(scanner)) { statement[StringToInteger(token)]=line;}
					}
					else {statement[StringToInteger(token)]=NULL;}
				}
				else { printf("The line number must be less than 1000.\n\n"); }
			}
			else 
			{
				if (IsPrintMessage(line)) {;}
				else {
					SaveToken(scanner,token);
					if (!IsStatement(scanner)) {  ExecuteCommand(scanner,statement,number);}
				}
			}
			except(ErrorException)
            printf("Error: %s\n", (string) GetExceptionValue());
        } endtry
    }
}

void Initializing()
{
	printf("MiniBasic (type \"quit\" to exit and \"help\" for help)\n\n");
	InitVariableTable();
	InitCommandTable();
}

string * InitStatement()
{
	int i;
	string *statement;

	statement=GetBlock(MaxStatementNum * sizeof (string) );
	for (i=0;i<MaxStatementNum;i++)
	{
		statement[i]=NULL;
	}
	return statement;
}

/*
	Function :IsNumber
	----------------------
	This function returns TRUE if the string is an integer.
*/

bool IsNumber(string token)
{
	int i;
	int k=StringLength(token);

	for (i=0;i<k;i++)
	{
		if (!isdigit(token[i])) {return FALSE;}
	}
	return TRUE;
}

/*
	Function :IsSuitableNumber
	----------------------
	This function returns TRUE if the string is an suitable
	integer.That means betweeen 0 and 999,because the array 
	size is 1000.
*/

bool IsSuitableNumber(string token)
{
	int i;
	int k=StringLength(token);

	for (i=0;i<k;i++)
	{
		if (!isdigit(token[i])) {return FALSE;}
	}
	return StringToInteger(token)<MaxStatementNum;
}

bool IsCommand(scannerADT scanner)
{
	string token=ReadToken(scanner);
	if (StringEqual(token,"run")||StringEqual(token,"list")||
		StringEqual(token,"help")||StringEqual(token,"quit")||StringEqual(token,"clear"))
	{
		printf ("\"%s\" is a command and cannot have line number\n\n",ConvertToUpperCase(token));
		return TRUE;
	}
	else {  SaveToken(scanner,token);  return FALSE;}
}

bool IsStatement(scannerADT scanner)
{
	string token=ReadToken(scanner);
	if (StringEqual(token,"rem")||StringEqual(token,"goto")||
		StringEqual(token,"if")||StringEqual(token,"end"))
	{
		printf ("\"%s\" is a statement and must have line number\n\n",ConvertToUpperCase(token));
		return TRUE;
	}
	else {  SaveToken(scanner,token);  return FALSE;}
}

/*
	Extension Function : IsPrintMessage
	---------------------------------------------
	This function gives the "PRINT" command/statement an additional use.
	When you enter :

	PRINT 1+2

	you will see " 3 " immediately. However, 
	sometimes you want the computer to print something without calculating
	it (appears exactly as what you enter).
	Then you can add two quotation marks to it. For example ,if you enter:
				
	PRINT "1+2"

    you will see:

	1+2

	rather than 3.
	This helps you to give some instructions to the user.

	This function returns TRUE if it is a "PRINT" command/statement
	and FALSE if it is not. Checking whether it has quotation marks
	is included inside , but not affecting what it returns. Note that
	what betweem the quotation marks will be case sensitive, which means 
	a lowercase letter is still a lowercase letter when printed out.
*/

bool IsPrintMessage(string line)
{
	int a,b;
	scannerADT scanner=NewScanner();
	string str="",token;
	SetScannerString(scanner,ConvertToLowerCase(line));
	SetScannerSpaceOption(scanner, IgnoreSpaces);

	if ( ! StringEqual(ReadToken(scanner), "print") )  { return FALSE;}
	else
	{
		token=ReadToken(scanner);
		if ( ! StringEqual(token,"\""))   
		{ 
			SaveToken(scanner,token);
			printf("%d\n",EvalExp(ParseExp(scanner)));
		}
		else 
		{
			while (MoreTokensExist(scanner))
			{
				str=ReadToken(scanner);
				if (StringEqual(str,"\"")) {break;}
			}
			if ( StringEqual(str,"\"") && !MoreTokensExist(scanner) )
			{
				a=FindString("\"",line,0);
				b=FindString("\"",line,a+1);
				printf("%s\n",SubString(line,a+1,b-1));
			}
			else { Error("Illegal gramma of \"PRINT\""); }
		}
		return TRUE;
	}
}



void InitCommandTable(void)
{
    commandTable = NewSymbolTable();

    DefineCommand("rem", RemCmd);
    DefineCommand("run", RunCmd);
    DefineCommand("help", HelpCmd);
    DefineCommand("goto", GotoCmd);
    DefineCommand("if", IfCmd);
	DefineCommand("end", EndCmd);
	DefineCommand("let", LetCmd);
    DefineCommand("print", PrintCmd);
    DefineCommand("input", InputCmd);
    DefineCommand("list", ListCmd);
	DefineCommand("clear",ClearCmd);
}

static void DefineCommand(string cmd, commandFnT fn)
{
    commandEntryT entry;

    entry = New(commandEntryT);
    entry->fn = fn;
    Enter(commandTable, cmd, entry);
}

void ExecuteCommand(scannerADT scanner,string *statement,int *num)
{
    commandEntryT entry;
	string token;
	SetScannerSpaceOption(scanner, IgnoreSpaces);
	token=ReadToken(scanner);

	entry = Lookup( commandTable, token );
    if (entry == UNDEFINED) {
        printf("Undefined command: %s\n", token);
        return;
    }
    entry->fn(scanner,statement,num);
}

/* Command dispatch functions */

/*Some Explanations:
		Why every function below has a "int *num" argument ?
      --Because this pointer serves as a calculator when "RUN"
	    command runs the whole program ( an array actually ).
		The "RUN" command just operates every element in this
		array from 0 to 999 ,but several statements such as 
		"goto" often change this order.In order to trace what
		is going to be operated next,we store an integer in 
		that pointer,showing where the program is arriving at.
		When *num==1000,that means the program comes to the end.
*/

static void RemCmd(scannerADT scanner,string *statement,int *num)
{
    *num=*num+1;
}

static void GotoCmd(scannerADT scanner,string *statement,int *num)
{
    *num=EvalExp(ParseExp(scanner));
}

static void HelpCmd(scannerADT scanner,string *statement,int *num)
{
    printf("\nThis program implements a minimal interpreter.\n\n");
	printf("Commands:\n"
			"  RUN            --Runs current program\n"
			"  LIST           --Lists the program\n"
			"  HELP           --This message\n"
			"  QUIT           --Exits from interpreter\n"
			"  CLEAR          --Clears all statements entered before\n\n"
			"Statements:\n"
			"  REM...         --Remark\n"
			"  LET v=exp      --Assignment\n"
			"  PRINT v        --Reads value of expression\n"
			"  PRINT \"...\"    --Prints a message on screen without calculating\n"
			"  GOTO n         --Goes to line n\n"
			"  IF c THEN n    --Goes to line n if c is TRUE\n\n");
}

static void EndCmd(scannerADT scanner,string *statement,int *num)
{
    *num=MaxStatementNum;
}

static void LetCmd(scannerADT scanner,string *statement,int *num)
{
	string name;
	
	name=ReadToken(scanner);
	*num=*num+1;

	if ( StringEqual(ReadToken(scanner),"=") )
	{
		SetIdentifierValue ( name , EvalExp(ParseExp(scanner)) );
	}
	else 
	{
		Error("Illegal grammar of \"LET\".");
	}
}

static void PrintCmd(scannerADT scanner,string *statement,int *num)
{
	int n=FindString("p",ConvertToLowerCase(statement[*num]),0);
	int m=StringLength(statement[*num]);
	string line=SubString(statement[*num],n,m-1);

	if (IsPrintMessage(line)) {;}
	else {printf("%d\n",EvalExp(ParseExp(scanner)));}
	*num=*num+1;

}

static void InputCmd(scannerADT scanner,string *statement,int *num)
{
	*num=*num+1;
	SetIdentifierValue(ReadToken(scanner),GetInteger());
}

static void IfCmd(scannerADT scanner,string *statement,int *num)
{
	scannerADT scanner1,scanner2;
	expressionADT exp1,exp2;
	string string1,string2;
	string relation,then;

	string1=string2="";
	scanner1=NewScanner();
	scanner2=NewScanner();
	SetScannerSpaceOption(scanner1, IgnoreSpaces);
	SetScannerSpaceOption(scanner2, IgnoreSpaces);

	while(TRUE)
	{
		relation=ReadToken(scanner);
		if (IsRelation(relation)) {break;}
		string1=Concat(string1,relation);
	}
	SetScannerString(scanner1,string1);
	exp1=ParseExp(scanner1);

	while(TRUE)
	{
		then=ReadToken(scanner);
		if (StringEqual(then,"then")) {break;}
		string2=Concat(string2,then);
	}
	SetScannerString(scanner2,string2);
	exp2=ParseExp(scanner2);

	if (Satisfied(exp1,relation,exp2))
	{
		*num=EvalExp(ParseExp(scanner));
	}
	else 
	{
		*num=*num+1;
	}
}

static void ListCmd(scannerADT scanner,string *statement,int *num)
{
	int i;
	printf("\n");
	for (i=0;i<MaxStatementNum;i++)
	{
		if (statement[i]!=NULL)
		{
			printf("%s\n",statement[i]);
		}
	}
	printf("\n");
}

static void RunCmd(scannerADT scanner,string *statement,int *num)
{
	scannerADT scanner1=NewScanner();
	int *i=GetBlock(sizeof(int));

	*i=0;
	while (*i<MaxStatementNum)
	{
		if (statement[*i]==NULL)
		{
			*i=*i+1;
		}
		else
		{
			SetScannerString(scanner1,ConvertToLowerCase(statement[*i]));
			SetScannerSpaceOption(scanner1, IgnoreSpaces);
			ReadToken(scanner1);
			ExecuteCommand(scanner1,statement,i);
		}
	}
}

/*
	Extension Function: ClearCmd
	---------------------------------
	This function corresponds to the "Clear" command , which
	clears all statements stored in the statement[] array,
	so that a new program can be entered .It is not difficult to 
	implement this function,but this function is quite useful.
*/

static void ClearCmd(scannerADT scanner,string *statement,int *num)
{
	int i;
	for (i=0;i<MaxStatementNum;i++)
	{
		statement[i]=NULL;
	}
}

/*
	Function : IsRelation
	---------------------------------
	This function returns TRUE if its argument is a relational
	operator(">","=","<"). Otherwise ,it returns FALSE.
*/

bool IsRelation(string str)
{
	if (StringEqual(str,">") || StringEqual(str,"=") ||
		StringEqual(str,"<") )
	{
		return TRUE;
	}
	return FALSE;
}

/*
	Function : Satisfied
	------------------------------
	This function returns TRUE if the two expression of its 
	arguments satisfies the relational operator given by the 
	string argument.
*/

bool Satisfied(expressionADT exp1,string relation,expressionADT exp2)
{
	if (StringEqual(relation,">"))
	{
		return EvalExp(exp1)>EvalExp(exp2);
	}
	if (StringEqual(relation,"="))
	{
		return EvalExp(exp1)==EvalExp(exp2);
	}
	else
	{
		return EvalExp(exp1)<EvalExp(exp2);
	}
}

