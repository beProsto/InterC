# This file contains a specification of every command and option avaliable in the interc compiled language.
## Every command follows the same syntax; [COMMAND_NAME] [ARG0] [ARG1] [...] ;
## The ";" character at the end is the action seperator; it seperates the commands.

## The list of commands:
1) Memory management:
- `NEW`
	- Takes in 2 arguments
		- First argument is the name of the variable we want to create
		- Second argument is the type of the variable (for now only pointer are not supported)
			- Variable types:
				- `CHAR` - is an 8 bit signed integer
				- `UCHAR` - is an 8 bit unsigned integer
				- `SHORT` - is a 16 bit signed integer
				- `USHORT` - is a 16 bit unsigned integer
				- `INT` - is a 32 bit signed integer
				- `UINT` - is a 32 bit unsigned integer
				- `MAX` - is a maximal signed integer
				- `UMAX` - is a maximal unsigned integer
				- `PTR` - a pointer to any type
				- `P` - combine it with any of the other types - and you get a pointer to the specific type, for instance: `PINT` is a pointer to `INT`
- `DEL`
	- Takes in 1 argument
		- The argument specifies the name of the variable that should be deleted
1) Calculations:
- `SET`
	- Takes in 2 arguments
		- First argument specifies where the second argument's value will be stored
		- Second argument is the value
- `ADD`
	- Takes in 3 arguments
		- First argument specifies where the operation's returned value will be stored
		- Second argument is the first parameter of the addition 
		- Third argument is the second parameter of the addition 
- `SUB`
	- Takes in 3 arguments
		- First argument specifies where the operation's returned value will be stored
		- Second argument is the first parameter of the substraction 
		- Third argument is the second parameter of the substraction 
- `MUL`
	- Takes in 3 arguments
		- First argument specifies where the operation's returned value will be stored
		- Second argument is the first parameter of the multiplication 
		- Third argument is the second parameter of the multiplication 
- `DIV`
	- Takes in 3 arguments
		- First argument specifies where the operation's returned value will be stored
		- Second argument is the first parameter of the division 
		- Third argument is the second parameter of the division 
- `MOD`
	- Takes in 3 arguments
		- First argument specifies where the operation's returned value will be stored
		- Second argument is the first parameter of the modulo 
		- Third argument is the second parameter of the modulo 
3) Input/Output:
- `PRINT`
	- Takes in 1 or more arguments
		- The arguments specify values / variables that should be displayed

