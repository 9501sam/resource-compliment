rc: rc.cpp
	g++ -o rc rc.cpp

run: rc
	./rc

clean:
	$(RM) ./rc
