toycompiler: lexer.c parser.c ast.c symbolTable.c typeExtractor.c symanticAnalyzer.c driver.c 
	gcc -o toycompiler lexer.c parser.c ast.c  symbolTable.c  typeExtractor.c symanticAnalyzer.c codeGenerator.c driver.c -I.
