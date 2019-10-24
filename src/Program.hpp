#ifndef TPCPPM1S1_PROGRAM_H
#define TPCPPM1S1_PROGRAM_H

#include <istream>

class Program {
private:
	std::istream &_in;

public:
	explicit Program(std::istream &in);

	void exec() const;
};

#endif //TPCPPM1S1_PROGRAM_H
