CXX = g++

CXXFLAGS = -Wall -Werror -pedantic --std=c++11 -g

	
RubiksCube.exe: RubiksCube.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


.SUFFIXES:

.PHONY: clean
clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump
	
		# Copy files to CAEN Linux
sync :
	rsync \
  -rtv \
  --delete \
  --exclude '.git*' \
  --filter=':- .gitignore' \
  ./ \
  ksyasuda@login.engin.umich.edu:RubiksCube/
