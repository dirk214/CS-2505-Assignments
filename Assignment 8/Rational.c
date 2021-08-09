#include <stdio.h>
#include <stdint.h>
#include "Rational.h"

Rational Rational_Construct(int32_t Numerator, int32_t Denominator)
{
	Rational R;
	R.Top = Numerator;
	R.Bottom = Denominator;
	return R;
}


Rational Rational_Negate(const Rational R)
{
	Rational N;
	N.Top = R.Top * -1;
	N.Bottom = R.Bottom;
	return N;
}

int32_t Rational_Floor(const Rational R)
{
	if (R.Top > 0)
	{
		return R.Top / R.Bottom;
	}
	else
	{
		if (R.Top % R.Bottom == 0)
		{
			return R.Top / R.Bottom;
		}
		else
		{
			int r = R.Top / R.Bottom;
			return (r - 1);
		}
	}
}

Rational Rational_Add(const Rational Left, const Rational Right)
{
	Rational total;
	total.Top = Left.Top * Right.Bottom + Left.Bottom * Right.Top;
	total.Bottom = Left.Bottom * Right.Bottom;
	return total;
}

Rational Rational_Multiply(const Rational Left, const Rational Right)
{
	Rational Product;
	Product.Top = Left.Top * Right.Top;
	Product.Bottom = Left.Bottom * Right.Bottom;
	return Product;
}

bool Rational_Equals(const Rational Left, const Rational Right)
{
	Rational nL;
	nL.Top = Left.Top;
	nL.Bottom = Left.Bottom;
	Rational nR;
	nR.Top = Right.Top;
	nR.Bottom = Right.Bottom;
	
	int sign = 1;
	if (nL.Top < 0) 
	{
		sign = -1;
		nL.Top = - nL.Top;
	}
	if (nL.Bottom < 0) 
	{
		sign = - sign;
		nL.Bottom = - nL.Bottom;
	} 
	nL.Top = sign * nL.Top;
	nL.Bottom = sign * nL.Bottom;
	
	int signr = 1;
	if (nR.Top < 0) 
	{
		signr = -1;
		nR.Top = - nR.Top;
	}
	if (nR.Bottom < 0) 
	{
		signr = - signr;
		nR.Bottom = - nR.Bottom;
	} 
	nR.Top = signr * nR.Top;
	nR.Bottom = signr * nR.Bottom;
	
	int ll = nL.Top * nR.Bottom;
	int rr = nR.Top * nL.Bottom;
	
	return (ll == rr);
}

bool Rational_LessThan(const Rational Left, const Rational Right)
{
	Rational nL;
	nL.Top = Left.Top;
	nL.Bottom = Left.Bottom;
	Rational nR;
	nR.Top = Right.Top;
	nR.Bottom = Right.Bottom;
	
	int sign = 1;
	if (nL.Top < 0) 
	{
		sign = -1;
		nL.Top = - nL.Top;
	}
	if (nL.Bottom < 0) 
	{
		sign = - sign;
		nL.Bottom = - nL.Bottom;
	} 
	nL.Top = sign * nL.Top;
	nL.Bottom = sign * nL.Bottom;
	
	int signr = 1;
	if (nR.Top < 0) 
	{
		signr = -1;
		nR.Top = - nR.Top;
	}
	if (nR.Bottom < 0) 
	{
		signr = - signr;
		nR.Bottom = - nR.Bottom;
	} 
	nR.Top = signr * nR.Top;
	nR.Bottom = signr * nR.Bottom;
	
	int ll = nL.Top * nR.Bottom;
	int rr = nR.Top * nL.Bottom;
	
	return (ll < rr);
}


//   On my honor:
//
//   - I have not discussed the C language code in my program with
//     anyone other than my instructor or the teaching assistants 
//     assigned to this course.
//
//   - I have not used C language code obtained from another student,
//     or any other unauthorized source, either modified or unmodified.  
//
//   - If any C language code or documentation used in my program 
//    was obtained from an allowed source, such as a text book or course
//    notes, that has been clearly noted with a proper citation in
//    the comments of my program.
//
//   <Andrew Herbert>
