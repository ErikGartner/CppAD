# ifndef CppADSubIncluded
# define CppADSubIncluded

/* -----------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-06 Bradley M. Bell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
------------------------------------------------------------------------ */

/*
-------------------------------------------------------------------------------
$begin Sub$$
$spell
	Var
	const
	Add
$$

$index binary, AD subtract operator$$
$index AD, binary subtract operator$$
$index operator, AD binary subtract$$
$index subtract, AD binary operator$$
$index -, AD binary operator$$

$section AD Binary Subtraction Operator$$

$table
$bold Syntax$$ 
$cnext 
$syntax% %z% = %x% - %y%$$
$tend

$fend 20$$

$head Purpose$$
Computes the difference of $italic x$$ minus $italic y$$ 
where one of the operands is a $syntax%AD<%Base%>%$$ object and
$code -$$ has the same interpretation as for the $italic Base$$ type.

$head x$$
The operand $italic x$$ has prototype
$syntax%
	const %Type% &%x%
%$$
where $italic Type$$ is $syntax%AD<%Base%>%$$, $italic Base$$, or $code int$$.

$head y$$
The operand $italic y$$ has prototype
$syntax%
	const %Type% &%y%
%$$
where $italic Type$$ is $syntax%AD<%Base%>%$$, $italic Base$$, or $code int$$.

$head z$$
The result $italic z$$ has type
$syntax%
	const AD<%Base%> %z%
%$$

$head Assumptions$$
If the $code -$$ operator is used with an 
$syntax%AD<%Base%>%$$ object,
it must be defined for the type $italic Base$$.
In addition,
if $latex f$$ and $latex g$$ are 
$xref/glossary/Base Function/Base functions/$$
$latex \[
	\D{[ f(x) - g(x) ]}{x} = \D{f(x)}{x} - \D{g(x)}{x}
\] $$

$head Example$$
$children%
	Example/Sub.cpp
%$$
The file
$xref/Sub.cpp/$$
contains an example and a test of these operations.
It returns true if it succeeds and false otherwise.

$end
-------------------------------------------------------------------------------
*/
//  BEGIN CppAD namespace
namespace CppAD {

template <class Base>
AD<Base> AD<Base>::operator -(const AD<Base> &right) const
{
	AD<Base> result;
	CppADUnknownError( Parameter(result) );

	result.value  = value - right.value;

	if( Variable(*this) )
	{	if( Variable(right) )
		{	// result = variable - variable
			Tape()->RecordOp(SubvvOp, 
				result, taddr, right.taddr
			);
		}
		else if( IdenticalZero(right.value) )
		{	// result = variable - 0
			result.MakeVariable(taddr);
		}
		else
		{	// result = variable - parameter
			Tape()->RecordOp(SubvpOp, 
				result, taddr, right.value
			);
		}
	}
	else if( Variable(right) )
	{	// result = parameter - variable
		Tape()->RecordOp(SubpvOp, 
			result, value, right.taddr
		);
	}

	return result;
}

// convert other cases to the case above
CppADFoldBinaryOperator(AD<Base>, -)


} // END CppAD namespace

# endif 
