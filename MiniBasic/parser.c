/*  
 *  Grammar:
 *
 *       E  ->  T + E
 *       E  ->  T - E
 *		 E  ->  T
 *
 *		 T  ->  F * T
 *		 T  ->  F / T
 *       T  ->  F
 *
 *       F  ->  integer
 *       F  ->  identifier
 *       F  ->  ( E )
 *
 */

#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "strlib.h"
#include "simpio.h"
#include "scanadt.h"
#include "parser.h"
#include "exp.h"



expressionADT ParseExp(scannerADT scanner)
{
    expressionADT exp;

    exp = ReadE(scanner);
    if (MoreTokensExist(scanner)) {
        Error("ParseExp: %s unexpected", ReadToken(scanner));
    }
    return (exp);
}



expressionADT ReadE(scannerADT scanner)
{
    expressionADT exp, rhs;
    string token;

    exp = ReadT(scanner);
	token = ReadToken(scanner);
	if ( IsPlusOrMinus(token) )
	{
        rhs = ReadE(scanner);
        exp = NewCompoundExp(token[0], exp, rhs);
    }
	else
	{
		SaveToken(scanner, token);
	}
    return (exp);
}


expressionADT ReadT(scannerADT scanner)
{
    expressionADT exp,rhs;
    string token;

    exp = ReadF(scanner);
	token = ReadToken(scanner);
	if ( IsTimesOrDivided(token) )
	{
        rhs = ReadT(scanner);
        exp = NewCompoundExp(token[0], exp, rhs);
    }
	else
	{
		SaveToken(scanner, token);
	}
    return (exp);
}

expressionADT ReadF(scannerADT scanner)
{
	expressionADT exp;
    string token;

	token = ReadToken(scanner);
    if (StringEqual(token, "(")) {
        exp = ReadE(scanner, 0);
        if (!StringEqual(ReadToken(scanner), ")")) {
            Error("Unbalanced parentheses");
        }
    } else if (isdigit(token[0])) {
        exp = NewIntegerExp(StringToInteger(token));
    } else if (isalpha(token[0])) {
        exp = NewIdentifierExp(token);
    } else {
        Error("Illegal term in expression");
    }
    return (exp);
}



static bool IsPlusOrMinus (string token)
{
	if ( StringEqual (token,"+") || StringEqual (token,"-") )
	{
		return TRUE;
	}
	return FALSE;
}

static bool IsTimesOrDivided (string token)
{
	if ( StringEqual (token,"*") || StringEqual (token,"/") )
	{
		return TRUE;
	}
	return FALSE;
}

