DEFAULT=a.out

a.out: simplewebserver.c Makefile
	cc -g3 simplewebserver.c 

clean:	
	-rm a.out
	-rm *.o *.core index.html

testclient:
	curl --http0.9  http://localhost:8989/index.html

test:	index.html a.out
	./a.out

index.html:
	echo "<html> " > index.html 
	echo "<body> " >> index.html 
	echo "<h1>Hello World</h1> " >> index.html 
	echo "This is a test file in the WWWROOT = . " >> index.html 
	echo "</body> " >> index.html 
	echo "</html> " >> index.html 

