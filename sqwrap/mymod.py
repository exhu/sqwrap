baseName = "mymod"

header = """#include <stdio.h>"""
	
classes = (
	{
	'native' : 'ui.MyCls',
	'name' : 'MyCls',
	'methods' : ('doit', ('int'))
	}
)

functions = (
	{
	'native' : 'printf',
	'name' : 'printf',
	'args' : ('string', 'varargs'),
	
	},
)

namespaces = {
	'global' : {'classes' : classes, 'functions' : None },
}
