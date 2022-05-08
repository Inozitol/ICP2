build: src
	mkdir build -p; \
	cd build; \
	qmake ../src/ICP.pro; \
	make -j8;

run: build
	./ICP

doxygen:
	doxygen doxyconf

clean:
	rm -rf ICP build doc/*

pack: clean
	tar -czf 1-xhorac19-xmurga01.tar.gz doc src Makefile doxyconf doxygen-awesome.css
