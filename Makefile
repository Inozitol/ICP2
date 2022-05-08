run: ICP
	./ICP

ICP: src
	mkdir build -p; \
	cd build; \
	qmake ../src/ICP.pro; \
	make -j8;

doxygen:
	doxygen doxyconf

clean:
	rm -rf ICP build doc/*

pack: clean
	tar -czf 2-xhorac19-xmurga01.tar.gz doc src Makefile
