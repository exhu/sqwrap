# supported wrapping types
# number_int/float = allow any number, but convert to int or float
sqtypes = ('int', 'float', 'string', 'instance', 'number_int', 
	'number_float', 'bool', 'varargs')

sqtypes_to_maskchar = {
	'int' : 'i',
	'float' : 'f',
	'number_int' : 'n',
	'number_float' : 'n',
	'string' : 's',
	'instance' : 'x',
	'bool' : 'b'
}

"""
	The types are expressed as follows: 'o' null, 'i' integer, 'f' float, 'n' integer or
	float, 's' string, 't' table, 'a' array, 'u' userdata, 'c' closure and nativeclosure, 'g' generat-
	or, 'p' userpointer, 'v' thread, 'x' instance(class instance), 'y' class, 'b' bool. and '.' any
	type. The symbol '|' can be used as 'or' to accept multiple types on the same paramet-
	er. There isn't any limit on the number of 'or' that can be used. Spaces are ignored so
	can be inserted between types to increase readbility. 
"""

def sqtypes_to_typemask_and_argscount(sqt):
	"""sqt = tuple of strings, see sqtypes global tuple for supported values"""	
	typemask = ""
	argscount = len(sqt)
	if 'varargs' in sqt:
		argscount = -(argscount-1)
	
	for i in sqt:
		typemask += sqtypes_to_maskchar[i]
		
	return typemask, argscount
	
# ---------


