COMPILER = g++
FILESYSTEM_FILES = cache.cpp

build: $(FILESYSTEM_FILES)
	$(COMPILER) $(FILESYSTEM_FILES) -o gl -lGL -lGLU -lglut
	echo 'To execute ./gl'

clean:
	rm gl