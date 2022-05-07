ICP: src src/CMakeLists.txt
	cmake -Ssrc -Bbuild -DQt5_DIR="/usr/local/share/Qt-5.5/5.5/gcc_64/lib/cmake/Qt5";\
	cd build; make;\
	mv ICP ..; cd ..;\
	rm -rf build;

doxygen:
	doxygen doxyconf

clean:
	rm -rf ICP doc/*

pack: clean
	tar -czf 2-xhorac19-xmurga01.tar.gz doc src Makefile
