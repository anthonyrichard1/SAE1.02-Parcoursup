all : doc

doc :
	doxygen
	mv html/* .
	rmdir html

clean :
	mkdir ../tmp
	mv Doxyfile Makefile ../tmp
	rm -r -f *
	mv ../tmp/Doxyfile ../tmp/Makefile .
	rmdir ../tmp
